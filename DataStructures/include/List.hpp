/**
 ********************************************************************************
 * @file    List.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Doubly-Linked List
 * @version 1.0
 * @date    2024-03-20
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <stdlib.h>

namespace DataStructures {

namespace __List {

template<typename _T>
struct ListNode {
    ListNode<_T> *prev;
    ListNode<_T> *next;
    _T data;
};

} // end namespace __List

using ListSize_t = unsigned int;

template<typename T>
class List {

    using ListNode = __List::ListNode<T>;

    public:

        List();
        ~List();

        void push_front(T data);
        void push_back(T data);

        void pop_front(T& data);
        void pop_back(T& data);
        T pop_front();
        T pop_back();

        inline T& peek_front();
        inline T& peek_back();

        ListSize_t size();

        inline bool empty();

        T& operator[](ListSize_t index);
        const T& operator[](const ListSize_t index) const;

    private:

        ListNode *front;
        ListNode *back;

        ListSize_t list_size;

        T& get(ListSize_t index);
        const T& get(const ListSize_t index) const;

};

} // end namespace DataStructures

#endif // __LIST_HPP__