#ifndef LL1PARSER_H
#define LL1PARSER_H

#include <map>
#include <set>
#include <string>
#include "Grammar.h"

class LL1Parser {
   public:
    LL1Parser();

    // 输出Follow集合
    void printFollow();

    // 输出预测分析表
    void printPredictionsTable(Grammar& grammar);

    // 计算First集合
    void computeFirst(Grammar& grammar);

    // 计算Follow集合
    void computeFollow(Grammar& grammar);

    // 构建预测分析表
    void computePredictionsTable(Grammar& grammar);

    // 检查是否是LL(1)文法
    bool isLL1(const Grammar& grammar) const;

    // 解析输入字符串
    void parse(const Grammar& grammar, const std::string& inputString);

   private:
    // First集合、Follow集合和预测分析表
    std::map<std::string, std::set<std::string>> first;
    std::map<std::string, std::set<std::string>> follow;
    std::map<std::pair<std::string, std::string>, std::string> predictionsTable;

    // 辅助函数，用于计算非终结符的First集合
    void calculateFirst(Grammar& grammar, const std::string& nonTerminal);

    // 辅助函数，用于反转产生式字符串
    std::string preReversed(const std::string& production);
};

#endif  // LL1PARSER_H
