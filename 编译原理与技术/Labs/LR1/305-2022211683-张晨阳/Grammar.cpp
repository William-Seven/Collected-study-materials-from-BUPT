#include "Grammar.h"
#include <sstream>

// 构造函数：初始化产生式计数
Grammar::Grammar()
    : count(0) {}

// 添加产生式：将新的产生式加入到非终结符和终结符集合中，并记录插入顺序
void Grammar::addProduction(const std::string& non_terminal, const std::string& production) {
    if (productions.find(non_terminal) == productions.end())
        productions[non_terminal] = {};

    productions[non_terminal].push_back(production);
    nonTerminals.insert(non_terminal);

    if (production == "num")
        terminals.insert("num");
    else
        for (char symbol : production) {
            if (isupper(symbol))  // 是大写字母
                nonTerminals.insert(std::string(1, symbol));
            else
                terminals.insert(std::string(1, symbol));
        }
}

// 拓广文法：添加新的开始符号，并为所有产生式编号
void Grammar::expandGrammar() {
    std::set<std::string> newNonTerminals;
    std::map<std::string, std::vector<std::string>> newProductions;
    std::string newStartSymbol = startSymbol + "'";

    newNonTerminals.insert(newStartSymbol);
    newProductions[newStartSymbol] = {startSymbol};
    productionCount[0][newStartSymbol] = startSymbol;  // 编号为 0
    count = 1;                                         // 从 1 开始计数

    // 第二步：保留原始输入顺序添加产生式
    for (const auto& non_terminal : nonTerminals) {
        newNonTerminals.insert(non_terminal);

        if (productions.find(non_terminal) != productions.end()) {
            newProductions[non_terminal] = productions[non_terminal];

            // 为每个产生式分配编号
            for (const auto& rightStr : productions[non_terminal]) {
                productionCount[count][non_terminal] = rightStr;
                count++;
            }
        }
    }

    // 更新类成员
    nonTerminals = newNonTerminals;
    productions = newProductions;
    startSymbol = newStartSymbol;

    for (int i = 0; i < count; ++i)
        for (const auto& pair : productionCount[i])
            std::cout << i << " : " << pair.first << " -> " << pair.second << std::endl;

    std::cout << std::endl;
}

// 打印文法
void Grammar::printGrammar() const {
    for (const auto& non_terminal : productions) {
        std::cout << non_terminal.first << " -> ";
        for (size_t i = 0; i < non_terminal.second.size(); ++i) {
            std::cout << non_terminal.second[i];
            if (i < non_terminal.second.size() - 1)
                std::cout << " | ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// 根据左部和右部查找产生式编号
std::string Grammar::findProduction(const std::string& left, const std::string& right) const {
    for (int i = 0; i < count; ++i) {
        auto it = productionCount.find(i);
        if (it != productionCount.end() && it->second.find(left) != it->second.end() &&
            it->second.at(left) == right) {
            return std::to_string(i);
        }
    }
    return "";
}
