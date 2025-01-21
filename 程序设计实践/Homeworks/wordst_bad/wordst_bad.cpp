#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct WordInfo {
    std::vector<int> lines;  // 单词在文本中的行号记录
};

typedef std::map<std::string, WordInfo*> WordsStatis;

typedef std::pair<std::string, WordInfo*> WordPair;

typedef std::vector<WordPair> WordsVector;

// 单词统计。输入参数为统计信息map，当前单词word，当前单词出现的行号lineNo
void statisWord(WordsStatis& wordsStatis, std::string& word, int lineNo) {
    if (wordsStatis.find(word) == wordsStatis.end()) {
        // 如果当前统计表中没找到，则新增一项
        WordInfo* wordInfo = new WordInfo;
        wordInfo->lines.push_back(lineNo);
        wordsStatis[word] = wordInfo;
    } else {
        // 如果找到了，则增加一个新的行号
        wordsStatis[word]->lines.push_back(lineNo);
    }
}

// 排序所需的比较函数
bool cmp(WordPair a, WordPair b) {
    return a.second->lines.size() > b.second->lines.size();
}

void printStatis(WordsStatis& wordsStatis) {
    // 将统计信息map中的数据复制到一个vector中
    WordsVector wordsVector(wordsStatis.begin(), wordsStatis.end());

    // 对vector进行排序
    std::sort(wordsVector.begin(), wordsVector.end(), cmp);

    // 打印统计结果
    printf("WORD                 COUNT APPEARS-LINES\n");
    WordsVector::iterator iter;
    for (iter = wordsVector.begin(); iter != wordsVector.end(); iter++) {
        // 打印单词以及出现的次数统计
        printf("%-20s %-5ld ", iter->first.c_str(), iter->second->lines.size());

        // 打印此单词出现的行号，最多打印20个
        int i = 0;
        std::vector<int>::iterator linesIter;
        for (linesIter = iter->second->lines.begin(); linesIter != iter->second->lines.end(); linesIter++) {
            if (i != 0)
                printf(",");
            printf("%d", *linesIter);
            if (++i >= 20)
                break;
        }
        printf("\n");
    }

    // 输出额外统计信息
    size_t totalWords = 0;
    for (auto& entry : wordsStatis) {
        totalWords += entry.second->lines.size();
    }
    printf("\nTotal number of words: %ld\n", totalWords);
    printf("Number of unique words: %ld\n", wordsVector.size());

    printf("Top 3 most frequent words:\n");
    for (size_t i = 0; i < 3 && i < wordsVector.size(); i++) {
        printf("%s: %ld\n", wordsVector[i].first.c_str(), wordsVector[i].second->lines.size());
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
