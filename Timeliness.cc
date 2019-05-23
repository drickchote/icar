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

#include "Timeliness.h"

Timeliness::Timeliness() {
    // TODO Auto-generated constructor stub

}

Timeliness::~Timeliness() {
    // TODO Auto-generated destructor stub
}

std::string Timeliness::info() {
}

///*
std::string Timeliness::infoTrace(bool header)
{
    std::ostringstream ost;
    if (header)
       ost << ";age;validit Time; timeStampUpdate";
    else
        ost << ";" << this->age << ";" << this->validity << ";" << this->timeStampUpdate;

    return ost.str();
}
//*/

double Timeliness::getAge() {
    return age;
}


void Timeliness::setAge(double xage) {
    this->age = xage;
}


double Timeliness::getValidity() {
    return validity;
}


void Timeliness::setValidity(double validity) {
    this->validity = validity;
}

simtime_t Timeliness::getTimeoutValidity(){
    return timeoutValidity;
}

void Timeliness::setTimeoutValidity(simtime_t timeoutValidity) {
    this->timeoutValidity = timeoutValidity;
}

double Timeliness::getValidityNow(){
    double valNow=0;

    if (this->timeoutValidity > simTime())
        valNow = this->validity - (this->timeoutValidity - simTime()).dbl();

    //std::cout << "Timeliness class validity now=" << valNow << endl;

    if (valNow < 0) return 0;
    return valNow;
}

simtime_t Timeliness::getTimeStampUpdate(){
    return timeStampUpdate;
}

void Timeliness::setTimeStampUpdate(simtime_t timeStampUpdate) {
    this->timeStampUpdate = timeStampUpdate;
}

