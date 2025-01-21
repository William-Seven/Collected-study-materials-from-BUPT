#ifndef DFA_H
#define DFA_H

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "Grammar.h"

class DFA {
   public:
    DFA();

    // 计算 First 集，用于 LR1 自动机的闭包计算
    std::string getFirst(const Grammar& grammar, const std::string& symbol);

    // 计算 LR1 自动机的闭包
    std::set<std::pair<std::pair<std::string, std::string>, std::set<std::string>>>
    getClosure(const Grammar& grammar, const std::set<std::pair<std::pair<std::string, std::string>, std::set<std::string>>>& state);

    // 合并同一左部产生式的 lookahead 集
    std::set<std::pair<std::pair<std::string, std::string>, std::set<std::string>>>
    mergeStates(const std::set<std::pair<std::pair<std::string, std::string>, std::set<std::string>>>& state);

    // 添加边到 DFA 转移图
    void addEdge(int start, int end, const std::string& symbol);

    // 打印指定状态的内容
    void printState(int number) const;

    // 打印整个 DFA
    void showDFA() const;

    // 所有状态集合，key 为状态编号，value 为状态集合
    std::unordered_map<int, std::set<std::pair<std::pair<std::string, std::string>, std::set<std::string>>>> states;

    // 转移集合，key 为起始状态编号，value 为目标状态编号和转移符号的映射
    std::unordered_map<int, std::unordered_map<int, std::string>> transitions;

    // 状态计数器，表示状态总数
    int stateCount;

   private:
    // 判断符号是否为终结符
    bool isTerminal(const std::string& symbol, const Grammar& grammar) const;
};

#endif  // DFA_H
