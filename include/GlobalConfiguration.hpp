/**
 ********************************************************************************
 * @file    GlobalConfiguration.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Configuration for Arduino MEGA 2560
 * @version 1.0
 * @date    2024-03-20
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __GLOBAL_CONFIGURATION_HPP__
#define __GLOBAL_CONFIGURATION_HPP__

#include <Arduino.h>

// Serial USART Allocation
#define DEBUG Serial
#define HC05  Serial1

// Module Names
#define TELECOM CORALS_Telecommunication

// Telecommunication Settings
#define TELECOM_RECEIVE_BUFFER 256
#define TELECOM_TRANSMIT_BUFFER 256
#define TELECOM_CHECKSUM_LENGTH 19
#define TELECOM_RAW_ECHO_MODE false

#endif // __GLOBAL_CONFIGURATION_HPP__