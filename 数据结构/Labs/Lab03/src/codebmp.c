#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// �ṹ���ڴ洢����ֵ����Ƶ��
typedef struct
{
    uint8_t pixelValue; // ����ֵ
    int frequency;      // ����Ƶ��
} PixelFrequency;

// ���������ڵ�ṹ
typedef struct HuffmanNode
{
    uint8_t pixelValue;        // ����ֵ
    int frequency;             // ����Ƶ��
    struct HuffmanNode *left;  // ������
    struct HuffmanNode *right; // ������
} HuffmanNode;

// ��������ͳ������ֵ��Ƶ��
void countPixelFrequencies(const char *inputFileName, PixelFrequency *pixelFrequencies)
{
    FILE *inputFile = fopen(inputFileName, "rb");
    if (inputFile == NULL)
    {
        printf("Error opening input BMP file\n");
        exit(1);
    }

    // �ƶ��ļ�ָ�뵽��������λ��
    fseek(inputFile, 1078, SEEK_SET);

    // ��ȡ��������
    uint8_t pixelData[512 * 512];
    fread(pixelData, sizeof(uint8_t), 512 * 512, inputFile);

    // ͳ������ֵƵ��
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

// �������ڹ�����������
HuffmanNode *buildHuffmanTree(PixelFrequency *pixelFrequencies)
{
    // ����Ҷ�ӽڵ�����
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

    // �����ڲ��ڵ�����
    int numInternalNodes = numLeafNodes - 1;
    HuffmanNode *internalNodes[numInternalNodes];

    // �ϲ�Ҷ�ӽڵ�ֱ��ֻʣһ�����ڵ�
    for (int i = 0; i < numInternalNodes; ++i)
    {
        // Ѱ��Ƶ����С�������ڵ�
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

        // �����µ��ڲ��ڵ�
        internalNodes[i] = (HuffmanNode *)malloc(sizeof(HuffmanNode));
        internalNodes[i]->frequency = leafNodes[min1]->frequency + leafNodes[min2]->frequency;
        internalNodes[i]->left = leafNodes[min1];
        internalNodes[i]->right = leafNodes[min2];

        // ���Ѿ��ϲ��Ľڵ��Ҷ�ӽڵ�������ɾ��
        leafNodes[min1] = internalNodes[i];
        leafNodes[min2] = leafNodes[i + 2];
    }

    // ���ع��������ĸ��ڵ�
    return internalNodes[0];
}

// �����������ɹ����������
void generateHuffmanCodesHelper(HuffmanNode *node, char *code, int depth, char **huffmanCodes)
{
    // �����Ҷ�ӽڵ㣬������洢��������
    if (node->left == NULL && node->right == NULL)
    {
        code[depth] = '\0'; // �ڱ���ĩβ��� null ��ֹ��
        huffmanCodes[node->pixelValue] = strdup(code);
        return;
    }

    // ��������ʾ 0
    code[depth] = '0';
    generateHuffmanCodesHelper(node->left, code, depth + 1, huffmanCodes);

    // ��������ʾ 1
    code[depth] = '1';
    generateHuffmanCodesHelper(node->right, code, depth + 1, huffmanCodes);
}

void generateHuffmanCodes(HuffmanNode *root, char **huffmanCodes)
{
    // ��ʼ�������ַ���
    char code[256];
    generateHuffmanCodesHelper(root, code, 0, huffmanCodes);
}

// ���벢�洢
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

    // ��ȡbmp�ļ�����������ֵ
    uint8_t pixelValue;
    while (fread(&pixelValue, sizeof(uint8_t), 1, bmpFile) == 1)
    {
        // ������������д��output�ļ�
        fprintf(outputFile, "%s", huffmanCodes[pixelValue]);
    }

    // �ر��ļ�
    fclose(bmpFile);
    fclose(outputFile);

    printf("BMP file has been successfully encoded and written to %s.\n", outputFilename);
}

int main()
{
    // ��ʼ������Ƶ������
    PixelFrequency pixelFrequencies[256];
    for (int i = 0; i < 256; ++i)
    {
        pixelFrequencies[i].pixelValue = 0;
        pixelFrequencies[i].frequency = 0;
    }

    // ��ȡ BMP �ļ�����ȡ����ֵƵ��
    countPixelFrequencies("lena.bmp", pixelFrequencies);

    // ������������
    HuffmanNode *huffmanTreeRoot = buildHuffmanTree(pixelFrequencies);

    // ��ʼ�������������
    char *huffmanCodes[256];
    for (int i = 0; i < 256; ++i)
        huffmanCodes[i] = NULL;

    // ���ɹ���������
    generateHuffmanCodes(huffmanTreeRoot, huffmanCodes);

    // ���벢�洢
    const char *bmpFilename = "lena.bmp";
    const char *outputFilename = "output.txt";
    encodeBMPAndWriteToFile(bmpFilename, outputFilename, huffmanCodes);

    return 0;
}
