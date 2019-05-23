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

#include "ChannelList.h"

ChannelList::ChannelList() {
    // TODO Auto-generated constructor stub

}


Channel* ChannelList::getChannel(int64_t sourceId, int64_t destinationId){
    Channel *c=NULL;

    bool find=false;
    unsigned int index = 0;
    //std::cout << "buscar canal origem=" << sourceId << "   destino=" << destinationId << std::endl;
    while (!find && this->channels.size()> index)
    {
        //c = dynamic_cast<Channel*>(&channels[index]);
        c = dynamic_cast<Channel*>(channels[index]);

        if (c->getAgentS()->getId() == sourceId && c->getAgentD()->getId()==destinationId)
           find=true;
        else c=NULL;

        ++index;
    }
     return c;
}

Channel* ChannelList::getChannel(int64_t sourceId, int64_t destinationId, std::vector<Channel*> aChannels){
    Channel *c=NULL;

    bool find=false;
    unsigned int index = 0;
    //std::cout << "buscar canal origem=" << sourceId << "   destino=" << destinationId << std::endl;
    while (!find && aChannels.size()> index)
    {
        //c = dynamic_cast<Channel*>(&channels[index]);
        c = dynamic_cast<Channel*>(aChannels[index]);

        if (c->getAgentS()->getId() == sourceId && c->getAgentD()->getId()==destinationId)
           find=true;
        else c=NULL;

        ++index;
    }
     return c;
}


int ChannelList::getChannelIndex(int64_t sourceId , int64_t destinationId)
{
    Channel *c=NULL;
    int index = -1;
    unsigned int i = 0;

    while (index==-1 && this->channels.size()> i)
    {
        //c = dynamic_cast<Channel*>(&channels[i]);
        c = dynamic_cast<Channel*>(channels[i]);

        if (c->getAgentS()->getId() == sourceId && c->getAgentD()->getId()==destinationId)
            index = i;

        ++i;
     }

    return index;
}

std::vector<Channel*>  ChannelList::listNeighbors(int64_t agentId)
{
    Channel *c=NULL;

    std::vector<Channel*> neighborList;

    bool find=false;
    unsigned int index = 0;

    while (!find && channels.size()> index)
    {

        c = dynamic_cast<Channel*>(channels[index]);

    //   if (c->getAgentD()==NULL) std::cout << index << "encontrar vizinho de " << agentId<< std::endl;
    /*
     * Verifica se o destino desejado foi a origem do canal e se � comunic�vel e vizinho
     */

     if ((c->getAgentD()->getId() == agentId || c->getAgentS()->getId() == agentId) && c->isNeighbors())
             //|| (c->getAgentS()->getId()==agentId
             //&&  c->getChannelMobility()->getDistancelr() < c->getAgentS()->getSetRadius()))
     {
               neighborList.push_back(c);

     }

        ++index;
    }

    return  neighborList;
}

/*
 * list all channels that exist agentId
 */
std::vector<Channel*>  ChannelList::listChannelsWith(int64_t agentId)
{
    Channel *c=NULL;

    std::vector<Channel*> cList;

    bool find=false;
    unsigned int index = 0;

    while (!find && channels.size()> index)
    {

        c = dynamic_cast<Channel*>(channels[index]);


     if ((c->getAgentD()->getId() == agentId || c->getAgentS()->getId()==agentId))
     {
         cList.push_back(c);
               //std::cout << endl << "  destino: " << c->getAgentD()->getId() << "   origem: " << c->getAgentS()->getId() << endl;
     }

        ++index;
    }

    return  cList;
}

ChannelList::~ChannelList() {
    // TODO Auto-generated destructor stub
    delete (this);
}

/**
 * @brief
 *
 * @param
 */
