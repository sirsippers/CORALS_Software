/**
 ********************************************************************************
 * @file    Telecommunication.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Telecommunication Process
 * @version 1.0
 * @date    2024-03-22
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __TELECOMMUNICATION_HPP__
#define __TELECOMMUNICATION_HPP__

#include <Queue.tpp>

#include "Telecommunication_Configuration.hpp"
#include "Telecommunication_Literals.hpp"

namespace Telecommunication {

class Telecommunication {
    using MessageQueue = DataStructures::Queue<String>;

    friend class TelecommunicationInterpreter;
    friend class TelecommunicationDelegator;
    
    public:
        Telecommunication() : ReceiveBufferIndex(0) {};
        ~Telecommunication() {};
        
        void Receive(unsigned int count = 0);
        void Transmit(unsigned int count = 0);
    
    private:
        TeleMessage GetReception();
        void SendTransmission(TeleMessage message);
        
        MessageQueue ReceiveQueue;
        MessageQueue TransmitQueue;
        
        char ReceiveBuffer[TELECOM_RECEIVE_BUFFER];
        unsigned int ReceiveBufferIndex;

};

} // end namespace Telecommunication

#endif // __TELECOMMUNICATION_HPP__