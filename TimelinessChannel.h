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

#ifndef TIMELINESSCHANNEL_H_
#define TIMELINESSCHANNEL_H_

//#ifndef DBG
//#define DBG EV
//#endif
#define DBG std::cerr << "[" << simTime().raw() << "] " << getParentModule()->getFullPath() << " "
#include <omnetpp.h>
#include "Timeliness.h"
#include "Channel.h"
#include "math.h"
#include <iostream>
using namespace omnetpp;

class Channel;

class TimelinessChannel : public Timeliness {
private:


    Channel * c;
    void calcTimeoutValidity();
    double slr=0;

    double validityNeighborConserv=0;
    double validityNeighberCondition=0;
    double ageNeighberCondition=0;
    double validityNeighbor250=0;
    double validityNeighborConserv250=0;
    double validity250=0;
    double slr250=0;

    simtime_t timeOutvalidityConservNext;
    double validityConservadorNext=0;
    double slrConservadorNext=0;

    double vslrNext=0;
    double validityVmNext=0;
    double validityNext=0;
    double validityVm=0;

    double distancialr=0;
    double distanciaNextlr=0;
    double maxRelativeSpeed=0;
    double relativeSpeed = 0;

    Coord sNext;
    Coord dNext;
    simtime_t timeoutValidityNeighberCondition;
    simtime_t timeStampUpdateNeighberCondition;

    double validityMobilityCondition=0;
    double ageMobilityCondition=0;
    simtime_t timeoutValidityMobilityCondition;
    simtime_t timeStampUpdateMobilityCondition;

    double validityCommState=0;
    double ageCommState=0;
    simtime_t timeoutValidityCommState;
    simtime_t timeStampUpdateCommState;
    simtime_t timeoutvalidityVmNext;
    simtime_t timeoutvalidityVm;
    simtime_t timeoutValidityNext;
    simtime_t timeoutvalidityNeighborConserv250;

    double setDigits(double _number, int _digits);
public:

    TimelinessChannel();
    TimelinessChannel(Channel* c, simtime_t dataValidity);
    std::string infoTrace(bool header);
    virtual ~TimelinessChannel();
    double calcValidity(simtime_t dataValidity);
    double calcAge();
    void update(simtime_t dataValidity);
    std::string  info();
   // double getDlr();
   // void setDlr(double dlr);
    double getSlr();
    void setSlr(double slr);

    double getAgeCommState();
    void setAgeCommState(double ageCommState);
    double getAgeMobilityCondition();
    void setAgeMobilityCondition(double ageMobilityCondition);
    double getAgeNeighberCondition();
    void setAgeNeighberCondition(double ageNeighberCondition);
    simtime_t getTimeoutValidityCommState();
    void setTimeoutValidityCommState(simtime_t timeoutValidityCommState);
    simtime_t getTimeoutValidityMobilityCondition();
    void setTimeoutValidityMobilityCondition(
            simtime_t timeoutValidityMobilityCondition);
    simtime_t getTimeoutValidityNeighberCondition();
    void setTimeoutValidityNeighberCondition(
            simtime_t timeoutValidityNeighberCondition);
    simtime_t getTimeStampUpdateCommState();
    void setTimeStampUpdateCommState(simtime_t timeStampUpdateCommState);
    simtime_t getTimeStampUpdateMobilityCondition();
    void setTimeStampUpdateMobilityCondition(
            simtime_t timeStampUpdateMobilityCondition);
    simtime_t getTimeStampUpdateNeighberCondition();
    void setTimeStampUpdateNeighberCondition(
            simtime_t timeStampUpdateNeighberCondition);
    double getValidityCommState();
    void setValidityCommState(double validityCommState);
    double getValidityMobilityCondition();
    void setValidityMobilityCondition(double validityMobilityCondition);
    double getValidityNeighberCondition();
    void setValidityNeighberCondition(double validityNeighberCondition);

};

#endif /* TIMELINESSCHANNEL_H_ */
