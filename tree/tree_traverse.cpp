//
// Created by wujiayang on 2022/9/25.
//
#include <cstdio>
#include <iostream>

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

void SwapChildTree(BiTree tree) {
    if(tree == nullptr) {
        return;
    }
    BiTNode *temp = tree -> lchild;
    tree -> lchild = tree -> rchild;
    tree -> rchild = temp;
    SwapChildTree(tree -> lchild);
    SwapChildTree(tree -> rchild);
}

int main(int argc, char *argv[]) {
    BiTree tree;
//    createBiTree(tree);
    string str = "ABDH#K###E##CFI###G#J##";
    createBiTreeFromString(tree, str);
    cout << "Preorder traverse: ";
    PreorderTraverse(tree);
    cout << endl;

    cout << "Inorder traverse: ";
    InOrderTraverse(tree);
    cout<<endl;

    cout << "Postorder traverse: ";
    PostorderTraverse(tree);
    cout << endl;

    cout << "Preorder stack traverse: " ;
    PreorderStack(tree);
    cout <<endl;

    cout << "Inorder stack traverse: ";
    InorderStack(tree);
    cout<< endl;

    cout << "Postorder stack traverse: ";
    PostorderStackTraverse(tree);
    cout << endl;

    cout << "Tree height " << TreeHeight(tree);
    // 线性索引二叉树
    cout << endl;

    cout << "交换二叉树的所有左右节点" << endl;
    SwapChildTree(tree);
    PreorderTraverse(tree);
    cout << endl;

    return 0;
}