double ChannelList::calcMaxDistancelr(int64_t agent ) {
    Channel *c=NULL;
    double maxDistance = 0;
    unsigned int index = 0;

    while (channels.size()> index)
    {

        c = dynamic_cast<Channel*>(channels[index]);

         if (c->getCommnunicationState()!=CommState::faulty
                 && (c->getAgentD()->getId() == agent || c->getAgentS()->getId())
                 && c->getChannelMobility()->getDistancelr(c->getAgentS()->getMobilityInfo()->getActualMove(),c->getAgentD()->getMobilityInfo()->getActualMove())
                         > maxDistance )
         {
             maxDistance = c->getChannelMobility()->getDistancelr(c->getAgentS()->getMobilityInfo()->getActualMove(),c->getAgentD()->getMobilityInfo()->getActualMove());
           //std::cout << endl << "  destino: " << c->getAgentD()->getId() << "   origem: " << c->getAgentS()->getId() << endl;
         }

        ++index;
    }

    return  maxDistance;

}

/**
 * @brief
 *
 * @param
 */
double ChannelList::calcMinDistancelr(int64_t agent) {
    Channel *c=NULL;
    double minDistance = 0;
    unsigned int index = 0;

    while (channels.size()> index)
    {

        c = dynamic_cast<Channel*>(channels[index]);

        if (index == 0 ) minDistance = c->getChannelMobility()->getDistancelr(c->getAgentS()->getMobilityInfo()->getActualMove(),c->getAgentD()->getMobilityInfo()->getActualMove());

         if (c->getCommnunicationState()!=CommState::faulty
                 && (c->getAgentD()->getId() == agent || c->getAgentS()->getId())
                 && c->getChannelMobility()->getDistancelr(c->getAgentS()->getMobilityInfo()->getActualMove(),c->getAgentD()->getMobilityInfo()->getActualMove()) < minDistance )
         {
             minDistance = c->getChannelMobility()->getDistancelr(c->getAgentS()->getMobilityInfo()->getActualMove(),c->getAgentD()->getMobilityInfo()->getActualMove());
           //std::cout << endl << "  destino: " << c->getAgentD()->getId() << "   origem: " << c->getAgentS()->getId() << endl;
         }

        ++index;
    }

    return  minDistance;
}

/**
 * @brief
 *
 * @param
 */
double ChannelList::calcMaxSlr(int64_t agent) {
    Channel *c=NULL;
    double maxSlr = 0;
    unsigned int index = 0;
    double aux;

    while (channels.size()> index)
    {
        c = dynamic_cast<Channel*>(channels[index]);

        aux = fabs(c->getQoCChannel()->getTimelinessChannel()->getSlr());

         if (c->getCommnunicationState()!=CommState::faulty
                 && (c->getAgentD()->getId() == agent || c->getAgentS()->getId())
                 && aux > maxSlr )
         {
             maxSlr = aux;
           //std::cout << endl << "  destino: " << c->getAgentD()->getId() << "   origem: " << c->getAgentS()->getId() << endl;
         }

        ++index;
    }

    return  maxSlr;
}

/**
 * @brief
 *
 * @param
 */
double ChannelList::calcMinSlr(int64_t agent) {
    Channel *c=NULL;
    double minSlr = -1;
    unsigned int index = 0;
    double aux;

    while (channels.size()> index)
    {
        c = dynamic_cast<Channel*>(channels[index]);

         if ((c->getAgentD()->getId() == agent || c->getAgentS()->getId())
                 && c->getCommnunicationState()!=CommState::faulty
                 && c->isNeighbors())
                 {
                 aux = fabs(c->getQoCChannel()->getTimelinessChannel()->getSlr());

                 if (minSlr == -1)
                  {
                     minSlr = aux;
                  }

                  if (aux < minSlr )
                     {
                      minSlr = aux;
                     }

                 // std::cout << endl << "  destino: " << c->getAgentD()->getId() << "   origem: " << c->getAgentS()->getId()
                //          << " min slr " << minSlr;

                 }

        ++index;
    }

    return  minSlr;
}


