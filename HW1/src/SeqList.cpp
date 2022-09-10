//
// Created by wujiayang on 2022/9/9.
//

#include "SeqList.h"

/**
 * Init seqlist
 * @param L seqlist
 */
void SeqInitList(SeqList &L){
    L.length = 0;
}


void SeqInsertElem(SeqList &L, ElemType elem, int i){

}

/**
 * Return the length of seqlist
 * @param L seqlist
 * @return
 */
int SeqLength(SeqList &L){
    return L.length;
}

/**
 * Delete specific element in seqlist
 * @param L seqList
 * @param elem The specific element
 */
void SeqListDelete(SeqList &L, ElemType elem){
    int i = 0;
    while (i < L.length) {
        if (L.data[i] == elem) {
            for (int j = i; j < L.length - 1; j++) {
                L.data[j] = L.data[j + 1];
            }
            L.length = L.length - 1;
        }
        i++;
    }
}

/**
 * Delete repeated element in seqlist
 * @param L seqlist
 */
void SeqDeleteRepeatElem(SeqList &L){

}
