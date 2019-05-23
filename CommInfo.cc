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

#include <veins/modules/application/icarnew/CommInfo.h>

CommInfo::CommInfo(){
    // TODO Auto-generated constructor stub
    this->radius = 0;
    this->senseGHZ = 0;
}


CommPerformance* CommInfo::getCommPerformance(){
    return commPerformance;
}

double CommInfo::getRadius(){
    return radius;
}

void CommInfo::setRadius(double radius) {
    this->radius = radius;
}

double CommInfo::getSenseGhz(){
    return senseGHZ;
}

void CommInfo::setSenseGhz(double senseGhz) {
    senseGHZ = senseGhz;
}

CommInfo::~CommInfo() {
    // TODO Auto-generated destructor stub
}

std::string CommInfo::info() {
    std::ostringstream ost;
    ost << " Radius : " << this->radius
        << " Sensibilidade Antena : " << this->senseGHZ
        << " Period Mesurement: " << this->commPerformance->info();

    return ost.str();
}


std::string CommInfo::infoTrace(bool header=false) {
    std::ostringstream ost;

    if (header)
        ost << ";radius; Sensibilidade Antena " << this->commPerformance->infoTrace(header);
    else
        ost <<";" << this->radius<< ";" << this->senseGHZ << this->commPerformance->infoTrace(header);
    return ost.str();
}
