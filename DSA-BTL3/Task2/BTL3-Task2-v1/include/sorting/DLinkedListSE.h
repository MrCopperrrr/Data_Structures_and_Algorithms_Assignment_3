
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
        this->head = mergeSort(this->head, comparator); // Bắt đầu từ node đầu tiên
    };
    
protected:
    static int compare(T& lhs, T& rhs, int (*comparator)(T&,T&)=0){
        if(comparator != 0) return comparator(lhs, rhs);
        else{
            if(lhs < rhs) return -1;
            else if(lhs > rhs) return +1;
            else return 0;
        }
    }
private:
    // Hàm hợp nhất hai danh sách đã sắp xếp
    typename DLinkedList<T>::Node* merge(typename DLinkedList<T>::Node* left, typename DLinkedList<T>::Node* right, int (*comparator)(T&, T&)) {
        if (!left) return right;
        if (!right) return left;

        // So sánh hai phần tử đầu tiên của mỗi danh sách
        if (compare(left->data, right->data, comparator) <= 0) {
            left->next = merge(left->next, right, comparator);
            if (left->next) left->next->prev = left; // Cập nhật liên kết ngược
            left->prev = nullptr;
            return left;
        } else {
            right->next = merge(left, right->next, comparator);
            if (right->next) right->next->prev = right; // Cập nhật liên kết ngược
            right->prev = nullptr;
            return right;
        }
    }

    // Hàm thực hiện Merge Sort đệ quy
    typename DLinkedList<T>::Node* mergeSort(typename DLinkedList<T>::Node* node, int (*comparator)(T&, T&)) {
        if (!node || !node->next) return node; // Nếu chỉ có một phần tử hoặc rỗng, không cần sắp xếp

        // Tìm giữa danh sách
        typename DLinkedList<T>::Node* middle = getMiddle(node);
        typename DLinkedList<T>::Node* nextToMiddle = middle->next;

        // Tách danh sách thành hai nửa
        middle->next = nullptr;

        // Sắp xếp đệ quy
        node = mergeSort(node, comparator);
        nextToMiddle = mergeSort(nextToMiddle, comparator);

        // Hợp nhất hai danh sách đã sắp xếp
        return merge(node, nextToMiddle, comparator);
    }

    // Hàm tìm phần tử giữa của danh sách liên kết
    typename DLinkedList<T>::Node* getMiddle(typename DLinkedList<T>::Node* node) {
        if (!node) return node;

        typename DLinkedList<T>::Node* slow = node;
        typename DLinkedList<T>::Node* fast = node;

        // Sử dụng thuật toán "chạy nhanh, chạy chậm" để tìm phần tử giữa
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }
};

#endif /* DLINKEDLISTSE_H */

