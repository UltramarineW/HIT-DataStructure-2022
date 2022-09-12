#include <iostream>
#include "SeqList.h"
#include "LinkList.h"

using namespace std;


int main(int argc, char* argv[]){
    cout << "Sequence List Test" << endl;
    SeqList List;

    SeqInitList(List);
    for (int i = 0; i < 5; i++) {
        SeqInsertElem(List, i + 1, i + 1);
    }
    SeqInsertElem(List, 5, List.length + 1);

    SeqDeleteRepeatElem(List);

    SeqList List2;
    SeqInitList(List2);
    for (int i = 2; i < 7;i++){
        SeqInsertElem(List2, i + 1, i - 1);
    }
    SeqList MergedList = SeqMerge(List, List2);
//    SeqListDelete(List, 3);
//    SeqReverse(List);
//    SeqRotateRight(List, 1);

    cout << "SeqLength: " << SeqLength(List) << endl;
    SeqPrintElem(List);
    SeqPrintElem(List2);
    SeqPrintElem(MergedList);

    cout << endl;
    cout << "Link List Test" << endl;

    LinkList TestLinklist;
    LinkListInit(TestLinklist);
    for (int i = 0; i < 10; i++) {
        LinkListInsertTail(TestLinklist, i + 1);
    }
    LinkListInsertTail(TestLinklist, 10);
    LinkListDeleteRepeat(TestLinklist);
    LinkListDeleteElem(TestLinklist, 5);
    LinkListReverse(TestLinklist);

    LinkListPrint(TestLinklist);
    cout << "The length of link list: " << LinkListLength(TestLinklist) << endl;

    return 0;
}
