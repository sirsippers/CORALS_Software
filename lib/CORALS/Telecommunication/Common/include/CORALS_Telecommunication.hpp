/**
 ********************************************************************************
 * @file    CORALS_Telecommunication.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   CORALS Configuration for Arduino MEGA 2560
 * @version 1.0
 * @date    2024-03-20
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __CORALS_TELECOMMUNICATION_HPP__
#define __CORALS_TELECOMMUNICATION_HPP__

#include <Telecommunication.hpp>
#include <Telecommunication_Delegator.hpp>
#include <Telecommunication_Interpreter.hpp>
#include <Telecommunication_Types.hpp>

namespace CORALS {
namespace Telcommunication {

using ::Telecommunication::Telecommunication;
using ::Telecommunication::TelecommunicationDelegator;
using ::Telecommunication::TelecommunicationInterpreter;

using ::Telecommunication::Command;
using ::Telecommunication::Keyword;

void initialize();

void receive();
void transmit();
void delegate();

void Register_RxInterpreter(Command command, TelecommunicationInterpreter *interpreter);

} // end namespace Telcommunication
} // end namespace CORALS

#endif // __CORALS_TELECOMMUNICATION_HPP__