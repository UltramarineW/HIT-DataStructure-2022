//
// Created by wujiayang on 2022/10/10.
//
#include <cstdlib>
#include <map>
#include <algorithm>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <cassert>


using namespace std;

typedef struct BiTNode{
    pair<char, int> data;
    struct BiTNode* lchild, *rchild;
}BiTNode, *BiTree;


map<char, string> huffcode;
map<char, string> binarycode;

string ReadFile(string file_addr) {
    ifstream test_file;
    string char_vec;
    char c;

    // 打开文件
    test_file.open(file_addr.c_str(), ios::in);
    assert(test_file.is_open());

    // 防止文件流略过空格和换行
    test_file >> noskipws;

    // 读入文件中的每一个字符（包括空格）
    while(test_file.peek() != EOF) {
        test_file >> c;
        cout << c;
        char_vec.push_back(c);
    }
    test_file.close();
    return char_vec;
}

void GetFreq(string str, map<char, int> &char_freq) {
    char_freq.clear();

    for(int i = 0; i < str.size(); i++) {
        if(!char_freq.count(str[i])) {
            char_freq.insert(map<char, int>::value_type(str[i], 1));
        } else {
            char_freq[str[i]]++;
        }
    }

}

void ShowMap(map<char, int> map1) {
    map<char, int>::iterator it;
    for(it = map1.begin(); it != map1.end(); it++) {
        cout << it -> first << " " <<  it -> second << endl;
    }
}



vector<BiTNode*> CreateTreeNode(map<char, int> char_freq) {
    vector<BiTNode*> nodes;
    map<char, int>::iterator it;
    for(it = char_freq.begin(); it != char_freq.end(); it++) {
        BiTNode *node = new BiTNode ;
        node -> data = make_pair(it -> first, it -> second);
        node -> lchild = node -> rchild = nullptr;
        nodes.push_back(node);
    }
    return nodes;
}

BiTNode* FindSmallest(vector<BiTNode*> nodes, int &index) {

    int smallest = nodes[0] ->data.second;
    BiTNode *smallestNode = nodes[0];

    for(int i = 1; i < nodes.size(); i++) {
        if(nodes[i] -> data.second < smallest) {
            smallest = nodes[i] -> data.second;
            smallestNode = nodes[i];
            index = i;
        }
    }
    return smallestNode;
}

BiTree CreateHuffmanTree(map<char, int> char_freq){
    // 将所有map中的数据存放到树的节点中去
    vector<BiTNode*> nodes = CreateTreeNode(char_freq);
    int index = 0;


    while (nodes.size() != 1) {

        // 寻找节点中最小的两个节点
        BiTNode* startNode = FindSmallest(nodes, index);
        auto it = nodes.begin() + index;
        nodes.erase(it);
        index = 0;

        BiTNode* node = FindSmallest(nodes, index);
        it = nodes.begin() + index;
        nodes.erase(it);
        index = 0;

        //建立新节点
        BiTNode* newNode = new BiTNode ;
        newNode -> data.second = startNode->data.second + node -> data.second;
        newNode -> lchild = startNode;
        newNode -> rchild = node;
        nodes.push_back(newNode);
    }

    return nodes[0];
}

void PreorderTraverse(BiTree tree) {
    if(tree == nullptr) {
        cout << "# ";
        return;
    }
    if(tree -> data.first == '\0') {
        cout << "& ";
    }
    else {
        cout << tree -> data.second << " ";
    }
    PreorderTraverse(tree -> lchild);
    PreorderTraverse(tree -> rchild);
}

void HuffmanEncode(BiTree huffmanTree, string code) {
    // 如果是根节点就输出对应的编码
    if(huffmanTree -> lchild == nullptr && huffmanTree -> rchild == nullptr) {
        cout << huffmanTree -> data.first << " " << code << endl;
        huffcode.insert(make_pair(huffmanTree -> data.first, code));
    }
    // 朝左走 字符串 + 0
    if(huffmanTree -> lchild != nullptr) {
        HuffmanEncode(huffmanTree -> lchild, code + '0');
    }
    // 朝右走 字符串 + 1
    if(huffmanTree -> rchild != nullptr) {
        HuffmanEncode(huffmanTree -> rchild, code + '1');
    }
}

