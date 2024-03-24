/**
 ********************************************************************************
 * @file    List.cpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Doubly-Linked List
 * @version 1.0
 * @date    2024-03-20
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "List.hpp"

#include <stdlib.h>

namespace DataStructures {

template<typename T>
List<T>::List() {
    front = NULL;
    back = NULL;
    list_size = 0;
}

template<typename T>
List<T>::~List() {
    T temp;
    while (list_size > 0) pop_front(temp);
}

template<typename T>
void List<T>::push_front(T data) {
    if (list_size == 0) {
        front = back = new ListNode;
        front->data = data;
        front->prev = NULL;
        front->next = NULL;
    }
    else {
        front->prev = new ListNode;
        front = front->prev;
        front->data = data;
        front->prev = NULL;
    }
    list_size++;
}
        
template<typename T>
void List<T>::push_back(T data) {
    if (list_size == 0) {
        front = back = new ListNode;
        back->data = data;
        back->prev = NULL;
        back->next = NULL;
    }
    else {
        back->next = new ListNode;
        back = back->next;
        back->data = data;
        back->next = NULL;
    }
    list_size++;
}

template<typename T>
void List<T>::pop_front(T& data) {
    if (list_size == 0) return;
    data = front->data;
    list_size--;
    if (list_size == 0) {
        delete front;
        front = NULL;
        back = NULL;
    }
    else {
        front = front->next;
        delete front->prev;
        front->prev = NULL;
    }
}

template<typename T>
void List<T>::pop_back(T& data) {
    if (list_size == 0) return;
    data = back->data;
    list_size--;
    if (list_size == 0) {
        delete back;
        front = NULL;
        back = NULL;
    }
    else {
        back = back->prev;
        delete back->next;
        back->next = NULL;
    }
}
        
template<typename T>
inline T List<T>::pop_front() {
    T data;
    pop_front(data);
    return data;
}

template<typename T>
inline T List<T>::pop_back() {
    T data;
    pop_back(data);
    return data;
}

template<typename T>
inline T& List<T>::peek_front() { return this->front->data; }
template<typename T>
inline T& List<T>::peek_back() { return this->back->data; }

template<typename T>
inline ListSize_t List<T>::size() { return this->list_size; }

template<typename T>
inline T& List<T>::operator[](ListSize_t index) {
    ListNode *ptr = front;
    for (ListSize_t i = 0; i < index; i++) ptr = ptr->next;
    return ptr->data;
}

template<typename T>
inline const T& List<T>::operator[](const ListSize_t index) const {
    ListNode *ptr = front;
    for (ListSize_t i = 0; i < index; i++) ptr = ptr->next;
    return ptr->data;
}

template<typename T>
inline bool List<T>::empty() { return list_size == 0; }

} // end namespace DataStructures