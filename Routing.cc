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

#include "Routing.h"

Routing::Routing() {
}

Routing::~Routing() {
}


ForwardingNode* Routing::getFowardNode( RemoteAgentGroup * groupAgent, ChannelList * pChannelList, int64_t pDestinationId,
        int64_t pSourceId, int64_t pAntecessorMsgId, double pMsgTimeToLive, Coord pTarget1, Coord pTarget2)
{

    this->groupAgent = groupAgent;
    this->channelList=pChannelList;
    this->destinationId = pDestinationId;
    this->antecessorMsgId = pAntecessorMsgId;
    this->sourceId = pSourceId;
    this->msgTimeToLive = pMsgTimeToLive;
    this->target1 = pTarget1;
    this->target2 = pTarget2;

    return searchNode();

}



ForwardingNode * Routing::searchNode()
{
    // inicializacao dos nos
    Channel * c = NULL;
    ForwardingNode * foward = new ForwardingNode();
    RemoteAgent *agDestination = this->groupAgent->getRemoteAgent(destinationId);
    if (agDestination != NULL)
        if (agDestination->getId() != -1)
        {
            // s->d
            c = verifyChannelc( this->sourceId, this->destinationId,"0", this->msgTimeToLive);
            if (c!=NULL)
            {
                foward->update("0", this->destinationId, c, 0);
            }else
            {
                // d-> s
                c = verifyChannelc(this->destinationId,this->sourceId, "1", this->msgTimeToLive);
                if (c!=NULL)
                {
                    foward->update("1", this->destinationId, c, 0);
                }else
                {
                    //std::cout << endl << "R0" << r0_foward->getFowardId() << endl;
                     foward = rule2();
                     if (foward->getFowardId()==-1)
                        foward = rule3();
                         if (foward->getFowardId()==-1)
                           foward = rule4();
                     //         if (foward->getFowardId()==-1)
                     //             foward = oldRule();
                }

              }
          }
    return foward;
}

ForwardingNode * Routing::rule2()
{
    ForwardingNode * fowardNode = new ForwardingNode();


    std::vector<Channel *>channels = channelList->listNeighbors(destinationId);
    bool find=false;
    unsigned int index = 0;
    Channel *  c =NULL;
    Channel * cInt = NULL;
    while (!find && channels.size()> index)
    {
            c = dynamic_cast<Channel*>(channels[index]);
            //verifica se o canal é vizinho
            if ((c->getCommnunicationState() == CommState::communicating || c->getCommnunicationState() == CommState::transmitting))
                //&& ( simTime() + c->getMessageTTime()).dbl() <= msgTimeToLive)
                   // && ( simTime() + c->getMessageTTime())<= msgTimeToLive && (simTime() + c->getQoCChannel()->getTimeliness()->getValidity())>=msgTimeToLive)
             {
                if (c->getAgentD()->getId()==destinationId)
                {
                    cInt = verifyChannelc( sourceId, c->getAgentS()->getId(), "2", c->getMessageTTime());
                    if (cInt != NULL) {
                        fowardNode->update("2", c->getAgentS()->getId(), cInt, 0);
                    }

                    if (fowardNode->getFowardId()!=-1) find = true;
                        //std::cout << endl << "R1: " << r1_foward->getFowardId() << endl;

                    if (!find){
                        cInt = verifyChannelc( c->getAgentS()->getId(), sourceId, "3", c->getMessageTTime());
                        if (cInt != NULL) {
                            fowardNode->update("3", c->getAgentS()->getId(), cInt, 0);
                        }

                    }
                }
             }
            index++;
    }

    cInt = NULL;
    if (fowardNode->getFowardId()==-1){
        index = 0;
        while (!find && channels.size()> index)
        {
                c = dynamic_cast<Channel*>(channels[index]);
                //verifica se o canal é vizinho
                if ((c->getCommnunicationState() == CommState::communicating || c->getCommnunicationState() == CommState::transmitting))
                        //&& ( simTime() + c->getMessageTTime()).dbl() <= msgTimeToLive)
                       // && ( simTime() + c->getMessageTTime())<= msgTimeToLive && (simTime() + c->getQoCChannel()->getTimeliness()->getValidity())>=msgTimeToLive)
                 {
                    if (c->getAgentS()->getId()==destinationId)
                    {
                        cInt = verifyChannelc( sourceId, c->getAgentD()->getId(), "4", c->getMessageTTime());
                        if (cInt != NULL) {
                            fowardNode->update("4", c->getAgentD()->getId(), cInt, 0);
                        }


                        if (fowardNode->getFowardId()!=-1) find = true;
                            //std::cout << endl << "R1: " << r1_foward->getFowardId() << endl;
                        if (!find){
                            cInt = verifyChannelc( c->getAgentD()->getId(), sourceId, "5", c->getMessageTTime());
                            if (cInt != NULL) {
                                fowardNode->update("5", c->getAgentD()->getId(), cInt, 0);
                            }
                        }
                    }
                 }

                index++;
        }

    }
    return fowardNode;
}




