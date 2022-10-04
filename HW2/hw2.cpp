//
// Created by wujiayang on 2022/9/25.
//
#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;

typedef struct BiTNode{
    char data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

typedef struct StackNode{
    BiTNode* ptr;
    int flag;
}StackNode;


void createBiTreeFromString(BiTree &tree, string str) {
    static int index = 0;
    char ch = str[index++];
    if (ch == '#') {
        tree = nullptr;
    } else {
        tree = new BiTNode;
        tree -> data = ch;
        createBiTreeFromString(tree -> lchild, str);
        createBiTreeFromString(tree -> rchild, str);
    }
}

// remember to reference the tree start node
void createBiTree(BiTree &T) {
    char ch;
    scanf("%c", &ch);
    if (ch == '#') {
        T = nullptr;
    } else {
        T = new BiTNode;
        T -> data = ch;
        createBiTree(T -> lchild);
        createBiTree(T -> rchild);
    }
}

void PreorderTraverse(BiTNode *T) {
    if (T == nullptr) {
        return;
    }
    cout << T -> data << " ";
    PreorderTraverse(T -> lchild);
    PreorderTraverse(T -> rchild);
}

void InOrderTraverse(BiTNode *T) {
    if (T == nullptr) {
        return ;
    }
    InOrderTraverse(T -> lchild);
    cout << T -> data << " ";
    InOrderTraverse(T -> rchild);
}

void PostorderTraverse(BiTree tree){
    if(tree == nullptr) {
        return;
    }
    PostorderTraverse(tree -> lchild);
    PostorderTraverse(tree -> rchild);
    cout << tree -> data << " ";
}

void PreorderStack(BiTree tree) {
    BiTNode* s[100];
    int top = -1;
    BiTree root = tree;
    while (root != nullptr || top != -1) {
        while (root != nullptr) {
            s[++top] = root;
            cout << root -> data <<" ";
            root = root -> lchild;
        }
        if (top != -1) {
            root = s[top--];
            root = root -> rchild;
        }
    }
}

void InorderStack(BiTree tree) {
    BiTNode* s[100];
    int top = -1;
    BiTNode *root = tree;
    while (root != nullptr || top != -1) {
        while (root != nullptr) {
            s[++top] = root;
            root = root->lchild;
        }
        if(top != -1) {
            root = s[top--];
            cout << root -> data << " ";
            root = root -> rchild;
        }
    }
}

void PostorderStackTraverse(BiTree tree) {
    StackNode s[100];
    int top = -1;
    BiTNode *root = tree;
    while(root != nullptr || top != -1) {
        while (root != nullptr) {
            s[++top].ptr = root;
            s[top].flag = 1;
            root = root -> lchild;
        }
        while (top != -1 && s[top].flag == 2) {
            root = s[top--].ptr;
            cout << root -> data << " ";
            root = nullptr;
        }
        if (top != -1) {
            s[top].flag = 2;
            root = s[top].ptr -> rchild;
        }
    }
}

int TreeHeight(BiTree tree) {
    if (tree == nullptr) {
        return 0;
    }
    int m = TreeHeight(tree -> lchild);
    int n = TreeHeight(tree -> rchild);
    return (m > n) ? (m + 1) : (n + 1);
}

void SequenceTraverse(BiTree tree, int level) {
    if (tree == nullptr || level == 0) {
        return;
    }
    if (level == 1) {
        cout << tree ->data << " ";
        return;
    }
    SequenceTraverse(tree -> lchild, level - 1);
    SequenceTraverse(tree -> rchild, level - 1);
}

void SequenceQueneTraverse(BiTree tree) {
    queue<BiTNode*> q;
    BiTNode *root = tree;
    q.push(root);
    while(!q.empty()) {
        cout << q.front() -> data << " ";
        if(q.front() -> lchild != nullptr){
            q.push(q.front() -> lchild);
        }
        if(q.front() -> rchild != nullptr) {
            q.push(q.front() -> rchild);
        }
        q.pop();
    }
}

int main(int argc, char *argv[]) {
    BiTree tree;
//    createBiTree(tree);
    cout << "通过先序序列构造一棵树" <<endl;
    string str = "ABDH#K###E##CFI###G#J##";
    cout << "树为 "<< str<< endl;

    createBiTreeFromString(tree, str);
    cout << "递归先序遍历   ";
    PreorderTraverse(tree);
    cout << endl;

    cout << "递归中序遍历   ";
    InOrderTraverse(tree);
    cout<<endl;


    cout << "递归后续遍历   ";
    PostorderTraverse(tree);
    cout << endl;

    cout << "递归层序遍历   ";
    for (int i = 0; i <= TreeHeight(tree); i++) {
        SequenceTraverse(tree, i);
    }
    cout <<endl;

    cout << "非递归前序遍历 " ;
    PreorderStack(tree);
    cout <<endl;

    cout << "非递归中序遍历 ";
    InorderStack(tree);
    cout<< endl;

    cout << "非递归后续遍历 ";
    PostorderStackTraverse(tree);
    cout << endl;

    cout << "非递归层序遍历 " ;
    SequenceQueneTraverse(tree);
    cout <<endl;

    cout << "Tree height " << TreeHeight(tree);
    // 线性索引二叉树

    return 0;
}
