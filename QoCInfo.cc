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

#include "QoCInfo.h"

QoCInfo::QoCInfo() {
    // TODO Auto-generated constructor stub

}


Timeliness* QoCInfo::getTimeliness(){
    return timeliness;
}

void QoCInfo::setTimeliness(Timeliness* timeliness) {
    this->timeliness = timeliness;
}

QoCInfo::~QoCInfo() {
    // TODO Auto-generated destructor stub
    delete(this);
}




/*REMOVER DEPOIS
 *
 *
 *simtime_t  QoCInfo::calcValidity(){}
 *
 *void QoCInfo::setValidity(simtime_t validity) {
    this->validity = validity;
}
 *
void QoCInfo::setValidityPeriod(double vmr, double distanceab, simtime_t maxIntervalBetweenMsg, double radiusa, double radiusb, double periodSensorMoving) {
    calcValidityPeriod(vmr, distanceab, maxIntervalBetweenMsg, radiusa, radiusb, periodSensorMoving);
}
 * void QoCInfo::calcValidityPeriod(double vmr, double  distanceab, simtime_t maxIntervalBetweenMsg, double radiusa, double radiusb, double periodSensorMoving)
{

    // calculate the s value = space between a and b range radius
     double s;

     s = distanceab - radiusa - radiusb;
     if (s < 0){ // agenteb est� no alcance de a
         s = radiusa - distanceab;
     }

     //
     if (s == 0 || vmr==0 )
         this->validityPeriod = maxIntervalBetweenMsg;
     else{
         this->validityPeriod = fabs(s)/fabs(vmr);
         if (s > 0 && this->validityPeriod > maxIntervalBetweenMsg && this->validityPeriod > periodSensorMoving) this->validityPeriod = maxIntervalBetweenMsg;
     }
}

    std::string QoCInfo::recordInfo()
    {
        std::ostringstream strs;
        strs << this->getValidityPeriod();
        std::string str = strs.str();

        return str + ";";
    }

*/
