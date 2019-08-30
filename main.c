/*************************************************************************
	> File Name: main.c
	> Author: NoMi
	> Mail: 1559674040@qq.com
	> Created Time: 2019年08月01日 星期四 14时17分16秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include"stackcal.h"

void Init(void);
void Run(void);
void Exit(void);
float op_num(char c, float d1, float d2);

int main()
{
    Init();
    Run();
    Exit();

    /*以下注释部分代码为了测试操作符栈和操作数栈而用，经测试已经成功！*/
    //oprator_t opr = create_opratorstack();
    //init_oprator(opr);
    //print_oprator(opr);
    //number_t num = create_numberstack();
    //init_number(num);
    //print_number(num);
    return 0;
}

//程序界面初始化
void Init(void)
{
    printf("*************************************************************\n");
    printf("*                  智能计算器程序                           *\n");
    printf("*                 powwered by NoMi                          * \n");
    printf("*************************************************************\n");

    return;
}
//清洗字符串
void wash_str(char a[])
{
    char *p = a;
    while(1)
    {
        if('=' == *p)
            break;
        else
        {
            if('\0' == *(p+1))
            {
                *(++p) = '=';
                break;
            }
        }
        p++;
    }
    //printf("%s\n", a);
}

//程序执行函数
void Run(void)
{
    char *p = NULL;
    float d1, d2, d3;
    float count = 0;
    char t_c;
    int flag = 0;
    oprator_t opr = create_opratorstack();
    number_t num = create_numberstack();
    char str[41]="";
    printf("请输入表达式...\n>");
    gets(str);

    //处理输入字符串
    wash_str(str);
    p = str;

    //精华部分，入栈出栈，进行计算！
    while('\0' != *p)
    {
        //sleep(1);
        //操作数处理
        if(is_num(*p))
        {
            count = count*10 + (*p - '0');
            if(is_num(*(p+1)))
            {
                p++;
                continue;
            }
            else
            {
                pushStack_cu(num, count);
                //printf("in:%.2f ", count);
                count = 0;
            }
        }
        //操作符处理
        else if(is_op(*p))
        {
            //操作符进栈情况
            if(('(' == *p) || (pri(opr->op[opr->top]) < pri(*p)) )
               {
                pushStack_op(opr, *p);
                //printf("in:%c ", *p);
               }
            //右括号处理
            else if(')' == *p)
            {
                //printf("meet:) ");
                t_c = readStack_op(opr);
                while('(' != t_c)
                {
                    d1 = readStack_cu(num);
                    d2 = readStack_cu(num);
                    d3 = op_num(t_c, d2, d1);
                    pushStack_cu(num, d3);
                    //printf("take %.2f %.2f get:%.2f\n", d2, d1, d3);
                    t_c = readStack_op(opr);
                    //sleep(1);
                }
                //printf("out:( \n");
            }
            //优先级高，进行运算并继续比较
            else if(pri(opr->op[opr->top]) >= pri(*p))
            {
                d1 = readStack_cu(num);
                d2 = readStack_cu(num);
                d3 = op_num(readStack_op(opr), d2, d1);
                pushStack_cu(num, d3);
                //printf("take %.2f %.2f get:%.2f", d2, d1, d3);
                pushStack_op(opr, *p);
                //sleep(1);
            }
        }
        //遇到"="号
        else if('=' == *p)
        {
            while('#' != opr->op[opr->top])
            {
                d1 = readStack_cu(num);
                d2 = readStack_cu(num);
                d3 = op_num(readStack_op(opr), d2, d1);
                pushStack_cu(num, d3);
                //printf("take %.2f %.2f get:%.2f", d2, d1, d3);
                //sleep(1);
            }
        }
        if('z' == *p || 'Z' == *p)
        {
            flag = -1;
            break;
        }
        p++;
    }
    printf("结果:%g\n\n******************************************\n", readStack_cu(num));
    if(-1 != flag)
        Run();

    return;
}

//程序结束函数
void Exit(void)
{
    printf("*************************************************************************\n");
    printf("*                       智能计算器程序结束                              * \n");
    printf("*************************************************************************\n");

    return;
}

//计算函数
float op_num(char c, float d1, float d2)
{
    switch(c)
    {
        case '+':
        {
            return d1 + d2;
            break;
        }
        case '-':
        {
            return d1 - d2;
            break;
        }
        case 'x':
        {
            return d1 * d2;
            break;
        }
        case '*':
        {
            return d1 * d2;
            break;
        }
        case '/':
        {
            if(0 == d2)
            {
                printf("被除数不为0！\n");
                return 0;
            }
            else
            {
                return d1/d2;
                break;
            }
        }
        case '^':
        {
            int n = d2;
            int sum = 1;
            while(n--)
                sum *= d1;
            return sum;
            break;
        }
        default:
            printf("暂不提供“%c”支持!\n", c);
            return 0;
    }
}
