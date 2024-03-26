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

#include "Telecommunication_Literals.hpp"
#include "Telecommunication_Types.hpp"

namespace Telecommunication {

CString GetCommandLiteral(Command command);
CString GetKeywordLiteral(Keyword keyword);
KeywordParameter_t GetKeywordParameter(Keyword keyword);

Checksum crc32(String data, StringSize length);

namespace Decoding {

bool VerifyTarget(String &ptr);
bool VerifyDotDelimiter(String &ptr);
bool VerifyCommaDelimiter(String &ptr);
Command GetCommand(String &ptr);
Keyword GetKeyword(String &ptr);

} // namespace Decoding

} // namespace Telecommunication

#endif // __TELECOMMUNICATION_UTILITIES_HPP__