/**
 ********************************************************************************
 * @file    Telecommunication_Interpreter.cpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Base Class for Telecommunication Interpreters
 * @version 1.0
 * @date    2024-03-22
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "Telecommunication_Interpreter.hpp"

#include "Telecommunication_Literals.hpp"
#include "Telecommunication_Types.hpp"
#include "Telecommunication_Utilities.hpp"

namespace Telecommunication {

TelecommunicationInterpreter::TelecommunicationInterpreter(const Telecommunication *telecommunicator,
                                                           const Command command, 
                                                           const Keyword *keywords, 
                                                           const unsigned int keyword_count)
    : telecommunicator(telecommunicator), command(command), keywords(keywords), keyword_count(keyword_count) {}

TelecommunicationInterpreter::~TelecommunicationInterpreter() {}

} // end namespace Telecommunication