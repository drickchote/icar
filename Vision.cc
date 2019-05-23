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

#include "Vision.h"

Vision::Vision() {
    // TODO Auto-generated constructor stub
}

Vision::~Vision() {
    // TODO Auto-generated destructor stub
    delete (this);
}

void Vision::callFinish(){

}


Vision::Vision(TraCIMobility *traci, int64_t id, std::string agentName, KnownGlobal * pKnownGlobal, double maxSpeed, Icarqoc * pIcar) {
    this->oKnownGlobal = pKnownGlobal;
    this->agentGroup = new RemoteAgentGroup();
    this->myData = new LocalAgent(id, new LocalMobility(traci, maxSpeed), agentName);
    this->channelList = new ChannelList();

    // temporally here -- should be here a service list
    this->routing = new Routing();

    this->oIcarModule = pIcar;

    this->dataLocalAgent << "";
    this->dataMinslr << "";
    if (this->oKnownGlobal->simulationDataheaderLine){
        // data trace
        this->dataLocalAgent << "timeStamp; localId; localName" << this->myData->infoTrace(true) << std::endl;
        // data minslr
        this->dataMinslr << "timeStamp; localId; localName" << this->myData->infoTrace(true) << std::endl;
    }
}

void Vision::updateVision(ICMessage* m) {

    //@brief update local agent communication data
    this->myData->getLocalCommInfo()->getLocalAgentCommPerformance()->addCorrectMsgRecievedMsg();

    //@brief update the list of agents and the group data (group data in construction yet)
    updateAgentGroup(m);

    //@brief update the channels list and the data channel
    updateChannels(m);
}

/*
 * @brief update the list of agents and the group data (group data in construction yet)
 */
void Vision::updateAgentGroup(ICMessage* m){
    // ver a atualizacao do ds (agente fonte dos dados) -- o ds � o agente de origem do canal mesmo?
    DeciderResult80211 *macRes = dynamic_cast<DeciderResult80211 *>(PhyToMacControlInfo::getDeciderResult(m));
    ASSERT(macRes);


    //updating message antecessor node
    if (m->getAntecessorId()!= m->getSourceId())
    {
        // updating message source node
        updateAgentGroup(m->getSourceId(), m->getSourcePosTimeStamp(),m->getSourceX(), m->getSourceY(), m->getSourceZ(), m->getSourceSpeed(),
                m->getSourceMaxSpeed(), 0, true, m->getSourceAceleration(), m->getAntecessorAngle());

        updateAgentGroup(m->getAntecessorId(), m->getAntecessorMsgTimeStamp(), m->getAntecessorX(), m->getAntecessorY(),
                m->getAntecessorZ(), m->getAntecessorSpeed(), m->getAntecessorMaxSpeed(),
                macRes->getRecvPower_dBm(), true, m->getAntecessorAceleration(), m->getAntecessorAngle());
    }else{
        // updating message source node
        updateAgentGroup(m->getSourceId(), m->getSourcePosTimeStamp(),m->getSourceX(), m->getSourceY(), m->getSourceZ(), m->getSourceSpeed(),
                m->getSourceMaxSpeed(), macRes->getRecvPower_dBm(), true, m->getSourceAceleration(), m->getAntecessorAngle());
    }


    //updating message next node
    if (m->getNextId()!= -1) //modificar .. colocar os dados do next no cabecalho da mensagem
        {
            //cout <<"1 - source - " << m->getSourceId() << "   destiny - " << m->getNextId() << "   destiny MSG  - " << m->getDestinationId() << std::endl;
            updateAgentGroup(m->getNextId(), m->getNextPosTimeStamp(),m->getNextX(), m->getNextY(), m->getNextZ(),
                    m->getNextSpeed(), m->getNextMaxSpeed(), 0, false, m->getNextAceleration(), m->getNextAngle());
        }


    //updating message destination node
    if (m->getNextId()!=m->getDestinationId())
    {
        updateAgentGroup(m->getDestinationId(), m->getDestinationPosTimeStamp(),m->getDestinationX(), m->getDestinationY(),
                m->getDestinationZ(), m->getDestinationSpeed(), m->getDestinationMaxSpeed(), macRes->getRecvPower_dBm(), false,
                m->getDestinationAceleration(), m->getDestinationAngle());
    }else{
        if (m->getDestinationPosTimeStamp() > m->getNextPosTimeStamp())
        {
            updateAgentGroup(m->getDestinationId(), m->getDestinationPosTimeStamp(),m->getDestinationX(), m->getDestinationY(), m->getDestinationZ(), m->getDestinationSpeed(),
                    m->getDestinationMaxSpeed(), macRes->getRecvPower_dBm(), false, m->getDestinationAceleration(), m->getDestinationAngle());
        }
    }
}

