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

#ifndef SRC_VEINS_MODULES_APPLICATION_ICARNEW_RADIUSESTIMATORCHANNEL_H_
#define SRC_VEINS_MODULES_APPLICATION_ICARNEW_RADIUSESTIMATORCHANNEL_H_
#include <veins/modules/application/icarnew/RadiusEstimatorChannel.h>
#include <omnetpp.h>
#include <iostream>
using namespace std;

class RadiusEstimatorChannel {
public:
    RadiusEstimatorChannel();
    virtual ~RadiusEstimatorChannel();
    double getSignalRange(double transPower_dbm, double d_lr);
    double sensitivityPower_dbm;
};

#endif /* SRC_VEINS_MODULES_APPLICATION_ICARNEW_RADIUSESTIMATORCHANNEL_H_ */
