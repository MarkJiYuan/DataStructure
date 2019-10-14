/*
* @Author: MarkJiYuan
* @Date:   2019-09-25 16:21:42
* @Last Modified by:   MarkJiYuan
* @Last Modified time: 2019-09-26 01:42:44
*/

#include <stdio.h>
#include <stdlib.h>

// 定义Node，和Node的指针Pnode
typedef struct ListNode {
    int value;
    struct ListNode* next;
}Node, *Pnode;

Pnode create_linked_list(int length);
void print_linked_list(Pnode Phead);
Pnode flip_linked_list(Pnode Phead);

int main()
{
    Pnode Pstart;
    Pstart = create_linked_list(10);
    print_linked_list(Pstart);

    // 函数返回新的链表头，将其赋给Pstart
    Pstart = flip_linked_list(Pstart);
    print_linked_list(Pstart);
    return 0;
}

Pnode create_linked_list(int length)
{
    Pnode Phead = (Pnode)malloc(sizeof(Node));
    Pnode Ptail = Phead;
    Ptail->next = NULL;
    for (int i = 0; i < length; ++i)
    {
        Pnode newnode = (Pnode)malloc(sizeof(Node));
        Ptail->next = newnode;
        newnode->value = i;
        newnode->next = NULL;
        Ptail = newnode;
    }
    return Phead->next;
}

void print_linked_list(Pnode Phead)
{
    printf("Printing Linked List:\n");
    Pnode Ptail = Phead;
    while (Ptail->next!=NULL)
    {
        printf("%d ", Ptail->value);
        Ptail = Ptail->next;
    }
    printf("%d\n", Ptail->value);
}

Pnode flip_linked_list(Pnode Phead)
{
    // 是否存在更巧妙的算法？
    Pnode Pprev, Pnow, Pnext, Ptemp;
    Pprev = Phead;
    Pnow = Pprev->next;
    Pnext = Pnow->next;

    while (Pnext->next!=NULL)
    {
        Pnow->next = Pprev;
        Ptemp = Pnow;
        Pnow = Pnext;
        Pnext = Pnext->next;
        Pprev = Ptemp;
    }

    // 处理结尾处特例
    Pnow->next = Pprev;
    Pnext->next = Pnow;
    Phead->next = NULL;

    // 返回新的链表头
    return Pnext;
}