ForwardingNode * Routing::rule3()
{
    ForwardingNode * fowardNode = new ForwardingNode();
    std::vector<Channel *>channels = channelList->listNeighbors(sourceId);
    bool find=false;
    unsigned int index = 0;
    Channel *  c =NULL;

    while (!find && channels.size()> index)
    {
            c = dynamic_cast<Channel*>(channels[index]);


            if ((c->getCommnunicationState() == CommState::communicating || c->getCommnunicationState() == CommState::transmitting)
                && c->isNeighbors() ) //&& ( simTime() + c->getMessageTTime()).dbl() <= msgTimeToLive)
            {
                if (c->getAgentS()->getId()==sourceId)
                {
                     //  R3 - existe um agents vizinho comunivel entre o agente local e o destino
                        fowardNode=verifyChannelNotNeighbor(c->getAgentD()->getId(), destinationId, "6", c->getMessageTTime());
                        if (fowardNode->getFowardId()!=-1) find = true;
                        //std::cout << endl << "R1: " << r1_foward->getFowardId() << endl;
                } else{
                    //  R3 - existe um agents vizinho comunivel entre o agente local e o destino
                       fowardNode=verifyChannelNotNeighbor(c->getAgentS()->getId(), destinationId, "7", c->getMessageTTime());
                       //if (fowardNode->getFowardId()!=-1) find = true;
                       //std::cout << endl << "R1: " << r1_foward->getFowardId() << endl;
                }
             }

            index++;
    }
    return fowardNode;
}

