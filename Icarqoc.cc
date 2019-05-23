//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Icarqoc.h"

Define_Module(Icarqoc);


void Icarqoc::initialize(int stage) {
    BaseWaveApplLayer::initialize(stage);

    if (stage == 0) {

        //Initializing members and pointers of your application goes here
        EV << "Initializing " << par("appName").stringValue() << std::endl;
        this->seqMsg=0;
        this->tempNode=-1;


        if (FindModule<KnownGlobal*>::findGlobalModule())
        {
            oKnownGlobal = FindModule<KnownGlobal*>::findGlobalModule();

            //agent name = vehicle creation order
            std::stringstream aName;
            aName << oKnownGlobal->knownVehicles.size();
            this->oVision = new Vision(TraCIMobilityAccess().get(getParentModule()),
                    this->myId, aName.str(), this->oKnownGlobal, par("maxSpeed").doubleValue(), this);

            oKnownGlobal->knownVehicles.push_back(this->oVision->getMyData());

            //get configuration from physic layer module
            BasePhyLayer * x = FindModule<BasePhyLayer*>::findGlobalModule();
            oKnownGlobal->oRadiusEstimatorChannel->sensitivityPower_dbm = x->getAncestorPar("sensitivity").doubleValue();
        }

        //max velocity of vehicle in m/s
       // this->oVision->getMyData()->getMobilityInfo()->setMaxSpeed(par("maxSpeed").doubleValue());

        //declared radius in meters
        this->oVision->getMyData()->setSetRadius(par("radiusSet").doubleValue());

        // period of communication performance measurement
        perforMesurementPeriod = par("perforMesurementPeriod").doubleValue();
         //schedule first to measure communication performance
        cMessage *msgPer = new cMessage("commperform", MEASURE_COMM_PERFORMANCE);
        scheduleLoadApp(oKnownGlobal->startSimulation, MEASURE_COMM_PERFORMANCE, "firstLoad", msgPer);

        //schedule first load monitor message
        this->monitorMsg = new cMessage("firstLoad", SEND_MONITOR_EVT);
        this->loadPeriodMonitor = par("monitorPeriod").doubleValue();
        scheduleLoadApp(oKnownGlobal->startSimulation, SEND_MONITOR_EVT, "firstLoad", this->monitorMsg);

        // vehicle amount
        vehicleAmout = oKnownGlobal->vehicleAmout;

        // general type of application
        this->vfs = oKnownGlobal->oGeneralCommunicationService;

        // period to send application messages
        loadPeriodApp = oKnownGlobal->oGeneralCommunicationService.appPeriodLoadMsg;
        //schedule first load application messages
        cMessage *msg = new cMessage("firstLoad", SEND_ICM_EVT);
        scheduleLoadApp(oKnownGlobal->startSimulation, SEND_ICM_EVT, "firstLoad", msg );

        //initialize trace
        if (oKnownGlobal->simulationDataheaderLine)
             dataNetwork << ";vehicleAmout;loadPeriodApp;" <<  msgInfoTraceTransmitting(NULL, "", "", true);
        else dataNetwork << "";

    }
    else if (stage == 1) {
        //Initializing members that require initialized other modules goes here
    }


}

void Icarqoc::finish() {
        cout << endl << "id no final e " << this->getId()<< endl;
        this->oKnownGlobal->fileMessages << dataNetwork.str();
        this->oKnownGlobal->fileRemoteAgents << oVision->dataRemoteAgent.str();
        this->oKnownGlobal->fileLocalAgents << oVision->dataLocalAgent.str();
        this->oKnownGlobal->fileChannels << oVision->dataChannel.str();
        this->oKnownGlobal->fileChannelsMinslr << oVision->dataMinslr.str();
        this->oKnownGlobal->fileCommPerformance << oVision->dataCommPerformance.str();
}

void Icarqoc::onBSM(BasicSafetyMessage* bsm) {
    //Your application has received a beacon message from another car or RSU
    //code for handling the message goes here

}

void Icarqoc::onWSM(WaveShortMessage* wsm) {
    //Your application has received a data message from another car or RSU
    //code for handling the message goes here, see TraciDemo11p.cc for examples
    ICMessage * icm;
    if (icm = dynamic_cast<ICMessage*>(wsm)) onWSM(icm);

}

