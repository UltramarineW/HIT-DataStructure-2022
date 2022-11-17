//
// Created by wujiayang on 2022/10/16.
//

#include <stack>
#include <queue>
#include <iostream>
#include <cassert>
#include <fstream>
#include <algorithm>
#define MAX_VERTEX_NUM 100

typedef char VertexType;
typedef int EdgeType;

enum GraphKind{DG, UDG}; // 图的种类 有向图、无向图

// 邻接矩阵
typedef struct MGraph{
    VertexType Vex[MAX_VERTEX_NUM];
    EdgeType Edge[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum, arcnum;
    enum GraphKind kind;
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
    enum GraphKind kind;
}ALGraph;

typedef struct TreeNode{
    char data;
    struct TreeNode *lchild;
    struct TreeNode *nextsbling;
}TreeNode, *CSTree;

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

void CreateMGraph(MGraph &graph, string file_name, enum GraphKind kind) {
    fstream ifs;
    graph.kind = kind;
    ifs.open(file_name.c_str(), ios::in);
    assert(ifs.is_open());

    ifs >> graph.vexnum;
    for(int i = 0; i < graph.vexnum; i++) {
        char a;
        ifs >> a;
        graph.Vex[i] = a;
    }
    while(!ifs.eof()) {
        int colIdx, rowIdx;
        ifs >> colIdx >> rowIdx;
        colIdx -= 1, rowIdx -= 1;
        if(graph.kind == DG) {
            graph.Edge[colIdx][rowIdx] =1;
        }
        else if (graph.kind == UDG) {
            graph.Edge[colIdx][rowIdx] = 1;
            graph.Edge[rowIdx][colIdx] = 1;
        }
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

void CreateALGraph(ALGraph &graph, string file_name, enum GraphKind kind) {
    fstream ifs;
    ifs.open(file_name.c_str(), ios::in);
    assert(ifs.is_open());

    ifs >> graph.vexnum;

    // 输入节点信息
    for (int i = 0; i < graph.vexnum; i++) {
        char a;
        ifs >> a;
        graph.vertices[i].data = a;
    }

    graph.kind = kind;
    while (!ifs.eof()) {
        int nodeIdx1, nodeIdx2;
        ifs >> nodeIdx1 >> nodeIdx2;
        nodeIdx1 -= 1, nodeIdx2 -= 1;

        // 利用头插法往链表中插入元素
        // 有向图
        if (graph.kind == DG) {
            auto *pointer = new ArcNode;
            pointer->next = graph.vertices[nodeIdx1].first;
            pointer->adjvex = nodeIdx2;
            graph.vertices[nodeIdx1].first = pointer;
        }
            // 无向图
        else if (graph.kind == UDG) {
            auto *pointer = new ArcNode;
            pointer->next = graph.vertices[nodeIdx1].first;
            pointer->adjvex = nodeIdx2;
            graph.vertices[nodeIdx1].first = pointer;

            pointer = new ArcNode;
            pointer->next = graph.vertices[nodeIdx2].first;
            pointer->adjvex = nodeIdx1;
            graph.vertices[nodeIdx2].first = pointer;
            graph.arcnum++;
        }
    }
    ifs.close();
}


void ShowALGraph(ALGraph graph) {
    for(int i = 0; i < graph.vexnum;i++) {
        ArcNode *pointer = graph.vertices[i].first;
        cout << graph.vertices[i].data << " -> ";
        while(pointer != nullptr) {
            cout << graph.vertices[pointer -> adjvex].data << " -> ";
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
    transferGraph.kind = graph.kind;

    for(int i = 0; i < graph.vexnum; i++) {
        transferGraph.vertices[i].data = graph.Vex[i];
    }

    for(int i = 0; i < graph.vexnum; i++) {
        for(int j = 0; j < graph.vexnum; j++) {
            if(graph.Edge[i][j] == 1) {
                ArcNode *pointer = new ArcNode;
                pointer->next = transferGraph.vertices[i].first;
                pointer->adjvex = j;
                transferGraph.vertices[i].first = pointer;
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
    transferedGraph.kind = graph.kind;

    for(int i = 0; i < graph.vexnum;i++){
        ArcNode* pointer = graph.vertices[i].first;
        while(pointer != nullptr) {
            transferedGraph.Edge[i][pointer -> adjvex] = 1;
            pointer = pointer -> next;
        }
    }
    return transferedGraph;
}

bool visited[MAX_VERTEX_NUM] ;
// 深度优先搜索递归方式 邻接表
void DFS(ALGraph graph, int i, TreeNode *tree) {
    cout << graph.vertices[i].data << " ";
    visited[i] = true;
    bool first = true;
    TreeNode *node_pointer = nullptr;
    for(ArcNode *pointer = graph.vertices[i].first; pointer != nullptr; pointer = pointer -> next) {
        if(!visited[pointer -> adjvex]) {
            TreeNode *child_node = new TreeNode;
            child_node -> data = graph.vertices[pointer -> adjvex].data;
            child_node -> lchild = nullptr, child_node -> nextsbling = nullptr;
            if(first) {
                tree -> lchild = child_node;
                first = false;
            }
            else {
                node_pointer -> nextsbling = child_node;
            }
            node_pointer = child_node;
            DFS(graph, pointer -> adjvex, child_node);
        }
    }
}

void DFS(MGraph graph, int i) {
    cout << graph.Vex[i]<< " ";
    visited[i] = true;
    for(int j = 0; j < graph.vexnum - i; j++) {
        if(graph.Edge[i][j] == 1 && !visited[j]) {
            DFS(graph, j);
        }
    }
}

// 深度优先搜索递归方式 邻接表
void DFSTraverse(ALGraph graph, CSTree &Tree) {
    Tree = nullptr;
    for(int i = 0; i < graph.vexnum; i++) {
        visited[i] = false;
    }
    TreeNode *pointer = nullptr;
    for(int i = 0; i < graph.vexnum;i++){
        if(!visited[i]) {
            TreeNode *node = new TreeNode;
            node -> data = graph.vertices[i].data;
            node -> lchild = nullptr, node -> nextsbling = nullptr;
            if(Tree == nullptr) {
                Tree = node;
            }
            else {
                pointer -> nextsbling = node;
            }
            pointer = node;
            DFS(graph, i, node);
        }
    }
}

void DFSTraverse(MGraph graph) {
    for(int i = 0; i < graph.vexnum; i++) {
        visited[i] = false;
    }
    for(int i = 0; i < graph.vexnum;i++){
        if(!visited[i]) {
            DFS(graph, i);
        }
    }
}


queue<int> visitQueue;
void BFS(ALGraph graph, int i) {
    cout << graph.vertices[i].data << " ";
    visitQueue.push(i);
    visited[i] = true;
    while(!visitQueue.empty()) {
        for(ArcNode *pointer = graph.vertices[visitQueue.front()].first; pointer !=nullptr; pointer = pointer -> next) {
            if (!visited[pointer->adjvex]) {
                cout << graph.vertices[pointer -> adjvex].data << " ";
                visited[pointer->adjvex] = true;
                visitQueue.push(pointer->adjvex);
            }
        }
        visitQueue.pop();
    }
}
void BFSTraverse(ALGraph graph) {
    while(!visitQueue.empty()) {
        visitQueue.pop();
    }
    for(int i = 0; i < graph.vexnum; i++) {
        visited[i] = false;
    }
    for(int i = 0; i < graph.vexnum;i++) {
        if(!visited[i]) {
            BFS(graph, i);
        }
    }
}

void BFS(MGraph graph, int i) {
    cout << graph.Vex[i] << " ";
    visitQueue.push(i);
    visited[i] = true;
    while(!visitQueue.empty()) {
        for(int j = 0; j < graph.vexnum; j++) {
            if(graph.Edge[i][j] == 1 && !visited[j]) {
                visited[j] = true;
                cout << graph.Vex[j] << " ";
                visitQueue.push(j);
            }
        }
        visitQueue.pop();
    }
}

void BFSTraverse(MGraph graph) {
    while(!visitQueue.empty()) {
        visitQueue.pop();
    }
    for(int i = 0; i < graph.vexnum; i++) {
        visited[i] = false;
    }
    for(int i = 0; i < graph.vexnum;i++) {
        if(!visited[i]) {
            BFS(graph, i);
        }
    }
}


void CountVexDegree(ALGraph graph){
    vector<int> VexDegree;
    vector<int> InVexDegree, OutVexDegree;
    if (graph.kind == UDG) {
        for(int i = 0; i < graph.vexnum; i++) {
            int count = 0;
            ArcNode *pointer = graph.vertices[i].first;
            while(pointer != nullptr) {
                count++;
                pointer = pointer -> next;
            }
            VexDegree.push_back(count);
        }
        cout << "无向图的顶点度数为 ";
        vector<int>::iterator it;
        for(it = VexDegree.begin(); it != VexDegree.end(); it++) {
            cout << *it << " ";
        }
        cout << endl;
    }
    else if (graph.kind == DG) {
        for(int i = 0; i < graph.vexnum; i++) {
            OutVexDegree.push_back(0);
            InVexDegree.push_back(0);
        }
        for(int i = 0; i < graph.vexnum; i++) {
            ArcNode *pointer = graph.vertices[i].first;
            while(pointer != nullptr) {
                OutVexDegree[i]++;
                InVexDegree[pointer->adjvex]++;
                pointer = pointer -> next;
            }
        }
        vector<int>::iterator it;
        cout << "有向图的出度为 " ;
        for(it = InVexDegree.begin(); it != InVexDegree.end(); it++){
            cout << *it << " " ;
        }
        cout << endl;

        cout << "有向图的入度为 ";
        for(it = OutVexDegree.begin(); it != OutVexDegree.end(); it++) {
            cout << *it << " ";
        }
        cout << endl;
    }
}

void DFSTraverseWORecurse(ALGraph graph) {
    stack<int> vexStack;
    // 初始化访问数组
    for(int i = 0; i < graph.vexnum; i++) {
        visited[i] = false;
    }
    for(int i = 0; i < graph.vexnum; i++) {
        if(!visited[i]) {
            visited[i] = true;
            vexStack.push(i);
            while(!vexStack.empty()){
                int t = vexStack.top();
                vexStack.pop();
                cout << graph.vertices[t].data << " ";
                ArcNode *pointer = graph.vertices[t].first;
                while(pointer != nullptr) {
                    if(!visited[pointer -> adjvex]){
                        vexStack.push(pointer ->adjvex);
                        visited[pointer ->adjvex] = true;
                    }
                    pointer = pointer -> next;
                }
            }
        } // if
    } // for

}

void DFSTraverseWORecurse(MGraph graph) {
    stack<int> vexStack;
    // 初始化访问数组
    for(int i = 0; i < graph.vexnum; i++) {
        visited[i] = false;
    }
    for(int i = 0; i < graph.vexnum; i++) {
        if(!visited[i]) {
            visited[i] = true;
            vexStack.push(i);
            while(!vexStack.empty()){
                int t = vexStack.top();
                vexStack.pop();
                cout << graph.Vex[t] << " ";
                for(int j = 0; j < graph.vexnum; j++) {
                    if(graph.Edge[i][j] == 1 && !visited[j]){
                        visited[j] = true;
                        vexStack.push(j);
                    }
                }
            }
        } // if
    } // for


}


void TreeTraverse(CSTree Tree){
    if(Tree == nullptr) {
        return ;
    }
    cout << Tree -> data << " ";
    TreeTraverse(Tree -> lchild);
    TreeTraverse(Tree -> nextsbling);
}

int main() {
    MGraph MGraph_UDG, MGraph_DG;
    InitialMGraph(MGraph_UDG);
    InitialMGraph(MGraph_DG);
    ALGraph ALGraph_UDG, ALGraph_DG;
    InitialALGraph(ALGraph_UDG);
    InitialALGraph(ALGraph_DG);
    cout << "用邻接矩阵存储的图的大小为: " << sizeof(MGraph) << " " << "时间复杂度为O(n^2)" << endl;
    cout << "用邻接表存储的图的大小为: " << sizeof(ALGraph) << " " << "时间复杂度为O(n^2)" << endl;
    cout << endl;

    string file_name = "../../HW3/graph.txt";
    cout << "建立用邻接矩阵表示的图" << endl;
    CreateMGraph(MGraph_UDG, file_name, UDG);
    CreateMGraph(MGraph_DG, file_name, DG);
    ShowMGraph(MGraph_UDG);
    cout << endl;

    cout << "用邻接表表示的图" << endl;
    CreateALGraph(ALGraph_UDG, file_name, UDG);
    CreateALGraph(ALGraph_DG, file_name, DG);
    ShowALGraph(ALGraph_UDG);
    cout << endl;

    cout << "从邻接矩阵转化为邻接表" << endl;
    ALGraph transferedGraph1 = TransferFromMtoAL(MGraph_UDG);
    ShowALGraph(transferedGraph1);
    cout << endl;

    cout << "从邻接表转化为邻接矩阵" << endl;
    MGraph transferedGraph2 = TransferFromALtoM(ALGraph_UDG);
    ShowMGraph(transferedGraph2);
    cout << endl;

    cout << "用递归的方法进行无向图深度优先搜索（用邻接表存储）同时构建树" << endl;
    CSTree ALG_UDG_Tree;
    DFSTraverse(ALGraph_UDG, ALG_UDG_Tree);
    cout << endl;


    cout << "用递归的方法进行无向图深度优先搜索（用邻接矩阵存储）" << endl;
    DFSTraverse(MGraph_UDG);
    cout << endl;

    cout << "用非递归的方法进行深度优先搜索（用邻接表存储）" << endl;
    DFSTraverseWORecurse(ALGraph_UDG);
    cout << endl;

    cout << "用非递归的方法进行深度优先搜索（用邻接矩阵存储）" << endl;
    DFSTraverseWORecurse(MGraph_UDG);
    cout << endl;

    cout << "用非递归的方法进行广度优先搜索（用邻接表存储）" << endl;
    BFSTraverse(ALGraph_UDG);
    cout << endl;

    cout << "用非递归的方法进行广度优先搜索（用邻接矩阵存储）" << endl;
    BFSTraverse(MGraph_UDG);
    cout << endl;

    cout << endl;
    cout << "深度优先搜索生成树遍历" << endl;
    TreeTraverse(ALG_UDG_Tree);
    cout << endl;

    cout << endl;
    CountVexDegree(ALGraph_DG);
    CountVexDegree(ALGraph_UDG);


    return 0;
}