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
        if ((op.empty()) || (!op.empty() && compare(input[i], op.top()))) {
            op.push(input[i]);
            PrintProcess(op, expression, i);
            continue;
        }
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

int main() {
    char input[100] = "(7+15)*(23-28/4)+3^2+4.32*2";
    char temp;
    int count = 0;

    // 自动输入的时候添加
    int x = 0;
    while(input[x] != '\0') {
        count ++;
        x++;
    }

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


    vector<char> expression = ChangeExpression(input, count);

    cout << endl;
    cout << "得到的后缀表达式为 " ;
    PrintExpression(expression);


    float result = GetResult(expression);
    cout <<endl;
    cout << "计算得到的结果为 " << result;
    cout <<endl;

    return 0;
}