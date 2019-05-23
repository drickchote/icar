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

#include "RemoteMobility.h"

RemoteMobility::RemoteMobility() {
    // TODO Auto-generated constructor stub
}

RemoteMobility::RemoteMobility(simtime_t tsStart, double x, double y, double z, double speed, double maxSpeed, float acceleration, float angle){
    this->setActualMove(new Move());
    updateMobilityInfo(tsStart, x, y, z, speed, maxSpeed, acceleration, angle);
}



void  RemoteMobility::updateMobilityInfo(simtime_t tsStart, double x, double y, double z, double speed, double maxSpeed, float acceleration, float angle){
    Move * om = new Move();
    om->setStart(Coord(x, y,z), tsStart);
    om->setSpeed(speed);
    this->setActualMove(om);
    this->setMaxSpeed(maxSpeed);
    this->setAcceleration(acceleration);
    this->setAngle(angle);
}


RemoteMobility::~RemoteMobility() {

    //delete this;
}


/*std::string RemoteMobility::moveInfoTrace(bool header=false){

       std::ostringstream ost;
       if (header)
           ost << MobilityInfo::moveInfoTrace(header);
       else
           ost << MobilityInfo::moveInfoTrace(header);
       return ost.str();
}*/