//MELHORAR CÓDIGO DEPOIS ---
ForwardingNode * Routing::rule4()
{
    ForwardingNode * fowardNode = new ForwardingNode();
    ForwardingNode * fowardNodeNotNeighbor = new ForwardingNode();
    ForwardingNode * fowardNodeNeighbor = new ForwardingNode();

    std::vector<Channel *>channels = channelList->listChannelsWith(destinationId);
    std::vector<Channel *>channelsInt = channelList->listNeighbors(sourceId);

    bool find=false;
    unsigned int index = 0;
    unsigned int indexI;
    int fd, fs;
    Channel *  cd =NULL;
    Channel *  cs =NULL;
    Channel *  cf =NULL;
    //std::cout << channels.size() << "  routing class = " << channelsInt.size() << endl;

    while (!find && channels.size()> index)
    {
            cd = dynamic_cast<Channel*>(channels[index]);

            if ((cd->getCommnunicationState() == CommState::communicating || cd->getCommnunicationState() == CommState::transmitting)
                    && ( simTime() + cd->getMessageTTime()).dbl() <= msgTimeToLive)
             {
                if (cd->getAgentD()->getId()==destinationId) fd =  cd->getAgentS()->getId();
                else fd =  cd->getAgentD()->getId();

                indexI = 0;
                while (!find && channelsInt.size()> indexI)
                {
                        cs = dynamic_cast<Channel*>(channelsInt[indexI]);

                        if ((cs->getCommnunicationState() == CommState::communicating || cs->getCommnunicationState() == CommState::transmitting))
                         {
                                if (cs->getAgentD()->getId()==sourceId)
                                    fs = cs->getAgentS()->getId();
                                else fs = cs->getAgentD()->getId();

                                if (cd->isNeighbors())
                                {
                                    fowardNodeNeighbor=verifyChannel(fs, fd, "8", cs->getMessageTTime());

                                    if (fowardNodeNeighbor->getFowardId()!=-1) find = true;
                                    std::cout << " passei aqui routing class 1" << endl;

                                    if (fowardNodeNeighbor->getFowardId()==-1)
                                        fowardNodeNeighbor=verifyChannel(fd, fs, "9", cs->getMessageTTime());

                                    if (fowardNodeNeighbor->getFowardId()==-1)
                                        fowardNodeNeighbor=verifyChannelNotNeighbor(fd, fs, "10", cs->getMessageTTime());

                                    if (fowardNodeNeighbor->getFowardId()==-1)
                                        fowardNodeNeighbor=verifyChannelNotNeighbor(fs, fd, "11", cs->getMessageTTime());

                                    cf = cs;

                                    if (fowardNodeNeighbor->getFowardId()!=-1) find = true;

                                }else
                                {
                                    fowardNodeNotNeighbor=verifyChannel(fs, fd, "12", cs->getMessageTTime());

                                    if (fowardNodeNotNeighbor->getFowardId()==-1)
                                        fowardNodeNotNeighbor=verifyChannel(fd, fs, "13", cs->getMessageTTime());

                                    if (fowardNodeNotNeighbor->getFowardId()==-1)
                                        fowardNodeNotNeighbor=verifyChannelNotNeighbor(fd, fs, "14", cs->getMessageTTime());

                                    if (fowardNodeNotNeighbor->getFowardId()==-1)
                                        fowardNodeNotNeighbor=verifyChannelNotNeighbor(fs, fd, "15", cs->getMessageTTime());

                                    cf = cs;
                                }
                          }
                        indexI++;
                }//endwhile
             }//endif

            index++;
    }//endwhile
    std::cout << " passei aqui routing class 2" << endl;

    if (fowardNodeNeighbor->getFowardId()!=-1)
    {
        fowardNode = fowardNodeNeighbor;
    }else
    {
        if (fowardNodeNotNeighbor->getFowardId()!=-1)
            fowardNode = fowardNodeNotNeighbor;
    }

    if (fowardNode->getFowardId()!=-1) {
        if (cf->getAgentD()->getId() == sourceId)
        {
            fowardNode->setFowardId(cf->getAgentS()->getId());
            fowardNode->setChannel(cf);
        }else{
            fowardNode->setFowardId(cf->getAgentD()->getId());
            fowardNode->setChannel(cf);

        }
        std::cout << " passei aqui routing class 3  agentOrigem=" << sourceId << " agent channel f=" << fowardNode->getFowardId() << " agent channel d="
                << fowardNode->getChannel()->getAgentD()->getId()
        << " agent channel S=" << fowardNode->getChannel()->getAgentS()->getId() << endl;
    }

    std::cout << " passei aqui routing class 4  agentOrigem=" << sourceId << " agent channel D=" <<
            destinationId << "   forward="<< fowardNode->getFowardId() << endl;

    return fowardNode;
}

ForwardingNode * Routing::oldRule()
{
    ForwardingNode * fowardNode = new ForwardingNode();


    std::vector<Channel *>channels = channelList->listNeighbors(sourceId);
    bool find=false;
    unsigned int index = 0;
    Channel *  c =NULL;

    while (!find && channels.size()> index)
    {
            c = dynamic_cast<Channel*>(channels[index]);

            if (c->getAgentD()->getId()!= this->antecessorMsgId && c->getAgentS()->getId()!= this->antecessorMsgId
                && (c->getCommnunicationState() == CommState::communicating || c->getCommnunicationState() == CommState::transmitting)
                && ( simTime() + c->getMessageTTime()).dbl() <= msgTimeToLive)
                   // && ( simTime() + c->getMessageTTime())<= msgTimeToLive && (simTime() + c->getQoCChannel()->getTimeliness()->getValidity())>=msgTimeToLive)
             {
                if (c->getAgentD()->getId()==sourceId)
                    fowardNode->update("16", c->getAgentS()->getId() , c, 0);
                else fowardNode->update("17", c->getAgentD()->getId() , c, 0);

                find = true;
             }
            index++;
    }

    return fowardNode;
}


