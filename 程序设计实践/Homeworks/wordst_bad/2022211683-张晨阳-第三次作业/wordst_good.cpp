#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

struct WordInfo {
    std::vector<int> lines;  // 单词在文本中的行号记录，最多记录20行
    size_t count = 0;        // 单词出现次数
};

typedef std::unordered_map<std::string, WordInfo> WordsStatis;

// 单词统计。输入参数为统计信息map，当前单词word，当前单词出现的行号lineNo
void statisWord(WordsStatis& wordsStatis, std::string& word, int lineNo) {
    WordInfo& wordInfo = wordsStatis[word];  // 使用unordered_map的自动插入特性
    wordInfo.count++;
    if (wordInfo.lines.size() < 20) {
        wordInfo.lines.push_back(lineNo);  // 仅存储前20次行号
    }
}

// 排序所需的比较函数
bool cmp(const std::pair<std::string, WordInfo>& a, const std::pair<std::string, WordInfo>& b) {
    return a.second.count > b.second.count;
}

void printStatis(const WordsStatis& wordsStatis) {
    std::vector<std::pair<std::string, WordInfo>> wordsVector(wordsStatis.begin(), wordsStatis.end());

    // 使用partial_sort，仅排序前3名
    std::partial_sort(wordsVector.begin(), wordsVector.begin() + 3, wordsVector.end(), cmp);

    // 统计总单词数和唯一单词数
    size_t totalWords = 0;
    for (const auto& entry : wordsStatis) {
        totalWords += entry.second.count;
    }

    printf("WORD                 COUNT APPEARS-LINES\n");
    for (const auto& wordPair : wordsVector) {
        printf("%-20s %-5ld ", wordPair.first.c_str(), wordPair.second.count);

        // 打印行号
        for (size_t i = 0; i < wordPair.second.lines.size(); ++i) {
            if (i > 0)
                printf(",");
            printf("%d", wordPair.second.lines[i]);
        }
        printf("\n");
    }

    // 打印总单词数、唯一单词数和前三名
    printf("\nTotal number of words: %ld\n", totalWords);
    printf("Number of unique words: %ld\n", wordsStatis.size());

    printf("Top 3 most frequent words:\n");
    for (size_t i = 0; i < 3 && i < wordsVector.size(); ++i) {
        printf("%s: %ld\n", wordsVector[i].first.c_str(), wordsVector[i].second.count);
    }
}

int main(int argc, const char* argv[]) {
    // 命令行需要1个参数，指定要处理的文本文件
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }
    const char* fileName = argv[1];

    FILE* f = fopen(fileName, "r");
    if (f == NULL) {
        printf("can not open file %s\n", fileName);
        return 1;
    }

    WordsStatis wordsStatis;               // 用于存放统计结果
    std::string word;                      // 用于存放当前处理的单词
    int lastChar = 0;                      // 上一个被处理的字符
    int curChar;                           // 当前被处理字符
    int lineNo = 1;                        // 记录当前行号
    while ((curChar = fgetc(f)) != EOF) {  // 依次读取文件中每一个字符，直到遇到EOF结束
        if (curChar == '\n')
            lineNo++;  // 遇到回车符，则行号加1

        if (isalpha(curChar))  // 如果当前字符是字母，则当前单词追加这个字母（统一转换为小写字母）
            word += (char)tolower(curChar);
        else {
            // 如果当前字符不是字母，并且上一个字符是字母，则表明一个单词处理完毕，统计它
            if (isalpha(lastChar)) {
                statisWord(wordsStatis, word, lineNo);
                word.clear();
            }
        }
        lastChar = curChar;
    }

    fclose(f);

    printStatis(wordsStatis);
    return 0;
}
