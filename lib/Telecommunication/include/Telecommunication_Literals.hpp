/**
 ********************************************************************************
 * @file    Telecommunication_Literals.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   String Literals for Telecommunication
 * @version 1.0
 * @date    2024-03-22
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __TELECOMMAND_LITERALS_HPP__
#define __TELECOMMAND_LITERALS_HPP__

#include <string.h>

#include "Telecommunication_Types.hpp"

namespace Telecommunication {

const String RECEIVER = "CORALS";
const StringSize RECEIVER_LENGTH = strlen(RECEIVER);
const String DESTINATION = "DARTS";
const StringSize DESTINATION_LENGTH = strlen(DESTINATION);
const String COMMAND_DELIMITER = " . ";
const StringSize COMMAND_DELIMITER_LENGTH = strlen(COMMAND_DELIMITER);
const String KEYVALUE_DELIMITER = ", ";
const StringSize KEYVALUE_DELIMITER_LENGTH = strlen(KEYVALUE_DELIMITER);

enum class Command {
    // Telecommands
    TC_SET = 0,
    TC_ECHO,
    TC_TARGET_ADD,
    TC_HALT,
    TC_SET_POWER,
    TC_SET_INERTIA,
    TC_SET_CONTROL,
    TC_SET_SINGULARITY,
    TC_SET_ERROR,
    TC_CLEAR_ERRORS,
    // Telemetry Requests
    TR_GET,
    TR_GET_TARGET,
    TR_GET_HALT,
    TR_GET_POWER,
    TR_GET_INERTIA,
    TR_GET_CONTROL,
    TR_GET_SINGULARITY,
    TR_GET_STATE,
    TR_GET_ATTITUDE,
    TR_GET_ERROR,
    TR_GET_ERRORS,
    // Telemetry Replies
    TR_REGISTER,
    TR_ECHO_REPLY,
    TR_CURRENT_TARGET,
    TR_TARGET_LIST,
    TR_HALT_STATE,
    TR_POWER_STATE,
    TR_INERTIA_MATRIX,
    TR_CONTROL_STATE,
    TR_SINGULARITY_STATE,
    TR_CORALS_STATE,
    TR_ATTITUDE,
    TR_ERROR_STATE,
    // Other Values
    COMMAND_COUNT,
    NO_COMMAND,
    RECEIVING_COMMAND_COUNT = Command::TR_REGISTER,
};

const String CommandLiterals[(int)Command::COMMAND_COUNT] = {
    "SET",
    "ECHO",
    "TARGET_ADD",
    "HALT",
    "SET_POWER",
    "SET_INERTIA",
    "SET_CONTROL",
    "SET_SINGULARITY",
    "SET_ERROR",
    "CLEAR_ERRORS",
    "GET",
    "GET_TARGET",
    "GET_HALT",
    "GET_POWER",
    "GET_INERTIA",
    "GET_CONTROL",
    "GET_SINGULARITY",
    "GET_STATE",
    "GET_ATTITUDE",
    "GET_ERROR",
    "GET_ERRORS",
    "REGISTER",
    "ECHO_REPLY",
    "CURRENT_TARGET",
    "TARGET_LIST",
    "HALT_STATE",
    "POWER_STATE",
    "INERTIA_MATRIX",
    "CONTROL_STATE",
    "SINGULARITY_STATE",
    "CORALS_STATE",
    "ATTITUDE",
    "ERROR_STATE"
};

enum class Keyword {
    KW_ARGUMENT_ERROR = 0,
    KW_COMM_LR,
    KW_CONTROL_LR,
    KW_ENABLE_OVERRIDE,
    KW_GAIN11,
    KW_GAIN12,
    KW_GAIN13,
    KW_GAIN21,
    KW_GAIN22,
    KW_GAIN23,
    KW_GAIN31,
    KW_GAIN32,
    KW_GAIN33,
    KW_GM_MASTER_POWER,
    KW_HALT_STATUS,
    KW_Q0,
    KW_Q1,
    KW_Q2,
    KW_Q3,
    KW_Q4,
    KW_QUAT_DISAGREE_ERROR,
    KW_QUAT_FORMAT,
    KW_SINGULARITY_HALTING,
    KW_SINGULARITY_OVERRIDE_ERROR,
    KW_SINGULARITY_THOLD,
    KW_SINGULARITY_TRIP,
    KW_SM_MASTER_POWER,
    KW_TARGET_NUM,
    // Other Values
    KEYWORD_COUNT,
    NO_KEYWORD
};

enum class ParameterDomain {
    SET,
    RANGE,
    ANY
};

enum class ParameterType {
    INTEGER,
    DECIMAL,
    STRING,
};

union ValueData { // Union Pointer Conjugate defined in Telecommunication_Types.hpp
    void *any;
    long int *integer;
    double *decimal;
    const String *string;
};

struct KeywordParameter {
    const String literal;
    ParameterDomain domain;
    ParameterType datatype;
    StringSize length;
    ValueData value;
};

const String ON_LITERAL = "ON";
const String OFF_LITERAL = "OFF";
const String ON_OFF_SET[] = {ON_LITERAL, OFF_LITERAL};

const String ACTIVE_LITERAL = "ACTIVE";
const String INACTIVE_LITERAL = "INACTIVE";
const String ACTIVE_INACTIVE_SET[] = {ACTIVE_LITERAL, INACTIVE_LITERAL};

const String Q0_LITERAL = "Q0";
const String Q4_LITERAL = "Q4";
const String QUAT_FORMAT_SET[] = {Q0_LITERAL, Q4_LITERAL};

double NORM_RANGE[] = {0.0, 1.0};

const KeywordParameter KeywordParameters[(int)Keyword::KEYWORD_COUNT] = {
    {"ARGUMENT_ERROR",             ParameterDomain::SET,   ParameterType::STRING,  2, .value.string  = ON_OFF_SET},
    {"COMM_LR",                    ParameterDomain::ANY,   ParameterType::DECIMAL, 0, .value.any     = NULL},
    {"CONTROL_LR",                 ParameterDomain::ANY,   ParameterType::DECIMAL, 0, .value.any     = NULL},
    {"ENABLE_OVERRIDE",            ParameterDomain::SET,   ParameterType::STRING,  2, .value.string  = ON_OFF_SET},
    {"GAIN11",                     ParameterDomain::ANY,   ParameterType::DECIMAL, 0, .value.any     = NULL},
    {"GAIN12",                     ParameterDomain::ANY,   ParameterType::DECIMAL, 0, .value.any     = NULL},
    {"GAIN13",                     ParameterDomain::ANY,   ParameterType::DECIMAL, 0, .value.any     = NULL},
    {"GAIN21",                     ParameterDomain::ANY,   ParameterType::DECIMAL, 0, .value.any     = NULL},
    {"GAIN22",                     ParameterDomain::ANY,   ParameterType::DECIMAL, 0, .value.any     = NULL},
    {"GAIN23",                     ParameterDomain::ANY,   ParameterType::DECIMAL, 0, .value.any     = NULL},
    {"GAIN31",                     ParameterDomain::ANY,   ParameterType::DECIMAL, 0, .value.any     = NULL},
    {"GAIN32",                     ParameterDomain::ANY,   ParameterType::DECIMAL, 0, .value.any     = NULL},
    {"GAIN33",                     ParameterDomain::ANY,   ParameterType::DECIMAL, 0, .value.any     = NULL},
    {"GM_MASTER_POWER",            ParameterDomain::SET,   ParameterType::STRING,  2, .value.string  = ON_OFF_SET},
    {"HALT_STATUS",                ParameterDomain::SET,   ParameterType::STRING,  2, .value.string  = ACTIVE_INACTIVE_SET},
    {"Q0",                         ParameterDomain::RANGE, ParameterType::DECIMAL, 0, .value.decimal = NORM_RANGE},
    {"Q1",                         ParameterDomain::RANGE, ParameterType::DECIMAL, 0, .value.decimal = NORM_RANGE},
    {"Q2",                         ParameterDomain::RANGE, ParameterType::DECIMAL, 0, .value.decimal = NORM_RANGE},
    {"Q3",                         ParameterDomain::RANGE, ParameterType::DECIMAL, 0, .value.decimal = NORM_RANGE},
    {"Q4",                         ParameterDomain::RANGE, ParameterType::DECIMAL, 0, .value.decimal = NORM_RANGE},
    {"QUAT_DISAGREE_ERROR",        ParameterDomain::SET,   ParameterType::STRING,  2, .value.string  = ON_OFF_SET},
    {"QUAT_FORMAT",                ParameterDomain::SET,   ParameterType::STRING,  2, .value.string  = QUAT_FORMAT_SET},
    {"SINGULARITY_HALTING",        ParameterDomain::SET,   ParameterType::STRING,  2, .value.string  = ON_OFF_SET},
    {"SINGULARITY_OVERRIDE_ERROR", ParameterDomain::SET,   ParameterType::STRING,  2, .value.string  = ON_OFF_SET},
    {"SINGULARITY_THOLD",          ParameterDomain::RANGE, ParameterType::DECIMAL, 0, .value.decimal = NORM_RANGE},
    {"SINGULARITY_TRIP",           ParameterDomain::SET,   ParameterType::STRING,  2, .value.string  = ACTIVE_INACTIVE_SET},
    {"SM_MASTER_POWER",            ParameterDomain::SET,   ParameterType::STRING,  2, .value.string  = ON_OFF_SET},
    {"TARGET_NUM",                 ParameterDomain::ANY,   ParameterType::INTEGER, 0, .value.any     = NULL}
};

} // end namespace Telecommunication

#endif // __TELECOMMAND_LITERALS_HPP__