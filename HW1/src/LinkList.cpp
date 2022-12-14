//
// Created by wujiayang on 2022/9/10.
//

#include "LinkList.h"
using namespace std;

/**
 * Init the list list
 * @param L
 */
void LinkListInit(LinkList &L){
    L = new LNode;
    L -> data = 0;
    L -> next = nullptr;
}

/**
 * Insert element to link list head
 * @param L
 * @param Elem
 */

void LinkListInsertHead(LinkList &L, ElemType Elem){
    auto s = new LNode;
    s -> data = Elem;
    s -> next = L -> next;
    L -> next = s;
}


/**
 * Insert element to the linkl list tail
 * @param L
 * @param Elem
 */
void LinkListInsertTail(LinkList &L, ElemType Elem){
    // 建立工作指针
    LNode* pw = L;
    while(pw -> next != nullptr){
        pw = pw -> next;
    }
    auto s = new LNode;
    s -> data = Elem;
    s -> next = nullptr;
    pw -> next = s;
}

/**
 * Delete specific element in the link list
 * @param L
 * @param Elem
 * @return
 */
bool LinkListDeleteElem(LinkList &L, ElemType Elem){
    LNode* pw = L;
    while(pw -> next != nullptr) {
        if (pw -> next -> data == Elem) {
            LNode* pwn = pw -> next;
            pw -> next = pwn -> next;
            delete pwn;
        }
        if (pw -> next == nullptr) {
            break;
        }
        pw = pw -> next;
    }
    return true;
}

/**
 * Delete repeated element in the link list
 * @param L
 * @return
 */
bool LinkListDeleteRepeat(LinkList &L){
    LNode* pw = L;
    if (pw -> next != nullptr) {
        pw = pw -> next;
    } else {
        return false;
    }

    while(pw -> next != nullptr) {
        if (pw -> data == pw -> next -> data) {
            LNode* pwn = pw -> next;
            pw -> next = pwn ->next;
            delete pwn;
        }
        if (pw -> next == nullptr) {
            break;
        }
        pw = pw -> next;
    }
    return true;
}

/**
 * Reverse the linklist
 * @param L
 * @return
 */
bool LinkListReverse(LinkList &L) {
    LNode *pw = L;
    if (pw -> next == nullptr) {
        return false;
    }
    LNode *pwn = nullptr;
    pw = pw -> next;
    L -> next = nullptr;
    while(pw != nullptr) {
        pwn = pw -> next;
        pw -> next = L->next;
        L -> next = pw;
        pw = pwn;
    }
    return true;
}

/**
 * Rotate the link list k length to the right
 * @param L
 * @param k
 * @return
 */
bool LinkListRotateRight(LinkList &L, int k) {
    int count = 0;
    int length = LinkListLength(L);
    k = k % length;

    LNode *p1 = L, *p2 = L;
    while (count < k) {
        p1 = p1 -> next;
        count ++;
    }
    while(p1 -> next != nullptr) {
        p1 = p1 -> next;
        p2 = p2 -> next;
    }
    p1 -> next = L -> next;
    L -> next = p2 -> next;
    p2 -> next = nullptr;
    return true;
}

/**
 * Rotate the link list k length to the left
 * @param L
 * @param k
 * @return
 */
bool LinkListRotateLeft(LinkList &L, int k) {
    int length = LinkListLength(L);
    k = k % length;
    LNode *p1 = L, *p2 = L -> next, *p3 = L;
    while (p3 -> next != nullptr) {
        p3 = p3 -> next;
    }
    for (int i = 0; i < k; i++) {
        p1 = p1 -> next;
    }
    L -> next = p1 -> next;
    p1 -> next = nullptr;
    p3 -> next = p2;
}

/**
 * Compute the length of link list
 * @param L
 * @return
 */
int LinkListLength(LinkList &L) {
    int count = 0;
    LNode *pw = L;
    pw = pw -> next;
    while (pw != nullptr) {
        count ++;
        pw = pw -> next;
    }
    return count;
}

/**
 * Merge two sorted link lists
 * @param L1
 * @param L2
 * @return
 */
LinkList LinkListMerge(LinkList &L1, LinkList &L2) {
    auto L3 = new LNode;
    L3 -> next = nullptr;
    LNode *p1 = L1, *p2 = L2, *p3 = L3;
    p1 = p1 ->next, p2 = p2 -> next;
    while(p1 != nullptr && p2 != nullptr){
        p3 -> next = new LNode;
        p3 = p3 -> next;
        p3 -> next = nullptr;
        if (p1 -> data <= p2 -> data) {
            p3 -> data = p1 -> data;
            p1 = p1 -> next;
        } else {
            p3 -> data = p2 -> data;
            p2 = p2 -> next;
        }
    }
    if (p1 != nullptr) {
        while(p1 != nullptr) {
            p3 -> next = new LNode;
            p3 = p3 -> next;
            p3 ->next = nullptr;
            p3 -> data = p1 -> data;
            p1 = p1 -> next;
        }
    }
    if (p2 != nullptr) {
        while(p2 != nullptr) {
            p3 -> next = new LNode;
            p3 = p3 -> next;
            p3 ->next = nullptr;
            p3 -> data = p2 -> data;
            p2 = p2 -> next;
        }
    }
    return L3;
}

/**
 * Show all element in the link list
 * @param L
 */
void LinkListPrint(LinkList &L) {
    LNode* pw = L;
    while (pw -> next != nullptr) {
        pw = pw -> next;
        cout << pw -> data << " " ;
    }
    cout << endl;
}
