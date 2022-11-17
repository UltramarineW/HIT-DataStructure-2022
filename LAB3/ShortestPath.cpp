//
// Created by wujiayang on 2022/10/27.
//
#include <iomanip>
#include <iostream>
#include <fstream>
#define MAX_VERTEX_NUM 50
#define INF 99999
typedef char VertexType;
typedef int EdgeType;

using namespace std;

typedef struct MGraph{
    VertexType Vex[MAX_VERTEX_NUM];
    EdgeType Edge[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum, arcnum;
}MGraph;

void InitialMGraph(MGraph &graph) {
    graph.vexnum = 0;
    graph.arcnum = 0;
    for(int i = 0; i < MAX_VERTEX_NUM; i++) {
        for(int j = 0; j < MAX_VERTEX_NUM; j++) {
            if(i == j) {
                graph.Edge[i][j] = 0;
            }
            //用INT_MAX来替代无穷大
            else{
                graph.Edge[i][j] = INF;
            }
        }
    }

}
void CreateMGraph(MGraph &graph, string file_name) {
    fstream ifs;
    ifs.open(file_name, ios::in);
    if(!ifs.is_open()) {
        cout << "Error in file reading" <<endl;
        exit(-1);
    }
    ifs >> graph.vexnum >> graph.arcnum;
    for(int i = 0; i < graph.vexnum; i++){
        char temp;
        ifs >> temp;
        graph.Vex[i] = temp;
    }
    while(!ifs.eof()){
        int i, j, length;
        ifs >> i >> j >> length;
        graph.Edge[i - 1][j - 1] = length;
        graph.Edge[j - 1][i - 1] = length;
    }
    ifs.close();
}

void Dijkstra(MGraph graph, int v, int* distance) {
    bool visited[MAX_VERTEX_NUM];
    string path[MAX_VERTEX_NUM];
    int index = -1;
    for(int i = 0; i < graph.vexnum; i++) {
        visited[i] = false;
        distance[i] = graph.Edge[v][i];
        if(distance[i]!= INF) {
            path[i].push_back(graph.Vex[v]);
            path[i] += " -> ";
            path[i].push_back(graph.Vex[i]);
        }
        else{
            path[i] = "";
        }
    }

    distance[v] = 0;
    visited[v] = true;
    for(int i = 1; i < graph.vexnum; i++) {
        // find min
        index = -1;
        for(int j = 0; j < graph.vexnum; j++) {
            if(!visited[j] && (index == -1 || distance[j] < distance[index])) {
                index = j;
            }
        }
        visited[index] = true;
        for(int j = 0; j < graph.vexnum; j++) {
            if(!visited[j] && distance[index] + graph.Edge[index][j] < distance[j]) {
                distance[j] = distance[index] + graph.Edge[index][j];
                path[j] = path[index] + " -> ";
                path[j].push_back(graph.Vex[j]);
            }
        }
    }
    for(int i = 0; i < graph.vexnum; i++) {
        if (path[i] == "") {
            cout << "No Path" << endl;
        }
        else {
            cout << path[i] << endl;
        }
    }
}

void Floyd(MGraph graph, int distance[MAX_VERTEX_NUM][MAX_VERTEX_NUM]) {
    string paths[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    for(int i =0; i < graph.vexnum; i++) {
        for(int j = 0; j < graph.vexnum; j++) {
            distance[i][j] = graph.Edge[i][j];
            if (i !=j) {
                if(distance[i][j] != INF) {
                    paths[i][j].push_back(graph.Vex[i]);
                    paths[i][j] += " -> ";
                    paths[i][j].push_back(graph.Vex[j]);

                } else {
                    paths[i][j] = "";
                    paths[j][i] = "";
                }
            } else {
                paths[i][j].push_back(graph.Vex[i]);
                paths[i][j] += " -> ";
                paths[i][j].push_back(graph.Vex[j]);
            }
        }
    }
    for(int k = 0; k < graph.vexnum; k++) {
        for(int i = 0; i < graph.vexnum; i++) {
            for(int j = 0; j < graph.vexnum; j++) {
                if (distance[i][j] > distance[i][k] + distance[k][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                    paths[i][j] = paths[i][k].substr(0, paths[i][k].length() - 5) + " -> " + paths[k][j];
                    paths[j][i] = paths[j][k].substr(0, paths[j][k].length() - 5) + " -> " + paths[k][i];
                }
            }
        }
    }
    for(int i = 0; i < graph.vexnum; i++) {
        for(int j = 0; j < graph.vexnum; j++){
            cout << paths[i][j] << endl;
        }
    }
}

void ShowGraph(MGraph graph) {
    for(int i = 0; i < graph.vexnum; i++) {
        for(int j = 0; j < graph.vexnum; j++) {
            cout.width(6);
            cout << setiosflags(ios::left)<<graph.Edge[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int GetIndex(MGraph graph, VertexType v) {
    for(int i = 0; i < graph.vexnum;i ++) {
        if(graph.Vex[i] == v) {
            return i;
        }
    }
    return -1;
}

// 返回顶点1到顶点2的最短路径
string Dijkstra(MGraph graph, VertexType v1, VertexType v2) {
    int u = GetIndex(graph, v1);
    int v = GetIndex(graph, v2);
    if (u < 0 || v < 0) {
        cout << "图中没有这个节点" << endl;
        exit(0);
    }

    int distance[MAX_VERTEX_NUM];
    bool visited[MAX_VERTEX_NUM];
    string path[MAX_VERTEX_NUM];
    int index = -1;
    // 初始化distance数组与visited数组与最短路径
    for(int i = 0; i < graph.vexnum; i++) {
        visited[i] = false;
        distance[i] = graph.Edge[u][i];
        if(distance[i]!= INF) {
            path[i].push_back(graph.Vex[u]);
            path[i] += " -> ";
            path[i].push_back(graph.Vex[i]);
        }
        else{
            path[i] = "";
        }
    }

    distance[u] = 0;
    visited[u] = true;
    // 遍历n - 1次，
    for(int i = 1; i < graph.vexnum; i++) {
        // find min
        index = -1;
        for(int j = 0; j < graph.vexnum; j++) {
            if(!visited[j] && (index == -1 || distance[j] < distance[index])) {
                index = j;
            }
        }
        visited[index] = true;
        //更新选定顶点与相邻顶点的最短路径
        for(int j = 0; j < graph.vexnum; j++) {
            if(!visited[j] && distance[index] + graph.Edge[index][j] < distance[j]) {
                distance[j] = distance[index] + graph.Edge[index][j];
                path[j] = path[index] + " -> ";
                path[j].push_back(graph.Vex[j]);
            }
        }
    }
    return path[v];

}

// 求解单顶点对间的最短路径问题
void Dijkstra(MGraph graph, VertexType v1, VertexType v2, string &route1, string &route2) {
    route1 = Dijkstra(graph, v1, v2);
    route2 = Dijkstra(graph, v2, v1);
}

int main() {
    MGraph graph;
    string file_name = "./graph1.txt";
    InitialMGraph(graph);
    CreateMGraph(graph, file_name);
    ShowGraph(graph);

    cout << "Dijkstra算法求单源路径最短" << endl;
    int distance[MAX_VERTEX_NUM];
    Dijkstra(graph, 0, distance);
    // 依次输出图顶点与选定顶点间的最短路径
    for(int i = 0; i < graph.vexnum;i++) {
        cout << distance[i] << " ";
    }
    cout << endl;

    cout <<endl;
    cout << "Floyd算法求全局路径最短" << endl;
    int floyd_distance[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    Floyd(graph, floyd_distance);
    for(int i = 0; i < graph.vexnum; i++) {
        for(int j = 0; j < graph.vexnum; j++) {
            cout << setiosflags(ios::right) << floyd_distance[i][j] <<" ";
        }
        cout <<endl;
    }


    cout << endl;
    cout << "从顶点u到顶点v的单源路径最短问题的最短路径 利用Dijkstra算法" <<endl;
    string route = Dijkstra(graph, 'A', 'E');
    cout << "路径为: " << route <<endl;

    cout << endl;
    string route1, route2;
    cout << "求取单顶点对的最短路径问题 从u到v和从v到u" <<endl;
    Dijkstra(graph, 'A', 'E', route1, route2);
    cout << "从u到v的路径为: " << route1 <<endl;
    cout << "从v到u的路径为: " << route2 << endl;

    return 0;
}
