#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

// ���� LineNode �ṹ
struct LineNode
{
    char *text;            // �洢һ���ı�����
    struct LineNode *prev; // ָ��ǰһ�е�ָ��
    struct LineNode *next; // ָ���һ�е�ָ��
};

// ����1 ���ļ�text.txt�����ļ����ݴ洢��������
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
        newNode->text = strdup(line); // ʹ��strdup������������

        newNode->next = NULL; // �����½ڵ����һ���ڵ�ָ��Ϊ��
        if (head == NULL)
        {
            head = newNode;       // ���ͷ�ڵ�Ϊ�գ����½ڵ�����Ϊͷ�ڵ�
            newNode->prev = NULL; // �½ڵ��ǰһ���ڵ�ָ��Ϊ��
        }
        else
        {
            tail->next = newNode; // ���򣬽��½ڵ����ӵ�β�ڵ�
            newNode->prev = tail; // �½ڵ��ǰһ���ڵ�ָ��ָ��β�ڵ�
        }
        tail = newNode; // ����β�ڵ�ָ��Ϊ�½ڵ�
    }

    fclose(file);
    printf("The file has been successfully opened and read into memory!\n\n");
    return head;
}

// ����2 ���Ѿ������ڴ���ı��ļ���ָ������ʾ����Ļ
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

// ����3 ��������
void InsertLine(struct LineNode **head, int lineNumber, const char *newText)
{
    struct LineNode *current = *head;
    int currentLine = 1;

    struct LineNode *newNode = (struct LineNode *)malloc(sizeof(struct LineNode));
    newNode->text = strdup(newText);

    while (current != NULL)
    { // �����½ڵ�
        if (currentLine == lineNumber)
        {
            if (current == *head && lineNumber == 1)
            {
                *head = newNode; // ������뵽ͷ��������ͷָ��
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

    // ����кŴ���������������׷�ӵ�ĩβ
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

// ����4 ɾ����
void DeleteLines(struct LineNode **head, int start, int end)
{
    struct LineNode *current = *head;
    int currentLine = 1;

    while (current != NULL)
    {
        if (currentLine >= start && currentLine <= end)
        {                              // �ҵ�Ҫɾ������
            if (current->prev != NULL) // ����ǰһ���ڵ��nextָ��
                current->prev->next = current->next;
            if (current->next != NULL) // ���º�һ���ڵ��prevָ��
                current->next->prev = current->prev;
            if (current == *head) // ���ɾ������ͷ�ڵ㣬����ͷָ��
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

// ����5 �����ı�����
void InsertText(struct LineNode *head, int line, int position, const char *Intext)
{
    struct LineNode *current = head;
    int currentLine = 1;
    // ��������ֱ���ҵ�ָ����
    while (currentLine != line)
    {
        current = current->next;
        currentLine++;
    }
    // Ϊ���ı������㹻���ڴ�ռ�
    char *newText = (char *)malloc(strlen(current->text) + strlen(Intext) + 1);
    if (newText == NULL) // �����ڴ�������
        return;

    strncpy(newText, current->text, position);
    strcpy(newText + position, Intext);
    strcpy(newText + position + strlen(Intext), current->text + position);

    free(current->text);
    current->text = newText; // �ͷ�ԭʼ�ı����ڴ棬��ָ�����ı�

    printf("Text Insert Successfully!\n\n");
}

// ����6 �����ı�ɾ��
void DeleteText(struct LineNode *head, int line, int position, int length)
{
    struct LineNode *current = head;
    int currentLine = 1;
    // ��������ֱ���ҵ�ָ����
    while (currentLine != line)
    {
        current = current->next;
        currentLine++;
    }
    // ��ɾ�����ȳ����˵�ǰ�ı���ʣ�೤�ȣ������ȵ���Ϊ���ʵ�ֵ
    if (position + length >= strlen(current->text))
        length = strlen(current->text) - position;

    char *newText = (char *)malloc(strlen(current->text) - length + 1);
    if (newText == NULL) // �����ڴ�������
        return;

    strncpy(newText, current->text, position);
    strcpy(newText + position, current->text + position + length);

    free(current->text);
    current->text = newText;

    printf("Text Delete Successfully!\n\n");
}

// ����7 �ı�����
void SearchText(struct LineNode *head, int line, const char *searchStr)
{
    struct LineNode *current = head;
    int currentLine = 1;
    while (currentLine != line)
    {
        current = current->next;
        currentLine++;
    }
    // ʹ��strstr�����ڵ�ǰ�е��ı��в���ָ�����ַ���
    char *found = strstr(current->text, searchStr);

    if (found != NULL)
        printf("The first position is %d\n\n", found - current->text + 1);
    else
        printf("NotFound!\n\n");
}

// ����8 �ı��ļ�����
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

// ���ӹ��� ����ƥ��
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
                    printf("NotMatching!\n\n"); // ���Ų�ƥ��
                    return;
                }
            }
        }

        node = node->next;
    }

    // ���ջΪ�գ�˵���������Ŷ�ƥ��
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
