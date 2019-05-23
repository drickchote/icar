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

#include "Channel.h"

Channel::Channel(){
    // TODO Auto-generated constructor stub

}

Channel::~Channel() {
    // TODO Auto-generated destructor stub
    delete (this);
}


//creating channel
Channel::Channel(Agent* agentS, Agent* agentD, simtime_t msgReceivingTime, simtime_t msgSendingTime, RadiusEstimatorChannel * pRadiusEstimator, int neighbor, int event,
        simtime_t dataValidity, double pPeriodApp, double powerReceived_dbm )
{

 this->setAgentS(agentS);
 this->setAgentD(agentD);
 this->oPeriodApplication = pPeriodApp;
 this->penultTMsgSending = 0;
 this->lastTMsgSending = msgSendingTime;
 this->setNeighbors(neighbor);
 this->setLastTMsgReceiving(msgReceivingTime);
 this->setCurrentTMsgReceiving(msgReceivingTime);
 this->setMessageTTime((msgReceivingTime - msgSendingTime).dbl());
 this->channelMobility = new ChannelMobility(agentS->getMobilityInfo()->getActualMove(), agentD->getMobilityInfo()->getActualMove());
 this->setTxReceivedDBm(powerReceived_dbm);
 this->radiusEstimator = pRadiusEstimator;

 if (powerReceived_dbm<0){
     this->setCalcRadius();
 }else {
     this->calcRadius = 0;
     this->outOfRadiusRange =0;
 }

 this->setCommnunicationState(0);
 updateCommnunicationState(event);
 this->qoCChannel = new QoCChannel(this,dataValidity);
 //std::cout << endl << "testando "<< endl;
}


//canal criado quando l recebe uma mensagem de r
void Channel::updateChannel(simtime_t msgReceivingTime, simtime_t msgSendingTime, int neighbor,
        int event,  simtime_t dataValidity, double powerReceived_dbm)
{

 if (lastTMsgSending <= msgSendingTime)
 {
     this->penultTMsgSending = this->lastTMsgSending;
     this->lastTMsgSending = msgSendingTime;

    // if (neighbor == CommState::unKnowedNeighbor && event ==CommState::received){
    //     std::cout << "neighbor =="<< CommState::unKnowedNeighbor << " && event ==" << CommState::received;
    // } else this->setNeighbors(neighbor);

     this->setNeighbors(neighbor);

     this->channelMobility->updateChannelMobility(this->agent_s->getMobilityInfo()->getActualMove(),
             this->agent_d->getMobilityInfo()->getActualMove());

     this->setLastTMsgReceiving(getCurrentTMsgReceiving());
     this->setCurrentTMsgReceiving(msgReceivingTime);
     this->setMessageTTime((msgReceivingTime - msgSendingTime).dbl());
     this->setTxReceivedDBm(powerReceived_dbm);

     if (isNeighbors()|| this->getTxReceivedDBm()<0){
         this->setCalcRadius();
     }else {
         this->calcRadius = 0;
         this->outOfRadiusRange =0;
     }
     // atualizacao do estado da comunicao
     updateCommnunicationState(event);
     this->getQoCChannel()->getTimelinessChannel()->update(dataValidity);
  }
}


//update communication state
//indica se a distancia entre os agentes � menor que o alcance do agente de origem
void Channel::updateCommnunicationState(int event){
    int cstate = CommState::updateCommnunicationState(event, this->getCommnunicationState());
    if (cstate >= 0) this->setCommnunicationState(cstate);
    else this->setCommnunicationState(-1);
}

bool Channel::isInChannel(int id)
{
    if (id == this->getAgentS()->getId() || id == this->getAgentD()->getId())
        return true;
    else
        return false;
}


Agent* Channel::getAgentD() {
    return agent_d;
}

void Channel::setAgentD( Agent* agentD) {
    agent_d = agentD;
}

Agent* Channel::getAgentS() {
    return agent_s;
}

void Channel::setAgentS(Agent* agentS) {
    agent_s = agentS;
}

double Channel::getCalcRadius() {
    return calcRadius;
}

