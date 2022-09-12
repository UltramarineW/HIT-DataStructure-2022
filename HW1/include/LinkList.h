//
// Created by wujiayang on 2022/9/10.
//

#ifndef DATA_STRUCTURE_LINKLIST_H
#define DATA_STRUCTURE_LINKLIST_H

#define ElemType int
#include <iostream>

typedef struct LNode{
    ElemType data;
    struct LNode* next;
}LNode, *LinkList;

void LinkListInit(LinkList &L);

void LinkListInsertHead(LinkList &L, ElemType Elem);

void LinkListInsertTail(LinkList &L, ElemType Elem);

bool LinkListDeleteElem(LinkList &L, ElemType Elem);

bool LinkListDeleteRepeat(LinkList &L);

bool LinkListReverse(LinkList &L);

bool LinkListRotateRight(LinkList &L, int k);

bool LinkListRotateLeft(LinkList &L, int k);

int LinkListLength(LinkList &L);

LinkList LinkListMerge(LinkList &L1, LinkList &L2);

void LinkListPrint(LinkList &L);
#endif //DATA_STRUCTURE_LINKLIST_H
