/*
 * CommState.h
 * class represent the communication state of an agent
 *  Created on: 03/12/2015
 *      Author: Margarete
 *
 * In this version we define (decimal representation):
 *              0 = no-communicating
 *              1 = communicating
 *              2 = transmitting
 *              3 = receptor
 *              4 = faulty
 *
 *
 * events
  * 0 = l received message from r
  * 1 = l sent message to r
  * 2 = l knows r received from l recently
  * 3 = l didn't do anything
  * 4 = l receive msg error about r
  *
  *
  * kind field of Messages
  * 10 - monitoring request
  * 11 - response of monitoring request
  * 12 - wait monitoring response
  *
  * type Message - type of package
  * 10 - request package
  * 11 - monitoring response package
  *
  */




#ifndef COMMSTATE_H_
#define COMMSTATE_H_

class CommState {
public:
   // static const int TOTAL_NUMBER = 5;
    /*
     * list of communication states
     */
   static const int noCommunicating=0;
   static const int communicating=1;
   static  const int transmitting=2;
   static const int receptor=3;
   static  const int faulty=4;

   /* type Message - type of package
   * 10 - request package
   * 11 - monitoring response package
   *
   */
    static const int requestPack = 10;
    static const int responsePack = 11;

   /*
   * field kind  of monitoring event
   * 10 - monitoring request
   * 11 - response of monitoring request
   * 12 - wait monitoring response
   */
    static const int monitoringReqEvent = 10;
    //static const int MonitoringResponseEvent = 11;
    static const int waitingMonitoringResponse = 12;


    /*
    * List of possibles events
    */

    //
    static const int received = 0;

    //
    static const int sent = 1;

    //
    static const int knows = 2;

    //
    static const int nothing = 3;

    //error message event
    static const int erroMsg = 4;

    // end event of simulation
    static const int simulationFinal = 99;

    // begin event of simulation
    static const int simulationBegin = 20;


   /*
    * list of neighborhood situation
    */
   static const int neighbor = 1;
   static const int noNeighbor = 0;
   static const int unKnowedNeighbor = -1;

   static const int updateCommnunicationState(int event, int correntState){
        int newState;
        switch (correntState)
        {
        case noCommunicating: newState = noCommunicatingTransition(event);
            break;
        case communicating:newState = communicatingTransition(event);
            break;
        case transmitting: newState = transmittingTransition(event);
            break;
        case receptor: newState = receptorTransition(event);
            break;
        case faulty: newState = faultyTransition(event);
            break;
        default: newState =  -1;
            break;
        }

        return newState;
    }


   static const int noCommunicatingTransition(int event)
    {
        int newState;
        switch (event)
        {

        case received : newState = transmitting;
         break;

        //case sent : newState = receptor;
        // break;

        // case knows : newState = communicating;
        // break;

         case erroMsg: newState = faulty;
         break;

         default: newState = -1;
         break;
         }

         return newState;
    }


   static const int communicatingTransition(int event){
        int newState=-1;
        switch (event)
        {
         //case sent : newState = communicating;
         //break;

         //case knows : newState = communicating;
         //break;

         case nothing: newState = noCommunicating;
         break;

         case erroMsg: newState = faulty;
         break;

         default: newState = -1;
         break;
         }

         return newState;
    }


   static const int transmittingTransition(int event)
    {
        int newState=-1;
        switch (event)
        {
         case received: newState = transmitting;
         break;

         //case knows : newState = communicating;
         //break;

         case nothing: newState = noCommunicating;
         break;

         case erroMsg: newState = faulty;
         break;

         default: newState = -1;
         break;
         }

        return newState;
    }




   static const int receptorTransition(int event)
    {
        int newState=-1;
        switch (event)
        {
        case received : newState = communicating;
         break;
         case sent : newState = receptor;
         break;

         case nothing: newState = noCommunicating;
         break;

         case erroMsg: newState = faulty;
         break;

         default: newState = -1;
         break;
         }

         return newState;

    }

   static const int faultyTransition(int event)
    {
        int newState=-1;
        switch (event)
        {

        case received : newState = transmitting;
         break;

        //case sent : newState = receptor;
        // break;

        // case knows : newState = communicating;
        // break;

         case erroMsg: newState = faulty;
         break;

         default: newState = -1;
         break;
         }

         return newState;
    }


};



#endif /* COMMSTATE_H_ */