void Icarqoc::onWSM(ICMessage * wsm) {
    //Your application has received a data message from another car or RSU
    //code for handling the message goes here, see TraciDemo11p.cc for examples
    //double vtime;

    if (wsm->getSourceId()!=this->myId && wsm->getAntecessorId()!=this->myId)
    {
        this->oVision->updateVision(wsm);
        dataNetwork << ";" << this->oKnownGlobal->vehicleAmout << ";" << this->oKnownGlobal->loadPeriodApp << ";" <<  msgInfoTraceTransmitting(wsm, "receiving", "rcv" ,false);

        if (wsm->getNextId()==this->myId && wsm->getDestinationId() != this->myId
                && wsm->getHopNumber()<4)
        {
            this->sendForwardMessage(wsm);
            this->scheduleLoadApp(this->loadPeriodMonitor, SEND_MONITOR_EVT, "monitorMessage", this->monitorMsg);

        }
    }
}

void Icarqoc::onWSA(WaveServiceAdvertisment* wsa) {
    //Your application has received a service advertisement from another car or RSU
    //code for handling the message goes here, see TraciDemo11p.cc for examples
}

void Icarqoc::handleSelfMsg(cMessage* msg) {
    //BaseWaveApplLayer::handleSelfMsg(msg);
    //this method is for self messages (mostly timers)
    //it is important to call the BaseWaveApplLayer function for BSM and WSM transmission
    //SEND_ICM_EVT, // general event of IC Message
    //SEND/-*--_ICAR_PROTOCOL, //Data dissemination
    //SEND_FORMATION_VEHIC, // vehicular formation
    //SEND_IMAGES_STREAMS // images streams
    //MEASURE_COMM_PERFORMANCE // event to measure the environment communication performance
    //CHANNEL_MONITOR_MESSAGE = For each knowed CHANNEL when need to update communication state (communicatin, non-communicating, fault etc.)
    switch (msg->getKind()) {
    case MEASURE_COMM_PERFORMANCE:
    {
        // calc performance measurement
        if (msg->getName()=="firstLoad") this->oVision->calcCommPerformVision(true);
        else this->oVision->calcCommPerformVision(false);

        //schedule new performance measurement
        this->scheduleLoadApp(this->perforMesurementPeriod, MEASURE_COMM_PERFORMANCE, "commperform", msg);
    }break;

    case CHANNEL_MONITOR_MESSAGE:
    {
        Channel * c = (Channel *)(msg->getContextPointer());
        int64_t s = c->getAgentS()->getId();
        int64_t d = c->getAgentD()->getId();
        oVision->updateCommunicationState(s,d);
        //cout << endl << "CHANNEL_MONITOR_MESSAGE  source= " << s << "destination= " << d << endl;
    }break;

    case SEND_MONITOR_EVT:
    {
        //send monitor message
        loadApp(msg);
    }break;

    case SEND_ICM_EVT:
    {
        loadApp(msg);
        this->scheduleLoadApp(this->loadPeriodApp, SEND_ICM_EVT, "appMessage", msg);
    }break;


   default:
    {
        if (msg)
            DBG_APP << "APP: Error: Got Self Message of unknown kind! Name: " << msg->getName() << endl;
    }break;

    }
}


void Icarqoc::receptionMsg(ICMessage* msg){

}

/*****************************************************************************************************************************************************
 * APPLICATION LOAD IN NETWORK
 ****************************************************************************************************************************************************/

void Icarqoc::loadApp(cMessage *msg)
{
    int64_t destinyNode=-1;
    ForwardingNode * foward = new ForwardingNode();

    if (msg->getKind()!=SEND_MONITOR_EVT)
    {
        destinyNode = vfs.getDestination(this->oKnownGlobal->knownVehicles, this->myId);
        //std::cout << endl<< " destiny node" << destinyNode << std::endl;
        foward = oVision->getRouting()->getFowardNode(this->oVision->getAgentGroup(), this->oVision->getChannelList(), destinyNode,
                oVision->getMyData()->getId(), -1, vfs.timeToLive, Coord(0,0,0), Coord(0,0,0));
    }

    //std::cout << " teste routing" << foward->getRule() << std::endl;
    sendMessageApplication(foward, destinyNode, vfs.timeToLive, msg->getKind(), -1, -1);

    this->scheduleLoadApp(this->loadPeriodMonitor, SEND_MONITOR_EVT, "monitorMessage", this->monitorMsg);

}


