/**
 ********************************************************************************
 * @file    Telecommunication_Utilities.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Telecommunication Encoding/Decoding Utilities
 * @version 1.0
 * @date    2024-03-22
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __TELECOMMUNICATION_UTILITIES_HPP__
#define __TELECOMMUNICATION_UTILITIES_HPP__

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "Telecommunication_Literals.hpp"
#include "Telecommunication_Interpreter.hpp"

namespace Telecommunication {

uint32_t crc32(const uint8_t *data, uint32_t length);

namespace Decoding {

bool VerifyTarget(char* &ptr);
bool VerifyDotDelimiter(char* &ptr);
bool VerifyCommaDelimiter(char* &ptr);
Command_t GetCommand(char* &ptr);
Keyword_t GetKeyword(char* &ptr);

} // namespace Decoding

} // namespace Telecommunication

#endif // __TELECOMMUNICATION_UTILITIES_HPP__