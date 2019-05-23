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

#ifndef SRC_VEINS_MODULES_APPLICATION_ICARNEW_LOCALMOBILITYTRACI_H_
#define SRC_VEINS_MODULES_APPLICATION_ICARNEW_LOCALMOBILITYTRACI_H_
#include "veins/modules/mobility/traci/TraCIMobility.h"


using Veins::TraCIMobility;

class LocalMobilityTraci :public TraCIMobility {
public:
    LocalMobilityTraci();
    virtual ~LocalMobilityTraci();
    Move * getMove();

    std::string getExternal_id(); /**< updated by setExternalId() */
    double getAntennaPositionOffset(); /**< front offset for the antenna on this car */

    simtime_t getLastUpdate(); /**< updated by nextPosition() */
    Coord getNextRoadPosition(); /**< position of front bumper, updated by nextPosition() */
    std::string getNextRoad_id(); /**< updated by nextPosition() */
    double getNextSpeed(); /**< updated by nextPosition() */
    double getNextAngle(); /**< updated by nextPosition() */
    //TraCIScenarioManager::VehicleSignal getSignals(); /**<updated by nextPosition() */

};

#endif /* SRC_VEINS_MODULES_APPLICATION_ICARNEW_LOCALMOBILITYTRACI_H_ */
