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

#ifndef ROUTE_H_
#define ROUTE_H_

#include "Agent.h"
class Route {

private:
    Agent * sourceAgent;
    //Agent * destinationAgent;
    Agent * nextAgent;
    Agent * antecessorAgent;
    double messageTTimeFromSource;
    double messageTTimeFromAntecessor;
    double timeoute;
    //QoCRoute * qocRoute;

public:
    Route();
    virtual ~Route();
    Agent* getAntecessorAgent();
    void setAntecessorAgent(Agent* antecessorAgent);
    double getMessageTTimeFromAntecessor();
    void setMessageTTimeFromAntecessor(double messageTTimeFromAntecessor);
    double getMessageTTimeFromSource();
    void setMessageTTimeFromSource(double messageTTimeFromSource);
    Agent* getNextAgent();
    void setNextAgent( Agent* nextAgent);
    Agent* getSourceAgent();
    void setSourceAgent(Agent* sourceAgent);
    double getTimeoute();
    void setTimeoute(double timeoute);
};

#endif /* ROUTE_H_ */
