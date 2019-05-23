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

#ifndef __VEINS_ICARQOC_H_
#define __VEINS_ICARQOC_H_
#include <omnetpp.h>
#include <vector>
#include "veins/base/phyLayer/BasePhyLayer.h"
#include <veins/modules/mobility/traci/TraCIScenarioManager.h>
#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"
#include <veins/modules/application/icarnew/KnownGlobal.h>
#include "CommState.h"
#include "Vision.h"
#include "messages/ICMessage_m.h"
#include "Channel.h"

//using namespace omnetpp;
class Vision;
class Channel;
using namespace Veins;

/**
 * TODO - Generated class
 */

class Icarqoc : public BaseWaveApplLayer {
public:

    private:
        CommState constanceValues; // constant values
        double loadPeriodApp; //application period load
        //double loadPeriodMonitor; // monitor period load
        int64_t seqMsg;  // counter vehicle messages
        int64_t tempNode; //to handle application messages
        long vehicleAmout; //vehicle amount in the simulation
        double perforMesurementPeriod; //period of communication performance measurement
        cMessage * monitorMsg; //monitor message event
        GeneralCommunicationService vfs;
        KnownGlobal* oKnownGlobal;
        Vision * oVision; // vehicular agent vision

       TraCIScenarioManager* managerx;

        // buffer file trace netwok;
         std::stringstream dataNetwork;

         // ManagerFile * mf;
          fstream fileNetwork;

    public:
          enum WaveApplMessageKinds {
                  SEND_ICM_EVT = 2,
                  SEND_MONITOR_EVT,
                  SEND_ICAR_PROTOCOL,
                  SEND_FORMATION_VEHIC,
                  SEND_IMAGES_STREAMS,
                  MEASURE_COMM_PERFORMANCE,
                  CHANNEL_MONITOR_MESSAGE
                  };

        double loadPeriodMonitor; // monitor period load
        virtual void initialize(int stage);
        virtual void finish();
        void scheduleLoadApp(double appPeriod, int AppTypeId, char * name,  cMessage *m1 );
    protected:
        virtual void onBSM(BasicSafetyMessage* bsm);
        virtual void onWSM(WaveShortMessage* wsm);
        virtual void onWSA(WaveServiceAdvertisment* wsa);

        virtual void handleSelfMsg(cMessage* msg);
        virtual void handlePositionUpdate(cObject* obj);

        //==== NOT VEINS ==========================
        /**
         * @brief
         *
         * @param
         */

        /**
         * @brief
         *
         * @param
         */
        double calcDelaySendLoadApp();
        /**
         * @brief
         *
         * @param
         */
        int64_t calcDestination(const vector<int> destinyVehicles);

        /**
         * @brief
         *
         * @param
         */
        void loadApp(cMessage *msg);

        /**
         * @brief
         *
         * @param
         */
        void onWSM(ICMessage * m);
        /**
         * @brief
         *
         * @param
         */
        ICMessage*  prepareWSM(int lengthBits, t_channel channel, int priority);
        /**
         * @brief
         *
         * @param
         */
        void sendMessageApplication(ForwardingNode * fowardNode, int64_t destination, double timetoLiveApp, unsigned int pMsgType, int64_t lastNodeNext, int64_t lastNextNodeRequestMsg);

        /**
         * @brief
         *
         * @param
         */
        void receptionMsg(ICMessage* msg);

        /**
         * @brief
         *
         * @param
         */
        //void sendForwardMessage(ForwardingNode * fowardAgent, ICMessage* wsm);
        void sendForwardMessage( ICMessage* wsm);
        /**
         * @brief
         *
         * @param
         */
        void receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj, cObject* details);

        /**
         * @brief
         *
         * @param
         */
        void sendMessagestoAgents();

        /**
         * @brief
         *
         * @param
         */
        void sendICMessage(ICMessage * wsm);
        void sendICMessage(ICMessage * wsm, std::string evento, std::string ruleRoute, bool header);
        /**
         * @brief
         *
         * @param
         */
        std::string msgInfoTraceTransmitting(ICMessage * wsm, std::string evento, std::string ruleRoute, bool header);
    };
#endif

