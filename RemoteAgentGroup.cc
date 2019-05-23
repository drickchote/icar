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

#include "RemoteAgentGroup.h"

RemoteAgentGroup::RemoteAgentGroup() {
    // TODO Auto-generated constructor stub
    maxMessageTTime=0;
    minApplicationTime=0;
    minMessageTTime=0;
}

double RemoteAgentGroup::getMaxMessageTTime(){
    return maxMessageTTime;
}

void RemoteAgentGroup::setMaxMessageTTime(double maxMessageTTime) {
    this->maxMessageTTime = maxMessageTTime;
}

double RemoteAgentGroup::getMinApplicationTime(){
    return minApplicationTime;
}

void RemoteAgentGroup::setMinApplicationTime(double minApplicationTime) {
    this->minApplicationTime = minApplicationTime;
}

double RemoteAgentGroup::getMinMessageTTime(){
    return minMessageTTime;
}

void RemoteAgentGroup::setMinMessageTTime(double minMessageTTime) {
    this->minMessageTTime = minMessageTTime;
}

RemoteAgentGroup::~RemoteAgentGroup() {
    // TODO Auto-generated destructor stub
    delete (this);
}

RemoteAgent* RemoteAgentGroup::getRemoteAgent(int64_t id){
    RemoteAgent *a=NULL;

    bool find=false;
    unsigned int index = 0;
    cout << std::endl << this->knownRemoteAgents.size() << std::endl;
    while (!find && this->knownRemoteAgents.size()> index)
    {
        //a = dynamic_cast<RemoteAgent*>(&knownRemoteAgents[index]);
        a = dynamic_cast<RemoteAgent*>(knownRemoteAgents[index]);

        if (a->getId() == id)
           find=true;
        else
            {
                a=NULL;
            }

        ++index;
    }
    if (a!=NULL) cout << std::endl << this->knownRemoteAgents.size()<< " - id " << a->getId() << " = " << id << std::endl;
     return a;
}

int RemoteAgentGroup::getRemoteAgentIndex(int64_t id){
    RemoteAgent *a=NULL;
    int index = -1;
    unsigned int i = 0;

    while (index==-1 && this->knownRemoteAgents.size()> i)
    {
        a = dynamic_cast<RemoteAgent*>(knownRemoteAgents[i]);

        if (a->getId() == id) index = i;
        ++i;
     }

    return index;
}

//calc the rate of the correct transmitted message for each group remote agent
std::string RemoteAgentGroup::calcRemoteAgentGroupCommPerform(bool header){
    RemoteAgent *a=NULL;
    std::ostringstream ost;
    unsigned int i = 0;

    while (this->knownRemoteAgents.size()> i)
    {
        a = dynamic_cast<RemoteAgent*>(knownRemoteAgents[i]);

        if (i==0) ost << a->infoTrace(true)<<std::endl;

        if (a->getRemoteAgentCommInfo()->getRemoteAgentCommPerformance()->getRateCorrectTransmittedMsgTemp()>0)
        {
            a->getRemoteAgentCommInfo()->getRemoteAgentCommPerformance()->calRateCorrectTransmittedMsgPerPeriod();
            ost << a->infoTrace(false)<<std::endl;
        }

        ++i;
     }
    return ost.str();
}
