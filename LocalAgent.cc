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

#include "LocalAgent.h"

LocalAgent::LocalAgent(int64_t id, LocalMobility* localMobility, std::string agentName ) {
    // TODO Auto-generated constructor stub
    this->setId(id);
    this->setMobilityInfo(localMobility);
    this->setAgentName(agentName);
    this->commInfo = new LocalCommInfo();

}

LocalAgent::~LocalAgent() {
    // TODO Auto-generated destructor stub
    delete(this);
}

std::string LocalAgent::info() {
    std::ostringstream ost;
    ost << Agent::info()
        << "  Local Mobility: " << this->getLocalMobility()->info();
    return ost.str();
}

std::string LocalAgent::infoTrace(bool header=false){
    std::ostringstream ost;
    ost <<  Agent::infoTrace(header) << this->getLocalCommInfo()->infoTrace(header);
    return ost.str();
}


void LocalAgent::updateLocalAgent(double maxSpeed, double radius) {
    this->getMobilityInfo()->setMaxSpeed(maxSpeed);
    //radius
    this->getLocalCommInfo()->setRadius(radius);
}


LocalMobility * LocalAgent::getLocalMobility(){
    return (LocalMobility *) this->getMobilityInfo();
}


LocalCommInfo* LocalAgent::getLocalCommInfo() {
    return ((LocalCommInfo*) this->commInfo);
}