void Channel::setCalcRadius() {
    this->calcRadius = this->radiusEstimator->getSignalRange(this->txReceived_dBm,
            this->channelMobility->getDistancelr(this->agent_s->getMobilityInfo()->getActualMove(),
            this->agent_d->getMobilityInfo()->getActualMove()));

    this->setOutOfRadiusRangeState();

}

//void Channel::setCalcRadius(double calcRadius) {
//    this->calcRadius = calcRadius;
//}

ChannelMobility* Channel::getChannelMobility() {
    return channelMobility;
}

void Channel::setChannelMobility(ChannelMobility* channelMobility) {

    this->channelMobility = channelMobility;
}

int Channel::getCommnunicationState() {

    return commnunicationState;
}

void Channel::setCommnunicationState(int pcommnunicationState) {
    this->commnunicationState = pcommnunicationState;
}

simtime_t Channel::getCurrentTMsgReceiving() {
    return currentTMsgReceiving;
}

void Channel::setCurrentTMsgReceiving( simtime_t correntTMsgReceiving) {
    this->currentTMsgReceiving = correntTMsgReceiving;
}

simtime_t Channel::getLastTMsgReceiving() {
    return lastTMsgReceiving;
}

void Channel::setLastTMsgReceiving(simtime_t lastTMsgReceiving) {
    this->lastTMsgReceiving = lastTMsgReceiving;
}


double Channel::getMessageTTime(){
    return messageTTime;
}

void Channel::setMessageTTime(double messageTTime) {
    this->messageTTime = messageTTime;
}

bool Channel::isNeighbors(){
    if (neighbors==1) return true;
    else return false;
}

void Channel::setNeighbors(int neighbors) {
    this->neighbors = neighbors;
}

int Channel::getNeighbors() {
    return neighbors;
}

/*double Channel::calcSlr()
{

    //double x = this->calcRadius - this->channelMobility->getDistancelr();
    //std::cout << " O="
    //        << this->getAgentS()->getId() << "  - D= " << this->getAgentD()->getId() << "     radius= " << this->calcRadius << "  = distancelr "
    //        << this->channelMobility->getDistancelr() << std::endl;
    //std::cout << endl<< "slr=" << x << "= calcradius " << this->calcRadius << " - getDistancelr " << this->channelMobility->getDistancelr();
    return 0;
}

double Channel::getSlr() {
    return slr;
}

void Channel::setSlr(double slr) {
    this->slr = slr;
}
*/

std::string Channel::info() {
    std::ostringstream ost;
    ost << "  agente destino: " << this->agent_d->info()
        << "  agente origem : " << this->agent_s->info()
        << "  dados da mobie: " << this->channelMobility->info()
        << "  estado canal  : " << this->commnunicationState
        << "  ultimo ST Rec. MSG: " << this->currentTMsgReceiving
        << "  penultimo ST Rec.MSG:  " << this->lastTMsgReceiving
        << "  tempo viagem MSG  : " << this->messageTTime
        << "  vizinho : " << this->neighbors
        << "  QOC :: " <<  ((TimelinessChannel *) this->qoCChannel->getTimeliness())->info();

    return ost.str();
}

double Channel::getPeriodApplication() {
    return oPeriodApplication;
}

double Channel::getTxReceivedDBm() {
    return txReceived_dBm;
}

void Channel::setTxReceivedDBm(double txReceivedDBm) {
    txReceived_dBm = txReceivedDBm;
}

void Channel::setPeriodApplication(double periodApplication) {
    oPeriodApplication = periodApplication;
}

