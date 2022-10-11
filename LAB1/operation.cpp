//
// Created by wujiayang on 2022/9/14.
//
#include <iostream>
#include <algorithm>
#include <stack>
#include <utility>
#include <vector>

/*
 * 因为涉及多位数的计算，因此在设计后缀表达式的时候，数字之间采用‘ ’来分割
 */

using namespace std;

int priority(char ch) {
    if (ch == '(') {
        return 4;
    }
    else if (ch == '+' || ch == '-') {
        return 1;
    }
    else if (ch == '*' || ch == '/') {
        return 2;
    }
    else if (ch == '^') {
        return 3;
    }
    return 0;
}

bool compare(char op1, char op2) {
    if (priority(op1) > priority(op2)) {
        return true;
    }
    return false;
}

void PrintStack(stack<char> s) {
    while(!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
}

void PrintExpression(vector<char> vec) {
    vector<char>::iterator it;
    for(it = vec.begin(); it != vec.end(); it++) {
        cout << *it;
    }
}

void PrintProcess(stack<char> op, vector<char> vec, int i){
    cout << "第" << i << "步中的栈为：";
    PrintStack(std::move(op));
    cout << endl;
    cout << "打印出的字母为 ";
    PrintExpression(std::move(vec));
    cout << endl;
}


float GetResult(vector<char> expression){
    stack<float> value;
    vector<char>::iterator it;
    float num = 0;
    for(it = expression.begin(); it != expression.end(); it++){
        num = 0;
        if (*it == ' '){
            continue;
        }
        // 字符为数字
        if (isdigit(*it)) {
            while (isdigit(*it)) {
                num *= 10;
                num += (float)(*it - '0');
                it++;
            }
            if(*it == '.') {
                it++;
                float mul = 0.1;
                while (isdigit(*it)) {
                    num += (mul * (float)(*it - '0'));
                    mul /= 10;
                    it++;
                }
            }
            it--;
            value.push(num);
            continue;
        }

        // 字符为操作符
        if (*it == '+') {
            num = value.top();
            value.pop();
            num += value.top();
            value.pop();
            value.push(num);
        }
        if (*it == '-') {
            num = -value.top();
            value.pop();
            num += value.top();
            value.pop();
            value.push(num);
        }
        if (*it == '*') {
            num = value.top();
            value.pop();
            num *= value.top();
            value.pop();
            value.push(num);
        }
        if (*it == '/') {
            float temp = value.top();
            value.pop();
            num = value.top() / temp;
            value.pop();
            value.push(num);
        }
        // 扩充运算符 '^'
        if (*it == '^') {
            int temp = (int)value.top();
            value.pop();
            float base = value.top();
            value.pop();
            num = base;
            for(int i = 0; i < temp - 1; i++) {
                num *= base;
            }
            value.push(num);
        }
    }
    return value.top();
}

vector<char> ChangeExpression(char input[], int count) {

    stack<char> op;
    vector<char> expression;

    for (int i = 0; i < count; i++) {
        // 字符为数字
        if (isdigit(input[i])) {
            while (isdigit(input[i])) {
                expression.push_back(input[i]);
                PrintProcess(op, expression, i);
                i++;
            }
            if(input[i] == '.') {
                expression.push_back(input[i]);
                PrintProcess(op, expression, i);
                i++;
                while (isdigit(input[i])) {
                    expression.push_back(input[i]);
                    PrintProcess(op, expression, i);
                    i++;
                }
            }
            i--;
            expression.push_back(' ');
            continue;
        }
        if(input[i] == ')') {
            while(!op.empty() && op.top() != '('){
                expression.push_back(op.top());
                expression.push_back(' ');
                op.pop();
            }
            op.pop();
            PrintProcess(op, expression, i);
            continue;
        }
        // 栈为空或者字符的优先级大于栈顶的优先级
        if ((op.empty()) || (!op.empty() && compare(input[i], op.top()))) {
            op.push(input[i]);
            PrintProcess(op, expression, i);
            continue;
        }
        // 字符的优先级小于栈顶的优先级
        while (!op.empty() && !compare(input[i], op.top())) {
            if(op.top() != '(') {
                expression.push_back(op.top());
                expression.push_back(' ');
                op.pop();
            }
            else break;
        }
        op.push(input[i]);
        PrintProcess(op, expression, i);
    }

    while (!op.empty()) {

        if(op.top() != '(') {
            expression.push_back(op.top());
            expression.push_back(' ');
        }
        op.pop();
    }
    return expression;

}

int ReadLine(char input[]) {
    // 在clion中 可执行文件的位置在cmake-build-debug/LAB1中，所以地址采用../../LAB1/expression.txt
    FILE *pf = fopen("../../LAB1/expression.txt", "r");
    if (pf == nullptr) {
        exit(-1);
    }
    int count = 0;
    char ch;

    while(true) {
        fscanf(pf, "%c", &ch);
        if(ch == '#') {
            break;
        }
    }
    while (true){
        fscanf(pf, "%c", &ch);
        if(ch == '#') {
            break;
        }
        input[count++] = ch;
    }
    return count;
}

int main() {
    // 从文件输入
    char input [100];
    int count = ReadLine(input);

//    // 自动输入的时候添加
//    char input[100] = "(7+15)*(23-28/4)+3^2+4.32*2";
//    char input[100] = "12+(3*(5/6)-7)";
//    int x = 0;
//    int count = 0;
//    while(input[x] != '\0') {
//        count ++;
//        x++;
//    }

//手动输入的时候取消注释
//    while(1) {
//        temp = cin.get();
//        if(temp == '#') break;
//    }
//    while (true) {
//        temp = cin.get();
//        if (temp == '#') break;
//        if (temp == ' ') continue;
//        input[count] = temp;
//        count++;
//    }
//    cout <<count <<endl;

    // 中缀表达式转后缀表达式
    vector<char> expression = ChangeExpression(input, count);

    cout << endl;
    cout << "得到的后缀表达式为 " ;
    PrintExpression(expression);

    //计算后缀表达式值
    float result = GetResult(expression);
    cout <<endl;
    cout << "计算得到的结果为 " << result;
    cout <<endl;

    return 0;
}