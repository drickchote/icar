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

#include "TimelinessChannel.h"

TimelinessChannel::TimelinessChannel(Channel *c, simtime_t dataValidity) {
    // TODO Auto-generated constructor stub
    this->c = c;
    update(dataValidity);
}


TimelinessChannel::~TimelinessChannel() {
    // TODO Auto-generated destructor stub
    delete(this);
}



/*double TimelinessChannel::calcValidity(double dataValidity){
    double validity=0;
    double maxRelativeSpeed;
    double vslr;
    Coord s, d;

     if (c->isNeighbors()) // && (s.x!=0.0 && s.y!=0.0 && d.x!=0.0 && d.y!=0.0)
    {
        s = c->getAgentS()->getMobilityInfo()->getMove()->getCurrentPosition();
        d = c->getAgentD()->getMobilityInfo()->getMove()->getCurrentPosition();

        vslr = fabs(c->getCalcRadius() - this->c->getChannelMobility()->getDistancelr(c->getAgentS()->getMobilityInfo()->getMove(), c->getAgentD()->getMobilityInfo()->getMove()));
        this->setSlr(vslr);
        maxRelativeSpeed = c->getAgentS()->getMobilityInfo()->getMaxSpeed() + c->getAgentD()->getMobilityInfo()->getMaxSpeed();

        this->validityNeighbor = vslr/maxRelativeSpeed;

       //std::ostringstream ost;
        //ost << "  slr: " << slr
        //     << "  STL - " << dlr << maxRelativeSpeed;
        //DBG << std::endl << ost <<  std::endl;

    }else
    {
         // value from the message - when is not neighbor

        if (validity != -1){
            this->setSlr(0);
           this->validityNeighbor = dataValidity;
        }
        //std::cout << " validity msg = " << dataValidity << endl;

    }

     if (c->getPeriodApplication()>0 && this->validityNeighbor > c->getPeriodApplication())
         this->validity = c->getPeriodApplication();
     else this->validity = this->validityNeighbor;

    return validity;

}*/

double TimelinessChannel::calcValidity(simtime_t dataValidity){
    double vslr, vslr250;
    Coord s, d;
    simtime_t pTime = simTime();
    this->timeStampUpdate =  pTime;

     if (c->isNeighbors() && c->getCommnunicationState()!=CommState::noCommunicating
             && c->getCommnunicationState()!=CommState::faulty
             && c->getTxReceivedDBm()<0)
    {
        s = c->getAgentS()->getMobilityInfo()->getActualMove()->getCurrentPosition();
        d = c->getAgentD()->getMobilityInfo()->getActualMove()->getCurrentPosition();

        this->distancialr = this->c->getChannelMobility()->calcEuclideanDistancelr(s,d);
        vslr = fabs(c->getCalcRadius() - this->distancialr);
        this->setSlr(vslr);

        //baseado na velocidade relativa na última posição coletada dos agentes
        this->relativeSpeed = this->c->getChannelMobility()->calRelativeSpeed(c->getAgentD()->getMobilityInfo()->getActualMove()->getSpeed(),
                c->getAgentS()->getMobilityInfo()->getActualMove()->getSpeed());
        //normalize relative speed.
        if (relativeSpeed<1) relativeSpeed = 1;

        this->validity = vslr/relativeSpeed;

        //baseado na velocidade média na última posição coletada do agente destino da mensagem
        this->validityVm = (2*slr)/(c->getAgentD()->getMobilityInfo()->getActualMove()->getSpeed()
                + c->getAgentD()->getMobilityInfo()->getLastMove()->getSpeed());

        timeoutValidity = pTime + this->validity;
        this->timeoutvalidityVm = timeStampUpdate + validityVm;

        // calculo conservador
        maxRelativeSpeed = c->getAgentS()->getMobilityInfo()->getMaxSpeed() + c->getAgentD()->getMobilityInfo()->getMaxSpeed();
        vslr250 = fabs(250 - distancialr);
        this->slr250=vslr250;
        this->validityNeighborConserv250 = vslr250/maxRelativeSpeed;
        this->timeoutvalidityNeighborConserv250 = pTime + validityNeighborConserv250;

        // cálculo próxima posição dos agentes
        sNext = c->getAgentS()->getMobilityInfo()->getPositionAtTime(pTime);
        dNext = c->getAgentD()->getMobilityInfo()->getPositionAtTime(pTime);
        this->distanciaNextlr = this->c->getChannelMobility()->calcEuclideanDistancelr(s,d);
        vslrNext = fabs(c->getCalcRadius() - this->distanciaNextlr);

        // baseado na velocidade relativa na próxima posição dos agentes
        this->validityNext = vslrNext/relativeSpeed;
        this->timeoutValidityNext = pTime + validityNext;


        //baseado na velocidade média na próxima posição do agente destino
        double vNextD= c->getAgentD()->getMobilityInfo()->getActualMove()->getSpeed()
                        + c->getAgentD()->getMobilityInfo()->getAcceleration()
                        *(pTime.dbl()- c->getAgentD()->getMobilityInfo()->getActualMove()->getStartTime().dbl());

        this->validityVmNext = (2*vslrNext)/(c->getAgentD()->getMobilityInfo()->getActualMove()->getSpeed()
                + vNextD);

        this->timeoutvalidityVmNext = pTime +  this->validityVmNext;

        slrConservadorNext = fabs(250 - this->distanciaNextlr );
        validityConservadorNext = slrConservadorNext/maxRelativeSpeed;
        timeOutvalidityConservNext = pTime + validityConservadorNext;

    }else
    {
        /*
         * value is from message - when is not neighbor
         */
            distancialr = this->c->getChannelMobility()->calcEuclideanDistancelr(s,d);
            setSlr(0);
            relativeSpeed = 0;
            validityVm = 0;
            timeoutValidity = 0;
            timeoutvalidityVm = 0;
            maxRelativeSpeed = 0;
            slr250=0;
            validityNeighborConserv250 = 0;
            timeoutvalidityNeighborConserv250 = 0;
            sNext = Coord(0, 0,0);
            dNext = Coord(0, 0,0);
            distanciaNextlr = 0;
            vslrNext = 0;
            validityNext = 0;
            timeoutValidityNext = 0;
            validityVmNext = 0;
            timeoutvalidityVmNext = 0;
            slrConservadorNext = 0;
            validityConservadorNext = 0;
            timeOutvalidityConservNext = 0;

            this->validity = (dataValidity - pTime).dbl();
            if (this->validity > 0)
            {
                this->timeoutValidity= dataValidity;
                //cout << endl << "validity= "<< this->validity << endl;

            }else{
                this->validity = 0;
                this->timeoutValidity  = pTime;
                //cout << endl << "else validity= "<< this->validity << endl;
            }

            //cout << endl << "validity= "<< this->validity << "   datavalidity= " << dataValidity <<endl;
    }

    return validity;

}


