//
// Created by wujiayang on 2022/9/14.
//
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>

using namespace std;


int main() {
    char input[100];
    char temp;
    int count = 0;
    while(1) {
        temp = cin.get();
        if(temp == '#') break;
    }
    while (true) {
        temp = cin.get();
        if (temp == '#') break;
        if (temp == ' ') continue;
        input[count] = temp;
        count++;
    }
    cout <<count <<endl;

    stack<char> s;
    return 0;
}