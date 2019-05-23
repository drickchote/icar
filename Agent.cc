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

#include "Agent.h"

Agent::Agent(int64_t id, std::string name){
    setId(id);
    setAgentName(name);
}

Agent::Agent(){
    this->id = -1;
}

int64_t Agent::getId() {
    return id;
}

void Agent::setId(int64_t  id) {
    this->id = id;
}

std::string Agent::info() {
    std::ostringstream ost;
    ost << "  Agent ID: " << this->id;
    return ost.str();
}


std::string Agent::infoTrace(bool header=false) {
    std::ostringstream ost;

    if (this->getMobilityInfo()!=NULL){
    if (header)
        ost << ";AgentID;agentName" << this->getMobilityInfo()->infoTrace(header) ;
    else
        ost <<";" << this->id<< ";" << this->agentName << this->getMobilityInfo()->infoTrace(header);
    }
    return ost.str();
}

Agent::~Agent() {
    delete(this);
}

MobilityInfo* Agent::getMobilityInfo() {
    return mobilityInfo;
}

double Agent::getSetRadius(){
    return setRadius;
}

std::string Agent::getAgentName(){
    return agentName;
}

CommInfo* Agent::getCommInfo() {
    return commInfo;
}

void Agent::setCommInfo(CommInfo* commInfo) {
    this->commInfo = commInfo;
}

void Agent::setAgentName(std::string agentName) {
    this->agentName = agentName;
}

void Agent::setSetRadius(double setRadius) {
    this->setRadius = setRadius;
}

void Agent::setMobilityInfo(MobilityInfo *mobilityInfo) {
    this->mobilityInfo = mobilityInfo;
}
/*
 *
 * LAddress::L3Type Agent::getNetworkAdress() const {
    return networkAdress;
}

void Agent::set const Coord& Agent::getCoord() const {
    return coord;
}

void Agent::setCoord(const Coord& coord) {
    this->coord = coord;

}NetworkAdress(LAddress::L3Type networkAdress) {
    this->networkAdress = networkAdress;
}

 * double Agent::getSpeed() const {
    return speed;
}

void Agent::setSpeed(double speed) {
    this->speed = speed;
}

void Agent::setNewAgent(int ag,Coord& co, simtime_t tSource, simtime_t tsLocal, double speed,  LAddress::L3Type agnetAdress,
        double distanceRadiusCommA, double distanceRadiusCommB, double vmr, double distanceab, double periodSensorMoving) {
    this->setId(ag);
   // this->commInfo = new CommInfo(tsLocal, tSource, radius);
    this->commInfo = new CommInfo();
    this->mobilityInfo = new MobilityInfo();
    updateAgent(co, tSource, tsLocal, speed, agnetAdress, distanceRadiusCommA, distanceRadiusCommB, vmr, distanceab, periodSensorMoving);
    this->mobilityInfo->setSpeed(speed);
    this->mobilityInfo->setStart(co, tSource);
    this->setNetworkAdress(agnetAdress);
    this->setTimeSourceArrivedLocal(tsLocal);
    this->setTimeSourceKnowed(tSource);

}

const CommInfo* Agent::getCommInfo() const {
    return commInfo;
}

void Agent::setCommInfo(CommInfo* commInfo) {
    this->commInfo = commInfo;
}

MobilityInfo* Agent::getMobilityInfo(){
    return this->mobilityInfo;
}

void Agent::setMobilityInfo(MobilityInfo* movement) {
    this->mobilityInfo = movement;
}



std::string Agent::info(){
    std::string reg = " em manutencao ainda \n"; //this->id + ";" + commInfo->recordComm() + ";" + mobilityInfo->record();
    return reg;
}

void Agent::updateCommInfo(double tSource)
{
void Agent::updateAgent(Coord& co, simtime_t tSource, simtime_t tsLocal, double speed,  LAddress::L3Type agnetAdress,
        double distanceRadiusCommB, double distanceRadiusCommA,  double speedRelative, double distanceab, double periodSensorMoving)
{
    this->mobilityInfo->setSpeed(speed);
    this->mobilityInfo->setStart(co, tSource);
    this->setNetworkAdress(agnetAdress);
    this->setTimeSourceArrivedLocal(tsLocal);
    this->setTimeSourceKnowed(tSource);
    this->commInfo->update(tsLocal, tSource, distanceRadiusCommA, distanceRadiusCommB,  this->mobilityInfo->getRelativeSpeed(),
            this->mobilityInfo->getDistanceab(), this->getMobilityInfo()->getMovementSensorPeriod());


 }

}
simtime_t Agent::getTimeSourceArrivedLocal() const {
    return timeSourceArrivedLocal;
}

void Agent::setTimeSourceArrivedLocal(simtime_t timeSourceArrivedLocal) {
    this->timeSourceArrivedLocal = timeSourceArrivedLocal;
}

simtime_t Agent::getTimeSourceKnowed() const {
    return timeSourceKnowed;
}

void Agent::setTimeSourceKnowed(simtime_t timeSourceKnowed) {
    this->timeSourceKnowed = timeSourceKnowed;
}
*/
/*
double Agent::getDirection() const {
    return direction;

}

void Agent::setDirection(double direction) {
    this->direction = direction;
}
*/

/*double Agent::getPeriodValidity() const {
    return periodValidity;
}

void Agent::setPeriodValidity(double periodValidity) {
    this->periodValidity = periodValidity;
}

simtime_t Agent::getValidityTime() const {
    return validityTime;
}
*/

//void Agent::setValidityTime(simtime_t validityTime) {
//    this->validityTime = validityTime;
//}
