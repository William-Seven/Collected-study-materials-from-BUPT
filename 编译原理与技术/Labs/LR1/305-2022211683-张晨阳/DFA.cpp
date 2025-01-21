#include "DFA.h"
#include <iostream>
#include <sstream>

DFA::DFA()
    : stateCount(0) {
    states[0] = {};
}

// 判断是否为终结符
bool DFA::isTerminal(const std::string& symbol, const Grammar& grammar) const {
    return grammar.terminals.find(symbol) != grammar.terminals.end();
}

// 获取First集合
std::string DFA::getFirst(const Grammar& grammar, const std::string& symbol) {
    if (isTerminal(symbol, grammar) || symbol == "$") {
        return symbol;  // 如果是终结符或结束符号，直接返回
    }

    // 找到非终结符的产生式
    auto productions = grammar.productions.find(symbol);

    if (productions != grammar.productions.end())
        for (const auto& right : productions->second) {
            // 如果产生式右部第一个符号是终结符，返回该终结符
            if (isTerminal(std::string(1, right[0]), grammar))
                return std::string(1, right[0]);
            // 特殊处理 "num" 符号
            else if (right == "num")
                return "num";
            // 如果产生式右部第一个符号与当前符号相同，跳过（避免递归陷入死循环）
            else if (right[0] == symbol[0])
                continue;
            // 否则递归调用 getFirst
            else if (right[0] != symbol[0])
                return getFirst(grammar, std::string(1, right[0]));
        }

    return "";
}

// 计算闭包
std::set<std::pair<std::pair<std::string, std::string>, std::set<std::string>>>
DFA::getClosure(const Grammar& grammar, const std::set<std::pair<std::pair<std::string, std::string>, std::set<std::string>>>& state) {
    auto closure = state;

    bool addedNewItem = true;  // 标志位，用于检测是否有新项目被添加

    // 不断扩展闭包，直到没有新项目被加入
    while (addedNewItem) {
        addedNewItem = false;

        std::set<std::pair<std::pair<std::string, std::string>, std::set<std::string>>> newItems;

        // 遍历当前闭包中的每个项目
        for (const auto& item : closure) {
            const auto& left = item.first.first;        // 获取产生式左部
            const auto& right_str = item.first.second;  // 获取产生式右部
            const auto& lookahead = item.second;        // 获取 lookahead 集合

            // 遍历 lookahead 集合
            for (const auto& currentLookahead : lookahead) {
                // 遍历右部的每个符号，寻找 "@" 的位置
                for (size_t i = 0; i < right_str.size(); ++i) {
                    if (right_str[i] == '@' && i + 1 < right_str.size()) {
                        std::string nextSymbol(1, right_str[i + 1]);  // 获取 "@" 后的符号

                        // 如果 "@" 后是非终结符
                        if (grammar.nonTerminals.find(nextSymbol) != grammar.nonTerminals.end()) {
                            // 获取该非终结符的所有产生式
                            for (const auto& production : grammar.productions.at(nextSymbol)) {
                                std::string strAhead;

                                // 计算新的 lookahead 串
                                if (i + 1 == right_str.size() - 1)
                                    strAhead = currentLookahead;  // 如果 "@" 在倒数第二个位置
                                else
                                    strAhead = right_str.substr(i + 2) + currentLookahead;  // 拼接 "@" 后的部分与 lookahead

                                // 获取 First 集
                                std::set<std::string> firstSet;

                                std::string symbol(1, strAhead[0]);
                                std::string first = getFirst(grammar, symbol);
                                if (!first.empty())
                                    firstSet.insert(first);

                                // 构造新的项目
                                std::pair<std::pair<std::string, std::string>, std::set<std::string>> newItem =
                                    std::make_pair(std::make_pair(nextSymbol, "@" + production), firstSet);

                                // 如果新项目不在闭包中，加入到新项目集合
                                if (closure.find(newItem) == closure.end() && newItems.find(newItem) == newItems.end()) {
                                    newItems.insert(newItem);
                                    addedNewItem = true;  // 有新项目加入
                                }
                            }
                        }
                    }
                }
            }
        }

        // 将新项目集合加入到闭包
        closure.insert(newItems.begin(), newItems.end());
    }

    return closure;
}

// 合并状态
std::set<std::pair<std::pair<std::string, std::string>, std::set<std::string>>>
DFA::mergeStates(const std::set<std::pair<std::pair<std::string, std::string>, std::set<std::string>>>& state) {
    // 使用 map 以 key 为基础合并 lookahead
    std::map<std::pair<std::string, std::string>, std::set<std::string>> merged;

    for (const auto& item : state) {
        const auto& key = item.first;
        const auto& lookahead = item.second;

        merged[key].insert(lookahead.begin(), lookahead.end());
    }

    // 将合并后的状态重新组织为结果集
    std::set<std::pair<std::pair<std::string, std::string>, std::set<std::string>>> result;
    for (const auto& [key, lookaheads] : merged) {
        result.insert({key, lookaheads});
    }
    return result;
}

// 添加边到转移图
void DFA::addEdge(int start, int end, const std::string& symbol) {
    transitions[start][end] = symbol;
}

// 打印指定状态
void DFA::printState(int number) const {
    if (states.find(number) == states.end()) {
        std::cout << "I" << number << " is not a valid state." << std::endl;
        return;
    }

    for (const auto& item : states.at(number)) {
        std::cout << item.first.first << " -> " << item.first.second << " , ";
        for (const auto& lookahead : item.second) {
            std::cout << lookahead << " ";
        }
        std::cout << std::endl;
    }
}

// 打印整个 DFA
void DFA::showDFA() const {
    for (int i = 0; i < stateCount; ++i) {
        std::cout << "I" << i << ":" << std::endl;
        printState(i);
        if (transitions.find(i) != transitions.end()) {
            for (const auto& edge : transitions.at(i)) {
                std::cout << "--- " << edge.second << " ---> I" << edge.first << std::endl;
            }
        }
        std::cout << std::endl;
    }
}
