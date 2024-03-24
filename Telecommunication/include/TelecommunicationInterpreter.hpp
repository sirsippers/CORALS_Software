/**
 ********************************************************************************
 * @file    TelecommunicationInterpreter.hpp
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

#include "GlobalConfiguration.hpp"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Telecommunication.hpp"
#include "TelecommunicationDecoding.hpp"
#include "TelecommunicationLiterals.hpp"

namespace CORALS {

union Value {
    long int integer;
    double decimal;
    const char *string;
};

struct KeyValue {
    Keyword_t keyword;
    ParameterType_t type;
    Value value;
};

struct TeleMessage {
    Command_t command;
    KeyValue *key_value_pairs;
    uint8_t pair_count;
    uint32_t checksum;
    bool valid;
};

class TelecommunicationInterpreter {

public:
    TelecommunicationInterpreter() {};
    TelecommunicationInterpreter(const Command_t command, Keyword_t *keywords, unsigned int keyword_count) {
        this->command = command;
        this->keywords = keywords;
        this->keyword_count = keyword_count;
    }
    ~TelecommunicationInterpreter() {}
    
    TeleMessage GetReception() {
        using namespace Decoding;

        TeleMessage retval;

        // Get Message from Queue
        const char *string = TELECOM.ReceiveQueue.pop_front();
        char *ptr = (char *)string;
        unsigned int length = strlen(string);
        uint32_t expected_checksum = crc32((uint8_t *)string, length-TELECOM_CHECKSUM_LENGTH);
        
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
        if (retval.command == NO_COMMAND) {
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
        DataStructures::List<KeyValue> key_value_pairs;
        do {
            // Get Keyword
            KeyValue key_value;
            key_value.keyword = GetKeyword(ptr);
            if (key_value.keyword == NO_KEYWORD) {
                retval.valid = false;
                delete[] string;
                return retval;
            }

            // Get Value
            key_value.type = KeywordParameters[key_value.keyword].datatype;
            char *tmp = ptr;
            switch (key_value.type) {
                case INTEGER:
                    long int integer = strtol(tmp, &ptr, 10);
                    if (tmp == ptr) {
                        retval.valid = false;
                        delete[] string;
                        return retval;
                    }
                    switch (KeywordParameters[key_value.keyword].domain) {
                        case SET:
                            unsigned int i = 0;
                            for (; i < KeywordParameters[key_value.keyword].length; i++) {
                                if (integer == KeywordParameters[key_value.keyword].value.integer[i]) {
                                    key_value.value.integer = integer;
                                    break;
                                }
                            }
                            if (i == KeywordParameters[key_value.keyword].length) {
                                retval.valid = false;
                                delete[] string;
                                return retval;
                            }
                            break;
                        case RANGE:
                            if (integer >= KeywordParameters[key_value.keyword].value.integer[0] && integer <= KeywordParameters[key_value.keyword].value.integer[1]) {
                                key_value.value.integer = integer;
                            }
                            else {
                                retval.valid = false;
                                delete[] string;
                                return retval;
                            }
                            break;
                        case ANY:
                            key_value.value.integer = integer;
                            break;
                        default:
                            retval.valid = false;
                            delete[] string;
                            return retval;
                    }
                    break;
                case DECIMAL:
                    double decimal = strtod(tmp, &ptr);
                    if (tmp == ptr) {
                        retval.valid = false;
                        delete[] string;
                        return retval;
                    }
                    switch (KeywordParameters[key_value.keyword].domain) {
                        case SET:
                            unsigned int i = 0;
                            for (; i < KeywordParameters[key_value.keyword].length; i++) {
                                if (decimal == KeywordParameters[key_value.keyword].value.decimal[i]) {
                                    key_value.value.decimal = decimal;
                                    delete[] string;
                                    break;
                                }
                            }
                            if (i == KeywordParameters[key_value.keyword].length) {
                                retval.valid = false;
                                delete[] string;
                                return retval;
                            }
                            break;
                        case RANGE:
                            if (decimal >= KeywordParameters[key_value.keyword].value.decimal[0] && decimal <= KeywordParameters[key_value.keyword].value.decimal[1]) {
                                key_value.value.decimal = decimal;
                            }
                            else {
                                retval.valid = false;
                                delete[] string;
                                return retval;
                            }
                            break;
                        case ANY:
                            key_value.value.decimal = decimal;
                            break;
                        default:
                            retval.valid = false;
                            delete[] string;
                            return retval;
                    }
                    break;
                case STRING:
                    switch(KeywordParameters[key_value.keyword].domain) {
                        case SET:
                            unsigned int i = 0;
                            for (; i < KeywordParameters[key_value.keyword].length; i++) {
                                if (strncmp(ptr, KeywordParameters[key_value.keyword].value.string[i], strlen(KeywordParameters[key_value.keyword].value.string[i])) == 0) {
                                    key_value.value.string = KeywordParameters[key_value.keyword].value.string[i];
                                    break;
                                }
                            }
                            if (i == KeywordParameters[key_value.keyword].length) {
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
            key_value_pairs.push_back(key_value);

        } while (!end_of_message);

        // Parse Key Value Pairs
        retval.pair_count = key_value_pairs.size();
        retval.key_value_pairs = new KeyValue[retval.pair_count];
        for (unsigned int i = 0; i < retval.pair_count; i++) {
            retval.key_value_pairs[i] = key_value_pairs.pop_front();
        }

        // Set Checksum
        retval.checksum = expected_checksum;

        // Set Valid
        retval.valid = true;

        // Clean Up
        delete[] string;

        return retval;
    }

    void SendTransmission(TeleMessage message) {

        const char *string = new char[TELECOM_TRANSMIT_BUFFER];
        char *ptr = (char *)string;

        // Set Target
        strncpy(ptr, DESTINATION, DESTINATION_LENGTH);
        ptr += DESTINATION_LENGTH;

        // Set Delimiter
        strncpy(ptr, COMMAND_DELIMITER, COMMAND_DELIMITER_LENGTH);
        ptr += COMMAND_DELIMITER_LENGTH;

        // Set Command
        strncpy(ptr, CommandLiterals[message.command], strlen(CommandLiterals[message.command]));
        ptr += strlen(CommandLiterals[message.command]);

        // Set Key Value Pairs
        for (unsigned int i = 0; i < message.pair_count; i++) {

            // Set Delimiter
            strncpy(ptr, KEYVALUE_DELIMITER, KEYVALUE_DELIMITER_LENGTH);
            ptr += KEYVALUE_DELIMITER_LENGTH;

            // Set Keyword
            strncpy(ptr, KeywordParameters[message.key_value_pairs[i].keyword].literal, 
                         strlen(KeywordParameters[message.key_value_pairs[i].keyword].literal));
            ptr += strlen(KeywordParameters[message.key_value_pairs[i].keyword].literal);
            *ptr++ = ' '; 

            // Set Value
            switch (KeywordParameters[message.key_value_pairs[i].keyword].datatype) {
                case INTEGER:
                    ptr += sprintf(ptr, "%d", message.key_value_pairs[i].value.integer);
                    break;
                case DECIMAL:
                    int pre_decimal_length = ceil(log10(message.key_value_pairs[i].value.decimal));
                    dtostrf(message.key_value_pairs[i].value.decimal, pre_decimal_length + 7, 6, ptr);
                    ptr += pre_decimal_length + 7;
                    break;
                case STRING:
                    strncpy(ptr, message.key_value_pairs[i].value.string, strlen(message.key_value_pairs[i].value.string));
                    ptr += strlen(message.key_value_pairs[i].value.string);
                    break;
                default:
                    break;
            }

        }

        uint32_t checksum = crc32((uint8_t *)string, strlen(string));

        // Set Delimiter
        strncpy(ptr, COMMAND_DELIMITER, COMMAND_DELIMITER_LENGTH);
        ptr += COMMAND_DELIMITER_LENGTH;

        // Set Checksum
        ptr += sprintf(ptr, "CRC32 0x%08X", checksum);

        // Set End of String
        *ptr = '\0';

        // Add to Transmit Queue
        TELECOM.TransmitQueue.push_back(string);
    }

private:
    Command_t command;
    Keyword_t *keywords;
    unsigned int keyword_count;

};

} // end namespace CORALS

#endif // __TELECOMMUNICATION_INTERPRETER_HPP__