/**
 * @brief Change the phy layer carrier sense threshold.
 *
 * @param ccaThreshold_dBm the cca threshold in dBm
 */
void Icarqoc::scheduleLoadApp(double appPeriod, int AppTypeId, char * name, cMessage *m1)
{
    if (m1->isScheduled())
        cancelEvent(m1);

    m1->setName(name);
    m1->setKind(AppTypeId);

    double calcDelay = calcDelaySendLoadApp();
    simtime_t s = simTime() + calcDelay + appPeriod;
    //std::cout << endl << "message name=" << m1->getName() << "  delay= " << calcDelay << "  periodo =" << appPeriod << "  time =" << s << endl;

    scheduleAt(s , m1);
}

/*****************************************************************************************************************************************************
 * END  -- APPLICATION LOAD IN NETWORK
 ****************************************************************************************************************************************************/




void Icarqoc::handlePositionUpdate(cObject* obj) {
    BaseWaveApplLayer::handlePositionUpdate(obj);
    //the vehicle has moved. Code that reacts to new positions goes here.
    //member variables such as currentPosition and currentSpeed are updated in the parent class
}

// ==========================================


/*
 * Calcing delay to send application load message
 */
double Icarqoc::calcDelaySendLoadApp()
{
    return ((double(rand()%10)+1)/1000);
}


/*
 *  @brief send application message
 *  @param forwarding node
 *  @param  destiny node
 *  @param  message time (time to leave)
 *  @param  message type (see enum in baseapp)
 *  @param  last node forwarding node
 *  @param  number of monitoring message)
 */

