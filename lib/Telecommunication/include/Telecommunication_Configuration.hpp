/**
 ********************************************************************************
 * @file    Telecommunication_Configuration.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Telecommunication Library Configuration
 * @version 1.0
 * @date    2024-03-22
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __TELECOMMUNICATION_CONFIGURATION_HPP__
#define __TELECOMMUNICATION_CONFIGURATION_HPP__

#include <Arduino.h>

// Serial USART Allocation
#define TC_DEBUG Serial

#define TC_USART Serial1
#define TC_BAUD_RATE 9600

// Telecommunication Settings
#define TELECOM_RECEIVE_BUFFER 256
#define TELECOM_TRANSMIT_BUFFER 256
#define TELECOM_CHECKSUM_LENGTH 19
#define TELECOM_MESSAGE_DELIMITER "\r\r\r"
#define TELECOM_RAW_ECHO_MODE false

#endif // __TELECOMMUNICATION_CONFIGURATION_HPP__