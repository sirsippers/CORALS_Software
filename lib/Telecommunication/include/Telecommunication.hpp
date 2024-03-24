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

#include "List.hpp"
#include "Telecommunication_Literals.hpp"

namespace CORALS {

class Telecommunication {
    using MessageList = DataStructures::List<const char *>;

    friend class TelecommunicationInterpreter;
    
public:
    Telecommunication() : ReceiveBufferIndex(0) {};
    ~Telecommunication() {};

    void Receive(unsigned int count = 0) {
        unsigned int messages_received = 0;
        for (unsigned int &i = ReceiveBufferIndex; i < TELECOM_RECEIVE_BUFFER && HC05.available() && (count == 0 || messages_received < count); i++) {
            ReceiveBuffer[i] = HC05.read();
            if (strncmp(&ReceiveBuffer[i - 2], "\r\r\r", 3) == 0) {
                ReceiveBuffer[i - 2] = '\0';
                char *new_string = new char[i -2];
                strncpy(new_string, ReceiveBuffer, i - 2);
                ReceiveQueue.push_front(new_string);
                i = 0;
                messages_received++;
            }
        }
        if (ReceiveBufferIndex == TELECOM_RECEIVE_BUFFER) ReceiveBufferIndex = 0;
    };

    void Transmit(unsigned int count = 0, bool echo_mode = false) {
        MessageList &OperatingQueue = echo_mode ? ReceiveQueue : TransmitQueue;
        for (unsigned int i = 0; (count == 0 || i < count) && !OperatingQueue.empty(); i++) {
            HC05.print(OperatingQueue.pop_front());
            HC05.print("\r\r\r");
        }
    };
    
private:
    MessageList ReceiveQueue;
    MessageList TransmitQueue;
    
    char ReceiveBuffer[TELECOM_RECEIVE_BUFFER];
    unsigned int ReceiveBufferIndex;

};

static Telecommunication TELECOM;

void Transmit() {
    TELECOM.Transmit(0);
}

void Receive() {
    TELECOM.Receive();
}

} // end namespace CORALS

#endif // __TELECOMMUNICATION_HPP__