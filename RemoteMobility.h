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

#ifndef REMOTEMOBILITY_H_
#define REMOTEMOBILITY_H_

#include "MobilityInfo.h"
#include "QoCInfo.h"

class RemoteMobility :public MobilityInfo {
private :

public:
    RemoteMobility();
    virtual ~RemoteMobility();



    RemoteMobility(simtime_t tsStart, double x, double y,  double z, double speed, double maxSpeed, float acceleration, float angle);

    void updateMobilityInfo(simtime_t tsStart, double x, double y,  double z, double speed, double maxSpeed, float acceleration, float angle);

};

#endif /* REMOTEMOBILITY_H_ */
