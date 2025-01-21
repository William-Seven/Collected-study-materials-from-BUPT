#ifndef LR1PARSER_H
#define LR1PARSER_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "DFA.h"
#include "Grammar.h"

class LR1Parser {
   public:
    LR1Parser();

    // 初始化 I0 状态
    void computeFirst(Grammar& grammar);

    // 构造 LR(1) 自动机
    void computeLR1Automaton(Grammar& grammar, int number = 0);

    // 构造 LR(1) 分析表
    void computeAnalysisTable(Grammar& grammar);

    // 使用分析表分析输入串
    void parse(Grammar& grammar, const std::string& inputString);

   private:
    DFA dfa;                                                                              // LR(1) 自动机
    std::unordered_map<int, std::unordered_map<std::string, std::string>> analysisTable;  // 分析表
};

#endif  // LR1PARSER_H