/*
 * @brief update the list of agents and the group data (group data in construction yet)
 */
void Vision::updateAgentGroup(int64_t id, simtime_t tsStart, double x, double y, double z, double speed,
        double maxSpeed, double setRadius, bool sourcerOrAntecessorMsg, float acceleration, float angle) {

    if (myData->getId()!= id ){

        RemoteAgent* a = this->agentGroup->getRemoteAgent(id);

        if (a == NULL)
        {
              //std::cout  << "AGENT NOT FIND = " << id << "  speed "<< speed << "  x="<< x << "  y="<< y <<std::endl;
              std::string  agentName = this->oKnownGlobal->getStringNamefromIdAgent(id);

              RemoteAgent* ai = new RemoteAgent(id, tsStart, x,  y, z, speed, maxSpeed, setRadius, agentName, acceleration, angle);

              this->agentGroup->knownRemoteAgents.push_back(ai);

              // informa que o agente transmissor e o de origem transmitiram uma mensagem corretamente.
              if (sourcerOrAntecessorMsg) ai->getRemoteAgentCommInfo()->getRemoteAgentCommPerformance()->addCorrectMsgTransmitted();

              //trace agent update
              //this->dataAgent << simTime() << " ;" << this->myData->getId() << ";" << this->myData->getAgentName() << ";" << a->infoTrace(false) << std::endl;
              //std::cout << "teste update agent  " << dataAgent.str() << std::endl;

             //cout << "  LOCAL: " << myData->getId() << " INSERT AGENT -> " << ai->info() << std::endl;
             // this->dataRemoteAgent << simTime() << " ;" << this->myData->getId() << ";" << this->myData->getAgentName() << a->infoTrace(false) << std::endl;

         } else
         {
             a->updateRemoteAgent(tsStart, x,  y, z, speed, maxSpeed, setRadius, acceleration, angle);
             // informa que o agente transmissor e o de origem transmitiram uma mensagem corretamente.
             if (sourcerOrAntecessorMsg) a->getRemoteAgentCommInfo()->getRemoteAgentCommPerformance()->addCorrectMsgTransmitted();

             //trace agent update
             this->dataRemoteAgent << simTime() << " ;" << this->myData->getId() << ";" << this->myData->getAgentName() << a->infoTrace(false) << std::endl;
             //cout << "  LOCAL: " << myData->getId() << " UPDATE AGENT -> " << a->info() << std::endl;
         }

    }
}


/*
 *  @brief update the channels list and the data channel
 *  @brief input message source, destiny, message receiving time, message sending time, target radius, neighborhood state
 */
