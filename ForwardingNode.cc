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

#include "ForwardingNode.h"

ForwardingNode::ForwardingNode() {
    // TODO Auto-generated constructor stub
    this->rule="-1";
    this->fowardId = -1;
    this->channel = NULL;

}

double ForwardingNode::getDataValidity(){
    return dataValidity;
}

void ForwardingNode::update(std::string rule, int fowardingAgent, Channel * c, double periodvalidty){
    this->setFowardId(fowardingAgent);
    this->setDataValidity(c->getQoCChannel()->getTimeliness()->getValidityNow());
    //this->setDataValidity(periodvalidty);
    //this->setTimeoutValidity(((simtime_t)(simTime() + periodvalidty)));
    this->setTimeoutValidity(c->getQoCChannel()->getTimeliness()->getTimeoutValidity());
    this->setRule(rule);
    this->channel = c;
}

void ForwardingNode::setDataValidity(double dataValidity) {
    this->dataValidity = dataValidity;
}

int64_t ForwardingNode::getFowardId(){
    return fowardId;
}

void ForwardingNode::setFowardId(int64_t fowardId) {
    this->fowardId = fowardId;
}

std::string ForwardingNode::getRule(){
    return rule;
}

void ForwardingNode::setRule(std::string rule) {
    this->rule = rule;
}

const simtime_t ForwardingNode::getTimeoutValidity(){
    return timeoutValidity;
}

Channel* ForwardingNode::getChannel(){
    return channel;
}

void ForwardingNode::setChannel(Channel* channel) {
    this->channel = channel;
}

void ForwardingNode::setTimeoutValidity(const simtime_t timeoutValidity) {
    this->timeoutValidity = timeoutValidity;
}

ForwardingNode::~ForwardingNode() {
    // TODO Auto-generated destructor stub
}

