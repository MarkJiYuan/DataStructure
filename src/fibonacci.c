/*
* @Author: MarkJiYuan
* @Date:   2019-09-23 19:17:46
* @Last Modified by:   MarkJiYuan
* @Last Modified time: 2019-09-26 01:31:21
*/

#include <stdio.h>
// 用于获取微秒级时间
#include <sys/time.h>

// typedef函数指针方便后面使用
typedef double(*Pfun1)(int,double,double);
double fibonacci_tail_recursion(int n, double last, double last2);
// 计时函数
double timer_for_recursion(Pfun1 p, int n, double last, double last2);

typedef double(*Pfun2)(int);
double fibonacci_interative(int n);
// 计时函数
double timer_for_interative(Pfun2 p, int n);

// 主函数入口
int main()
{
    int input;
    printf("获取斐波那契第n项：\n");
    scanf("%d", &input);
    printf("尾递归结果：\t%.0lf\n\n", timer_for_recursion(fibonacci_tail_recursion, input, 1, 1));
    printf("迭代结果：\t%.0lf\n", timer_for_interative(fibonacci_interative, input));
    
    return 0;
}

// 非尾递归的斐波那契我不太会写，最多只能跑到50多项，太慢了
double fibonacci_tail_recursion(int n, double last, double last2)
{
    if (n == 3) return last + last2;
    if (n == 1 || n == 2) return 1;

    double temp;
    // eg. (3,5) -> (5,8)
    temp = last2;
    last2 = last;
    last = temp + last;
    // 使得n减少1，继续递归，这里的n真实含义是还剩下多少次递归
    return fibonacci_tail_recursion(--n, last, last2);

}

// 循环版本的函数，也挺优雅的，逻辑也简单
double fibonacci_interative(int n)
{
    if (n == 1 || n == 2) return 1;
    double last = 1, last2 = 1, temp;
    for (int i = 3; i < n + 1; ++i)
    {
        temp = last2;
        last2 = last;
        last = last + temp;
    }
    return last;
}

// 想实现类似装饰器的效果，可以加在任意一个函数前面，但是不尽如人意，只能对一种函数实现一个计数器
double timer_for_recursion(Pfun1 p, int n, double last, double last2)
{
    double result;
    struct timeval start, end;
    gettimeofday( &start, NULL );
    // 运行太快以致于微妙都不够用，因此将函数跑100000次计算总时长
    for (int i = 0; i < 100000; ++i)
    {
        result = p(n, last, last2);
    }
    gettimeofday( &end, NULL );
    long durantion_sec;
    int durantion_usec;
    durantion_sec = end.tv_sec - start.tv_sec;
    durantion_usec = end.tv_usec - start.tv_usec;
    if (durantion_sec > 0)
    {
        // 处理退位问题
        if (durantion_usec < 0)
        {
            durantion_sec--;
            durantion_usec = 1000000 + durantion_usec;
        }
    }
    printf("*******************\n");
    // C没有字符串，深刻感到有必要实现一个
    printf("Time cost(run 100000 times): %ld.%06d\n", durantion_sec, durantion_usec);
    return result;
}

double timer_for_interative(Pfun2 p, int n)
{
    double result;
    struct timeval start, end;
    gettimeofday( &start, NULL );
    for (int i = 0; i < 100000; ++i)
    {
        result = p(n);
    }
    gettimeofday( &end, NULL );
    long durantion_sec;
    int durantion_usec;
    durantion_sec = end.tv_sec - start.tv_sec;
    durantion_usec = end.tv_usec - start.tv_usec;
    // 当duration_sec为正且duration_usec为负时需要退位
    if (durantion_sec > 0)
    {
        if (durantion_usec < 0)
        {
            durantion_sec--;
            durantion_usec = 1000000 + durantion_usec;
        }
    }
    printf("*******************\n");
    printf("Time cost(run 100000 times): %ld.%06d\n", durantion_sec, durantion_usec);
    return result;
}

