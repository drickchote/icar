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

#include <veins/modules/application/icarnew/RadiusEstimatorChannel.h>

RadiusEstimatorChannel::RadiusEstimatorChannel() {
    // TODO Auto-generated constructor stub

}

RadiusEstimatorChannel::~RadiusEstimatorChannel() {
    // TODO Auto-generated destructor stub
}

double RadiusEstimatorChannel::getSignalRange(double transPower_dbm, double d_lr) {
        double transPower_domw = pow(10, (transPower_dbm/10));
        double transPower_dmw = pow(10, (this->sensitivityPower_dbm/10));
        double x = transPower_dmw / transPower_domw;
        double raizx = sqrt(x);
        double d = (d_lr / raizx) + d_lr;

        std::cout << endl << "transPower_dbm=  " << transPower_dbm <<  "   sensitivityPower_dbm=" << sensitivityPower_dbm;
        std::cout << endl << "x= " << transPower_dmw << "/" << transPower_domw << "  square root=" << raizx << "   dist=" << d << " dist=" << d_lr << "/" << raizx;

        d = (d_lr / raizx);

        return d;

}
