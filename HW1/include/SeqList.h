//
// Created by wujiayang on 2022/9/10.
//

#ifndef DATA_STRUCTURE_SEQLIST_H
#define DATA_STRUCTURE_SEQLIST_H

#include <iostream>

#define MaxLength 50
#define ElemType int

typedef struct{
    ElemType data[MaxLength] ;
    int length;
}SeqList;


void SeqInitList(SeqList &L);

bool SeqInsertElem(SeqList &L, ElemType elem, int i);

void SeqPrintElem(SeqList &L);

int SeqLength(SeqList &L);

void SeqListDelete(SeqList &L, ElemType elem);

bool SeqDeleteRepeatElem(SeqList &L);

bool SeqReverse(SeqList &L);

bool SeqRotateRight(SeqList &L, int k);


SeqList SeqMerge(SeqList &L1, SeqList &L2);

#endif //DATA_STRUCTURE_SEQLIST_H
