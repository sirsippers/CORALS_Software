/**
 ********************************************************************************
 * @file    TelecommunicationUtilities.cpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Telecommunication Encoding/Decoding Utilities
 * @version 1.0
 * @date    2024-03-22
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "Telecommunication_Utilities.hpp"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "Telecommunication_Literals.hpp"
#include "Telecommunication_Types.hpp"
namespace Telecommunication {

uint32_t crc32(const uint8_t *data, uint32_t length) {
    uint32_t crc = 0xFFFFFFFF;

    for (uint32_t i = 0; i < length; ++i) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            uint32_t mask = -(crc & 1);
            crc = (crc >> 1) ^ (0xEDB88320 & mask);
        }
    }

    return crc;
}

namespace Decoding {

bool VerifyTarget(char* &ptr) {
    bool retval = strncmp(ptr, RECEIVER, RECEIVER_LENGTH) == 0;
    ptr += RECEIVER_LENGTH;
    return retval;
}

bool VerifyDotDelimiter(char* &ptr) {
    bool retval = strncmp(ptr, COMMAND_DELIMITER, COMMAND_DELIMITER_LENGTH) == 0;
    ptr += COMMAND_DELIMITER_LENGTH;
    return retval;
}

bool VerifyCommaDelimiter(char* &ptr) {
    bool retval = strncmp(ptr, KEYVALUE_DELIMITER, KEYVALUE_DELIMITER_LENGTH) == 0;
    ptr += KEYVALUE_DELIMITER_LENGTH;
    return retval;
}

Command_t GetCommand(char* &ptr) {
    Command_t retval = NO_COMMAND;
    for (int i = 0; i < COMMAND_COUNT; i++) {
        unsigned int length = strlen(CommandLiterals[i]);
        if (strncmp(ptr, CommandLiterals[i], length) == 0) {
            retval = (Command_t)i;
            ptr += length;
            break;
        }
    }
    return retval;
}

Keyword_t GetKeyword(char* &ptr) {
    Keyword_t retval = NO_KEYWORD;
    for (int i = 0; i < KEYWORD_COUNT; i++) {
        unsigned int length = strlen(KeywordParameters[i].literal);
        if (strncmp(ptr, KeywordParameters[i].literal, length) == 0) {
            retval = (Keyword_t)i;
            ptr += length;
            break;
        }
    }
    return retval;
}

} // namespace Decoding

} // namespace Telecommunication