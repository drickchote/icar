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

#include "Route.h"

Route::Route() {
    // TODO Auto-generated constructor stub

}

Route::~Route() {
    // TODO Auto-generated destructor stub
    delete (this);
}

Agent* Route::getAntecessorAgent()  {
    return antecessorAgent;
}

void Route::setAntecessorAgent( Agent* antecessorAgent) {
    this->antecessorAgent = antecessorAgent;
}


double Route::getMessageTTimeFromAntecessor() {
    return messageTTimeFromAntecessor;
}

void Route::setMessageTTimeFromAntecessor(double messageTTimeFromAntecessor) {
    this->messageTTimeFromAntecessor = messageTTimeFromAntecessor;
}

double Route::getMessageTTimeFromSource() {
    return messageTTimeFromSource;
}

void Route::setMessageTTimeFromSource(double messageTTimeFromSource) {
    this->messageTTimeFromSource = messageTTimeFromSource;
}

Agent* Route::getNextAgent() {
    return nextAgent;
}

void Route::setNextAgent( Agent* nextAgent) {
    this->nextAgent = nextAgent;
}

Agent* Route::getSourceAgent() {
    return sourceAgent;
}

void Route::setSourceAgent( Agent* sourceAgent) {
    this->sourceAgent = sourceAgent;
}

double Route::getTimeoute() {
    return timeoute;
}

void Route::setTimeoute(double timeoute) {
    this->timeoute = timeoute;
}
