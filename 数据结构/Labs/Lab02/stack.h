#include <stdio.h>
#include <stdlib.h>

struct Stack
{
    char data;
    struct Stack *next;
};

// ��ջ
void push(struct Stack **top, char data)
{
    struct Stack *newNode = (struct Stack *)malloc(sizeof(struct Stack));
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

// ��ջ
char pop(struct Stack **top)
{
    if (*top == NULL)
    {
        // ջΪ�գ���������ֵ��ʾ����
        return '\0';
    }
    struct Stack *temp = *top;
    char data = temp->data;
    *top = temp->next;
    free(temp);
    return data;
}