void TimelinessChannel::update(simtime_t dataValidity){
    this->calcValidity(dataValidity);
    this->calcTimeoutValidity();
    //this->calcAge();

}

void TimelinessChannel::calcTimeoutValidity()
{
    if (this->getValidity() > 0)  this->timeoutValidity = this->timeStampUpdate + this->getValidity() + c->getMessageTTime();
    else  this->timeoutValidity = 0;
    //else  this->timeoutValidity = this->timeStampUpdate + c->getMessageTTime();
}

double TimelinessChannel::calcAge()
{
    //this->age = (simTime() - c->getCurrentTMsgReceiving()).dbl();
    this->age = (simTime() - c->getMessageTTime()).dbl();
    return this->age;
}

std::string TimelinessChannel::info(){
    std::ostringstream ost;
    ost << "  TIMELINESS: "
        << "  VALIDITY - " << this->validity
        << "  AGE - " << this->calcAge();
    return ost.str();

}
std::string TimelinessChannel::infoTrace(bool header){

    std::ostringstream ost;
    if (header)
       ost <<  ";age;ageNow"
               ";timeStampUpdate"
               ";distancialr"
               ";maxRelativeSpeed"
               ";slrConservador250"
               ";validityConservador"
               "; timeoutValidityConservador"
               "; relativeSpeed"
               ";slr"
               ";validity"
               "; timeOutValidity"
               ";validityVm"
               ";TimeoutvalidityVm"
               "; distanciaNextlr"
               ";slrNext"
               ";validityNext"
               "; timeoutValidityNext"
               "; validityVmNext"
               ";timeoutvalidityVmNext"
               ";slrConservadorNext"
               ";validityConservadorNext"
               ";timeOutvalidityConservNext"
               ";sNext.x"
               "; sNext.y"
               "; sNext.z"
               ";dNext.x"
               "; dNext.y"
               "; dNext.z";
    else
        ost  << ";"<< this->age << ";" << this->calcAge()
        <<";"<<this->timeStampUpdate
        << ";"<< distancialr
        <<";" << maxRelativeSpeed
        << ";" << this->slr250
        <<";" << validityNeighborConserv250
        << ";" << this->timeoutvalidityNeighborConserv250 //simtime_t (this->timeStampUpdate.dbl() + validityNeighborConserv250)
        << ";" << relativeSpeed
        << ";" << this->slr
        <<";" << validity
        << ";" << timeoutValidity //simtime_t (this->timeStampUpdate.dbl() + validityNeighborConserv)
        << ";" << this->validityVm
        << ";" << this->timeoutvalidityVm
        << ";" << this->distanciaNextlr
        << ";" << this->vslrNext
        <<";" << validityNext
        << ";" << timeoutValidityNext
        << ";" << this->validityVmNext
        << ";" << this->timeoutvalidityVmNext
        << ";" << this->slrConservadorNext
        << ";" << this->validityConservadorNext
        << ";" << this->timeOutvalidityConservNext
        << ";" << this->sNext.x
        << ";" << this->sNext.y
        << ";" << this->sNext.z
        << ";" << this->dNext.x
        << ";" << this->dNext.y
        << ";" << this->dNext.z;

    return ost.str();
}

