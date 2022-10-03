#include <iostream>
#include "SeqList.h"
#include "LinkList.h"
#include "StaticLinkList.h"


using namespace std;


int main(int argc, char* argv[]){
    cout << "Sequence List Test" << endl;
    SeqList List;

    cout << "初始化线性表: 1 2 3 4 5" << endl;
    SeqInitList(List);
    for (int i = 0; i < 5; i++) {
        SeqInsertElem(List, i + 1, i + 1);
    }
    SeqPrintElem(List);
    cout << "在线性表的末尾添加元素 5" <<endl;
    SeqInsertElem(List, 5, List.length + 1);
    SeqPrintElem(List);


    cout << "删除重复的元素" <<endl;
    SeqDeleteRepeatElem(List);
    SeqPrintElem(List);

    cout << "删除指定的元素 3" << endl;
    SeqListDelete(List, 3);
    SeqPrintElem(List);

    cout << "线性表逆置" <<endl;
    SeqReverse(List);
    SeqPrintElem(List);

    cout << "线性表右移k位" << endl;
    SeqRotateRight(List, 2);
    SeqPrintElem(List);

    cout << "合并两个排序好的线性表" <<endl;
    SeqList List1;
    SeqList List2;
    SeqInitList(List1);
    SeqInitList(List2);
    for (int i = 0; i < 5; i++) {
        SeqInsertElem(List1, i + 1, i + 1);
    }
    for (int i = 2; i < 7;i++){
        SeqInsertElem(List2, i + 1, i - 1);
    }
    SeqList MergedList = SeqMerge(List1, List2);

    SeqPrintElem(List1);
    SeqPrintElem(List2);
    SeqPrintElem(MergedList);

    cout << endl;
    cout << "Link List Test" << endl;

    cout << "初始化链表 1 2 3 4 5 6 7 8 9 10" <<endl;

    cout << "合并两个链表" << endl;
    LinkList TestLinklist;
    LinkList TestLinklist2;
    LinkListInit(TestLinklist);
    LinkListInit(TestLinklist2);
    for (int i = 0; i < 10; i++) {
        LinkListInsertTail(TestLinklist, i + 1);
        LinkListInsertTail(TestLinklist2, i + 3);
    }
    LinkList L3 = LinkListMerge(TestLinklist, TestLinklist2);
    LinkListPrint(TestLinklist);
    LinkListPrint(TestLinklist2);
    LinkListPrint(L3);

    cout << "在链表的尾部添加元素 10" <<endl;
    LinkListInsertTail(TestLinklist, 10);
    LinkListPrint(TestLinklist);

    cout << "删除链表中的重复元素" << endl;
    LinkListDeleteRepeat(TestLinklist);
    LinkListPrint(TestLinklist);

    cout <<"删除指定的元素 5 " << endl;
    LinkListDeleteElem(TestLinklist, 5);
    LinkListPrint(TestLinklist);

    cout <<"链表转置"<< endl;
    LinkListReverse(TestLinklist);
    LinkListPrint(TestLinklist);

    cout << "链表右移25位" << endl;
    LinkListRotateRight(TestLinklist, 25);
    LinkListPrint(TestLinklist);

    cout << "链表左移2位" << endl;
    LinkListRotateLeft(TestLinklist, 2);
    LinkListPrint(TestLinklist);
    cout <<endl;

    cout << "测试静态链表" <<endl;
    cout <<"初始化静态链表" <<endl;
    StaticLinkList staticlist;
    StaticLinkListInit(staticlist);
    for(int i = 0; i < 5; i++) {
        StaticLinkListInsert(staticlist, i + 1);
    }
    StaticLinkListPrint(staticlist);

    cout << "转置后的静态链表"  <<endl;
    StaticLinkListReverse(staticlist);
    StaticLinkListPrint(staticlist);


    return 0;
}