void Vision::updateChannels(ICMessage* m)
{
    /*
     * @brief -- Define the channels, which pairs of agents can be a channel
     * channel of the antecessor and me
     */
    if (m->getAntecessorId()!=myData->getId())
    {
        DeciderResult80211 *macRes = dynamic_cast<DeciderResult80211 *>(PhyToMacControlInfo::getDeciderResult(m));
        ASSERT(macRes);
        double txReceived_dBm = macRes->getRecvPower_dBm();

        /*
         * channel from antecessor to local
         */
        //cout <<"2 - source - " << m->getAntecessorId() << "   destiny - " <<  myData->getId() << "   destiny MSG  - " << m->getDestinationId() << std::endl;
        updateChannel(m->getAntecessorId(), myData->getId(), simTime(), m->getAntecessorMsgTimeStamp(),
                CommState::neighbor, CommState::received, m, txReceived_dBm, -1);
        //cout <<"2 - source - " << m->getAntecessorId() << "   destiny - " <<  myData->getId() << "   destiny MSG  - " << m->getDestinationId() << std::endl;

        /*
         * channel from antecessor to next
         */
        if (m->getNextId()!= -1 && m->getNextId() != myData->getId())
        {
            updateChannel(m->getAntecessorId(), m->getNextId(), simTime(), m->getAntecessorMsgTimeStamp(),
                    CommState::neighbor, CommState::received, m, 0, m->getAnteNextValidityTimeStamp());
            //cout <<"3 - source - " << m->getAntecessorId() << "   destiny - " << m->getNextId() << "   destiny MSG  - " << m->getDestinationId() << std::endl;
        }

    // s->a e s -> n e s ->l
        //when antecessor is not equal to source node
        if (m->getAntecessorId()!= m->getSourceId())
        {
            /*
             * channel from source to local
             */
            //cout <<"4 - source - " << m->getSourceId() << "   destiny - " << myData->getId() << "   destiny MSG  - " << m->getDestinationId() << std::endl;
            updateChannel(m->getSourceId(), myData->getId(), simTime(), m->getSourceMsgTimeStamp(),
                    CommState::noNeighbor, CommState::received, m, 0, m->getValidityDataTimeStamp());

            /* ATTENTION REVIEWE HOPNUMBER
             * channel from source to antecessor
             */
            if (m->getHopNumber()<=2) // verify the hop number - optimistic vision
                //cout <<"5 - source - " << m->getSourceId() << "   destiny - " << m->getAntecessorId() << "   destiny MSG  - " << m->getDestinationId() << std::endl;
                updateChannel(m->getSourceId(), m->getAntecessorId(), simTime(), m->getSourceMsgTimeStamp(),
                        CommState::neighbor, CommState::received, m, 0, m->getValidityDataTimeStamp());
            else
                //cout <<"5 - source - " << m->getSourceId() << "   destiny - " << m->getAntecessorId() << "   destiny MSG  - " << m->getDestinationId() << std::endl;
                updateChannel(m->getSourceId(), m->getAntecessorId(), simTime(), m->getSourceMsgTimeStamp(),
                        CommState::noNeighbor, CommState::received, m, 0, m->getValidityDataTimeStamp());

            /*
             * channel from source to next
             */
            if (m->getNextId()!= -1){ // message without routing node
              //  cout <<"6 - source - " << m->getSourceId() << "   destiny  - " << m->getNextId() << "   destiny MSG  - " << m->getDestinationId() << std::endl;
                updateChannel(m->getSourceId(), m->getNextId(), simTime(), m->getSourceMsgTimeStamp(),
                        CommState::noNeighbor, CommState::received,  m, 0, m->getValidityDataTimeStamp());
            }
        }
    }
}


void Vision::updateCommunicationState(int64_t source, int64_t destination)
{
    Channel * c = channelList->getChannel(source, destination);

    if (c != NULL)
    {
        c->setCommnunicationState(CommState::noCommunicating);
        this->dataChannel << textDatachannel("updateCommunicationState", c, false) << std::endl;
    }
}
/*
 *  @brief update the channels list and the data channel
 *  @brief input message source, destiny, message receiving time, message sending time, target radius, neighborhood state
 */
