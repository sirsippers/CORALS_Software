/**
 ********************************************************************************
 * @file    Telecommunication_Delegator.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Telecommunication Delegator Class
 * @version 1.0
 * @date    2024-03-22
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __TELECOMMUNICATION_DELEGATOR_HPP__
#define __TELECOMMUNICATION_DELEGATOR_HPP__

#include "Telecommunication.hpp"
#include "Telecommunication_Configuration.hpp"
#include "Telecommunication_Interpreter.hpp"
#include "Telecommunication_Literals.hpp"
#include "Telecommunication_Types.hpp"
#include "Telecommunication_Utilities.hpp"

namespace Telecommunication {

class TelecommunicationDelegator {
    public:
        TelecommunicationDelegator(Telecommunication *telecommunicator);
        ~TelecommunicationDelegator();

        void AddInterpreter(Command command, TelecommunicationInterpreter *command_interpreter);

        void run();

    private:
        Telecommunication *telecommunicator;
        TelecommunicationInterpreter *interpreters[(int)Command::RECEIVING_COMMAND_COUNT];

};

} // end namespace Telecommunication

#endif // __TELECOMMUNICATION_DELEGATOR_HPP__