void Icarqoc::sendMessageApplication(ForwardingNode * fowardNode, int64_t destination, double timetoLive, unsigned int pMsgType, int64_t lastNodeNext,
        int64_t numMonitoringMsg)
{
        //preparing transmition wsm message
        ICMessage * wsm = new ICMessage();

        this->populateWSM(wsm);
        wsm->setKind(pMsgType);


        //prepareing icmessage
        wsm->setMsgType(pMsgType);
        wsm->setNumMsg(seqMsg++);
        wsm->setName("data");

        // data transmitter
        wsm->setAntecessoPosTimeStamp(this->oVision->getMyData()->getMobilityInfo()->getActualMove()->getStartTime());
        wsm->setAntecessorAngle(this->oVision->getMyData()->getMobilityInfo()->getAngle());
        wsm->setAntecessorAceleration(this->oVision->getMyData()->getMobilityInfo()->getAcceleration());
        wsm->setAntecessorMaxSpeed(this->oVision->getMyData()->getMobilityInfo()->getMaxSpeed());
        wsm->setAntecessorMsgTimeStamp(simTime());
        //wsm->setAntecessorRadius(this->oVision->getMyData()->getSetRadius());
        wsm->setAntecessorSpeed(this->oVision->getMyData()->getMobilityInfo()->getActualMove()->getSpeed());
        wsm->setAntecessorX(this->oVision->getMyData()->getMobilityInfo()->getActualMove()->getCurrentPosition().x);
        wsm->setAntecessorY(this->oVision->getMyData()->getMobilityInfo()->getActualMove()->getCurrentPosition().y);
        wsm->setAntecessorZ(this->oVision->getMyData()->getMobilityInfo()->getActualMove()->getCurrentPosition().z);

        // data source
        wsm->setSourceMaxSpeed(this->oVision->getMyData()->getMobilityInfo()->getMaxSpeed());
        wsm->setSourceAceleration(this->oVision->getMyData()->getMobilityInfo()->getAcceleration());
        wsm->setSourceAngle(this->oVision->getMyData()->getMobilityInfo()->getAngle());
        wsm->setSourceMsgTimeStamp(simTime());
        wsm->setSourcePosTimeStamp(this->oVision->getMyData()->getMobilityInfo()->getActualMove()->getStartTime());
        //wsm->setSourceRadius(this->oVision->getMyData()->getSetRadius());
        wsm->setSourceSpeed(this->oVision->getMyData()->getMobilityInfo()->getActualMove()->getSpeed());
        wsm->setSourceX(this->oVision->getMyData()->getMobilityInfo()->getActualMove()->getCurrentPosition().x);
        wsm->setSourceY(this->oVision->getMyData()->getMobilityInfo()->getActualMove()->getCurrentPosition().y);
        wsm->setSourceZ(this->oVision->getMyData()->getMobilityInfo()->getActualMove()->getCurrentPosition().z);
        wsm->setSourceId(this->oVision->getMyData()->getId());
        wsm->setAntecessorId(this->oVision->getMyData()->getId());

        // data destination
        wsm->setDestinationId(destination);
        RemoteAgent * ra = this->oVision->getAgentGroup()->getRemoteAgent(destination);
        if (ra!=NULL)
            if (ra->getId()!=-1){
                wsm->setDestinationMaxSpeed(ra->getMobilityInfo()->getMaxSpeed());
                wsm->setDestinationAngle(ra->getMobilityInfo()->getAngle());
                wsm->setDestinationAceleration(ra->getMobilityInfo()->getAcceleration());
                wsm->setDestinationPosTimeStamp(ra->getMobilityInfo()->getActualMove()->getStartTime());
                //wsm->setDestinationRadius(ra->getSetRadius());
                wsm->setDestinationSpeed(ra->getMobilityInfo()->getActualMove()->getSpeed());
                wsm->setDestinationX(ra->getMobilityInfo()->getActualMove()->getCurrentPosition().x);
                wsm->setDestinationY(ra->getMobilityInfo()->getActualMove()->getCurrentPosition().y);
                wsm->setDestinationZ(ra->getMobilityInfo()->getActualMove()->getCurrentPosition().z);
            }

        //wsm->setMsgLifeTime(timetoLive);
        wsm->setMsgLifeTime(simTime() + timetoLive);
        wsm->setWsmVersion(1);
        wsm->setTimestamp(simTime());
        wsm->setHopNumber(1);

         // next data
        std::string ruleRouting="";
        if (fowardNode!= NULL)
        {
            if (fowardNode->getFowardId() != -1)
            {
                wsm->setNextId(fowardNode->getFowardId());
                wsm->setValidityDataTimeStamp(fowardNode->getTimeoutValidity());
                wsm->setAnteNextValidityTimeStamp(fowardNode->getTimeoutValidity());
                ruleRouting = fowardNode->getRule();

                //std::cout << std::endl << ruleRouting << "  node forward - " << fowardNode->getFowardId() << "   local - " << this->myId << "   source- " << wsm->getSourceId() << "   destino- " << destination << endl;

                RemoteAgent * rm = this->oVision->getAgentGroup()->getRemoteAgent(fowardNode->getFowardId());

                if (rm != NULL){
                    //wsm->setNextRadius(this->oVision->getAgentGroup()->getRemoteAgent(fowardNode->getFowardId())->getSetRadius());
                    //std::cout << std::endl << "  aqui - ";
                    wsm->setNextSpeed(this->oVision->getAgentGroup()->getRemoteAgent(fowardNode->getFowardId())->getMobilityInfo()->getActualMove()->getSpeed());
                    wsm->setNextMaxSpeed(this->oVision->getAgentGroup()->getRemoteAgent(fowardNode->getFowardId())->getMobilityInfo()->getMaxSpeed());
                    wsm->setNextAceleration(this->oVision->getAgentGroup()->getRemoteAgent(fowardNode->getFowardId())->getMobilityInfo()->getAcceleration());
                    wsm->setNextAngle(this->oVision->getAgentGroup()->getRemoteAgent(fowardNode->getFowardId())->getMobilityInfo()->getAngle());
                    wsm->setNextPosTimeStamp(this->oVision->getAgentGroup()->getRemoteAgent(fowardNode->getFowardId())->getMobilityInfo()->getActualMove()->getStartTime());
                    wsm->setNextX(this->oVision->getAgentGroup()->getRemoteAgent(fowardNode->getFowardId())->getMobilityInfo()->getActualMove()->getCurrentPosition().x);
                    wsm->setNextY(this->oVision->getAgentGroup()->getRemoteAgent(fowardNode->getFowardId())->getMobilityInfo()->getActualMove()->getCurrentPosition().y);
                    wsm->setNextZ(this->oVision->getAgentGroup()->getRemoteAgent(fowardNode->getFowardId())->getMobilityInfo()->getActualMove()->getCurrentPosition().z);
                }
            } else{
                wsm->setNextId(-1);
                ruleRouting = "-1";
            }

        }
        else {
            wsm->setNextId(-1);
            wsm->setValidityDataTimeStamp(-1);
            wsm->setAnteNextValidityTimeStamp(-1);
            ruleRouting = "-1";
        }

        wsm->addByteLength(((string)wsm->getWsmData()).size());
        wsm->setWsmLength(((string)wsm->getWsmData()).size());

        sendICMessage(wsm, "transmitting", ruleRouting ,false);
}