void Vision::updateChannel(int64_t  source, int64_t destiny, simtime_t msgReceivingTime, simtime_t msgSendingTime,
       int neighbor, int event, ICMessage* m, double powerReceived_dbm, simtime_t  validtyTimeStamp)
{
    Agent* s;
    Agent *d;

    double msgLifeTime = (simTime() - m->getMsgLifeTime()).dbl();
    if (msgLifeTime < 0) msgLifeTime = -1;

    Channel * c = channelList->getChannel(source, destiny);
    if (c == NULL)
    {
        if (source!=destiny)
        {
            if (source != myData->getId()) s = this->agentGroup->getRemoteAgent(source); // os dados do agente local n�o est�o na lista de agentes remotos
            else s = myData;

            if (destiny != myData->getId()) d = this->agentGroup->getRemoteAgent(destiny);
            else  d = myData;

            if (s!=NULL && d!=NULL)
               if (s->getId()!=-1 && d->getId()!=-1)
                {
                      c = new Channel(s, d, msgReceivingTime, msgSendingTime,  this->oKnownGlobal->oRadiusEstimatorChannel, neighbor,
                              event, validtyTimeStamp, this->oKnownGlobal->loadPeriodApp, powerReceived_dbm);
                      this->channelList->channels.push_back(c);
                      if (this->channelList->channels.size() == 1)
                      {
                          this->dataChannel<< "";
                          if (this->oKnownGlobal->simulationDataheaderLine)
                              this->dataChannel << textDatachannel("event", c, true) << std::endl;
                      }

                      cMessage * m1 = new cMessage("channelMonitor", this->oIcarModule->CHANNEL_MONITOR_MESSAGE);

                      //m1->addObject(dynamic_cast<* cObject>(c));

                      this->oIcarModule->scheduleLoadApp(this->oIcarModule->loadPeriodMonitor, this->oIcarModule->CHANNEL_MONITOR_MESSAGE, "channelMonitor", m1);

                      c->setChannelMessage(m1);
                      m1->setContextPointer(c);

                      this->dataChannel << textDatachannel("including", c, false) << std::endl;

                      //cout << endl << "INCLUDING CHANNEL_MONITOR_MESSAGE" << endl;
                 }
        }
    }else
    {
       c->updateChannel(msgReceivingTime, msgSendingTime, neighbor, event, validtyTimeStamp, powerReceived_dbm);

       cMessage * m1;

       if (c->getChannelMessage()==NULL){
           cMessage * m1 = new cMessage("channelMonitor", this->oIcarModule->CHANNEL_MONITOR_MESSAGE);
           //m1->addObject(c);
           m1->setContextPointer(c);
           c->setChannelMessage(m1);
       }else
       {
           m1 = c->getChannelMessage();
       }

       this->oIcarModule->scheduleLoadApp(this->oIcarModule->loadPeriodMonitor,
               this->oIcarModule->CHANNEL_MONITOR_MESSAGE, "channelMonitor", m1);

       this->dataChannel << textDatachannel("update", c, false) << std::endl;
       //cout << endl << "UPDATING CHANNEL_MONITOR_MESSAGE" << endl;
    }
}


LocalAgent* Vision::getMyData() {
    return myData;
}

RemoteAgentGroup* Vision::getAgentGroup() {
    return agentGroup;
}

Routing* Vision::getRouting() {
    return routing;
}

GeneralCommunicationService Vision::getService() {
    return service;
}

ChannelList* Vision::getChannelList() {
    return channelList;
}

void Vision::updateChannels(Agent * agent, simtime_t timeStampData, std::string event){
    Channel *c=NULL;
    //double oldValidity=0;

    unsigned int index = 0;

        //std::cout << "buscar canal origem=" << sourceId << "   destino=" << destinationId << std::endl;
        while (this->getChannelList()->channels.size()> index)
        {
            //c = dynamic_cast<Channel*>(&channels[index]);
            c = dynamic_cast<Channel*>(this->getChannelList()->channels[index]);

            if (c->getAgentD()->getId() == agent->getId() || c->getAgentS()->getId()== agent->getId())
            {
                //oldValidity =c->getQoCChannel()->getTimeliness()->getValidityNow();

                // if the channel is not fault
                if(c->getCommnunicationState()!=CommState::faulty)
                        //&& c->getChannelMobility()->getMovementCurrentTime() <= timeStampData)
                {
                    //update distance between S and D
                    c->getChannelMobility()->updateChannelMobility(c->getAgentS()->getMobilityInfo()->getActualMove(),
                                               c->getAgentD()->getMobilityInfo()->getActualMove());

                    c->setOutOfRadiusRangeState();

                    if (c->isNeighbors()) c->getQoCChannel()->getTimelinessChannel()->update(-1);

                    //double currentValidityTime = c->getQoCChannel()->getTimelinessChannel()->getTimeoutValidity().dbl() - SimTime().dbl();
                   // double newValidityTime = c->getQoCChannel()->getTimelinessChannel()->calcValidity(-1);

                    //if (currentValidityTime>=0 && newValidityTime>=0 && newValidityTime < currentValidityTime)
                    //         c->getQoCChannel()->getTimelinessChannel()->update(-1);

                    //RETORNAR DEPOIS
                    //this->dataMinslr << ";"<< event << ";"<< this->oKnownGlobal->vehicleAmout << ";" << this->oKnownGlobal->loadPeriodApp << ";" << simTime() << ";" << this->myData->getId() << ";" << this->myData->getAgentName()
                    //        << ";"<< oldValidity  << c->infoTraceChannel(false) << ";"
                    //        << std::endl;

                    if (c->getCalcRadius() < c->getChannelMobility()->getDistancelr())
                        this->dataChannel << textDatachannel("OutOfRadius - TraceChangedMobility", c, false) << std::endl;
                    else
                        this->dataChannel << textDatachannel("updateTraceChangedMobility", c, false) << std::endl;
                }
            }
            ++index;
        }
    }

