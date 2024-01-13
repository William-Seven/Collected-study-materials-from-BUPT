#include <stdio.h>
#include <stdlib.h>

struct Stack
{
    char data;
    struct Stack *next;
};

// 入栈
void push(struct Stack **top, char data)
{
    struct Stack *newNode = (struct Stack *)malloc(sizeof(struct Stack));
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

// 出栈
char pop(struct Stack **top)
{
    if (*top == NULL)
    {
        // 栈为空，返回特殊值表示错误
        return '\0';
    }
    struct Stack *temp = *top;
    char data = temp->data;
    *top = temp->next;
    free(temp);
    return data;
}