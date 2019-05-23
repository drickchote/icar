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

#include <veins/modules/application/icarnew/RemoteAgentCommInfo.h>

RemoteAgentCommInfo::RemoteAgentCommInfo() {
    // TODO Auto-generated constructor stub
    this->commPerformance = new RemoteAgentCommPerformance();
    this->radius = 0;
    this->senseGHZ = 0;
}

RemoteAgentCommPerformance * RemoteAgentCommInfo::getRemoteAgentCommPerformance(){
    return (RemoteAgentCommPerformance *) this->commPerformance;
}

RemoteAgentCommInfo::~RemoteAgentCommInfo() {
    // TODO Auto-generated destructor stub
}

std::string RemoteAgentCommInfo::info() {
    std::ostringstream ost;
    ost << CommInfo::info()
        << this->getRemoteAgentCommPerformance()->info();
    return ost.str();
}

std::string RemoteAgentCommInfo::infoTrace(bool header=false){
    std::ostringstream ost;
     ost << CommInfo::infoTrace(header)
        << this->getRemoteAgentCommPerformance()->infoTrace(header);

    return ost.str();
}