void Vision::changeLocalMobility(){
    if (!this->getMyData()->getLocalMobility()->getTraci()->isTerminated())
    {
        //update traci the data mobility of local agent
        this->getMyData()->getLocalMobility()->updateLocalMobilityPos();
        this->dataLocalAgent << simTime() << " ;" << this->myData->getId() << ";" << this->myData->getAgentName() << this->myData->infoTrace(false) << std::endl;

        //update the global matrix
        //this->calcTraceChangedMobility(this->getMyData()->getAgentName());

        //find the lowest channel distance for the radius range
        //double minSlr = this->getChannelList()->calcMinSlr(myData->getId());

        // the trajectory traversed by local agent L[distance(t)] - L[distance(t-1)]
        //double dist = this->myData->getMobilityInfo()->calcEuclideanDistanceAgentMoving();

        //std::cout << " minimo slr "<< minSlr << "   distância percorrida por l  " << dist << endl;
        //if ( minSlr!= -1)
        //{
           //ATENTION!!! se a trajetório percorrida é maior ou igual à menor diferença de raio (slr) atual
           //if (minSlr <= dist){
               //this->dataChannel << endl << " agent=" << this->myData->getAgentName() << "minSlr value=" << minSlr << "  distancia=" << dist << endl;
        this->updateChannels(this->myData,this->myData->getMobilityInfo()->getActualMove()->getStartTime(), "minSlr");
    }
       //}
   // }
}

void Vision::calcCommPerformVision(bool header){
    this->myData->getLocalCommInfo()->getLocalAgentCommPerformance()->calcRateRecievedMsgPperiod();
   // this->dataCommPerformance << this->myData->getLocalCommInfo()->infoTrace(false);

    if (header)
        this->dataCommPerformance << this->myData->getLocalCommInfo()->infoTrace(true);
        //<< this->myData->getLocalCommInfo()->infoTrace(false)
       // << this->agentGroup->calcRemoteAgentGroupCommPerform(header)<<std::endl;
    else
        this->dataCommPerformance << this->myData->getLocalCommInfo()->infoTrace(false)
                << this->agentGroup->calcRemoteAgentGroupCommPerform(header)<<std::endl;

}

