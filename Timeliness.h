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

#ifndef TIMELINESS_H_
#define TIMELINESS_H_

#include <omnetpp.h>
#include "CommState.h"
using namespace omnetpp;

class Timeliness {
protected:

    /*
     * Validity = -1 -- the time is old, there is no validity
     */

    double validity;
    double age;
    simtime_t timeoutValidity;
    simtime_t timeStampUpdate;


public:
    Timeliness();
    virtual ~Timeliness();
    virtual double getAge();
    virtual void setAge(double age);
    virtual double getValidity();
    virtual double getValidityNow();
    virtual void setValidity(double validity);
    std::string infoTrace(bool header);

    // return the string with all attributes data  of this object
    std::string info();

    simtime_t getTimeoutValidity();
    void setTimeoutValidity(simtime_t timeoutValidity);
    simtime_t getTimeStampUpdate();
    void setTimeStampUpdate(simtime_t timeStampUpdate);
};

#endif /* TIMELINESS_H_ */
