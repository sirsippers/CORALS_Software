/**
 ********************************************************************************
 * @file    CORALS.cpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   CORALS Software Core
 * @version 1.0
 * @date    2024-03-24
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "CORALS.hpp"

#include <StateManager.hpp>

#include "CORALS_Configuration.hpp"

namespace CORALS {

namespace {

::StateManager::StateManager CORALS_OS;

} // end namespace

void intialize() {
    DEBUG.begin(115200);
}

void run() {
    CORALS_OS.Run();
}

} // end namespace CORALS