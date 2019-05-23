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

#include <veins/modules/application/icarnew/KnownGlobal.h>

Define_Module(KnownGlobal);

void KnownGlobal::initialize()
{
    // TODO - Generated method body
}

void KnownGlobal::initialize(int stage) {
    if (stage == 0) {

       //Initializing members and pointers of your application goes here
       EV << "Initializing " << "Known Global " << std::endl;

       // when begin to send messages in the simulation
       this->startSimulation = par("startSimulation").doubleValue();

        // vehicle amount
       this->vehicleAmout = par("vehicleAmount").longValue();

       this->simulationDataheaderLine = par("simulationDataheaderLine").boolValue();

       //creating channel to analyze simulation - this is a simulation parameter
       this->distMatrix = new double*[vehicleAmout];

       for (int x = 0 ; x < vehicleAmout ; x++) {
           distMatrix[x] = new double[vehicleAmout];
       }

       // period to send application messages
       this->loadPeriodApp = par("loadPeriodApp").doubleValue();
       this->oGeneralCommunicationService.appPeriodLoadMsg =   this->loadPeriodApp;
       //  code of application type
       this->oGeneralCommunicationService.appTypeId = par("appTypeId").longValue();

       // tolerated delay of application
       this->oGeneralCommunicationService.deliveryDelay = par("deliveryDelay").doubleValue();

       // application message time in the network
       this->oGeneralCommunicationService.timeToLive =  par("timeToLive").doubleValue();

       this->knownVehicles.clear();

       // the estimator of channel radius
       this->oRadiusEstimatorChannel = new RadiusEstimatorChannel();

       // trace message file
       stringstream nameFileMessage;
       stringstream sufixo;
       /// =====

       clock_t instantTimeSimulation = clock();
       sufixo << "ST"<< instantTimeSimulation << "V"<< vehicleAmout <<"App"<< loadPeriodApp << par("observation").stdstringValue();
       string aux=sufixo.str();

       nameFileMessage << aux << "traceMessages.csv";
       this->fileMessages.open(nameFileMessage.str(), fstream::in | fstream::out | fstream::app);
       //std::cout << nameFileMessage.str() << endl;

       nameFileMessage.str("");
       aux=sufixo.str();
       nameFileMessage << aux << "traceChannels.csv"  ;
       this->fileChannels.open(nameFileMessage.str(), fstream::in | fstream::out | fstream::app);

       nameFileMessage.str("");
       aux=sufixo.str();
       nameFileMessage  << aux << "traceLocalAgents.csv";
       this->fileLocalAgents.open (nameFileMessage.str(), fstream::in | fstream::out | fstream::app);
       //std::cout << nameFileMessage.str() << endl;

       nameFileMessage.str("");
       aux=sufixo.str();
       nameFileMessage  << aux << "traceRemoteAgents.csv";
       this->fileRemoteAgents.open (nameFileMessage.str(), fstream::in | fstream::out | fstream::app);
       //std::cout << nameFileMessage.str() << endl;

       nameFileMessage.str("");
      aux=sufixo.str();
      nameFileMessage  << aux << "traceCommPerformance.csv";
      this->fileCommPerformance.open(nameFileMessage.str(), fstream::in | fstream::out | fstream::app);
      //std::cout << nameFileMessage.str() << endl;

       nameFileMessage.str("");
      aux=sufixo.str();
      nameFileMessage  << aux << "traceMinslr.csv";
      this->fileChannelsMinslr.open(nameFileMessage.str(), fstream::in | fstream::out | fstream::app);
      //std::cout << nameFileMessage.str() << endl;
    }
}

/*
 *
 */
void KnownGlobal::calcTraceChangedMobility(std::string agentName)
{/*

    //to convert string to int for update the matrix distance of idLocalNode
    int changedVehicle;
    std::stringstream converter;
    converter << agentName;
    converter >> changedVehicle;
    double calDistance;

    if (this->knownVehicles.size() > changedVehicle)
    {

        LocalAgent * cv= this->knownVehicles.at(changedVehicle);
        LocalAgent * la;

        if (cv->getLocalMobility()->getMove()!=NULL)
        {
            this->distMatrix[changedVehicle][changedVehicle] = 0;
            //std::cout << endl << "Matrix" << "[" << changedVehicle << "]" << " [" << changedVehicle << "] = "
            //        <<  this->distMatrix[changedVehicle][changedVehicle];

            for (int i=0; i < this->knownVehicles.size(); i++)
            {
                if (i!=changedVehicle)
                {
                    la= knownVehicles.at(i);

                    if (la->getLocalMobility()->getMove()!=NULL)
                    {
                        calDistance = cv->getMobilityInfo()->calcEuclideanDistancelr(cv->getLocalMobility()->getMove()->getCurrentPosition(),
                                la->getLocalMobility()->getMove()->getCurrentPosition());

                        this->distMatrix[changedVehicle][i] = calDistance;
                        this->distMatrix[i][changedVehicle] = calDistance;
                      //  std::cout << endl << "Matrix" << "[" << changedVehicle << "]" << " [" << i << "] = "
                      //          <<  this->distMatrix[changedVehicle][i];
                       // std::cout << endl << "Matrix" << "[" << i << "]" << " [" << changedVehicle << "] = "
                           //     <<  this->distMatrix[i][changedVehicle];
                    }
                }
            }
        }
    }
*/
}

int KnownGlobal::getIntNamefromIdAgent(int agentId)
{
    bool find;
    LocalAgent * la;
    unsigned int i=0;
    while (i < this->knownVehicles.size() && !find )
    {
       la= knownVehicles.at(i);

       if (la->getId()==agentId) find = true;
       else i++;
    }

    if (find) return i;
    else return -1;
}

std::string KnownGlobal::getStringNamefromIdAgent(int agentId)
{
    bool find;
    LocalAgent * la;
    unsigned int i=0;
    while (i < this->knownVehicles.size() && !find )
    {
       la= knownVehicles.at(i);

       if (la->getId()==agentId) find = true;
       else i++;
    }

    if (find) return la->getAgentName();
    else return "";
}


void KnownGlobal::finish()
{
    // TODO - Generated method body
    this->fileChannels.close();
    this->fileMessages.close();
    this->fileLocalAgents.close();
    this->fileRemoteAgents.close();
    this->fileChannelsMinslr.close();
    this->fileCommPerformance.close();
}

void KnownGlobal::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}
