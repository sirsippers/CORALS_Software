/**
 ********************************************************************************
 * @file    Controls_Classes.hpp
 * @author  Vincent Lam (g.vincentlam@gmail.com)
 * @brief   CORALS Configuration for Arduino MEGA 2560
 * @version 1.0
 * @date    2024-03-27
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef CONTROLS_CLASSES_HPP
#define CONTROLS_CLASSES_HPP

#include <vector>
#include <iostream>
#include <math.h>

namespace Vector

template <typename T>
class Vector {
    private:
        T* elements;
        size_t len;
    public:
        // Allocate Memory for Vector
        Vector(size_t len): size(len) {
            elements = new T[len];
        }
        // Overload [] for Modification
        T& operator[](size_t index) {
            return elements[index];
        } // Implement in Matrix Class Instead? Want to minimize operations done
        // Return Size
        size_t getSize() const {
            return len;
        }
}

class Matrix {

}

class Tensor {

}

#endif 