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

#include "ChannelMobility.h"

ChannelMobility::ChannelMobility() {
    // TODO Auto-generated constructor stub

}

ChannelMobility::~ChannelMobility() {
    // TODO Auto-generated destructor stub
}

std::string ChannelMobility::info() {
    std::ostringstream ost;
    ost << "  l r agents distance: " << this->distancelr
        << "  l r relative speed : " << this->relativeSpeed;
     //   << "  l r agents movement time: " << this->movementCurrentTime;
    return ost.str();
}

std::string ChannelMobility::infoTrace(bool header)
{
    std::ostringstream ost;
    if (header)
       ost << ";distance_lr;relative_speed_lr";
    else
    {
        ost << ";" << this->distancelr
            << ";" << this->relativeSpeed;
    }
    return ost.str();
}



ChannelMobility::ChannelMobility(Move * l, Move * r)
{
    updateChannelMobility(l, r);
}

void ChannelMobility::updateChannelMobility(Move * l, Move * r)
{
    this->lastDistancelr = this->distancelr;
    this->lasDistanceTime = this->distanceTime;
    this->distanceTime = l->getStartTime();
    this->distancelr = this->calcEuclideanDistancelr(l->getCurrentPosition(), r->getCurrentPosition());
    this->relativeSpeed=this->calRelativeSpeed(l->getSpeed(), r->getSpeed());
}

double ChannelMobility::getLastDistancelr() const {
    return lastDistancelr;
}

double ChannelMobility::getRelativeSpeed() const {
    return relativeSpeed;
}

void ChannelMobility::setRelativeSpeed(double relativeSpeed) {
    this->relativeSpeed = relativeSpeed;
}

double ChannelMobility::calRelativeSpeed(float referenceSpeedsourceMsg, float speedl){

    if ((this->distancelr - this->lastDistancelr)>=0)
        return (referenceSpeedsourceMsg +speedl);
    else return fabs(referenceSpeedsourceMsg - speedl);
}

double ChannelMobility::getDistancelr(){
    return distancelr;
}

double ChannelMobility::getDistancelr(Move * l, Move * r){
    return this->calcEuclideanDistancelr(l->getCurrentPosition(), r->getCurrentPosition());
}

double ChannelMobility::calcEuclideanDistancelr(Coord l, Coord r){
    return sqrt((r.x - l.x)*(r.x - l.x) + (r.y - l.y)*(r.y - l.y));
}

