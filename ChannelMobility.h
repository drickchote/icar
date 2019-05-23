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

#ifndef CHANNELMOBILITY_H_
#define CHANNELMOBILITY_H_

#include <omnetpp.h>
#include "MobilityInfo.h"


class ChannelMobility {
private:

    /**
     * @brief relative speed between l and r
     */
    double relativeSpeed;

    /*
     *@brief actual distance between l and r agents
     */
    double distancelr;
    simtime_t distanceTime;
    /*
      *@brief last distance between l and r agents
      */
    double lastDistancelr;
    simtime_t lasDistanceTime;
    /*
     *@brief time stamp of movement
     */
    //simtime_t movementCurrentTime;

public:
    /**
       * @brief
       * @param
       * @return
       */
    ChannelMobility();
    /**
       * @brief
       * @param
       * @return
       */
    virtual ~ChannelMobility();
    /**
       * @brief
       * @param
       * @return
       */
    ChannelMobility(Move * l, Move * r);

    /**
       * @brief
       * @param
       * @return  the string with all attributes data  of this object
       */

    std::string info();

    /**
       * @brief
       * @param
       * @return
       */
    std::string infoTrace(bool header);

    /**
       * @brief
       * @param
       * @return
       */
    void updateChannelMobility(Move * l, Move * r);

    /**
       * @brief
       * @param
       * @return
       */
    double getDistancelr(Move * l, Move * r);

    double getDistancelr();

    double calcEuclideanDistancelr(Coord l, Coord r);
    double calRelativeSpeed(float referenceSpeedsourceMsg, float speedl);
    /**
       * @brief
       * @param
       * @return
       */
    //void setDistancelr(double distancelr);

    /**
       * @brief
       * @param
       * @return
       */
    //simtime_t getMovementCurrentTime();

    /**
       * @brief
       * @param
       * @return
       */
    //void setMovementCurrentTime(simtime_t movementCurrentTime);

    /**
        * @brief
        * @param
        * @return
        */
    double getLastDistancelr() const;
    double getRelativeSpeed() const;
    void setRelativeSpeed(double relativeSpeed);
};

#endif /* CHANNELMOBILITY_H_ */
