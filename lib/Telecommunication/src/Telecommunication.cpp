/**
 ********************************************************************************
 * @file    Telecommunication.cpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Telecommunication Process
 * @version 1.0
 * @date    2024-03-22
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "Telecommunication.hpp"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Queue.tpp>

#include "Telecommunication_Configuration.hpp"
#include "Telecommunication_Literals.hpp"
#include "Telecommunication_Types.hpp"
#include "Telecommunication_Utilities.hpp"

namespace Telecommunication {

Telecommunication::Telecommunication() : ReceiveBufferIndex(0) {
    TC_USART.begin(TC_BAUD_RATE);
};

Telecommunication::~Telecommunication() {};

void Telecommunication::Receive(unsigned int count) {
    unsigned int messages_received = 0;
    for (unsigned int &i = ReceiveBufferIndex; i < TELECOM_RECEIVE_BUFFER && TC_USART.available() && (count == 0 || messages_received < count); i++) {
        ReceiveBuffer[i] = TC_USART.read();
        if (strncmp(&ReceiveBuffer[i - 2], TELECOM_MESSAGE_DELIMITER, 3) == 0) {
            ReceiveBuffer[i - 2] = '\0';
            char *new_string = new char[i -2];
            strncpy(new_string, ReceiveBuffer, i - 2);
            ReceiveQueue.push(new_string);
            i = 0;
            messages_received++;
        }
    }
    if (ReceiveBufferIndex == TELECOM_RECEIVE_BUFFER) ReceiveBufferIndex = 0;
}

void Telecommunication::Transmit(unsigned int count) {
    MessageQueue &OperatingQueue = TELECOM_RAW_ECHO_MODE ? ReceiveQueue : TransmitQueue;
    for (unsigned int i = 0; (count == 0 || i < count) && !OperatingQueue.empty(); i++) {
        TC_USART.print(OperatingQueue.pop());
        TC_USART.print(TELECOM_MESSAGE_DELIMITER);
    }
}

TeleMessage Telecommunication::GetReception() {
    using namespace Decoding;

    TeleMessage retval;

    // Get Message from Queue
    String string = NULL;
    ReceiveQueue.pop(string);
    if (string == NULL) {
        retval.valid = false;
        return retval;
    }
    String ptr = (String) string;
    StringSize length = strlen(string);
    Checksum expected_checksum = crc32(ptr, length-TELECOM_CHECKSUM_LENGTH);
            
    // Verify Target is CORALS
    if (!VerifyTarget(ptr)) {
        retval.valid = false;
        delete[] string;
        return retval;
    }

    // Verify Delimiter
    if (!VerifyDotDelimiter(ptr)) {
        retval.valid = false;
        delete[] string;
        return retval;
    }

    // Verify Checksum
    uint32_t checksum = strtol(string + length - 8, NULL, 16);
    if (checksum != expected_checksum) {
        retval.valid = false;
        delete[] string;
        return retval;
    }

    // Get Command Keyword
    retval.command = GetCommand(ptr);
    if (retval.command == Command::NO_COMMAND) {
        retval.valid = false;
        delete[] string;
        return retval;
    }

    // Verify Delimiter
    if (!VerifyCommaDelimiter(ptr)) {
        retval.valid = false;
        delete[] string;
        return retval;
    }

    // Get Key Value Pairs
    bool end_of_message = false;
    DataStructures::Queue<KeyValue> key_value_pairs;
    do {
        // Get Keyword
        KeyValue key_value;
        key_value.keyword = GetKeyword(ptr);
        if (key_value.keyword == Keyword::NO_KEYWORD) {
            retval.valid = false;
            delete[] string;
            return retval;
        }

        const KeywordParameter keyword_parameter = GetKeywordParameter(key_value.keyword);

        // Get Value
        key_value.type = keyword_parameter.datatype;
        String tmp = ptr;
        unsigned int i = 0;
        Value value;
        switch (key_value.type) {
            case ParameterType::INTEGER:
                value.integer = strtol(tmp, &ptr, 10);
                if (tmp == ptr) {
                    retval.valid = false;
                    delete[] string;
                    return retval;
                }
                switch (keyword_parameter.domain) {
                    case ParameterDomain::SET:
                        for (; i < keyword_parameter.length; i++) {
                            if (value.integer == keyword_parameter.integer[i]) {
                                key_value.value.integer = value.integer;
                                break;
                            }
                        }
                        if (i == keyword_parameter.length) {
                            retval.valid = false;
                            delete[] string;
                            return retval;
                        }
                        break;
                    case ParameterDomain::RANGE:
                        if (value.integer >= keyword_parameter.integer[0] && value.integer <= keyword_parameter.integer[1]) {
                            key_value.value.integer = value.integer;
                        }
                        else {
                            retval.valid = false;
                            delete[] string;
                            return retval;
                        }
                        break;
                    case ParameterDomain::ANY:
                        key_value.value.integer = value.integer;
                        break;
                    default:
                        retval.valid = false;
                        delete[] string;
                        return retval;
                }
                break;
            case ParameterType::DECIMAL:
                value.decimal = strtod(tmp, &ptr);
                if (tmp == ptr) {
                    retval.valid = false;
                    delete[] string;
                    return retval;
                }
                switch (keyword_parameter.domain) {
                    case ParameterDomain::SET:
                        for (; i < keyword_parameter.length; i++) {
                            if (value.decimal == keyword_parameter.decimal[i]) {
                                key_value.value.decimal = value.decimal;
                                delete[] string;
                                break;
                            }
                        }
                        if (i == keyword_parameter.length) {
                            retval.valid = false;
                            delete[] string;
                            return retval;
                        }
                        break;
                    case ParameterDomain::RANGE:
                        if (value.decimal >= keyword_parameter.decimal[0] && value.decimal <= keyword_parameter.decimal[1]) {
                            key_value.value.decimal = value.decimal;
                        }
                        else {
                            retval.valid = false;
                            delete[] string;
                            return retval;
                        }
                        break;
                    case ParameterDomain::ANY:
                        key_value.value.decimal = value.decimal;
                        break;
                    default:
                        retval.valid = false;
                        delete[] string;
                        return retval;
                }
                break;
            case ParameterType::STRING:
                switch(keyword_parameter.domain) {
                    case ParameterDomain::SET:
                        for (; i < keyword_parameter.length; i++) {
                            if (strncmp(ptr, keyword_parameter.string[i], strlen(keyword_parameter.string[i])) == 0) {
                                key_value.value.string = keyword_parameter.string[i];
                                break;
                            }
                        }
                        if (i == keyword_parameter.length) {
                            retval.valid = false;
                            delete[] string;
                            return retval;
                        }
                        ptr += strlen(key_value.value.string);
                        break;
                    default:
                        retval.valid = false;
                        delete[] string;
                        return retval;
                }
                break;
            default:
                retval.valid = false;
                delete[] string;
                return retval;
        }

        // Check for CRC Next
        if (strncmp(ptr, ", ", 2) == 0) {
            ptr += 2;
        } else if (strncmp(ptr, " . ", 3) == 0) {
            end_of_message = true;
        } else {
            retval.valid = false;
            delete[] string;
            return retval;
        }

        // Add Key Value Pair to List
        key_value_pairs.push(key_value);

    } while (!end_of_message);

    // Parse Key Value Pairs
    retval.pair_count = key_value_pairs.size();
    retval.key_value_pairs = new KeyValue[retval.pair_count];
    for (unsigned int i = 0; i < retval.pair_count; i++) {
        retval.key_value_pairs[i] = key_value_pairs.pop();
    }

    // Set Checksum
    retval.checksum = expected_checksum;

    // Set Valid
    retval.valid = true;

    // Clean Up
    delete[] string;

    return retval;
}

void Telecommunication::SendTransmission(TeleMessage message) {

    const char *string = new char[TELECOM_TRANSMIT_BUFFER];
    char *ptr = (char *)string;

    // Set Target
    strncpy(ptr, DESTINATION, DESTINATION_LENGTH);
    ptr += DESTINATION_LENGTH;

    // Set Delimiter
    strncpy(ptr, COMMAND_DELIMITER, COMMAND_DELIMITER_LENGTH);
    ptr += COMMAND_DELIMITER_LENGTH;

    // Set Command
    CString command = GetCommandLiteral(message.command);
    strncpy(ptr, command, strlen(command));
    ptr += strlen(command);

    // Set Key Value Pairs
    for (unsigned int i = 0; i < message.pair_count; i++) {
        const KeyValue key_value = message.key_value_pairs[i];
        const KeywordParameter keyword_parameter = GetKeywordParameter(key_value.keyword);

        // Set Delimiter
        strncpy(ptr, KEYVALUE_DELIMITER, KEYVALUE_DELIMITER_LENGTH);
        ptr += KEYVALUE_DELIMITER_LENGTH;

        // Set Keyword
        CString literal = GetKeywordLiteral(key_value.keyword);
        strncpy(ptr, literal, strlen(literal));
        ptr += strlen(literal);
        *ptr++ = ' '; 

        // Set Value
        int pre_decimal_length = 0;
        switch (keyword_parameter.datatype) {
            case ParameterType::INTEGER:
                ptr += sprintf(ptr, "%ld", key_value.value.integer);
                break;
            case ParameterType::DECIMAL:
                pre_decimal_length = ceil(log10(key_value.value.decimal));
                dtostrf(key_value.value.decimal, pre_decimal_length + 7, 6, ptr);
                ptr += pre_decimal_length + 7;
                break;
            case ParameterType::STRING:
                strncpy(ptr, key_value.value.string, strlen(key_value.value.string));
                ptr += strlen(key_value.value.string);
                break;
            default:
                break;
        }

    }

    Checksum checksum = crc32((String)string, strlen(string));

    // Set Delimiter
    strncpy(ptr, COMMAND_DELIMITER, COMMAND_DELIMITER_LENGTH);
    ptr += COMMAND_DELIMITER_LENGTH;

    // Set Checksum
    ptr += sprintf(ptr, "CRC32 0x%08lX", checksum);

    // Set End of String
    *ptr = '\0';

    // Add to Transmit Queue
    TransmitQueue.push((String) string);
}

} // end namespace Telecommunication