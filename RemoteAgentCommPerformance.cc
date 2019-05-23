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

#include <veins/modules/application/icarnew/RemoteAgentCommPerformance.h>

RemoteAgentCommPerformance::RemoteAgentCommPerformance() {
    // TODO Auto-generated constructor stub
    this->rateCorrectTransmittedMsgTemp =0;
    this->rateCorrectTransmittedMsgToLocal=0;
    this->totalCorrectMsgTransmittedToLocal =0;
}

long RemoteAgentCommPerformance::getRateCorrectTransmittedMsgTemp(){
    return rateCorrectTransmittedMsgTemp;
}


void RemoteAgentCommPerformance::addCorrectMsgTransmitted() {
    this->rateCorrectTransmittedMsgTemp++;
    this->totalCorrectMsgTransmittedToLocal++;
}

long RemoteAgentCommPerformance::getRateCorrectTransmittedMsgToLocal(){
    return rateCorrectTransmittedMsgToLocal;
}

void RemoteAgentCommPerformance::calRateCorrectTransmittedMsgPerPeriod() {
    this->rateCorrectTransmittedMsgToLocal = rateCorrectTransmittedMsgTemp;
    this->rateCorrectTransmittedMsgTemp= 0;
}


long RemoteAgentCommPerformance::getTotalCorrectMsgTransmittedToLocal(){
    return totalCorrectMsgTransmittedToLocal;
}



RemoteAgentCommPerformance::~RemoteAgentCommPerformance() {
    // TODO Auto-generated destructor stub
}

std::string RemoteAgentCommPerformance::info() {
    std::ostringstream ost;
    ost << CommPerformance::info()
        << "  Remote rateCorrectTransmittedMsgTemporario: " << this->rateCorrectTransmittedMsgTemp
        << "  Remote rateCorrectTransmittedMsgToLocal: " << this->rateCorrectTransmittedMsgToLocal
        << "  Remote totalCorrectMsgTransmittedToLocal: " << this->totalCorrectMsgTransmittedToLocal;
    return ost.str();
}

std::string RemoteAgentCommPerformance::infoTrace(bool header=false){
    std::ostringstream ost;

    ost << CommPerformance::infoTrace(header);

    if (header)
       ost << ";Remote rateCorrectTransmittedMsgTemporario; Remote rateCorrectTransmittedMsgToLocal;Remote totalCorrectMsgTransmittedToLocal: ";
    else
       ost << ";" << this->rateCorrectTransmittedMsgTemp
           << ";" << this->rateCorrectTransmittedMsgToLocal
           << ";" << this->totalCorrectMsgTransmittedToLocal;

    return ost.str();
}
