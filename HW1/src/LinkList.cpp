//
// Created by wujiayang on 2022/9/10.
//

#include "LinkList.h"
using namespace std;

void LinkListInit(LinkList &L){
    L = new LNode;
    L -> data = 0;
    L -> next = nullptr;
}

void LinkListInsertHead(LinkList &L, ElemType Elem){
    auto s = new LNode;
    s -> data = Elem;
    s -> next = L -> next;
    L -> next = s;
}

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

bool LinkListRotateRight(LinkList &L, int k) {
    int count = 0;
    LNode *p1 = L, *p2 = L;
    while (count <= k) {
        *p1 = *p1 -> next;
        count ++;
    }


    return true;
}

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

bool LinkListMerge(LinkList &L1, LinkList &L2) {

    return true;
}

void LinkListPrint(LinkList &L) {
    LNode* pw = L;
    while (pw -> next != nullptr) {
        pw = pw -> next;
        cout << pw -> data << " " ;
    }
    cout << endl;
}