void Icarqoc::sendForwardMessage(ICMessage* pWsm)
{
    //ICMessage * wsm = pWsm;
    //preparing transmition wsm message
    //if (fowardNode->getTimeoutValidity() < simTime() || pWsm->getValidityDataTime()==-1 || pWsm->getMsgLifeTime() < simTime())
   // if (pWsm->getMsgLifeTime() < simTime())
   //     dataNetwork << ";" << this->oKnownGlobal->vehicleAmout << ";" << this->oKnownGlobal->loadPeriodApp << ";" <<   msgInfoTraceTransmitting(pWsm, "NOTforwarding", "99" ,false);
   //  else
    {

         // vtime = simTime().dbl()-wsm->getValidityDataTime().dbl();
          //if (vtime < 0) vtime = -1;

          //oVision->getRouting()->setValidityTime(vtime);
          ForwardingNode * fowardNode =  oVision->getRouting()->getFowardNode(oVision->getAgentGroup(), oVision->getChannelList(),
                  pWsm->getDestinationId(), oVision->getMyData()->getId(), pWsm->getAntecessorId(), pWsm->getMsgLifeTime().dbl(), Coord(0,0,0), Coord(0,0,0));

            ICMessage * wsm = new ICMessage();

            this->populateWSM(wsm);
            wsm->setKind(pWsm->getKind());
            wsm->setName(pWsm->getName());
            wsm->setNumMsg(pWsm->getNumMsg());
            wsm->setAntecessoPosTimeStamp(this->oVision->getMyData()->getMobilityInfo()->getActualMove()->getStartTime());
            wsm->setAntecessorMaxSpeed(this->oVision->getMyData()->getMobilityInfo()->getMaxSpeed());
            wsm->setAntecessorMsgTimeStamp(simTime());

            //wsm->setAntecessorRadius(this->oVision->getMyData()->getSetRadius());
            wsm->setAntecessorSpeed(this->oVision->getMyData()->getMobilityInfo()->getActualMove()->getSpeed());
            wsm->setAntecessorAceleration(this->oVision->getMyData()->getMobilityInfo()->getAcceleration());
            wsm->setAntecessorAngle(this->oVision->getMyData()->getMobilityInfo()->getAngle());
            wsm->setAntecessorX(this->oVision->getMyData()->getMobilityInfo()->getActualMove()->getCurrentPosition().x);
            wsm->setAntecessorY(this->oVision->getMyData()->getMobilityInfo()->getActualMove()->getCurrentPosition().y);
            wsm->setAntecessorZ(this->oVision->getMyData()->getMobilityInfo()->getActualMove()->getCurrentPosition().z);
            wsm->setAntecessorId(this->oVision->getMyData()->getId());
            wsm->setHopNumber(pWsm->getHopNumber()+1);


            // forwarding data
            std::string ruleRouting="";
             if (fowardNode!= NULL)
             {
                 if (fowardNode->getFowardId() != -1)
                 {

                     wsm->setNextId(fowardNode->getFowardId());

                     if (fowardNode->getTimeoutValidity() < pWsm->getValidityDataTimeStamp() || pWsm->getValidityDataTimeStamp()==-1 )
                         wsm->setValidityDataTimeStamp(fowardNode->getTimeoutValidity());

                     wsm->setAnteNextValidityTimeStamp(fowardNode->getTimeoutValidity());
                     wsm->setNextId(fowardNode->getFowardId());

                     ruleRouting = fowardNode->getRule();
                     //wsm->setNextRadius(this->oVision->getAgentGroup()->getRemoteAgent(fowardNode->getFowardId())->getSetRadius());
                     wsm->setNextMaxSpeed(this->oVision->getAgentGroup()->getRemoteAgent(fowardNode->getFowardId())->getMobilityInfo()->getMaxSpeed());
                     wsm->setNextSpeed(this->oVision->getAgentGroup()->getRemoteAgent(fowardNode->getFowardId())->getMobilityInfo()->getActualMove()->getSpeed());
                     wsm->setNextAngle(this->oVision->getAgentGroup()->getRemoteAgent(fowardNode->getFowardId())->getMobilityInfo()->getAngle());
                     wsm->setNextAceleration(this->oVision->getAgentGroup()->getRemoteAgent(fowardNode->getFowardId())->getMobilityInfo()->getAcceleration());
                     wsm->setNextPosTimeStamp(this->oVision->getAgentGroup()->getRemoteAgent(fowardNode->getFowardId())->getMobilityInfo()->getActualMove()->getStartTime());
                     wsm->setNextX(this->oVision->getAgentGroup()->getRemoteAgent(fowardNode->getFowardId())->getMobilityInfo()->getActualMove()->getCurrentPosition().x);
                     wsm->setNextY(this->oVision->getAgentGroup()->getRemoteAgent(fowardNode->getFowardId())->getMobilityInfo()->getActualMove()->getCurrentPosition().y);
                     wsm->setNextZ(this->oVision->getAgentGroup()->getRemoteAgent(fowardNode->getFowardId())->getMobilityInfo()->getActualMove()->getCurrentPosition().z);
                 }else{
                     wsm->setNextId(-1); //melhorar esta condicional -- est repetitiva
                     wsm->setAnteNextValidityTimeStamp(-1);
                 }
             }else {
                 wsm->setNextId(-1); // melhorar esta condicional -- est repetitiva
                 wsm->setAnteNextValidityTimeStamp(-1);
                 ruleRouting = "-1";
             }



             // destination data
               RemoteAgent * rd = this->oVision->getAgentGroup()->getRemoteAgent(pWsm->getDestinationId());
               wsm->setDestinationId(pWsm->getDestinationId());

               if (rd!=NULL)
                   if (rd->getId()!=-1 && wsm->getDestinationPosTimeStamp() < rd->getMobilityInfo()->getActualMove()->getStartTime()) {
                       wsm->setDestinationMaxSpeed(rd->getMobilityInfo()->getMaxSpeed());
                       wsm->setDestinationPosTimeStamp(rd->getMobilityInfo()->getActualMove()->getStartTime());
                       wsm->setDestinationSpeed(rd->getMobilityInfo()->getActualMove()->getSpeed());
                       wsm->setDestinationAceleration(rd->getMobilityInfo()->getAcceleration());
                       wsm->setDestinationAngle(rd->getMobilityInfo()->getAngle());
                       wsm->setDestinationX(rd->getMobilityInfo()->getActualMove()->getCurrentPosition().x);
                       wsm->setDestinationY(rd->getMobilityInfo()->getActualMove()->getCurrentPosition().y);
                       wsm->setDestinationZ(rd->getMobilityInfo()->getActualMove()->getCurrentPosition().z);
                   }else{
                       wsm->setDestinationMaxSpeed(pWsm->getDestinationMaxSpeed());
                       wsm->setDestinationPosTimeStamp(pWsm->getDestinationPosTimeStamp());
                       wsm->setDestinationSpeed(pWsm->getDestinationSpeed());
                       wsm->setDestinationAceleration(pWsm->getDestinationAceleration());
                       wsm->setDestinationAngle(pWsm->getDestinationAngle());
                       wsm->setDestinationX(pWsm->getDestinationX());
                       wsm->setDestinationY(pWsm->getDestinationY());
                       wsm->setDestinationZ(pWsm->getDestinationZ());
                    }



               // source data
                 RemoteAgent * rs = this->oVision->getAgentGroup()->getRemoteAgent(pWsm->getSourceId());
                 wsm->setSourceId(pWsm->getSourceId());
                 if (rs!=NULL)
                     if (rs->getId()!=-1 && pWsm->getSourcePosTimeStamp() < rs->getMobilityInfo()->getActualMove()->getStartTime()) {
                         wsm->setSourceMaxSpeed(rs->getMobilityInfo()->getMaxSpeed());
                         wsm->setSourcePosTimeStamp(rs->getMobilityInfo()->getActualMove()->getStartTime());
                         wsm->setSourceSpeed(rs->getMobilityInfo()->getActualMove()->getSpeed());
                         wsm->setSourceAngle(rs->getMobilityInfo()->getAngle());
                         wsm->setSourceAceleration(rs->getMobilityInfo()->getAcceleration());
                         wsm->setSourceX(rs->getMobilityInfo()->getActualMove()->getCurrentPosition().x);
                         wsm->setSourceY(rs->getMobilityInfo()->getActualMove()->getCurrentPosition().y);
                         wsm->setSourceZ(rs->getMobilityInfo()->getActualMove()->getCurrentPosition().z);
                     }else{
                         wsm->setSourceMaxSpeed(pWsm->getSourceMaxSpeed());
                         wsm->setSourcePosTimeStamp(pWsm->getSourcePosTimeStamp());
                         wsm->setSourceSpeed(pWsm->getSourceSpeed());
                         wsm->setSourceAngle(pWsm->getSourceAngle());
                         wsm->setSourceAceleration(pWsm->getSourceAceleration());
                         wsm->setSourceX(pWsm->getSourceX());
                         wsm->setSourceY(pWsm->getSourceY());
                         wsm->setSourceZ(pWsm->getSourceZ());
                     }

                 //cout << ";AQUI" << this->oKnownGlobal->vehicleAmout << ";" << this->oKnownGlobal->loadPeriodApp << ";" <<   msgInfoTraceTransmitting(wsm, "forwarding", ruleRouting ,false);
                 sendICMessage(wsm, "forwarding", ruleRouting ,false);
        }
}

