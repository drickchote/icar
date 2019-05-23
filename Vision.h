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

#ifndef VISION_H_
#define VISION_H_

#include <omnetpp.h>
#include <veins/modules/application/icarnew/GeneralCommunicationService.h>
#include "messages/ICMessage_m.h"
#include <vector>
#include "Agent.h"
#include "RemoteAgent.h"
#include "LocalAgent.h"
#include "LocalMobilityTraci.h"
#include "Channel.h"
#include "RemoteAgentGroup.h"
#include "messages/ICMessage_m.h"
#include "../../mobility/traci/TraCIMobility.h"
#include "ChannelList.h"
#include "Routing.h"
#include "KnownGlobal.h"
#include "veins/base/phyLayer/PhyToMacControlInfo.h"
#include "veins/modules/phy/DeciderResult80211.h"
#include "Icarqoc.h"


using Veins::TraCIMobility;

class Icarqoc;

class Vision
{
private:

    // data agent local
    LocalAgent* myData;

    // PS: Data local agent are not in this list
    RemoteAgentGroup * agentGroup;
    ChannelList * channelList;
    KnownGlobal * oKnownGlobal;

    // temporally here
    Routing * routing;
    GeneralCommunicationService service;

    Icarqoc * oIcarModule;

public:
    void updateCommunicationState(int64_t source, int64_t  destination);
    void callFinish();
    Vision();
    virtual ~Vision();
    Vision(TraCIMobility* bm, int64_t id, std::string agentName,  KnownGlobal * pKnownGlobal, double maxSpeed, Icarqoc * pIcarqoc);

    //Vision(TraCIMobility* bm, int64_t id, std::string agentName,  KnownGlobal * pKnownGlobal, double maxSpeed, );

    void updateChannels(Agent * agent, simtime_t timeStampData, std::string event);

    void updateChannels(ICMessage* m);
    void updateChannel(int64_t source, int64_t destiny, simtime_t msgReceivingTime, simtime_t msgSendingTime, int neighbor,
            int event, ICMessage* m, double txreceived, simtime_t  validtyTimeStamp);
    void updateAgentGroup(int64_t id, simtime_t tsStart, double x, double y, double z, double speed, double maxSpeed, double setRadius,
            bool sourcerOrAntecessorMsg, float acceleration, float angle);
    void updateAgentGroup(ICMessage* m);
    //void updateVisionMobility(Agent * source, Agent * destiny, ICMessage* m);
    void updateVision(ICMessage * m);
    void changeLocalMobility();

    // trace distance of two vehicles from traci
    void calcTraceChangedMobility(std::string agentName);

    // calc and update the communication performance
    void calcCommPerformVision(bool header);

    //  Channel* getChannel(int64_t sourceId, int64_t destinationId);
    int getChannelIndex(int64_t sourceId , int64_t destinationId);
    LocalAgent* getMyData();
    void setMyData(LocalAgent* myData);
    TraCIMobility* getTraci();
    void setTraci(TraCIMobility* traci);
    RemoteAgentGroup* getAgentGroup();
    void setAgentGroup(RemoteAgentGroup* agentGroup);
    Routing* getRouting();
    void setRouting(Routing* routing);
    GeneralCommunicationService getService();
    void setService(GeneralCommunicationService service);
    ChannelList* getChannelList() ;
    void setChannelList(ChannelList* channelList);
    std::string textDatachannel(string, Channel * c, bool header);
    // buffer file trace Channel;
     std::stringstream dataChannel;

     // buffer file trace Minslr;
     std::stringstream dataMinslr;

     // buffer file trace Remote Agent;
     std::stringstream dataRemoteAgent;

     // buffer file trace Remote Agent;
     std::stringstream dataLocalAgent;

     // buffer file trace Communication performance;
     std::stringstream dataCommPerformance;
};

#endif /* VISION_H_ */
