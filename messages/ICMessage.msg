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

//
// TODO generated message class
//

cplusplus {{
#include "veins/base/utils/Coord.h"
#include "veins/modules/messages/WaveShortMessage_m.h"
}}

class WaveShortMessage;
class noncobject Coord;

packet ICMessage extends WaveShortMessage {
	unsigned long numMsg; // number of message
    unsigned int msgType; // message type 
	long sourceId;  // source id node - 32bits 
    long destinationId; // destination id node - 32 bits 
    long antecessorId; // anetecessor id node - - 32 bits 
    long nextId; // next id node - 64 bits 
	
	float  sourceX=0;  //source x - 32 bits
    float sourceY=0; // source y - 32 bits
    float sourceZ=0; // source z - 32 bits
        
    float antecessorX=0;  // Antecessor x - 32 bits
    float antecessorY=0; // Antecessor y - 32 bits
    float antecessorZ=0; // Antecessor z  - 32 bits
    
    float nextX=0;  // next x - 64 bits
    float nextY=0; // next y - 64 bits
    float nextZ=0; // next z  - 64 bits
   
    float destinationX=0;  // destination x - 32 bits
    float destinationY=0; // destination y - 32 bits
    float destinationZ=0; // destination z  - 32 bits
    
    float sourceMaxSpeed=0;  // velocidade do agente de origem - 32 bits
    float antecessorMaxSpeed=0;  // velocidade do agente de antecessor - 32 bits
    float nextMaxSpeed=0;  // velocidade do pr�ximo agente de encaminhamento que ir� consumir a mensagem - 32 bits
    float destinationMaxSpeed=0;  // velocidade m�xima do agente destino que ir� consumir a mensagem - 32 bits

    float sourceAngle=0;  // angulo do agente de origem -  32 bits
    float antecessorAngle=0;  // angulo do agente de antecessor - 32 bits
    float nextAngle=0;  // angulo do pr�ximo agente de encaminhamento - 32 bits
    float destinationAngle=0;  // angulo do agente destino que ir� consumir a mensagem - 32 bits

    float sourceAceleration=0;  // aceleracao do agente de origem -  32 bits
    float antecessorAceleration=0;  // aceleracao do agente de antecessor - 32 bits
    float nextAceleration=0;  // aceleracao do pr�ximo agente de encaminhamento - 32 bits
    float destinationAceleration=0;  // aceleracao do agente destino que ir� consumir a mensagem - 32 bits
        
    float sourceSpeed=0;  // velocidade do agente de origem -  32 bits
    float antecessorSpeed=0;  // velocidade do agente de antecessor - 32 bits
    float nextSpeed=0;  // velocidade do proximo agente de encaminhamento - 32 bits
    float destinationSpeed=0;  // velocidade do agente destino que ir� consumir a mensagem - 32 bits
    
    simtime_t anteNextValidityTimeStamp=0; // alcance do sinal de comunica��o do agente de origem  - 32 bits
		
	simtime_t sourceMsgTimeStamp = 0; // timestamp da mensagem
	simtime_t antecessorMsgTimeStamp = 0; // timestamp da mensagem
	
	simtime_t msgLifeTime; // message life time - 16 bits
	
	simtime_t AntecessoPosTimeStamp = 0; // timestamp da da coleta da posicao do agente antecessor 
	simtime_t SourcePosTimeStamp = 0; // timestamp da da coleta da posi��o do agente de origem 
    simtime_t nextPosTimeStamp = 0; // timestamp da da coleta da posicao do proximo agente de encaminhamento
    simtime_t destinationPosTimeStamp = 0; // timestamp da da coleta da posi��o do pr�ximo agente de encaminhamento
    
    simtime_t validityDataTimeStamp; // validity timeout of the menor neighborhood condition of the route nodes
    unsigned int hopNumber =0; // hops counting of route in that moment 

}