void Icarqoc::sendICMessage(ICMessage * wsm)
{
      sendDown(wsm);
}


void Icarqoc::sendICMessage(ICMessage * wsm, std::string evento, std::string ruleRoute, bool header)
{
    dataNetwork << ";" << this->oKnownGlobal->vehicleAmout << ";" << this->oKnownGlobal->loadPeriodApp << ";" << msgInfoTraceTransmitting(wsm, evento, ruleRoute ,header);
    sendICMessage(wsm);
}

void Icarqoc::receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj, cObject* details){
    BaseWaveApplLayer::receiveSignal(source, signalID, obj, details);
    Enter_Method_Silent();
    if (signalID == mobilityStateChangedSignal)
    {
       // std::cout << endl<< "name="<< this->oVision->getMyData()->getAgentName()
       //         << "   id="<< this->oVision->getMyData()->getId() << "  pos: " << this->oVision->getMyData()->getLocalMobility()->getCurrentPosition();
        this->oVision->changeLocalMobility();
    }
}

/*
 *
 */

std::string Icarqoc::msgInfoTraceTransmitting(ICMessage * wsm, std::string evento, std::string ruleRoute, bool header)
{
    std::ostringstream ost;
    if (header){
        ost      << "event"
                 << ";printTime"
                 << ";timestampMSG"
                 << ";local id"
                 << ";local name"
                 //<< oVision->getMyData()->infoTrace(header)
                 << ";messageNumber"
                 << ";Name"
                 << ";MsgType"
                 << ";MsgLifeTime"

                 << ";RuleRoute"
                 << ";ValidityRouteTime"
                 << ";hopNumber"
                // << ";SourceName"
                 << ";SourceId"
                // << ";AntecessorName"
                 << ";AntecessorId"
                 //<< ";NextName"
                 << ";NextId"
                // << ";DestinationName"
                 << ";DestinationId"

                 << ";AntecessorMsgTimeStamp"
                 << ";AntecessorPostime"
                 << ";AntecessorMaxSpeed"
                 //<< ";AntecessorRadius"
                 << ";AntecessorSpeed"
                 << ";AntecessorX"
                 << ";AntecessorY"
                 << ";AntecessorZ"
                 << ";AnteNextValidityTimeStamp"

                 << ";SourceMsgTimeStamp"
                 << ";SourcePosTimeStamp"
                 << ";SourceMaxSpeed"
                 << ";SourceRadius"
                 //<< ";SourceSpeed"
                 << ";SourceX"
                 << ";SourceY"
                 << ";SourceZ"

                 << ";NextPosTimeStamp"
                 << ";NextMaxSpeed"
                 //<< ";NextRadius"
                 << ";NextSpeed"
                 << ";NextX"
                 << ";NextY"
                 << ";NextZ"


                 << ";DestinationPosTimeStamp"
                 << ";DestinationMaxSpeed"
                 //<< ";DestinationRadius"
                 << ";DestinationSpeed"
                 << ";DestinationX"
                 << ";DestinationY"
                 << ";DestinationZ"


                 << ";Msgdata" << std::endl;
    } else {
        ost     <<  evento
                << ";" << simTime()
                << ";" << wsm->getTimestamp()
                << ";" << oVision->getMyData()->getId()
                << ";" << oVision->getMyData()->getAgentName()
                //<< oVision->getMyData()->infoTrace(header)
                << ";" << wsm->getNumMsg()
                << ";" << wsm->getName()
                << ";" << wsm->getMsgType()
                << ";" << wsm->getMsgLifeTime()

                << ";" << ruleRoute
                << ";"<< wsm->getValidityDataTimeStamp()
                << ";" << wsm->getHopNumber()
               // << ";" << wsm->getSourceName()
                << ";" << wsm->getSourceId()
               // << ";" << wsm->getAntecessorName()
                << ";" << wsm->getAntecessorId()
               // << ";" << wsm->getNextName()
                << ";" << wsm->getNextId()
               // << ";" << wsm->getDestinationName()
                << ";" << wsm->getDestinationId()

                << ";" << wsm->getAntecessorMsgTimeStamp()
                << ";" << wsm->getAntecessoPosTimeStamp()
                << ";" << wsm->getAntecessorMaxSpeed()

                << ";" << wsm->getAntecessorSpeed()
                << ";" << wsm->getAntecessorX()
                << ";" << wsm->getAntecessorY()
                << ";" << wsm->getAntecessorZ()
                << ";" << wsm->getAnteNextValidityTimeStamp()

                << ";" << wsm->getSourceMsgTimeStamp()
                << ";" << wsm->getSourcePosTimeStamp()
                << ";" << wsm->getSourceMaxSpeed()
                //<< ";" << wsm->getSourceRadius()
                << ";" << wsm->getSourceSpeed()
                << ";" << wsm->getSourceX()
                << ";" << wsm->getSourceY()
                << ";" << wsm->getSourceZ()

                << ";" << wsm->getNextPosTimeStamp()
                << ";" << wsm->getNextMaxSpeed()
               // << ";" << wsm->getNextRadius()
                << ";" << wsm->getNextSpeed()
                << ";" << wsm->getNextX()
                << ";" << wsm->getNextY()
                << ";" << wsm->getNextZ()

                << ";" << wsm->getDestinationPosTimeStamp()
                << ";" << wsm->getDestinationMaxSpeed()
                //<< ";" << wsm->getDestinationRadius()
                << ";" << wsm->getDestinationSpeed()
                << ";" << wsm->getDestinationX()
                << ";" << wsm->getDestinationY()
                << ";" << wsm->getDestinationZ()

                << ";" << wsm->getWsmData() << ";"
                << std::endl;
    }

             return ost.str();
}


