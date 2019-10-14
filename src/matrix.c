/*
* @Author: MarkJiYuan
* @Date:   2019-09-25 16:17:41
* @Last Modified by:   MarkJiYuan
* @Last Modified time: 2019-09-26 01:38:20
*/

#include <stdio.h>
// 下面这两个是用来生成随机数的
#include <stdlib.h>
#include <time.h>

void initialize_matrix(int *p, int row, int column);
void print_matrix(int *p, int row, int column);
void tranverse_in_place(int *p, int rank);

int main()
{
    int matrix[3][3];
    int row, column, *start_element;

    // 获取row和column而非直接使用3，3是为了方便修改，只用改上面即可
    row = (int)sizeof(matrix)/sizeof(matrix[0]);
    column = (int)sizeof(matrix[0])/sizeof(matrix[0][0]);

    // 本题我采用的方法可能有点笨了，一直需要带着首元素和行列数
    start_element = &matrix[0][0];

    initialize_matrix(start_element, row, column);
    print_matrix(start_element, row, column);
    // 本题仅实现了n*n矩阵的转置，不支持m*n矩阵的转置
    if (row == column)
    {
        tranverse_in_place(start_element, row);
    }
    print_matrix(start_element, row, column);

   
    return 0;
}

void initialize_matrix(int *p, int row, int column)
{
    // 设定随机时间种子
    srand(time(0));
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < column; ++j)
        {
            // 向矩阵中填入随机生成的[0,99]的整数
            *p++ = rand() % 100;
        }
    }
}

void print_matrix(int *p, int row, int column)
{
    printf("This matrix is:\n");
    // i是row，j是column
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < column; ++j)
        {
            // 行间用空格
            printf("%d ", *p++);
        }
        // 矩阵下一行则换行
        printf("\n");
    }
}

void tranverse_in_place(int *p, int rank)
{
    printf("\nTransposing Matrix...\n");
    int temp;
    // 为了方便后面转置算法的实现，这里先在函数内部新建了一个指针矩阵，指向要转置的矩阵
    // 这样的好处是可以方便地进行下标访问
    // 缺点是占用了额外的空间
    int *matrix[rank][rank];
    for (int i = 0; i < rank; ++i)
    {
        for (int j = 0; j < rank; ++j)
        {
            matrix[i][j] = p++;
        }
    }

    // 使用下标访问轻松转置矩阵
    // 需要交换的仅为矩阵右上方的三角形，不包括对角线
    // 转换方法即将其值与对应位置的值互换
    for (int i = 0; i < rank; ++i)
    {
        for (int j = i+1; j < rank; ++j)
        { 
            temp = *matrix[i][j];
            *matrix[i][j] = *matrix[j][i];
            *matrix[j][i] = temp;
        }
    }
}

