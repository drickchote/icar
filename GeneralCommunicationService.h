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

#ifndef GENERALCOMMUNICATIONSERVICE_H_
#define GENERALCOMMUNICATIONSERVICE_H_
#include <omnetpp.h>
#include <vector>
#include "LocalAgent.h"

using namespace Veins;

class GeneralCommunicationService {
public:

    // tolerated delay of application
   double deliveryDelay;

   //  code of application type
   int   appTypeId;

   // application message time in the network
   double timeToLive;

   // period to send application messages
   double appPeriodLoadMsg;

   int calcDestination(std::vector <LocalAgent *> destinyVehicles);

   int getDestination(std::vector <LocalAgent *> destinyVehicles, int notThisId);

   GeneralCommunicationService();

   virtual ~GeneralCommunicationService();
};

#endif /* GENERALCOMMUNICATIONSERVICE_H_ */



