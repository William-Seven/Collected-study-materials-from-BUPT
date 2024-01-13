#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

// 定义 LineNode 结构
struct LineNode
{
    char *text;            // 存储一行文本内容
    struct LineNode *prev; // 指向前一行的指针
    struct LineNode *next; // 指向后一行的指针
};

// 功能1 打开文件text.txt，将文件内容存储在链表中
struct LineNode *OpenFile()
{
    FILE *file = fopen("test.txt", "r");
    if (file == NULL)
    {
        printf("Unable to open the file!\n");
        return NULL;
    }

    struct LineNode *head = NULL;
    struct LineNode *tail = NULL;

    char line[100];
    while (fgets(line, sizeof(line), file))
    {
        struct LineNode *newNode = (struct LineNode *)malloc(sizeof(struct LineNode));
        newNode->text = strdup(line); // 使用strdup来复制行内容

        newNode->next = NULL; // 设置新节点的下一个节点指针为空
        if (head == NULL)
        {
            head = newNode;       // 如果头节点为空，将新节点设置为头节点
            newNode->prev = NULL; // 新节点的前一个节点指针为空
        }
        else
        {
            tail->next = newNode; // 否则，将新节点连接到尾节点
            newNode->prev = tail; // 新节点的前一个节点指针指向尾节点
        }
        tail = newNode; // 更新尾节点指针为新节点
    }

    fclose(file);
    printf("The file has been successfully opened and read into memory!\n\n");
    return head;
}

// 功能2 将已经读入内存的文本文件的指定行显示到屏幕
void DisplayLines(struct LineNode *head, int start, int end)
{
    int lineNum = 1;
    struct LineNode *current = head;

    while (current != NULL && lineNum <= end)
    {
        if (lineNum >= start)
            printf("%s", current->text);
        current = current->next;
        lineNum++;
    }
    printf("\n");
}

// 功能3 插入新行
void InsertLine(struct LineNode **head, int lineNumber, const char *newText)
{
    struct LineNode *current = *head;
    int currentLine = 1;

    struct LineNode *newNode = (struct LineNode *)malloc(sizeof(struct LineNode));
    newNode->text = strdup(newText);

    while (current != NULL)
    { // 插入新节点
        if (currentLine == lineNumber)
        {
            if (current == *head && lineNumber == 1)
            {
                *head = newNode; // 如果插入到头部，更新头指针
                newNode->next = current;
            }
            else
            {
                newNode->prev = current;
                newNode->next = current->next;

                if (current->next != NULL)
                    current->next->prev = newNode;

                current->next = newNode;
            }
            printf("Insert Successfully!\n\n");
            return;
        }
        if (current == *head && currentLine == 1)
            currentLine++;
        else
        {
            current = current->next;
            currentLine++;
        }
    }

    // 如果行号大于行数，将新行追加到末尾
    if (current == NULL && currentLine == lineNumber)
    {
        struct LineNode *lastNode = *head;
        while (lastNode->next != NULL)
            lastNode = lastNode->next;

        newNode->prev = lastNode;
        newNode->next = NULL;
        lastNode->next = newNode;
        printf("Insert Successfully!\n\n");
    }
}

// 功能4 删除行
void DeleteLines(struct LineNode **head, int start, int end)
{
    struct LineNode *current = *head;
    int currentLine = 1;

    while (current != NULL)
    {
        if (currentLine >= start && currentLine <= end)
        {                              // 找到要删除的行
            if (current->prev != NULL) // 更新前一个节点的next指针
                current->prev->next = current->next;
            if (current->next != NULL) // 更新后一个节点的prev指针
                current->next->prev = current->prev;
            if (current == *head) // 如果删除的是头节点，更新头指针
                *head = current->next;

            free(current->text);
            free(current);
        }

        if (currentLine > end)
        {
            printf("Delete Successfully!\n\n");
            return;
        }

        current = current->next;
        currentLine++;
    }
}

// 功能5 行内文本插入
void InsertText(struct LineNode *head, int line, int position, const char *Intext)
{
    struct LineNode *current = head;
    int currentLine = 1;
    // 遍历链表，直到找到指定行
    while (currentLine != line)
    {
        current = current->next;
        currentLine++;
    }
    // 为新文本分配足够的内存空间
    char *newText = (char *)malloc(strlen(current->text) + strlen(Intext) + 1);
    if (newText == NULL) // 处理内存分配错误
        return;

    strncpy(newText, current->text, position);
    strcpy(newText + position, Intext);
    strcpy(newText + position + strlen(Intext), current->text + position);

    free(current->text);
    current->text = newText; // 释放原始文本的内存，并指向新文本

    printf("Text Insert Successfully!\n\n");
}

