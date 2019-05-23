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

#include "LocalMobility.h"




LocalMobility::LocalMobility(){
    // TODO Auto-generated constructor stub
    this->sensorPeriod = 0;
}

LocalMobility::LocalMobility(TraCIMobility* traci, float pMaxSpeed) {
    this->sensorPeriod = 0;
    this->setTraci((LocalMobilityTraci *)traci);

    //this->setMove(this->traci->getMove());
    this->lastMove = new Move();
    this->actualMove = this->traci->getMove();
    this->actualTemp =  this->actualMove;
    this->setMaxSpeed(pMaxSpeed);
    this->angle = traci->getAngleRad();
}

Move* LocalMobility::getMove() {
    //this->updateLocalMobilityPos();
    return this->actualMove;
}

Move* LocalMobility::getLastMove() {
    //this->updateLocalMobilityPos();
    return this->lastMove;
}

void LocalMobility::updateLocalMobilityPos()
{
     if(this->traci!=NULL)
     {
         if (!this->traci->isTerminated())
         {
             // to keep the last move
             this->lastMove = this->actualTemp;
             this->actualTemp = new Move();
             this->actualTemp->setStart(this->actualMove->getCurrentPosition(), this->actualMove->getStartTime());
             this->actualTemp->setSpeed(this->actualMove->getSpeed());

             this->actualMove = this->traci->getMove();
             this->angle = traci->getAngleRad();
             this->calcAcceleration();

         }
     }

}


double LocalMobility::getSensorPeriod(){
    //this->updateLocalMobilityPos();
    return sensorPeriod;
}

void LocalMobility::setSensorPeriod(double sensorPeriod) {
    //updateLocalMobilityPos();
    this->sensorPeriod=sensorPeriod;
}

LocalMobilityTraci * LocalMobility::getTraci()
{
    return (LocalMobilityTraci  * ) traci;
}

LocalMobility::~LocalMobility() {
    //delete (this);
}

void LocalMobility::setTraci(LocalMobilityTraci * traci) {
    this->traci = traci;
}


std::string LocalMobility::info() {

    std::ostringstream ost;
    ost << " sensor period: " << sensorPeriod << " acceleration: " << this->acceleration << " traci: " << traci->info();

    return ost.str();
}

std::string LocalMobility::moveInfoTrace(bool header=false){

       std::ostringstream ost;
       ost << ";" << MobilityInfo::moveInfoTrace(header);
       return ost.str();
}
