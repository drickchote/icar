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

#ifndef LOCALAGENT_H_
#define LOCALAGENT_H_
#include "LocalMobility.h"
#include "Agent.h"
#include "LocalCommInfo.h"

class LocalAgent : public Agent{
private:

public:
    LocalAgent(int64_t id, LocalMobility* lm, std::string agentName  );
   virtual ~LocalAgent();
   void updateLocalAgent(double maxSpeed, double setRadius);
    std::string info();
    std::string infoTrace(bool header);
    LocalMobility * getLocalMobility();
    LocalCommInfo* getLocalCommInfo();
};

#endif /* LOCALAGENT_H_ */
