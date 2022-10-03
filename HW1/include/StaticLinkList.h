//
// Created by wujiayang on 2022/10/3.
//

#ifndef DATA_STRUCTURE_STATICLINKLIST_H
#define DATA_STRUCTURE_STATICLINKLIST_H

#include <iostream>
#define ElemType int
#define STATIC_LIST_MAX_SIZE 20

typedef struct StaticLinkNode{
    ElemType data;
    int cur;
}StaticLinkNode;

typedef StaticLinkNode StaticLinkList[STATIC_LIST_MAX_SIZE];


void StaticLinkListInit(StaticLinkList &list);

void StaticLinkListInsert(StaticLinkList &list, ElemType value);

void StaticLinkListReverse(StaticLinkList &list);

void StaticLinkListPrint(StaticLinkList list) ;

#endif //DATA_STRUCTURE_STATICLINKLIST_H
