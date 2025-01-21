#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

class Grammar {
   public:
    Grammar();

    // 添加产生式
    void addProduction(const std::string& nonTerminal, const std::string& production);

    // 消除左递归
    void eliminateLeftRecursion();

    // 消除左公因子
    void eliminateLeftFactor();

    // 打印文法
    void printGrammar() const;

    // 非终结符、终结符、产生式和起始符号
    std::set<std::string> nonTerminals;
    std::set<std::string> terminals;
    std::map<std::string, std::vector<std::string>> productions;
    std::string startSymbol;

   private:
    // 消除左递归的辅助函数
    void handleImmediateLeftRecursion(const std::string& nonTerminal);
};

#endif  // GRAMMAR_H
