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

#include "Queue.hpp"

namespace DataStructures {

template<typename T>
Queue<T>::Queue() {
    head = NULL;
    queue_size = 0;
}

template<typename T>
Queue<T>::~Queue() {
    T temp;
    while (queue_size > 0) pop_front(temp);
}
template<typename T>
void Queue<T>::push(T data) {
    if (queue_size == 0) {
        head = new QueueNode;
        head->data = data;
        head->next = head;
    }
    else {
        QueueNode *new_node = new QueueNode; 
        new_node->data = data;
        new_node->next = head->next;
        head->next = new_node;
        head = new_node; 
    }
    list_size++;
}

template<typename T>
void Queue<T>::pop(T& data) {
    if (queue_size == 0) return;
    data = head->next->data;
    queue_size--;
    if (queue_size == 0) {
        delete head;
        head = NULL;
    }
    else {
        QueueNode *rm = head->next;
        head->next = rm->next;
        delete rm;
    }
}

template<typename T>        
inline T Queue<T>::pop() {
    T data;
    pop_front(data);
    return data;
}

template<typename T>
inline T& Queue<T>::peek() { return this->head->next->data; }

template<typename T>
inline QueueSize_t Queue<T>::size() { return this->queue_size; }

template<typename T>
inline bool Queue<T>::empty() { return queue_size == 0; }

} // end namespace DataStructures