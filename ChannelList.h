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

#ifndef CHANNELLIST_H_
#define CHANNELLIST_H_
#include "Channel.h"
#include <iostream>

class Channel;

class ChannelList {
public:
    std::vector<Channel*> channels;
    ChannelList();
    virtual ~ChannelList();
    Channel * getChannel(int64_t sourceId, int64_t destinationId);
    int getChannelIndex(int64_t sourceId , int64_t destinationId);
    std::vector<Channel*> listNeighbors(int64_t agentId);
    std::vector<Channel*> listChannelsWith(int64_t agentId);
    Channel* getChannel(int64_t sourceId, int64_t destinationId, std::vector<Channel*> aChannels);
    double calcMinDistancelr(int64_t agent);
    double calcMaxDistancelr(int64_t agent);
    double calcMaxSlr(int64_t agent);
    double calcMinSlr(int64_t agent);
};

#endif /* CHANNELLIST_H_ */
