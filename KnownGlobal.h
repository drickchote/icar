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

#ifndef __VEINS_APPVEHICULARFORMATION_H_
#define __VEINS_APPVEHICULARFORMATION_H_
#include <omnetpp.h>
#include <veins/modules/application/icarnew/RadiusEstimatorChannel.h>
#include <veins/modules/application/icarnew/GeneralCommunicationService.h>
#include "messages/ICMessage_m.h"
#include <vector>
#include "Agent.h"
#include "RemoteAgent.h"
#include "LocalAgent.h"
#include "Channel.h"
#include "RemoteAgentGroup.h"
#include "messages/ICMessage_m.h"
#include "../../mobility/traci/TraCIMobility.h"
#include "ChannelList.h"
#include "Routing.h"
#include <time.h>
using namespace omnetpp;


/**
 * TODO - Generated class
 */
class KnownGlobal : public cSimpleModule
{
  public:
    std::vector <LocalAgent *> knownVehicles;
   // ManagerFile * mf;
   fstream fileMessages;
   fstream fileChannels;
   fstream fileLocalAgents;
   fstream fileRemoteAgents;

   fstream fileChannelsMinslr;
   fstream fileCommPerformance;

   RadiusEstimatorChannel * oRadiusEstimatorChannel;
   GeneralCommunicationService oGeneralCommunicationService;
   double **distMatrix;
   double startSimulation; //time stamp to begin the message transmitting
   double loadPeriodApp; //application period load
   long vehicleAmout; //vehicle amount in the simulation
   double antennaSensitivity; // noise sensitivity of the antenna in dbm
   void calcTraceChangedMobility(std::string changedVehicle);
   int getIntNamefromIdAgent(int agentId);
   bool simulationDataheaderLine;
   std::string getStringNamefromIdAgent(int agentId);

  protected:
    virtual void initialize(int stage);
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};

#endif
