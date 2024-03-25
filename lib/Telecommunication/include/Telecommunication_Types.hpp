/**
 ********************************************************************************
 * @file    Telecommunication_Types.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Base Types for Telecommunication
 * @version 1.0
 * @date    2024-03-22
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __TELECOMMUNICATION_TYPES_HPP__
#define __TELECOMMUNICATION_TYPES_HPP__

#include <stdint.h>

namespace Telecommunication {

using Checksum = uint32_t;
using String = char*;
using StringSize = uint32_t;

union Value { // Union Pointer Conjugate defined in Telecommunication_Literals.hpp
    long int integer;
    double decimal;
    const char *string;
};

struct KeyValue {
    Keyword keyword;
    ParameterType type;
    Value value;
};

struct TeleMessage {
    Command command;
    KeyValue *key_value_pairs;
    uint8_t pair_count;
    uint32_t checksum;
    bool valid;
};

} // end namespace Telecommunication

#endif // __TELECOMMUNICATION_TYPES_HPP__