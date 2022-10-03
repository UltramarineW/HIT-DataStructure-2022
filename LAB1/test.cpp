//
// Created by wujiayang on 2022/10/2.
//
#include<iostream>
#include<ctype.h>
#include<assert.h>
using namespace std;

#define length 125

typedef struct{
    char *begin;
    char *end;
    int StackSize;
}SqStack;

void InitStack(SqStack *Q)
{
    Q->begin = new char[length];
    assert(Q->begin !=NULL);
    Q->end = Q->begin;
    Q->StackSize = length;
}

void InitStr(char str[])
{
    for(int i = 0;i < length;i++){
        str[i] = '\0';
    }
}

void PushStack(SqStack *Q,char c)
{
    *Q->end++ = c;
}

int StackLength(SqStack *Q)
{
    return (Q->end - Q->begin);
}

void PopStack(SqStack *Q,char *c)
{
    *c = *--Q->end;
}

void zhan()
{
    SqStack Q;
    InitStack(&Q);
    char str[length];
    InitStr(str);
    cin >> str;
    char c;
    for(int i = 0;str[i] != '\0';++i){
        if(isdigit(str[i]) || str[i]=='.') cout << str[i];
        else if(str[i] == '*' || str[i] == '/' || str[i] == '(') {if(str[i] != '(') cout << " ";PushStack(&Q,str[i]);}
        else if(str[i] == '+' || str[i] == '-'){
            if(!StackLength(&Q) && i != 0) {cout << " ";PushStack(&Q,str[i]);}
            else{
                if(i == 0) {
                    if(str[i] == '-') cout << str[i];
                    continue;
                }
                PopStack(&Q,&c);
                PushStack(&Q,c);
                if(c == '('){
                    if(str[i-1] == '(') {if(str[i] == '-') cout << str[i];}
                    else {cout << " ";PushStack(&Q,str[i]);}
                }
                else{
                    cout << " ";
                    do{
                        PopStack(&Q,&c);
                        if(c == '(') break;
                        else cout << c << " ";
                    }while(StackLength(&Q) && c != '(');
                    if(c == '(') PushStack(&Q,c);
                    PushStack(&Q,str[i]);
                }
            }
        }
        else if(str[i] == ')')
        {
            PopStack(&Q,&c);
            if(c == '(') continue;
            do{
                cout << " " << c;
                PopStack(&Q,&c);
            }while(c != '(');
        }
    }
    if(StackLength(&Q)) cout << " ";
    while(StackLength(&Q)){
        PopStack(&Q,&c);
        cout << c;
        if(StackLength(&Q) != 0) cout << " ";
    }
}


int main()
{
    zhan();
    return 0;
}