string EncodeFile(string file) {
    string ret = "";
    for(int i = 0; i < file.size(); i++) {
        ret += huffcode[file[i]];
    }
    return ret;
}

void SaveCode(string huffmanEncoded, string codeFileName) {
    ofstream ofs;
    ofs.open(codeFileName, ios::out);
    ofs << huffmanEncoded;
    ofs.close();
}


string DecodeHuffmanTree(BiTree huffmantree, string code, string decode) {
    int index = 0;
    string tempStr;
    BiTNode *root = huffmantree;
    // 将哈夫曼编码放到哈夫曼树中解码
    while(index != code.size()) {
        tempStr += code[index];
        // 如果编码是0 就朝左子树走 如果编码是1就朝右子树走
        if(code[index] == '0') {
            root = root -> lchild;
        } else {
            root = root -> rchild;
        }
        if(root -> lchild == nullptr && root -> rchild == nullptr) {
            decode += root -> data.first;
            root = huffmantree;
            tempStr.clear();
        }
        index++;
    }
    return decode;
}

string BinaryEncode(string file, map<char, int> char_freq) {
    string ret;
    int bit = 0;
    int char_size = char_freq.size();

    while (char_size != 0) {
        bit++;
        char_size /= 2;
    }

    int i;
    map<char, int>::iterator it;
    for(i = 0, it = char_freq.begin(); it != char_freq.end(); it++, i++) {
        char temp[1000];
        itoa(i, temp, 2);
        string ss(temp);
        if(ss.size()!= bit) {
            ss.insert(ss.begin(), bit - ss.size(), '0');
        }
        binarycode.insert(make_pair(it -> first, ss));
    }


    cout << "二进制编码" << endl;
    map<char, string>::iterator it2;
    for(it2 = binarycode.begin(); it2 != binarycode.end(); it2++) {
        cout << it2 -> first << " " << it2 ->second << endl;
    }

    for(i = 0; i < file.size(); i++) {
        ret += binarycode[file[i]];
    }
    return ret;
}

int main() {
    // 输入文本文件
    string file_addr = "../../LAB2/testfile.txt";
    string file = ReadFile(file_addr);

    // 获取每个字符的频率
    map<char, int> char_freq;
    cout << endl;
    cout << "字符的使用频率为" << endl;
    GetFreq(file, char_freq);

    // 输出每个字符的频率并建立哈夫曼树
    ShowMap(char_freq);
    BiTree huffmanTree = CreateHuffmanTree(char_freq);

    // 先序遍历展示哈夫曼树
    cout << endl;
    cout << "先序遍历展示建立的哈夫曼树" << endl;
    PreorderTraverse(huffmanTree);
    cout << endl;
    cout << endl;

    // 对字符进行哈夫曼编码
    cout << "哈夫曼编码" << endl;
    HuffmanEncode(huffmanTree, "");

    // 对文件进行哈夫曼编码
    string huffmanEncoded = EncodeFile(file);

    // 将哈夫曼编码的文件输出
    string codeFileName = "../../LAB2/encodeFile.txt";
    SaveCode(huffmanEncoded, codeFileName);

    ifstream ifs;
    ifs.open(codeFileName, ios::in);
    string code;
    ifs >> code;
    ifs.close();

    // 进行哈夫曼解码
    int index = 0;
    string decode;
    decode = DecodeHuffmanTree(huffmanTree, code, decode);

    codeFileName = "../../LAB2/decodeFile.txt";
    SaveCode(decode, codeFileName);

    // 判断原始文件与经过加解密后的字符串是否相等
    cout << endl;
    if(decode == file) {
        cout << "The two string is equal" <<endl;
    } else {
        cout << "The two string is not equal" <<endl;
    }
    cout << endl;

    string binaryCode = BinaryEncode(file, char_freq);
    codeFileName = "../../LAB2/binaryFile.txt";
    SaveCode(binaryCode, codeFileName);

    cout << endl;
    cout << "压缩率为" << (double)huffmanEncoded.size() / (double)binaryCode.size() << endl;
}
