//
// Created by wujiayang on 2022/10/16.
//

#include <iostream>
#include <cassert>
#include <fstream>
#include <algorithm>
#define MAX_VERTEX_NUM 100

typedef char VertexType;
typedef int EdgeType;

// 邻接矩阵
typedef struct MGraph{
    VertexType Vex[MAX_VERTEX_NUM];
    EdgeType Edge[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum, arcnum;
}MGraph;

// 邻接表
typedef struct ArcNode{
    int adjvex;
    struct ArcNode *next;
}ArcNode;

typedef struct VNode{
    VertexType data;
    ArcNode* first;
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct{
    AdjList vertices;
    int vexnum, arcnum;
}ALGraph;

using namespace std;

void InitialMGraph(MGraph &graph) {
    graph.vexnum = 0;
    graph.arcnum = 0;
    for(int i = 0; i < MAX_VERTEX_NUM; i++) {
        for (int j = 0; j < MAX_VERTEX_NUM; j++) {
            graph.Edge[i][j] = 0;
        }
    }
}

void CreateMGraph(MGraph &graph, string file_name) {
    fstream ifs;
    ifs.open(file_name.c_str(), ios::in);
    assert(ifs.is_open());

    ifs >> graph.vexnum;
    while(!ifs.eof()) {
        int colIdx, rowIdx;
        ifs >> colIdx >> rowIdx;
        colIdx -= 1, rowIdx -= 1;
        graph.Edge[colIdx][rowIdx] = 1;
        graph.Edge[rowIdx][colIdx] = 1;
        graph.arcnum ++;
    }
    ifs.close();
}

void ShowMGraph(MGraph &graph) {
    for(int i = 0; i < graph.vexnum; i++) {
        for(int j = 0; j < graph.vexnum; j++) {
            cout << graph.Edge[i][j] << " ";
        }
        cout << endl;
    }
}


void InitialALGraph(ALGraph graph){
    graph.vexnum = 0, graph.arcnum = 0;
    for(int i = 0; i < MAX_VERTEX_NUM; i++) {
        graph.vertices[i].first = nullptr;
    }
}

void CreateALGraph(ALGraph &graph, string file_name) {
    fstream ifs;
    ifs.open(file_name.c_str(), ios::in);
    assert(ifs.is_open());

    ifs >> graph.vexnum;
    while(!ifs.eof()){
        int nodeIdx1, nodeIdx2;
        ifs >> nodeIdx1 >>nodeIdx2;
        nodeIdx1 -= 1, nodeIdx2 -= 1;

        // 利用头插法往链表中插入元素
        ArcNode *pointer = new ArcNode;
        pointer -> next = graph.vertices[nodeIdx1].first;
        pointer -> adjvex = nodeIdx2;
        graph.vertices[nodeIdx1].first = pointer;

        pointer = new ArcNode;
        pointer -> next = graph.vertices[nodeIdx2].first;
        pointer -> adjvex = nodeIdx1;
        graph.vertices[nodeIdx2].first = pointer;
        graph.arcnum++;
    }
    ifs.close();
}

void ShowALGraph(ALGraph graph) {
    for(int i = 0; i < graph.vexnum;i++) {
        ArcNode *pointer = graph.vertices[i].first;
        cout << i + 1 << " -> ";
        while(pointer != nullptr) {
            cout << pointer->adjvex + 1 << " -> ";
            pointer = pointer ->next;
        }
        cout << "NULL" <<endl;
    }
}

ALGraph TransferFromMtoAL(MGraph graph) {
    ALGraph transferGraph;
    InitialALGraph(transferGraph);
    transferGraph.vexnum = graph.vexnum;
    transferGraph.arcnum = graph.arcnum;

    for(int i = 0; i < graph.vexnum; i++) {
        for(int j = 0; j < i; j++) {
            if(graph.Edge[i][j] == 1) {
                ArcNode *pointer = new ArcNode;
                pointer -> next = transferGraph.vertices[i].first;
                pointer -> adjvex = j;
                transferGraph.vertices[i].first = pointer;

                pointer = new ArcNode;
                pointer -> next = transferGraph.vertices[j].first;
                pointer -> adjvex = i;
                transferGraph.vertices[j].first = pointer;
            }
        }
    }
    return transferGraph;
}

MGraph TransferFromALtoM(ALGraph graph){
    MGraph transferedGraph;
    InitialMGraph(transferedGraph);
    transferedGraph.vexnum = graph.vexnum;
    transferedGraph.arcnum = graph.arcnum;

    for(int i = 0; i < graph.vexnum;i++){
        ArcNode* pointer = graph.vertices[i].first;
        while(pointer != nullptr) {
            transferedGraph.Edge[i][pointer -> adjvex] = 1;
            pointer = pointer -> next;
        }
    }
    return transferedGraph;
}

int main() {
    MGraph graph1;
    InitialMGraph(graph1);
    ALGraph graph2;
    InitialALGraph(graph2);
    cout << "用邻接矩阵存储的图的大小为: " << sizeof(MGraph) << endl;
    cout << "用邻接表存储的图的大小为: " << sizeof (ALGraph) <<endl;
    cout << endl;

    string file_name = "../../HW3/graph.txt";
    cout << "建立用邻接矩阵表示的图" << endl;
    CreateMGraph(graph1, file_name);
    ShowMGraph(graph1);
    cout << endl;

    cout << "用邻接表表示的图" << endl;
    CreateALGraph(graph2, file_name);
    ShowALGraph(graph2);
    cout << endl;

    cout << "从邻接矩阵转化为邻接表" << endl;
    ALGraph transferedGraph1 = TransferFromMtoAL(graph1);
    ShowALGraph(transferedGraph1);
    cout << endl;

    cout << "从邻接表转化为邻接矩阵" << endl;
    MGraph transferedGraph2 = TransferFromALtoM(graph2);
    ShowMGraph(transferedGraph2);


    return 0;
}