//
// Created by wujiayang on 2022/9/25.
//

#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

void get_next(string str, int *next)  {
    next[0] = -1;
    int k = 0;
    int i = 1;
    while (i < str.size()) {
        if (k == 0 || str[i] == str[k]) {
            k++;
            i++;
            next[i] = k - 1;
        } else {
            k = next[k];
        }
    }
}

int kmp_search(string str1, string str2) {
    int i = 0, j = 0;
    int next[255];
    get_next(str2, next);
    while (i < str1.size() && j < str2.size()) {
        if (str1[i] == str2[j]) {
            i++, j++;
        } else {
            j = next[j];
        }
    }
    if (j == str2.size()) {
        return i - str2.size();
    } else {
        return 0;
    }

}

int main(int argc, char *argv[]) {
    string str1 = "aabaababaaaba";
    string str2 = "ababaaaba";
    int result = kmp_search(str1, str2);
    cout << result << endl;
    return 0;
}