TimelinessChannel::TimelinessChannel() {
}

/*double TimelinessChannel::getDlr(){
    return dlr;
}

void TimelinessChannel::setDlr(double dlr) {
    this->dlr = dlr;
}
*/
double TimelinessChannel::getSlr() {
    return this->slr;
}

void TimelinessChannel::setSlr(double slr) {
    this->slr = slr;
}

double TimelinessChannel::getAgeCommState(){
    return ageCommState;
}

void TimelinessChannel::setAgeCommState(double ageCommState) {
    this->ageCommState = ageCommState;
}

double TimelinessChannel::getAgeMobilityCondition(){
    return ageMobilityCondition;
}

void TimelinessChannel::setAgeMobilityCondition(double ageMobilityCondition) {
    this->ageMobilityCondition = ageMobilityCondition;
}

double TimelinessChannel::getAgeNeighberCondition(){
    return ageNeighberCondition;
}

void TimelinessChannel::setAgeNeighberCondition(double ageNeighberCondition) {
    this->ageNeighberCondition = ageNeighberCondition;
}

simtime_t TimelinessChannel::getTimeoutValidityCommState(){
    return timeoutValidityCommState;
}

void TimelinessChannel::setTimeoutValidityCommState(
        simtime_t timeoutValidityCommState) {
    this->timeoutValidityCommState = timeoutValidityCommState;
}

simtime_t TimelinessChannel::getTimeoutValidityMobilityCondition() {
    return timeoutValidityMobilityCondition;
}

void TimelinessChannel::setTimeoutValidityMobilityCondition(
        simtime_t timeoutValidityMobilityCondition) {
    this->timeoutValidityMobilityCondition = timeoutValidityMobilityCondition;
}

simtime_t TimelinessChannel::getTimeoutValidityNeighberCondition(){
    return timeoutValidityNeighberCondition;
}

void TimelinessChannel::setTimeoutValidityNeighberCondition(
        simtime_t timeoutValidityNeighberCondition) {
    this->timeoutValidityNeighberCondition = timeoutValidityNeighberCondition;
}

simtime_t TimelinessChannel::getTimeStampUpdateCommState(){
    return timeStampUpdateCommState;
}

void TimelinessChannel::setTimeStampUpdateCommState(
        simtime_t timeStampUpdateCommState) {
    this->timeStampUpdateCommState = timeStampUpdateCommState;
}

simtime_t TimelinessChannel::getTimeStampUpdateMobilityCondition() {
    return timeStampUpdateMobilityCondition;
}

void TimelinessChannel::setTimeStampUpdateMobilityCondition(
        simtime_t timeStampUpdateMobilityCondition) {
    this->timeStampUpdateMobilityCondition = timeStampUpdateMobilityCondition;
}

simtime_t TimelinessChannel::getTimeStampUpdateNeighberCondition(){
    return timeStampUpdateNeighberCondition;
}

void TimelinessChannel::setTimeStampUpdateNeighberCondition(
        simtime_t timeStampUpdateNeighberCondition) {
    this->timeStampUpdateNeighberCondition = timeStampUpdateNeighberCondition;
}

double TimelinessChannel::getValidityCommState(){
    return validityCommState;
}

void TimelinessChannel::setValidityCommState(double validityCommState) {
    this->validityCommState = validityCommState;
}

double TimelinessChannel::getValidityMobilityCondition(){
    return validityMobilityCondition;
}

void TimelinessChannel::setValidityMobilityCondition(
        double validityMobilityCondition) {
    this->validityMobilityCondition = validityMobilityCondition;
}

double TimelinessChannel::getValidityNeighberCondition() {
    return validityNeighberCondition;
}

void TimelinessChannel::setValidityNeighberCondition(double validityNeighberCondition) {
    this->validityNeighberCondition = validityNeighberCondition;
}

double TimelinessChannel::setDigits(double _number, int _digits)
{
    double tenth = pow((double)10,_digits);
    _number *= tenth;
    _number = floor(_number);
    _number /= tenth;

    return _number;
}
