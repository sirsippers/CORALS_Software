/**
 ********************************************************************************
 * @file    Queue.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Queue
 * @version 1.0
 * @date    2024-03-20
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__

#include <stdlib.h>

namespace DataStructures {

namespace __Queue {

template<typename _T>
struct QueueNode {
    QueueNode<_T> *next;
    _T data;
};

} // end namespace __Queue

using QueueSize_t = unsigned int;

template<typename T>
class Queue {

    using QueueNode = __Queue::QueueNode<T>;

    public:

        Queue();
        ~Queue();

        void push(T data);
        void pop(T& data);
        inline T pop();
        inline T& peek();

        inline QueueSize_t size();
        inline bool empty();

    private:

        QueueNode *head;
        QueueSize_t queue_size;

};

} // end namespace DataStructures

#endif // __LIST_HPP__