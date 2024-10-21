#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// 结构用于存储像素值及其频率
typedef struct
{
    uint8_t pixelValue; // 像素值
    int frequency;      // 出现频率
} PixelFrequency;

// 哈夫曼树节点结构
typedef struct HuffmanNode
{
    uint8_t pixelValue;        // 像素值
    int frequency;             // 出现频率
    struct HuffmanNode *left;  // 左子树
    struct HuffmanNode *right; // 右子树
} HuffmanNode;

// 函数用于统计像素值的频率
void countPixelFrequencies(const char *inputFileName, PixelFrequency *pixelFrequencies)
{
    FILE *inputFile = fopen(inputFileName, "rb");
    if (inputFile == NULL)
    {
        printf("Error opening input BMP file\n");
        exit(1);
    }

    // 移动文件指针到像素数据位置
    fseek(inputFile, 1078, SEEK_SET);

    // 读取像素数据
    uint8_t pixelData[512 * 512];
    fread(pixelData, sizeof(uint8_t), 512 * 512, inputFile);

    // 统计像素值频率
    for (int i = 0; i < 512 * 512; ++i)
    {
        int found = 0;
        for (int j = 0; j < 256; ++j)
        {
            if (pixelFrequencies[j].pixelValue == pixelData[i])
            {
                pixelFrequencies[j].frequency++;
                found = 1;
                break;
            }
        }
        if (!found)
        {
            for (int j = 0; j < 256; ++j)
            {
                if (pixelFrequencies[j].pixelValue == 0)
                {
                    pixelFrequencies[j].pixelValue = pixelData[i];
                    pixelFrequencies[j].frequency = 1;
                    break;
                }
            }
        }
    }

    fclose(inputFile);
}

// 函数用于构建哈夫曼树
HuffmanNode *buildHuffmanTree(PixelFrequency *pixelFrequencies)
{
    // 创建叶子节点数组
    int numLeafNodes = 0;
    HuffmanNode *leafNodes[256];

    for (int i = 0; i < 256; ++i)
    {
        if (pixelFrequencies[i].frequency > 0)
        {
            leafNodes[numLeafNodes] = (HuffmanNode *)malloc(sizeof(HuffmanNode));
            leafNodes[numLeafNodes]->pixelValue = pixelFrequencies[i].pixelValue;
            leafNodes[numLeafNodes]->frequency = pixelFrequencies[i].frequency;
            leafNodes[numLeafNodes]->left = NULL;
            leafNodes[numLeafNodes]->right = NULL;
            numLeafNodes++;
        }
    }

    // 创建内部节点数组
    int numInternalNodes = numLeafNodes - 1;
    HuffmanNode *internalNodes[numInternalNodes];

    // 合并叶子节点直到只剩一个根节点
    for (int i = 0; i < numInternalNodes; ++i)
    {
        // 寻找频率最小的两个节点
        int min1 = 0, min2 = 1;
        for (int j = 2; j <= i; ++j)
        {
            if (leafNodes[j]->frequency < leafNodes[min1]->frequency)
            {
                min2 = min1;
                min1 = j;
            }
            else if (leafNodes[j]->frequency < leafNodes[min2]->frequency)
            {
                min2 = j;
            }
        }

        // 创建新的内部节点
        internalNodes[i] = (HuffmanNode *)malloc(sizeof(HuffmanNode));
        internalNodes[i]->frequency = leafNodes[min1]->frequency + leafNodes[min2]->frequency;
        internalNodes[i]->left = leafNodes[min1];
        internalNodes[i]->right = leafNodes[min2];

        // 将已经合并的节点从叶子节点数组中删除
        leafNodes[min1] = internalNodes[i];
        leafNodes[min2] = leafNodes[i + 2];
    }

    // 返回哈夫曼树的根节点
    return internalNodes[0];
}

// 函数用于生成哈夫曼编码表
void generateHuffmanCodesHelper(HuffmanNode *node, char *code, int depth, char **huffmanCodes)
{
    // 如果是叶子节点，将编码存储在数组中
    if (node->left == NULL && node->right == NULL)
    {
        code[depth] = '\0'; // 在编码末尾添加 null 终止符
        huffmanCodes[node->pixelValue] = strdup(code);
        return;
    }

    // 左子树表示 0
    code[depth] = '0';
    generateHuffmanCodesHelper(node->left, code, depth + 1, huffmanCodes);

    // 右子树表示 1
    code[depth] = '1';
    generateHuffmanCodesHelper(node->right, code, depth + 1, huffmanCodes);
}

void generateHuffmanCodes(HuffmanNode *root, char **huffmanCodes)
{
    // 初始化编码字符串
    char code[256];
    generateHuffmanCodesHelper(root, code, 0, huffmanCodes);
}

// 编码并存储
void encodeBMPAndWriteToFile(const char *bmpFilename, const char *outputFilename, char **huffmanCodes)
{
    FILE *bmpFile = fopen(bmpFilename, "rb");
    if (!bmpFile)
    {
        perror("Error opening BMP file");
        exit(EXIT_FAILURE);
    }

    FILE *outputFile = fopen(outputFilename, "w");
    if (!outputFile)
    {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    // 读取bmp文件并编码像素值
    uint8_t pixelValue;
    while (fread(&pixelValue, sizeof(uint8_t), 1, bmpFile) == 1)
    {
        // 将哈夫曼编码写入output文件
        fprintf(outputFile, "%s", huffmanCodes[pixelValue]);
    }

    // 关闭文件
    fclose(bmpFile);
    fclose(outputFile);

    printf("BMP file has been successfully encoded and written to %s.\n", outputFilename);
}

int main()
{
    // 初始化像素频率数组
    PixelFrequency pixelFrequencies[256];
    for (int i = 0; i < 256; ++i)
    {
        pixelFrequencies[i].pixelValue = 0;
        pixelFrequencies[i].frequency = 0;
    }

    // 读取 BMP 文件，获取像素值频率
    countPixelFrequencies("lena.bmp", pixelFrequencies);

    // 构建哈夫曼树
    HuffmanNode *huffmanTreeRoot = buildHuffmanTree(pixelFrequencies);

    // 初始化哈夫曼编码表
    char *huffmanCodes[256];
    for (int i = 0; i < 256; ++i)
        huffmanCodes[i] = NULL;

    // 生成哈夫曼编码
    generateHuffmanCodes(huffmanTreeRoot, huffmanCodes);

    // 编码并存储
    const char *bmpFilename = "lena.bmp";
    const char *outputFilename = "output.txt";
    encodeBMPAndWriteToFile(bmpFilename, outputFilename, huffmanCodes);

    return 0;
}
