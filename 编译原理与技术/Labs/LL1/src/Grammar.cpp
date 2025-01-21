#include "Grammar.h"
#include <algorithm>  // 用于 std::remove_if

// 构造函数
Grammar::Grammar() {}

// 添加产生式
void Grammar::addProduction(const std::string& nonTerminal, const std::string& production) {
    if (productions.find(nonTerminal) == productions.end()) {
        productions[nonTerminal] = {};
    }
    productions[nonTerminal].push_back(production);
    nonTerminals.insert(nonTerminal);

    // 添加终结符和非终结符
    if (production == "num") {
        terminals.insert("num");
    } else {
        for (char symbol : production) {
            if (isupper(symbol)) {
                nonTerminals.insert(std::string(1, symbol));
            } else {
                terminals.insert(std::string(1, symbol));
            }
        }
    }
}

// 消除左递归
void Grammar::eliminateLeftRecursion() {
    for (const std::string& nonTerminal : nonTerminals) {
        handleImmediateLeftRecursion(nonTerminal);
    }
}

void Grammar::handleImmediateLeftRecursion(const std::string& nonTerminal) {
    std::vector<std::string> alpha;  // 左递归的部分
    std::vector<std::string> beta;   // 非左递归的部分

    for (const std::string& production : productions[nonTerminal]) {
        if (production[0] == nonTerminal[0]) {
            alpha.push_back(production.substr(1));
        } else {
            beta.push_back(production);
        }
    }

    // 存在左递归时进行变换
    if (!alpha.empty()) {
        std::string newNonTerminal = nonTerminal + "'";

        // 更新原非终结符的产生式
        productions[nonTerminal].clear();
        for (const std::string& b : beta) {
            productions[nonTerminal].push_back(b + newNonTerminal);
        }

        // 添加新的非终结符的产生式
        for (const std::string& a : alpha) {
            productions[newNonTerminal].push_back(a + newNonTerminal);
        }
        productions[newNonTerminal].push_back("ε");
        nonTerminals.insert(newNonTerminal);
        terminals.insert("ε");
    }
}

// 消除左公因子
void Grammar::eliminateLeftFactor() {
    std::map<std::string, std::vector<std::string>> newProductions;

    for (const auto& [nonTerminal, rightList] : productions) {
        std::map<std::string, std::vector<std::string>> prefixGroups;

        // 将产生式按前缀分组
        for (const std::string& production : rightList) {
            std::string prefix = production.substr(0, 1);
            prefixGroups[prefix].push_back(production);
        }

        // 消除左公因子
        for (const auto& [prefix, group] : prefixGroups) {
            if (group.size() > 1) {  // 存在公因子
                std::string newNonTerminal = nonTerminal + "'";
                nonTerminals.insert(newNonTerminal);

                // 原产生式变为前缀 + 新非终结符
                newProductions[nonTerminal].push_back(prefix + newNonTerminal);

                // 新非终结符的产生式
                for (const std::string& production : group) {
                    newProductions[newNonTerminal].push_back(production.substr(1));
                }
            } else {  // 没有公因子，直接添加原产生式
                newProductions[nonTerminal].push_back(group[0]);
            }
        }
    }
    productions = newProductions;
}

// 打印文法的产生式
void Grammar::printGrammar() const {
    for (const auto& [nonTerminal, productionList] : productions) {
        std::cout << nonTerminal << " -> ";
        for (size_t i = 0; i < productionList.size(); ++i) {
            std::cout << productionList[i];
            if (i < productionList.size() - 1) {
                std::cout << " | ";
            }
        }
        std::cout << std::endl;
    }
}
