#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

class Grammar {
   public:
    Grammar();

    // 添加产生式
    void addProduction(const std::string& non_terminal, const std::string& production);

    // 拓广文法
    void expandGrammar();

    // 打印文法
    void printGrammar() const;

    // 查找产生式编号
    std::string findProduction(const std::string& left, const std::string& right) const;

    // 成员变量
    std::set<std::string> nonTerminals;                                           // 非终结符
    std::set<std::string> terminals;                                              // 终结符
    std::map<std::string, std::vector<std::string>> productions;                  // 产生式
    std::string startSymbol;                                                      // 开始符号
    std::unordered_map<int, std::map<std::string, std::string>> productionCount;  // 产生式编号
    int count;                                                                    // 产生式个数
};

#endif  // GRAMMAR_H
