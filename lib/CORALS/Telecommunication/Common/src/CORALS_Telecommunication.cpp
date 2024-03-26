/**
 ********************************************************************************
 * @file    CORALS_Telecommunication.cpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   CORALS Configuration for Arduino MEGA 2560
 * @version 1.0
 * @date    2024-03-20
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "CORALS_Telecommunication.hpp"

#include <Telecommunication.hpp>
#include <Telecommunication_Delegator.hpp>

namespace CORALS {
namespace Telcommunication {

namespace {

Telecommunication *TELECOM;
TelecommunicationDelegator *DELEGATOR;

} // end namespace

void initialize() {
    TELECOM = new Telecommunication();
    DELEGATOR = new TelecommunicationDelegator(TELECOM);
}

void receive() {
    TELECOM->Receive();
}

void transmit() {
    TELECOM->Transmit();
}

void delegate() {
    DELEGATOR->run();
}

} // end namespace Telcommunication
} // end namespace CORALS