std::string Channel::infoTraceChannel(bool header) {
    std::ostringstream ost;
   /* ORIGINAL
    *
     if (header){
        ost     << ";agenteOrigemName"
                << ";agenteDestinoName"
                << ";agenteOrigemID"
                << ";agenteDestinoID"
                <<";vizinho"
                  ";estadoCanal"
                  ";ultimoSTRecMSG"
                  ";penultimoSTRecMSG"
                  ";tempoviagemMSG"
                << this->channelMobility->infoTrace(true)
                << ";receivedPowerDcb"
                << ";radiusCalc"
                //<< "; slr"
                << ((TimelinessChannel *) this->qoCChannel->getTimeliness())->infoTrace(true)
                << ";agent origem" << this->agent_s->infoTrace(true)
                << ";agent destino" << this->agent_d->infoTrace(true);

    } else {
        ost << ";" << this->agent_s->getAgentName()
            << ";" << this->agent_d->getAgentName()
            << ";" << this->agent_s->getId()
            << ";" << this->agent_d->getId()
            << ";" << this->neighbors
            << ";" << this->commnunicationState
            << ";" << this->currentTMsgReceiving
            << ";" << this->lastTMsgReceiving
            << ";" << this->messageTTime
            <<  this->channelMobility->infoTrace(false)
            << ";" << this->txReceived_dBm
            << ";" << this->calcRadius
            //<< ";" << this->slr
            <<  ((TimelinessChannel *) this->qoCChannel->getTimeliness())->infoTrace(false)
            << ";o" << this->agent_s->infoTrace(false)
            << ";d" << this->agent_d->infoTrace(false);
            //<< this->agent_s->infoTrace(false)
            //<< this->agent_d->infoTrace(false);

    }

*/
    if (header){
       ost     << ";agenteOrigemName"
               << ";agenteDestinoName"
               << ";agenteOrigemID"
               << ";agenteDestinoID"
               <<";vizinho"
                 ";estadoCanal"
                 ";ultimoSTRecMSG"
                 ";penultimoSTRecMSG"
                 ";tempoviagemMSG"
               << this->channelMobility->infoTrace(true)
               << ";receivedPowerDcb"
               << ";radiusCalc"
               << "; outOfRadiusRange"
               << ((TimelinessChannel *) this->qoCChannel->getTimeliness())->infoTrace(true)
               << ";agent origem" << this->agent_s->infoTrace(true)
               << ";agent destino" << this->agent_d->infoTrace(true);
      /* if (RemoteAgent * bsm = dynamic_cast<RemoteAgent *>(this->agent_s))
       {
           ost <<  ";o" << dynamic_cast<RemoteAgent*>(this->agent_s)->infoTrace(true);
       }else
       {
           ost <<  ";o" << dynamic_cast<LocalAgent*>(this->agent_s)->infoTrace(true);
       }

       if (RemoteAgent * bsm1 = dynamic_cast<RemoteAgent*>(this->agent_d))
       {
           ost <<  ";d" << dynamic_cast<RemoteAgent*>(this->agent_d)->infoTrace(true);
       }else
       {
           ost <<  ";d" << dynamic_cast<LocalAgent*>(this->agent_d)->infoTrace(true);
       }//*/

   } else {
       ost << ";" << this->agent_s->getAgentName()
           << ";" << this->agent_d->getAgentName()
           << ";" << this->agent_s->getId()
           << ";" << this->agent_d->getId()
           << ";" << this->neighbors
           << ";" << this->commnunicationState
           << ";" << this->currentTMsgReceiving
           << ";" << this->lastTMsgReceiving
           << ";" << this->messageTTime
           <<  this->channelMobility->infoTrace(false)
           << ";" << this->txReceived_dBm
           << ";" << this->calcRadius
           << ";" << this->outOfRadiusRange
           <<  ((TimelinessChannel *) this->qoCChannel->getTimeliness())->infoTrace(false)
           << ";o" << this->agent_s->infoTrace(false)
           << ";d" << this->agent_d->infoTrace(false);

   }
    return ost.str();
}

Agent* Channel::getAgentDs() {
    return agent_ds;
}

void Channel::setAgentDs(Agent* agentDs) {
    agent_ds = agentDs;
}

QoCChannel* Channel::getQoCChannel(){
    return qoCChannel;
}


void Channel::setQoCChannel(QoCChannel* qoCChannel) {
    this->qoCChannel = qoCChannel;
}

 cMessage * Channel::getChannelMessage() {
    return channelMessage;
}

double Channel::getOutOfRadiusRangeState() {
    return outOfRadiusRange;
}

void Channel::setOutOfRadiusRangeState() {
    this->outOfRadiusRange = this->channelMobility->getDistancelr(this->agent_s->getMobilityInfo()->getActualMove(),
            this->agent_d->getMobilityInfo()->getActualMove()) - this->calcRadius;
}

void Channel::setChannelMessage(cMessage* channelMessage) {
    this->channelMessage = channelMessage;
}
