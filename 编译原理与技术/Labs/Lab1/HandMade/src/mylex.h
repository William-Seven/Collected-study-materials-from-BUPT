#ifndef MYLEX_H
#define MYLEX_H

#include <string>
#include <unordered_map>  // 用于统计token种类和数量
#include <vector>
#include "token.h"

class Lexer {
   public:
    Lexer(const std::string& input);
    Token getNextToken();          // 获取下一个token
    void printStatistics() const;  // 用于输出统计信息

   private:
    // peek()：查看当前字符，不移动position
    char peek() const;

    // advance()：移动到下一个字符并更新位置和字符计数
    char advance();

    // skipWhitespaceAndComments()：跳过空白字符和注释
    void skipWhitespaceAndComments();

    // identifier()：处理标识符或关键字
    Token identifier();

    // number()：处理数字（包括十进制、八进制、十六进制和浮点数）
    Token number();

    // floatNumber()：处理浮点数
    Token floatNumber(int start_line, int start_column, std::string text);

    // octalNumber()：处理八进制数
    Token octalNumber(int start_line, int start_column, std::string text);

    // hexNumber()：处理十六进制数
    Token hexNumber(int start_line, int start_column, std::string text);

    // hexFloatNumber()：处理十六进制浮点数
    Token hexFloatNumber(int start_line, int start_column, std::string text);

    // stringLiteral()：处理字符串字面量
    Token stringLiteral();

    // charConstant()：处理字符常量
    Token charConstant();

    // punctuator()：处理标点符号
    Token punctuator();

    std::string input;    // 输入的源代码
    size_t position;      // 当前字符在输入中的位置
    int line;             // 当前行号
    int column;           // 当前列号
    int totalTokens;      // 统计总的token数量
    int totalCharacters;  // 统计总的字符数量

    // 使用unordered_map来记录每种token的数量，key是TokenType，value是出现的次数
    std::unordered_map<TokenType, int> tokenCounts;
};

#endif
