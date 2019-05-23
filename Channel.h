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
 /*  LAddress::L3Type networkAdress in this version we consider that a car have only one network device;
 *
*/

#ifndef CHANNEL_H_
#define CHANNEL_H_

//#ifndef DBG
//#define DBG EV
//#endif
#define DBG std::cerr << "[" << simTime().raw() << "] " << getParentModule()->getFullPath() << " "

#include "messages/ChannelMonitor_m.h"
#include "./messages/ICMessage_m.h"
#include <vector>
#include "CommState.h"
#include "Agent.h"
#include "RemoteAgent.h"
#include "LocalAgent.h"
#include "Route.h"
#include "ChannelMobility.h"
#include "QoCChannel.h"
#include <veins/modules/application/icarnew/RadiusEstimatorChannel.h>

class QoCChannel;

class Channel {
private:
    /*
     * Agente origem da mensagem ou o que transmitiu mais recentemente
     */
    Agent *agent_s;

    /*
     * Agente que recebeu ou receber� a mensagem
     */
    Agent *agent_d;

    /*
     * Agente que informou sobre este canal -- que transmitiu a mensagem
     */
    Agent *agent_ds;

    /*
     * Mobilidade do canal
     */
    ChannelMobility* channelMobility;


    RadiusEstimatorChannel * radiusEstimator;

    double outOfRadiusRange;
    /*
     * raio estimado da origem ao destino
     */
    double calcRadius;
    /*
        * @brief txReceived_dBm power received from phy layer
        */
    double txReceived_dBm;
    /*
    * @brief Neighbor = 0 -- nao vizinho; neighbor= 1 -- eh vizinho; neighbor = -1 condicao desconhecida
    */
    int neighbors;
    int commnunicationState;

    QoCChannel * qoCChannel;
    double messageTTime;
    double oPeriodApplication; // periodo de carga de aplicação

    simtime_t penultTMsgSending;
    simtime_t lastTMsgSending;
    simtime_t lastTMsgReceiving;
    simtime_t currentTMsgReceiving;

    cMessage * channelMessage;


   //std::vector<Route*> routes;

public:

    Channel();
    virtual ~Channel();

    Channel(Agent* agentS, Agent* agentD, simtime_t msgReceivingTime, simtime_t msgSendingTime, RadiusEstimatorChannel * pRadiusEstimator,
            int neighbor, int event, simtime_t timeoutrouteValidity, double pPeriodApp, double powerReceived_dbm);

    void updateChannel(simtime_t msgReceivingTime, simtime_t msgSendingTime, int neighbor,int event,
            simtime_t timeoutdataValidity, double powerReceived_dbm);

    void updateRoute(ICMessage* m);

    void updateCommnunicationState(int event);

    Route * getRoute(ICMessage* m);

    bool isInChannel(int id);


   void setCalcRadius();
    /**
        * @brief
        * @param
        * @return
        */
    Agent* getAgentD();
    /**
        * @brief
        * @param
        * @return
        */
    void setAgentD(Agent* agentD);

    /**
        * @brief
        * @param
        * @return
        */
    Agent* getAgentS();
    /**
        * @brief
        * @param
        * @return
        */
    void setAgentS( Agent* agentS);


    /**
        * @brief
        * @param
        * @return
        */
    double getCalcRadius();

    /**
        * @brief
        * @param
        * @return
        */
    ChannelMobility* getChannelMobility();

    /**
        * @brief
        * @param
        * @return
        */
    void setChannelMobility(ChannelMobility * channelMobility);

    /**
        * @brief
        * @param
        * @return
        */
    int getCommnunicationState();

    /**
        * @brief
        * @param
        * @return
        */
    void setCommnunicationState(int commnunicationState);

    /**
        * @brief
        * @param
        * @return
        */
    simtime_t getCurrentTMsgReceiving();

    /**
        * @brief
        * @param
        * @return
        */
    void setCurrentTMsgReceiving(simtime_t correntTMsgReceiving);

    simtime_t getLastTMsgReceiving() ;
    /**
        * @brief
        * @param
        * @return
        */

    void setLastTMsgReceiving(simtime_t lastTMsgReceiving);
    /**
        * @brief
        * @param
        * @return
        */
    double getMessageTTime();
    /**
        * @brief
        * @param
        * @return
        */
    void setMessageTTime(double messageTTime);

    /**
        * @brief
        * @param
        * @return
        */
    bool isNeighbors();

    /**
        * @brief
        * @param
        * @return
        */
    void setNeighbors(int neighbors);


    // return the string with all attributes data  of this object
    std::string info();

    int getNeighbors();
    Agent* getAgentDs();
    void setAgentDs(Agent* agentDs);
    QoCChannel* getQoCChannel();
    void setQoCChannel(QoCChannel* qoCChannel);

    std::string infoTraceChannel(bool header);
    double getPeriodApplication();
    void setPeriodApplication(double periodApplication);
    double getTxReceivedDBm();
    void setTxReceivedDBm(double txReceivedDBm);
    cMessage* getChannelMessage();
    void setChannelMessage(cMessage* channelMessage);
    double getOutOfRadiusRangeState();
    void setOutOfRadiusRangeState();
};

#endif /* CHANNEL_H_ */