// 功能6 行内文本删除
void DeleteText(struct LineNode *head, int line, int position, int length)
{
    struct LineNode *current = head;
    int currentLine = 1;
    // 遍历链表，直到找到指定行
    while (currentLine != line)
    {
        current = current->next;
        currentLine++;
    }
    // 若删除长度超过了当前文本的剩余长度，将长度调整为合适的值
    if (position + length >= strlen(current->text))
        length = strlen(current->text) - position;

    char *newText = (char *)malloc(strlen(current->text) - length + 1);
    if (newText == NULL) // 处理内存分配错误
        return;

    strncpy(newText, current->text, position);
    strcpy(newText + position, current->text + position + length);

    free(current->text);
    current->text = newText;

    printf("Text Delete Successfully!\n\n");
}

// 功能7 文本查找
void SearchText(struct LineNode *head, int line, const char *searchStr)
{
    struct LineNode *current = head;
    int currentLine = 1;
    while (currentLine != line)
    {
        current = current->next;
        currentLine++;
    }
    // 使用strstr函数在当前行的文本中查找指定的字符串
    char *found = strstr(current->text, searchStr);

    if (found != NULL)
        printf("The first position is %d\n\n", found - current->text + 1);
    else
        printf("NotFound!\n\n");
}

// 功能8 文本文件保存
void saveToFile(struct LineNode *head)
{
    FILE *file = fopen("save.txt", "w");
    if (file == NULL)
    {
        printf("File cannot be opened for writing.\n");
        return;
    }

    struct LineNode *current = head;
    while (current != NULL)
    {
        fputs(current->text, file);
        current = current->next;
    }

    fclose(file);
    printf("Saved Successfully!\n\n");
}

// 附加功能 符号匹配
void BracketsMatching(struct LineNode *node)
{
    struct Stack *stack = NULL;

    while (node != NULL)
    {
        char *line = node->text;
        for (int i = 0; line[i] != '\0'; i++)
        {
            if (line[i] == '{' || line[i] == '(')
                push(&stack, line[i]);
            else if (line[i] == '}' || line[i] == ')')
            {
                char top = pop(&stack);
                if ((line[i] == '}' && top != '{') || (line[i] == ')' && top != '('))
                {
                    printf("NotMatching!\n\n"); // 括号不匹配
                    return;
                }
            }
        }

        node = node->next;
    }

    // 如果栈为空，说明所有括号都匹配
    printf("Matching!\n\n");
}

int main()
{
    int choice;
    struct LineNode *head;
    while (1)
    {
        printf("Please select your operation:\n");
        printf("1. Open and read a file.\n2. Output lines within a range.\n");
        printf("3. Insert a line.\n4. Line Delete.\n");
        printf("5. Insert text within a line.\n6. Delete text within a line.\n");
        printf("7. Find text.\n8. Save a text file.\n");
        printf("9. BracketsMatching\n10. Exit\nEnter:");
        scanf("%d", &choice);

        if (choice == 1)
        {
            head = OpenFile();
            if (head == NULL)
                return 0;
        }
        else if (choice == 2)
        {
            int start, end;
            printf("Please input the range of lines to display(start end):");
            scanf("%d %d", &start, &end);
            DisplayLines(head, start, end);
        }
        else if (choice == 3)
        {
            int num;
            printf("Please enter the line number where the insertion is: ");
            scanf("%d", &num);
            InsertLine(&head, num, "This is a new line.\n");
        }
        else if (choice == 4)
        {
            int start, end;
            printf("Please input the range of lines you wanna delete(start end):");
            scanf("%d %d", &start, &end);
            DeleteLines(&head, start, end);
        }
        else if (choice == 5)
        {
            int line, pos;
            char ch[100];
            printf("Please enter the line number where the insertion is: ");
            scanf("%d", &line);
            printf("Please enter the position where the insertion is:");
            scanf("%d", &pos);
            printf("Please enter the text to insert:");
            scanf("%s", ch);
            InsertText(head, line, pos, ch);
        }
        else if (choice == 6)
        {
            int line, pos, length;
            printf("Please enter the line number where the deletion is: ");
            scanf("%d", &line);
            printf("Please enter the position where the deletion is:");
            scanf("%d", &pos);
            printf("Please enter the text length to delete:");
            scanf("%d", &length);
            DeleteText(head, line, pos, length);
        }
        else if (choice == 7)
        {
            int line;
            char ch[25];
            printf("Please enter the line number where the search is: ");
            scanf("%d", &line);
            printf("Please enter the text you wanna search:");
            scanf("%s", ch);
            SearchText(head, line, ch);
        }
        else if (choice == 8)
            saveToFile(head);
        else if (choice == 9)
            BracketsMatching(head);
        else
            return 0;
    }
}
