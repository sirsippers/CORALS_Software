/**
 ********************************************************************************
 * @file    Telecommunication_Delegator.cpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Telecommunication Delegator Class
 * @version 1.0
 * @date    2024-03-22
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "Telecommunication_Delegator.hpp"

#include "Telecommunication.hpp"
#include "Telecommunication_Configuration.hpp"
#include "Telecommunication_Interpreter.hpp"
#include "Telecommunication_Literals.hpp"
#include "Telecommunication_Types.hpp"
#include "Telecommunication_Utilities.hpp"

namespace Telecommunication {

TelecommunicationDelegator::TelecommunicationDelegator(Telecommunication *telecommunicator) : telecommunicator(telecommunicator) {
    for (int i = 0; i < (int)Command::COMMAND_COUNT; i++) {
        interpreters[i] = nullptr;
    }
}

TelecommunicationDelegator::~TelecommunicationDelegator() {}

void TelecommunicationDelegator::AddInterpreter(Command command, TelecommunicationInterpreter *command_interpreter) {
    interpreters[(int)command] = command_interpreter;
}

void TelecommunicationDelegator::run() {
    TeleMessage message; 
    do {
        telecommunicator->GetReception();
        if (message.valid) interpreters[(int)message.command]->Interpret(message);
    } while (message.valid);
}

} // end namespace Telecommunication