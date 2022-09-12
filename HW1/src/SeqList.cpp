//
// Created by wujiayang on 2022/9/9.
//

#include "SeqList.h"
using namespace std;

/**
 * Init seqlist
 * @param L seqlist
 */
void SeqInitList(SeqList &L){
    L.length = 0;
}

/**
 * Insert element in the position i
 * @param L seqlist
 * @param elem element to insert
 * @param i position where element to insert
 * @return
 */
bool SeqInsertElem(SeqList &L, ElemType elem, int i){
    if (i < 1 || i > L.length + 1)
        return false;
    if (L.length >= MaxLength)
        return false;
    for (int j = L.length; j >= i; j--) {
        L.data[j] = L.data[j - 1];
    }
    L.data[i - 1] = elem;
    L.length++;
    return true;
}

void SeqPrintElem(SeqList &L) {
    for (int i = 0; i < L.length; i++) {
        cout <<  L.data[i] << " ";
    }
    cout << endl;
}

/**
 * Return the length of seqlist
 * @param L seqlist
 * @return Length of seqlist
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
bool SeqDeleteRepeatElem(SeqList &L){
    if (L.length == 0) {
        return false;
    }
    int i, j;
    for (i = 0, j = 1; j < L.length; j++) {
        if (L.data[i] != L.data[j]) {
            i++;
            L.data[i] = L.data[j];
        }
    }
    L.length = i + 1;
    return true;
}

/**
 * Reverse seqlist
 * @param L seqlist to reverse
 * @return status
 */
bool SeqReverse(SeqList &L) {
    if (L.length == 0) {
        return false;
    }
    int i = 0, j = L.length - 1;
    ElemType temp = 0;
    while (i < j) {
        temp = L.data[i];
        L.data[i] = L.data[j];
        L.data[j] = temp;
        i++, j--;
    }
    return true;
}

/**
 * The Sequence rotate to the right by k
 * @param L seqlist
 * @param k number to rotate
 * @return
 */
bool SeqRotateRight(SeqList &L, int k){
    if (L.length == 0) {
        return false;
    }
    for (int i = 0; i < k; i++) {
        ElemType temp = L.data[L.length - 1];
        for (int j = L.length - 1; j > 0; j--) {
            L.data[j] = L.data[j - 1];
        }
        L.data[0] = temp;
    }
    return true;
}

SeqList SeqMerge(SeqList &L1, SeqList &L2){
    int i = 0, j = 0, k = 0;
    SeqList retList;
    SeqInitList(retList);
    if (L1.length + L2.length > MaxLength) {
        cout << "Return list out of range, please modify MaxLength" << endl;
        exit(0);
    }

    while (i < L1.length && j < L2.length) {
        if (L1.data[i] <= L2.data[j]) {
            retList.data[k] = L1.data[i];
            i++, k++;
        } else {
            retList.data[k] = L2.data[j];
            j++, k++;
        }
    }
    if (i < L1.length) {
        for (;i < L1.length; i++, k++) {
            retList.data[k] = L1.data[i];
        }
    }
    if(j < L2.length) {
        for (; j < L2.length; j++, k++) {
            retList.data[k] = L2.data[j];
        }
    }
    retList.length = L1.length + L2.length;
    return retList;
}


