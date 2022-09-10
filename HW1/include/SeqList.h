//
// Created by wujiayang on 2022/9/10.
//

#ifndef DATA_STRUCTURE_SEQLIST_H
#define DATA_STRUCTURE_SEQLIST_H

#define MaxLength 50
#define ElemType int

typedef struct{
    ElemType data[MaxLength] ;
    int length;
}SeqList;


void SeqInitList(SeqList &L);

void SeqInsertElem(SeqList &L, ElemType elem, int i);

int SeqLength(SeqList &L);

void SeqListDelete(SeqList &L, ElemType elem);

void SeqDeleteRepeatElem(SeqList &L);


#endif //DATA_STRUCTURE_SEQLIST_H