/*
 * Verify if the channel is communicating and neighbor between source and destiny
 */
Channel * Routing::verifyChannelc(int64_t pSource, int64_t pDestination, string rule, double msgTTime)
{
    Channel * resp = NULL;
    Channel *  c = channelList->getChannel(pSource, pDestination);

    if (c!=NULL)
    {
        if (c->getCommnunicationState()==-1)
            std::cout << endl << c->info() << endl;

        //verify the communication state and if is neighbor
            if ((c->getCommnunicationState()== CommState::transmitting || c->getCommnunicationState()== CommState::communicating)
                && c->isNeighbors()) //  && ( simTime() + c->getMessageTTime()).dbl() <= msgTimeToLive)
                {
                    resp = c;
                }
        }

    return resp;
}

/*
 * Verify if the channel is communicating and neighbor between source and destiny
 */
ForwardingNode * Routing::verifyChannel(int64_t pSource, int64_t pDestination, string rule, double msgTTime)
{
    Channel *  c = channelList->getChannel(pSource, pDestination);

    return verifyConditionForwardAgent(c, rule, msgTTime);
}



/*s
 * Verify if the channel is communicating and neighbor between source and destiny
 */
ForwardingNode * Routing::verifyChannelNotNeighbor(int64_t pSource, int64_t pDestination,  string rule, double msgTTime)
{
    Channel *  c = channelList->getChannel(pSource, pDestination);
    return verifyConditionForwardNotNeighbor(c, rule, msgTTime);
}


/*
 * Verify if the channel is communicating and neighbor between source and destiny
 */
ForwardingNode * Routing::verifyChannelAneib(int64_t agentId, string rule, double msgTTime)
{
        ForwardingNode * fAgent = new ForwardingNode();

        Channel *c=NULL;

        bool find=false;
        unsigned int index = 0;

        while (!find && channelList->channels.size()> index)
        {

            c = dynamic_cast<Channel*>(channelList->channels[index]);

            //std::cout << channelList->channels.size() << std::endl;

            fAgent = verifyConditionForwardAgent(c, rule, msgTTime);

            if (fAgent->getFowardId()!= -1) find = true;

            index++;
        }

    return fAgent;
}


/*
 * Verify if the channel is communicating and neighbor between source and destiny
 */
ForwardingNode * Routing::verifyChannelInverse(int64_t pDestination, int64_t pSource, string rule, double msgTTime)
{
    Channel *  c = channelList->getChannel(pSource, pDestination);

    return verifyConditionForwardAgent(c, rule, msgTTime);
}


/*
 * return the forwarding agent - verify only agent neighbor
 */
ForwardingNode * Routing::verifyConditionForwardAgent(Channel * c, string rule, double msgTTime)
{
    ForwardingNode * fAgent = new ForwardingNode();

    if (c!=NULL)
    {
        //verify the communication state and if is neighbor
            if ((c->getCommnunicationState()== CommState::transmitting || c->getCommnunicationState()== CommState::communicating)
                && c->isNeighbors()) //  && ( simTime() + c->getMessageTTime()).dbl() <= msgTimeToLive)
                {
                    fAgent->update(rule, c->getAgentS()->getId(), c, 0);
                }
        }

    return fAgent;
}

/*
 * return the forwarding agent - verify only agent neighbor
 */
ForwardingNode * Routing::verifyConditionForwardNotNeighbor(Channel * c, string rule, double msgTTime)
{
    ForwardingNode * fAgent = new ForwardingNode();

    if (c!=NULL)
    {
          //verify the communication state and if is neighbor
            if ((c->getCommnunicationState()== CommState::transmitting || c->getCommnunicationState()== CommState::communicating))
                   // && ( simTime() + c->getMessageTTime()).dbl() <= msgTimeToLive)
                {
                    fAgent->update(rule, c->getAgentS()->getId(), c, 0);
                }
        }

    return fAgent;
}



