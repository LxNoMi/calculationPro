/*************************************************************************
	> File Name: stackal.c
	> Author: NoMi
	> Mail: 1559674040@qq.com
	> Created Time: 2019年08月01日 星期四 14时38分56秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"stackcal.h"

//创建操作符栈
oprator_t create_opratorstack(void)
{
    oprator_t op_s = (oprator_t)malloc(sizeof(oprator));
    op_s->top = 0;
    op_s->op[op_s->top] = '#';
    return op_s;
}
//创建操作数栈
number_t create_numberstack(void)
{
    number_t num_s = (number_t)malloc(sizeof(number));
    num_s->top = -1;
    return num_s;
}

//操作符入栈
int pushStack_op(oprator_t op_S, char c)
{
    if(isFull_stack_op(op_S))
        return -1;
    op_S->top++;
    op_S->op[op_S->top] = c;
    return 0;
}

//操作符出栈
char readStack_op(oprator_t op_S)
{
    char ch;
    if(isEmpty_stack_op(op_S))
        return 'E';
    ch = op_S->op[op_S->top];
    op_S->top--;
    return ch;
}

//判断栈满
int isFull_stack_op(oprator_t op_S)
{
    if(N == op_S->top)
        return 1;
    else
        return 0;
}

//判断栈空
int isEmpty_stack_op(oprator_t op_S)
{
    if(-1 == op_S->top)
        return 1;
    else
        return 0;
}

//操作数入栈
int pushStack_cu(number_t num_S, float a)
{
    if(isFull_stack_num(num_S))
        return -1;
    num_S->top++;
    num_S->data[num_S->top] = a;
    return 0;
}

//操作数出栈
float readStack_cu(number_t num_S)
{
    float a;
    if(isEmpty_stack_num(num_S))
        return -1.0;
    a = num_S->data[num_S->top];
    num_S->top--;
    return a;
}

//判断栈满
int isFull_stack_num(number_t num_S)
{
    if(N == num_S->top)
        return 1;
    else
        return 0;
}

//判断栈空
int isEmpty_stack_num(number_t num_S)
{
    if(-1 == num_S->top)
        return 1;
    else
        return 0;
}

//初始化操作符栈
void init_oprator(oprator_t op_S)
{
    int i = 'A';
    for(i = 'A'; i < 'G'; i++)
    {
        op_S->top++;
        op_S->op[op_S->top] = i;
    }
    return;
}
//遍历操作符栈
void print_oprator(oprator_t op_S)
{
    for(;op_S->top > -1; op_S->top--)
    {
        printf("%c ", op_S->op[op_S->top]);
    }
    printf("\n");
    return;
}

//初始化操作数栈
void init_number(number_t num_S)
{
    int i = 0;
    for(i = 0; i < 9; i++)
    {
        num_S->top++;
        num_S->data[num_S->top] = i+1;
    }
    return;
}
//遍历操作数栈
void print_number(number_t num_S)
{
    for(; num_S->top > -1; num_S->top--)
    {
        printf("%.2f ", num_S->data[num_S->top]);
    }
    printf("\n");
    return;
}

//返回优先级
int pri(char ch)
{
    switch(ch)
    {
        case '#':
        {
            return -1;
            break;
        }
        case '+':
        {
            return 2;
            break;
        }
        case '*':
        {
            return 3;
            break;
        }
        case '-':
        {
            return 2;
            break;
        }
        case 'x':
        {
            return 3;
            break;
        }
        case '/':
        {
            return 3;
            break;
        }
        case '^':
        {
            return 4;
            break;
        }
        case '(':
        {
            return 0;
            break;
        }
        case ')':
        {
            return 1;
            break;
        }
        default:
            printf("优先级寻找失败\n");

    }
    return -1;
}

//判断操作符
int is_op(char ch)
{
    int i = 0;
    char s[8] = {'+', '-', 'x', '/', '^', '(', ')', '*'};
    for(i = 0; i < 8; i++)
    {
        if(s[i] == ch)
            return 1;
    }
    return 0;
}

//判断操作数
int is_num(char ch)
{
    if(ch >= '0' && ch <= '9')
        return 1;
    return 0;
}