//ESTE MÉTODO LIMITA O TEMPO DE SIMULAÇÃO - MEDI OS DADOS DE MOBILIDADE
void Vision::calcTraceChangedMobility(std::string agentName)
{
    //to convert string to int for update the matrix distance of idLocalNode
    int changedVehicle;
    std::stringstream converter;
    converter << agentName;
    converter >> changedVehicle;
    double calDistance;
    std::vector<Channel*> agentChannels;
    //verifica se o tamanho do vetor está de acordo com a quantidade de agentes existentes
    if (this->oKnownGlobal->knownVehicles.size() > changedVehicle)
    {
        LocalAgent * cv= this->oKnownGlobal->knownVehicles.at(changedVehicle);
        if (cv->getLocalMobility()->getTraci()!=NULL)
        {
            agentChannels = this->channelList->listChannelsWith(cv->getId());
            LocalAgent * la=NULL;

            this->oKnownGlobal->distMatrix[changedVehicle][changedVehicle] = 0;
            //std::cout << endl << "Matrix" << "[" << changedVehicle << "]" << " [" << changedVehicle << "] = " <<  this->oKnownGlobal->distMatrix[changedVehicle][changedVehicle];

            for (unsigned int i=0; i < this->oKnownGlobal->knownVehicles.size(); i++)
            {
                if (i!=changedVehicle)
                {
                   la= oKnownGlobal->knownVehicles.at(i);

                   if (la !=NULL)
                   {

                       /*
                        * AMBIENTE PARA TESTE
                       try
                       {
                           Move * moveLa = NULL;
                           Move * moveCv = NULL;
                           moveLa = la->getLocalMobility()->getMove();
                           moveCv = cv->getLocalMobility()->getMove();
                           LocalMobilityTraci * tracitestLa = la->getLocalMobility()->getTraci();
                           LocalMobilityTraci * tracitestCv = cv->getLocalMobility()->getTraci();

                          ERRO--- > moveLa->getCurrentPosition(); PERDA DE PONTEIRO
                       }catch (const std::runtime_error& r) {
                           cout << r.what() << '\n';
                       }
                       FIM AMBIENTE PARA TESTE

                       */

                       //ATENCAO
                       //por conta de erro de acesso a memoria foi utilizado getLocalMobility()->getMove(), já que foi atualizado pela última vez que foi sinalizada a movimentação.
                        Move * moveLa = NULL;
                        Move * moveCv = NULL;
                        moveLa = la->getLocalMobility()->getMove();
                        moveCv = cv->getLocalMobility()->getMove();
                        LocalMobilityTraci * tracitestLa = la->getLocalMobility()->getTraci();
                        LocalMobilityTraci * tracitestCv = cv->getLocalMobility()->getTraci();

                        if (tracitestLa!=NULL && tracitestCv!=NULL){
                            //std::cout << endl << "teste "<< moveLa->getCurrentPosition()<< endl;

                            calDistance = cv->getMobilityInfo()->calcEuclideanDistancelr(moveCv->getCurrentPosition(),
                                    moveLa->getCurrentPosition());

                            Channel * c = this->channelList->getChannel(cv->getId(), la->getId(), agentChannels);

                            if (c!=NULL)
                            {
                                // calculated distance is greater than the channels radius
                                if (this->oKnownGlobal->distMatrix[i][changedVehicle] < c->getCalcRadius() && calDistance >= c->getCalcRadius() && c->isNeighbors() && c->getCommnunicationState()!=CommState::faulty)
                                   {
        //                            double oldValidity = c->getQoCChannel()->getTimelinessChannel()->getValidity();
        //                            this->dataChannel << ";greaterThanRadius" << ";"<< this->oKnownGlobal->vehicleAmout << ";" << this->oKnownGlobal->loadPeriodApp << ";" << simTime() << ";" << this->myData->getId() << ";" << this->myData->getAgentName()
        //                                         << ";"<< oldValidity  << c->infoTraceChannel(false) << ";"                                        << std::endl;
        //                            this->dataChannel << textDatachannel("greaterThanRadius", c, false);
                                      this->dataChannel << textDatachannel("calculatedDistance>channelsRadius", c, false) << std::endl;

                                   }
                             }
                            this->oKnownGlobal->distMatrix[changedVehicle][i] = calDistance;
                            //std::cout << endl << "Matrix" << "[" << changedVehicle << "]" << " [" << i << "] = " <<  this->oKnownGlobal->distMatrix[changedVehicle][i];

                            c = this->channelList->getChannel(la->getId(), cv->getId(), agentChannels);

                            if (c!=NULL)
                            {
                                // calculated distance is greater than the channels radius
                                if (this->oKnownGlobal->distMatrix[i][changedVehicle] < c->getCalcRadius() && calDistance >= c->getCalcRadius() && c->isNeighbors() && c->getCommnunicationState()!=CommState::faulty)
                                   {

                                      this->dataChannel << textDatachannel("calculatedDistance>channelsRadius", c, false) << std::endl;
                                   }
                             }

                            this->oKnownGlobal->distMatrix[i][changedVehicle] = calDistance;
                            //std::cout << endl << "Matrix" << "[" << i << "]" << " [" << changedVehicle << "] = " <<  this->oKnownGlobal->distMatrix[i][changedVehicle];
                        }//END if (moveLa!=NULL)

                        }//END IF (la !=NULL)
                    }//END if(i!=changedVehicle)
                }//end for (unsigned int...)
              }
          }
  }


std::string Vision::textDatachannel(string event, Channel * c, bool header=false){
    std::ostringstream ost;
        if (header)
            ost << ";event;qtVeic;period;updateTime;" << "idLocal;name"<< c->infoTraceChannel(true);
        else
         ost << ";" << event
                 << ";"<< this->oKnownGlobal->vehicleAmout
                 << ";" << this->oKnownGlobal->loadPeriodApp
                 << ";" << simTime()
                 << ";" << this->myData->getId()
                 //<< ";" << this->myData->getAgentName()<< this->myData->getLocalCommInfo()->infoTrace(header)  << c->infoTraceChannel(header);
                 << ";" << this->myData->getAgentName() << c->infoTraceChannel(header);
     return ost.str();
}


