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

#ifndef QOCINFO_H_
#define QOCINFO_H_
//#include "Math.h"
#include <omnetpp.h>
#include "Timeliness.h"
class QoCInfo {
protected:
    Timeliness *timeliness;

public:
    QoCInfo();
    virtual ~QoCInfo();
    Timeliness* getTimeliness();
    void setTimeliness(Timeliness* timeliness);
};

#endif /* QOCINFO_H_ */
