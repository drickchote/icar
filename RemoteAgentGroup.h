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

#ifndef AGENTGROUP_H_
#define AGENTGROUP_H_

#include <vector>
#include "RemoteAgent.h"
using namespace std;

class RemoteAgentGroup {
private:
double maxMessageTTime;
double minMessageTTime;
double minApplicationTime;
double maxApplicationTime;
double maxDistancelr;
double minDistancelr;
double maxSlr;
double minSlr;

public:
    RemoteAgentGroup();
    virtual ~RemoteAgentGroup();

    double getMaxMessageTTime();
    void setMaxMessageTTime(double maxMessageTTime);
    double getMinApplicationTime();
    void setMinApplicationTime(double minApplicationTime);
    double getMinMessageTTime();
    void setMinMessageTTime(double minMessageTTime);
    RemoteAgent* getRemoteAgent(int64_t id);
    int getRemoteAgentIndex(int64_t id);
    vector <RemoteAgent*> knownRemoteAgents;
    std::string calcRemoteAgentGroupCommPerform(bool header);



};

#endif /* GROUPAGENT_H_ */
