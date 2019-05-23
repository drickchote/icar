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

#include <veins/modules/application/icarnew/LocalMobilityTraci.h>

LocalMobilityTraci::LocalMobilityTraci() {
    // TODO Auto-generated constructor stub

}

LocalMobilityTraci:: ~LocalMobilityTraci() {
    // TODO Auto-generated destructor stub
}

Move * LocalMobilityTraci::getMove(){
    return (& this->move);

}

std::string LocalMobilityTraci::getExternal_id() {
    return this->external_id;
}

double LocalMobilityTraci::getAntennaPositionOffset() {
    return this->antennaPositionOffset;
}

simtime_t LocalMobilityTraci::getLastUpdate() {
    return this->lastUpdate;
}

Coord LocalMobilityTraci::getNextRoadPosition() {
    return this->roadPosition;
}

std::string LocalMobilityTraci::getNextRoad_id() {
    return this->road_id;
}

double LocalMobilityTraci::getNextSpeed() {
    return this->speed;
}

double LocalMobilityTraci::getNextAngle() {
    return this->angle;
}


