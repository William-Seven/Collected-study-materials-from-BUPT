#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义哈夫曼树的结点结构
typedef struct Node
{
    char data;
    int weight;
    struct Node *left;
    struct Node *right;
} Node;

// 建立哈夫曼树
Node *buildHuffmanTree(char characters[], int weights[], int n)
{
    // 创建叶子节点，并初始化哈夫曼树的叶子节点数组
    Node *leaves[n];
    for (int i = 0; i < n; ++i)
    {
        leaves[i] = (Node *)malloc(sizeof(Node));
        leaves[i]->data = characters[i];
        leaves[i]->weight = weights[i];
        leaves[i]->left = leaves[i]->right = NULL;
    }

    // 构建哈夫曼树
    while (n > 1)
    {
        // 找到两个权值最小的节点
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

        // 创建新节点，合并两个权值最小的节点
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = '\0'; // 非叶子节点没有字符值
        newNode->weight = leaves[min1]->weight + leaves[min2]->weight;
        newNode->left = leaves[min1];
        newNode->right = leaves[min2];

        // 删除已经合并的两个节点，并将新节点加入数组
        leaves[min1] = newNode;
        leaves[min2] = leaves[n - 1];
        n--;
    }

    // 返回哈夫曼树的根节点
    return leaves[0];
}

// 递归方式实现哈夫曼树的编码
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

    // 叶子结点，输出字符和对应的编码到文件
    if (!(root->left) && !(root->right))
    {
        code[top] = '\0';
        fprintf(outFile, "'%c': %s\n", root->data, code);
        // printf("%c: %s\n", root->data, code);
    }
}

// 获取字符 ch 的哈夫曼编码
void getHuffmanCodeHelper(Node *root, char ch, char path[], int pathLen, char result[])
{
    // 到达叶子节点时，检查是否为目标字符
    if (root->data == ch)
    {
        path[pathLen] = '\0'; // 添加字符串结束符
        strcpy(result, path); // 将路径拷贝到结果中
        return;
    }

    // 在路径上添加当前节点的字符 '0' 表示左子树，'1' 表示右子树
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
    // 假设字符集中不包含换行符，路径长度不超过100
    char path[100];
    char *result = (char *)malloc(100 * sizeof(char));

    // 调用辅助函数进行递归查找
    getHuffmanCodeHelper(root, ch, path, 0, result);

    return result;
}

// 编码文件中的报文并将结果存入CodeFile
void encodeFile(Node *root, FILE *inputFile, FILE *outputFile)
{
    char ch;
    while ((ch = fgetc(inputFile)) != EOF)
    {
        // 获取字符 ch 对应的哈夫曼编码
        char *huffmanCode = getHuffmanCode(root, ch);

        // fputc(huffmanCode, outputFile);
        fputs(huffmanCode, outputFile);
    }

    // 关闭文件
    fclose(inputFile);
    fclose(outputFile);
    printf("Successfully encoded and written to the file CodeFile.txt!\n\n");
}

// 译码CodeFile中的代码并将结果存入TextFile
void decodeFile(Node *root, FILE *inputFile, FILE *outputFile)
{
    Node *current = root;
    char ch;

    // 遍历码字串
    while ((ch = fgetc(inputFile)) != EOF)
    {
        // 根据码字决定向左/右孩子移动
        if (ch == '0')
            current = current->left;
        else
            current = current->right;

        // 如果到达叶子节点，表示找到了一个字符，将其写入输出文件
        if (current->left == NULL && current->right == NULL)
        {
            fputc(current->data, outputFile);
            current = root; // 重置当前节点为根节点，以便继续译码下一个字符
        }
    }

    // 关闭文件
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
    // 建立哈夫曼树并存入文件hfmtree
    FILE *huffmanTreeFile = fopen("hfmTree", "w");
    if (huffmanTreeFile == NULL)
    {
        printf("hfmTree cannot be opened for writing!\n");
        return 0;
    }
    Node *huffmanTreeRoot = buildHuffmanTree(characters, weights, n);
    char code[100]; // 假设最大编码长度不超过100
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
            // 编码
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
            // 译码
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