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

#include <veins/modules/application/icarnew/GeneralCommunicationService.h>

GeneralCommunicationService::GeneralCommunicationService() {
    // TODO Auto-generated constructor stub
    this->appPeriodLoadMsg = 0.0;
    this->appTypeId = 0;
    this->deliveryDelay = 0.0;
    this->timeToLive = 0.0;
}

GeneralCommunicationService::~GeneralCommunicationService() {
    // TODO Auto-generated destructor stub
}

/*
 generate a different node  from notThisId
*/
int GeneralCommunicationService::getDestination(const std::vector <LocalAgent *> destinyVehicles, int notThisId){

    std::vector<LocalAgent *> x = destinyVehicles;
    //std::cout << std::endl << "Vehicles amount = " << x.size() ;

    int z;

    if (x.size() > 1){
        z = calcDestination(x);
        while ( z==notThisId)
        {
            //std::cout << "repete calc. destination = " << z << "   notThisId = " << notThisId << std::endl; // MY DEBUG
            z = calcDestination(destinyVehicles);
        }

    }else{
        //std::cout << "destination = -1     " << "   myId = " << notThisId << std::endl;  // MY DEBUG
        z= -1;
    }

    //std::cout << "destination = "<< z << "     myId = " << notThisId << std::endl; // MY DEBUG
    return z;

}

/*
 generation of destination
*/
int GeneralCommunicationService::calcDestination(const std::vector <LocalAgent *> destinyVehicles){

    std::vector<LocalAgent *> x = destinyVehicles;

   // srand (time(NULL));

    if (!x.empty())
    {
        int z = rand() % (x.size());
        //std::cout << "destination = " << x.at(z) << "   indice= " << z <<  std::endl;
        return x.at(z)->getId();
    }else {
        //std::cout << "destination = -1 " << std::endl;
        return -1;
    }


}
