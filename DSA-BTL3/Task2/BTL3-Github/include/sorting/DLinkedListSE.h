/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DLinkedListSE.h
 * Author: LTSACH
 *
 * Created on 31 August 2020, 14:13
 */

#ifndef DLINKEDLISTSE_H
#define DLINKEDLISTSE_H
#include "list/DLinkedList.h"
#include "sorting/ISort.h"

template<class T>
class DLinkedListSE: public DLinkedList<T>{
public:
    
    DLinkedListSE(
            void (*removeData)(DLinkedList<T>*)=0, 
            bool (*itemEQ)(T&, T&)=0 ) : 
            DLinkedList<T>(removeData, itemEQ){
        
    };
    
    DLinkedListSE(const DLinkedList<T>& list){
        this->copyFrom(list);
    }
    
    void sort(int (*comparator)(T&,T&)=0){
        //TODO: implement this function
        //     - You should implement the merge sort algorithm
        if (this->count > 1){
            typename DLinkedList<T>::Node* temp = mergesort(this->begin(), this->count, comparator);
            this->head->next = temp;
            temp->next = this->head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            this->tail->prev = temp;
            temp->next = this->tail;
        }
    };
private:
    Node* merge(Node* left, int leftsize, Node* right, int rightsize, int (*comparator)(T&,T&)=0){
        typename DLinkedList<T>::Node dummy;
        typename DLinkedList<T>::Node* temp = &dummy;

        while (leftsize > 0 && rightsize > 0) {
            if (comparator(left->data, right->data) <= 0) {
                temp->next = left;
                left->prev = temp;
                left = left->next;
                --leftsize;
            } 
            else {
                temp->next = right;
                right->prev = temp;
                right = right->next;
                --rightsize;
            }
            temp = temp->next;
        }

        // Append remaining nodes
        while (leftsize > 0) {
            temp->next = left;
            left->prev = temp;
            left = left->next;
            --leftsize;
            temp = temp->next;
        }
        while (rightsize > 0) {
            temp->next = right;
            right->prev = temp;
            right = right->next;
            --rightsize;
            temp = temp->next;
        }

        dummy.next->prev = nullptr;
        return dummy.next;
    }
    Node* mergesort(Node* node, int size, int (*comparator)(T&,T&)=0){
        
        if (size == 1) {
            node->next = nullptr;
            return node;
        }

        // Split the list into two halves
        int mid = size / 2;
        typename DLinkedList<T>::Node* midNode = node;
        for (int i = 0; i < mid - 1; ++i) {
            midNode = midNode->next;
        }
        typename DLinkedList<T>::Node* right = midNode->next;
        midNode->next = nullptr;

        typename DLinkedList<T>::Node* leftSorted = mergeSort(node, mid, comparator);
        typename DLinkedList<T>::Node* rightSorted = mergeSort(right, size - mid, comparator);

        return merge(leftSorted, mid, rightSorted, size - mid, comparator);
    }
    
protected:
    static int compare(T& lhs, T& rhs, int (*comparator)(T&,T&)=0){
        if(comparator != 0) return comparator(lhs, rhs);
        else{
            if(lhs < rhs) return -1;
            else if(lhs > rhs) return +1;
            else return 0;
        }
    }
};

#endif /* DLINKEDLISTSE_H */

