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

#ifndef SRC_VEINS_MODULES_APPLICATION_ICARNEW_COMMINFO_H_
#define SRC_VEINS_MODULES_APPLICATION_ICARNEW_COMMINFO_H_

#include "CommPerformance.h"

class CommInfo {

protected:
    double radius;
    double senseGHZ;

    CommPerformance * commPerformance;

public:
    CommInfo();
    virtual ~CommInfo();
    std::string info();
    std::string infoTrace(bool header);
    CommPerformance * getCommPerformance();
    void setCommPerformance(CommPerformance * commPerformance);
    double getRadius();
    void setRadius(double radius);
    double getSenseGhz();
    void setSenseGhz(double senseGhz);
};

#endif /* SRC_VEINS_MODULES_APPLICATION_ICARNEW_COMMINFO_H_ */
