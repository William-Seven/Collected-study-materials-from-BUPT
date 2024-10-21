#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ������������Ľ��ṹ
typedef struct Node
{
    char data;
    int weight;
    struct Node *left;
    struct Node *right;
} Node;

// ������������
Node *buildHuffmanTree(char characters[], int weights[], int n)
{
    // ����Ҷ�ӽڵ㣬����ʼ������������Ҷ�ӽڵ�����
    Node *leaves[n];
    for (int i = 0; i < n; ++i)
    {
        leaves[i] = (Node *)malloc(sizeof(Node));
        leaves[i]->data = characters[i];
        leaves[i]->weight = weights[i];
        leaves[i]->left = leaves[i]->right = NULL;
    }

    // ������������
    while (n > 1)
    {
        // �ҵ�����Ȩֵ��С�Ľڵ�
        int min1 = 0, min2 = 1;
        if (leaves[min1]->weight > leaves[min2]->weight)
        {
            int temp = min1;
            min1 = min2;
            min2 = temp;
        }

        for (int i = 2; i < n; i++)
        {
            if (leaves[i]->weight < leaves[min1]->weight)
            {
                min2 = min1;
                min1 = i;
            }
            else if (leaves[i]->weight < leaves[min2]->weight)
                min2 = i;
        }

        // �����½ڵ㣬�ϲ�����Ȩֵ��С�Ľڵ�
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = '\0'; // ��Ҷ�ӽڵ�û���ַ�ֵ
        newNode->weight = leaves[min1]->weight + leaves[min2]->weight;
        newNode->left = leaves[min1];
        newNode->right = leaves[min2];

        // ɾ���Ѿ��ϲ��������ڵ㣬�����½ڵ��������
        leaves[min1] = newNode;
        leaves[min2] = leaves[n - 1];
        n--;
    }

    // ���ع��������ĸ��ڵ�
    return leaves[0];
}

// �ݹ鷽ʽʵ�ֹ��������ı���
void encodeHuffmanTree(Node *root, char code[], int top, FILE *outFile)
{
    if (root->left)
    {
        code[top] = '0';
        encodeHuffmanTree(root->left, code, top + 1, outFile);
    }

    if (root->right)
    {
        code[top] = '1';
        encodeHuffmanTree(root->right, code, top + 1, outFile);
    }

    // Ҷ�ӽ�㣬����ַ��Ͷ�Ӧ�ı��뵽�ļ�
    if (!(root->left) && !(root->right))
    {
        code[top] = '\0';
        fprintf(outFile, "'%c': %s\n", root->data, code);
        // printf("%c: %s\n", root->data, code);
    }
}

// ��ȡ�ַ� ch �Ĺ���������
void getHuffmanCodeHelper(Node *root, char ch, char path[], int pathLen, char result[])
{
    // ����Ҷ�ӽڵ�ʱ������Ƿ�ΪĿ���ַ�
    if (root->data == ch)
    {
        path[pathLen] = '\0'; // ����ַ���������
        strcpy(result, path); // ��·�������������
        return;
    }

    // ��·������ӵ�ǰ�ڵ���ַ� '0' ��ʾ��������'1' ��ʾ������
    if (root->left)
    {
        path[pathLen] = '0';
        getHuffmanCodeHelper(root->left, ch, path, pathLen + 1, result);
    }

    if (root->right)
    {
        path[pathLen] = '1';
        getHuffmanCodeHelper(root->right, ch, path, pathLen + 1, result);
    }
}

char *getHuffmanCode(Node *root, char ch)
{
    // �����ַ����в��������з���·�����Ȳ�����100
    char path[100];
    char *result = (char *)malloc(100 * sizeof(char));

    // ���ø����������еݹ����
    getHuffmanCodeHelper(root, ch, path, 0, result);

    return result;
}

// �����ļ��еı��Ĳ����������CodeFile
void encodeFile(Node *root, FILE *inputFile, FILE *outputFile)
{
    char ch;
    while ((ch = fgetc(inputFile)) != EOF)
    {
        // ��ȡ�ַ� ch ��Ӧ�Ĺ���������
        char *huffmanCode = getHuffmanCode(root, ch);

        // fputc(huffmanCode, outputFile);
        fputs(huffmanCode, outputFile);
    }

    // �ر��ļ�
    fclose(inputFile);
    fclose(outputFile);
    printf("Successfully encoded and written to the file CodeFile.txt!\n\n");
}

// ����CodeFile�еĴ��벢���������TextFile
void decodeFile(Node *root, FILE *inputFile, FILE *outputFile)
{
    Node *current = root;
    char ch;

    // �������ִ�
    while ((ch = fgetc(inputFile)) != EOF)
    {
        // �������־�������/�Һ����ƶ�
        if (ch == '0')
            current = current->left;
        else
            current = current->right;

        // �������Ҷ�ӽڵ㣬��ʾ�ҵ���һ���ַ�������д������ļ�
        if (current->left == NULL && current->right == NULL)
        {
            fputc(current->data, outputFile);
            current = root; // ���õ�ǰ�ڵ�Ϊ���ڵ㣬�Ա����������һ���ַ�
        }
    }

    // �ر��ļ�
    fclose(inputFile);
    fclose(outputFile);
    printf("Successfully decoded and written to the file TextFile.txt!\n\n");
}

int main()
{
    int n;
    printf("Step 1:Initialize\n");
    printf("Enter the number of characters: ");
    scanf("%d", &n);
    getchar();
    char characters[30];
    int weights[30];

    printf("Enter the characters and their weights:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%c %d", &characters[i], &weights[i]);
        getchar();
    }
    // �������������������ļ�hfmtree
    FILE *huffmanTreeFile = fopen("hfmTree", "w");
    if (huffmanTreeFile == NULL)
    {
        printf("hfmTree cannot be opened for writing!\n");
        return 0;
    }
    Node *huffmanTreeRoot = buildHuffmanTree(characters, weights, n);
    char code[100]; // ���������볤�Ȳ�����100
    encodeHuffmanTree(huffmanTreeRoot, code, 0, huffmanTreeFile);
    fclose(huffmanTreeFile);
    printf("Successfully build Huffman tree and store in file!\n\n");

    while (1)
    {
        int choice;
        printf("1. Build Huffman tree and store in file (Already done. Don't choose!)\n");
        printf("2. Encode file content\n");
        printf("3. Decode message\n");
        printf("4. Exit\n");
        printf("Please enter the operation you want to perform: ");
        scanf("%d", &choice);
        if (choice == 2)
        {
            // ����
            FILE *inputFile = fopen("ToBeTran.txt", "r");
            FILE *codeFile = fopen("CodeFile.txt", "w");
            if (codeFile == NULL)
            {
                printf("CodeFile.txt cannot be opened for writing!\n");
                return 0;
            }
            encodeFile(huffmanTreeRoot, inputFile, codeFile);
        }
        else if (choice == 3)
        {
            // ����
            FILE *codeFileInput = fopen("CodeFile.txt", "r");
            FILE *textFileOutput = fopen("TextFile.txt", "w");
            if (textFileOutput == NULL)
            {
                printf("TextFile.txt cannot be opened for writing!\n");
                return 0;
            }
            decodeFile(huffmanTreeRoot, codeFileInput, textFileOutput);
        }
        else if (choice == 4)
        {
            printf("Exit!\n");
            return 0;
        }
        else
        {
            printf("Invalid choice!\n");
            break;
        }
    }
    return 0;
}