/**
 ********************************************************************************
 * @file    Telecommunication_Interpreter.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Base Class for Telecommunication Interpreters
 * @version 1.0
 * @date    2024-03-22
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __TELECOMMUNICATION_INTERPRETER_HPP__
#define __TELECOMMUNICATION_INTERPRETER_HPP__

#include "Telecommunication.hpp"
#include "Telecommunication_Configuration.hpp"
#include "Telecommunication_Literals.hpp"
#include "Telecommunication_Types.hpp"
#include "Telecommunication_Utilities.hpp"

namespace Telecommunication {

class TelecommunicationInterpreter {
    friend class TelecommunicationDelegator;

    public:
        TelecommunicationInterpreter(const Telecommunication *telecommunicator, const Command command, const Keyword *keywords, const unsigned int keyword_count);
        ~TelecommunicationInterpreter();

        virtual void Interpret(TeleMessage message) = 0;

    protected:
        const Telecommunication *telecommunicator;
        const Command command;
        const Keyword *keywords;
        const unsigned int keyword_count;

};

} // end namespace Telecommunication

#endif // __TELECOMMUNICATION_INTERPRETER_HPP__