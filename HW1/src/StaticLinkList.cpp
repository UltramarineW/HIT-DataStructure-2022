//
// Created by wujiayang on 2022/10/3.
//
#include "StaticLinkList.h"

#define STATIC_LIST_MAX_SIZE 20

using namespace std;


void StaticLinkListInit(StaticLinkList &list) {
    for(int i = 0; i < STATIC_LIST_MAX_SIZE - 1; i++) {
        list[i].cur = i + 1;
    }
    list[STATIC_LIST_MAX_SIZE - 1].cur = 0;
    list[0].cur = -1;
}

void StaticLinkListInsert(StaticLinkList &list, ElemType value) {
    int i = list[1].cur;
    if(list[1].cur != 0) {
        list[1].cur = list[i].cur;
    }
    if(i == 0) {
        return;
    }
    list[i].data = value;
    if (list[0].cur == -1) {
        list[i].cur = -1;
    } else {
        list[i].cur = list[0].cur;
    }
    list[0].cur = i;
}


void StaticLinkListReverse(StaticLinkList& list) {
    int i = list[0].cur;
    int j = list[i].cur;
    list[0].cur = -1;
    while(list[i].cur!= -1) {
        j = list[i].cur;
        list[i].cur = list[0].cur;
        list[0].cur = i;
        i = j;
    }
    list[i].cur = list[0].cur;
    list[0].cur = i;
}

void StaticLinkListPrint(StaticLinkList list) {
    int i = list[0].cur;
    while (i != -1) {
        cout << list[i].data << " ";
        i = list[i].cur;
    }
    cout << endl;
}
