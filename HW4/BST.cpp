//
// Created by wujiayang on 2022/11/3.
//
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

#define N 1024

using namespace std;
typedef int DataType;


typedef struct BSTNode {
    DataType data;
    BSTNode *lchild, *rchild;
} BSTNode, *BSTree;


BSTNode *BSTSearch(BSTree T, DataType key, int &count) {
    while (T != nullptr && T->data != key) {
        count += 1;
        if (key > T->data) {
            T = T->rchild;
        } else {
            T = T->lchild;
        }
    }
    return T;
}

void BSTInsert(BSTree &tree, DataType key) {
    if (tree == nullptr) {
        tree = new BSTNode;
        tree->data = key;
        tree->lchild = nullptr;
        tree->rchild = nullptr;
    } else if (key == tree->data) {
        return;
    } else if (key < tree->data) {
        BSTInsert(tree->lchild, key);
    } else if (key > tree->data) {
        BSTInsert(tree->rchild, key);
    }
}

BSTree CreateBST(vector<int> data_array) {
    BSTree tree = nullptr;
    for (int i = 0; i < N; i++) {
        BSTInsert(tree, data_array[i]);
    }
    return tree;
}

vector<int> ShuffleData(vector<int> src) {
    srand(time(0));
    for (int i = 0; i < 100000; i++) {
        int src_index = (rand() % (N));
        int dst_index = (rand() % (N));
        int temp = src[src_index];
        src[src_index] = src[dst_index];
        src[dst_index] = temp;
    }
    return src;
}


void BSTDelete(BSTree &tree, DataType key) {
    BSTNode *ptr = tree;
    BSTNode *prev_ptr = nullptr;
    while (ptr != nullptr && ptr->data != key) {
        if (ptr->data > key) {
            prev_ptr = ptr;
            ptr = ptr->lchild;
        } else {
            prev_ptr = ptr;
            ptr = ptr->rchild;
        }
    }
    if (ptr == nullptr) {
        cout << "Not find " << key << endl;
        return;
    }
    if (ptr->rchild == nullptr && ptr->rchild == nullptr) {
        if (prev_ptr->rchild == ptr) prev_ptr->rchild = nullptr;
        else prev_ptr->lchild = nullptr;
        return;
    } else if (ptr->rchild == nullptr && ptr->lchild != nullptr) {
        if (prev_ptr == nullptr) {
            tree = ptr->lchild;
            return;
        }
        if (prev_ptr->rchild == ptr) prev_ptr->rchild = ptr->lchild;
        else prev_ptr->lchild = ptr->lchild;
        return;
    } else if (ptr->rchild != nullptr && ptr->lchild == nullptr) {
        if (prev_ptr == nullptr) {
            tree = ptr->rchild;
            return;
        }
        if (prev_ptr->rchild == ptr) prev_ptr->rchild = ptr->rchild;
        else prev_ptr->lchild = ptr->rchild;
        return;
    } else {
        BSTNode *node = ptr->rchild;
        BSTNode *prevnode = ptr;
        while (node->lchild != nullptr) {
            prevnode = node;
            node = node->lchild;
        }
        ptr->data = node->data;
        if (prevnode != ptr) {
            prevnode->lchild = node->rchild;
        } else {
            prevnode->rchild = node->rchild;
        }
        return;
    }
}

void PreorderTraverse(BSTree tree) {
    if (tree == nullptr) {
        return;
    }
    cout << tree->data << " ";
    PreorderTraverse(tree->lchild);
    PreorderTraverse(tree->rchild);
}

void InorderTraverse(BSTree tree, vector<DataType> &array) {
    if (tree == nullptr) {
        return;
    }
    InorderTraverse(tree->lchild, array);
    array.push_back(tree->data);
    InorderTraverse(tree->rchild, array);

}

int BinarySearch(vector<int> array, DataType key, int &count) {
    int low = 0, high = array.size() - 1;
    while (low <= high) {
        count += 1;
        int mid = (low + high) / 2;
        if (array[mid] == key) {
            return mid;
        } else if (array[mid] < key) {
            low = mid + 1;
        } else if (array[mid] > key) {
            high = mid - 1;
        }
    }
    return -1;
}

int main() {

    cout << "???????????????: ???????????????0-2048????????????" << endl;
    vector<int> data_array1;
    for (int i = 1; i <= 2 * N; i += 2) {
        data_array1.push_back(i);
    }
    cout << "?????????????????????" << endl;
    BSTree tree = CreateBST(data_array1);
    // ?????????1??????
//    PreorderTraverse(tree);
//    cout << endl;
//    BSTDelete(tree, 13);
//    PreorderTraverse(tree);

    int count = 0;
    for (int i = 1; i < N * 2; i += 2) {
        BSTSearch(tree, i, count);
    }
    cout << count << endl;
    cout << (double) count / N << endl;

    cout << "???????????????: ?????????0-2048????????????" << endl;
    vector<int> data_array2;
    data_array2 = ShuffleData(data_array1);
    cout << "?????????????????????2" << endl;
    BSTree tree2 = nullptr;
    for (int i = 0; i < N; i++) {
        BSTInsert(tree2, data_array2[i]);
    }

    count = 0;
    for (int i = 1; i < N * 2; i += 2) {
        BSTSearch(tree2, i, count);
    }
    cout << count << endl;
    cout << (double) count / N << endl;

    cout << "????????????" << endl;
    vector<DataType> array;
    InorderTraverse(tree2, array);
    count = 0;
    for (int i = 1; i < N * 2; i += 2) {
        BinarySearch(array, i, count);
    }
    cout << count << endl;
    cout << (double) count / N << endl;

    cout << "???????????????????????????????????????BST???????????????????????????????????????????????????????????????????????????????????????" << endl;

    return 0;

}