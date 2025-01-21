#include "LL1Parser.h"
#include <algorithm>
#include <iomanip>  // 用于格式化输出
#include <iostream>
#include <stack>
#include <unordered_map>
#include <unordered_set>

// 构造函数
LL1Parser::LL1Parser() {}

// 输出Follow集
void LL1Parser::printFollow() {
    std::cout << "\nFollow Set:\n";
    for (const auto& [nonTerminal, symbols] : follow) {
        std::cout << "Follow(" << nonTerminal << ") = { ";
        for (const auto& symbol : symbols) {
            std::cout << symbol << " ";
        }
        std::cout << "}\n";
    }
}

// 输出预测分析表
void LL1Parser::printPredictionsTable(Grammar& grammar) {
    std::cout << "\nPredictions Table:\n";

    // 设置单元格的宽度
    const int cellWidth = 15;

    // 打印表头（终结符）
    std::cout << std::setw(cellWidth) << std::left << " ";
    for (const auto& terminal : grammar.terminals) {
        std::string symbol = (terminal == "ε") ? "$" : terminal;
        std::cout << std::setw(cellWidth) << std::left << symbol;
    }
    std::cout << std::endl;

    // 打印每个非终结符的行
    for (const auto& nonTerminal : grammar.nonTerminals) {
        std::cout << std::setw(cellWidth) << std::left << nonTerminal;  // 打印非终结符

        for (const auto& terminal : grammar.terminals) {
            std::string symbol = (terminal == "ε") ? "$" : terminal;
            auto key = std::make_pair(nonTerminal, symbol);

            if (predictionsTable.find(key) != predictionsTable.end()) {
                // 如果表中有该条目，则打印产生式
                std::cout << std::setw(cellWidth) << std::left
                          << (nonTerminal + " -> " + predictionsTable[key]);
                if (predictionsTable[key] == "ε") {
                    std::cout << " ";
                }
            } else {
                // 否则，打印空白
                std::cout << std::setw(cellWidth) << std::left << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// 计算First集合
void LL1Parser::computeFirst(Grammar& grammar) {
    for (const auto& nonTerminal : grammar.nonTerminals) {
        first[nonTerminal] = {};
    }
    for (const auto& terminal : grammar.terminals) {
        first[terminal] = {terminal};  // 终结符的First集为自身
    }
    for (const auto& nonTerminal : grammar.nonTerminals) {
        calculateFirst(grammar, nonTerminal);
    }

    // 输出 First 集合
    std::cout << "\nFirst Set:\n";
    for (const auto& [symbol, firstSet] : first) {
        // 仅打印非终结符的First集合
        if (grammar.nonTerminals.count(symbol) > 0) {
            std::cout << "First(" << symbol << ") = { ";
            for (const auto& terminal : firstSet) {
                std::cout << terminal << " ";
            }
            std::cout << "}" << std::endl;
        }
    }
}

// 计算单个非终结符的First集合
void LL1Parser::calculateFirst(Grammar& grammar, const std::string& nonTerminal) {
    // 遍历该非终结符的所有产生式
    for (const std::string& production : grammar.productions[nonTerminal]) {
        if (production == "ε") {
            // 如果产生式是ε，直接将ε加入First集中
            first[nonTerminal].insert("ε");
            continue;
        }

        // 确定第一个符号的处理方式（例如num，带撇符号的情况）
        std::string firstSymbol;
        if (production == "num") {
            firstSymbol = "num";
        } else if (production.size() > 1 && production[1] == '\'') {
            firstSymbol = production.substr(0, 2);  // 带撇符号，如A'
        } else {
            firstSymbol = production.substr(0, 1);  // 单个字符
        }

        // 处理终结符
        if (grammar.terminals.count(firstSymbol)) {
            first[nonTerminal].insert(firstSymbol);
        }
        // 处理非终结符
        else if (grammar.nonTerminals.count(firstSymbol)) {
            // 确保递归计算First集前符号已经存在于First集中
            calculateFirst(grammar, firstSymbol);
            first[nonTerminal].insert(first[firstSymbol].begin(), first[firstSymbol].end());

            // 如果第一个符号的First集中包含ε，继续处理后续符号
            size_t j = 1;
            while (first[firstSymbol].count("ε") > 0 && j < production.size()) {
                first[nonTerminal].erase("ε");
                std::string nextSymbol = std::string(1, production[j]);
                if (j + 1 < production.size() && production[j + 1] == '\'') {
                    nextSymbol += "'";
                    ++j;
                }

                // 处理下一个符号是终结符
                if (grammar.terminals.count(nextSymbol)) {
                    first[nonTerminal].insert(nextSymbol);
                    break;
                }
                // 处理下一个符号是非终结符
                else if (grammar.nonTerminals.count(nextSymbol)) {
                    calculateFirst(grammar, nextSymbol);
                    first[nonTerminal].insert(first[nextSymbol].begin(), first[nextSymbol].end());
                    first[nonTerminal].erase("ε");
                }
                j++;
            }
        }
    }
}

// 计算Follow集合
void LL1Parser::computeFollow(Grammar& grammar) {
    follow[grammar.startSymbol].insert("$");  // 起始符号的Follow集包含终结符$

    bool changed = true;
    while (changed) {
        changed = false;

        // 遍历所有非终结符的产生式
        for (const auto& [nonTerminal, productions] : grammar.productions) {
            for (const std::string& production : productions) {
                for (size_t i = 0; i < production.size(); ++i) {
                    // 当前符号
                    std::string symbol = production.substr(i, 1);
                    if (i != production.size() - 1 && production[i + 1] == '\'') {
                        symbol += "'";  // 检查带撇号符号
                        ++i;
                    }

                    if (grammar.nonTerminals.count(symbol)) {  // 当前符号是非终结符
                        std::set<std::string> nextFirst;
                        if (i + 1 < production.size()) {  // 非最后一个符号
                            std::string nextSymbol = production.substr(i + 1, 1);
                            if (i + 1 != production.size() - 1 && production[i + 2] == '\'') {
                                nextSymbol += "'";  // 检查带撇号符号
                            }

                            if (grammar.terminals.count(nextSymbol)) {  // 下一个符号是终结符
                                nextFirst.insert(nextSymbol);
                            } else if (grammar.nonTerminals.count(nextSymbol)) {  // 下一个符号是非终结符
                                nextFirst = first[nextSymbol];                    // 获取nextSymbol的First集
                            }
                        } else {  // 最后一个符号，将非终结符的Follow加入当前符号的Follow集
                            nextFirst = follow[nonTerminal];
                        }

                        // 更新Follow集
                        size_t oldSize = follow[symbol].size();
                        follow[symbol].insert(nextFirst.begin(), nextFirst.end());
                        follow[symbol].erase("ε");  // 去除ε

                        // 如果nextFirst包含ε，添加nonTerminal的Follow集
                        if (i + 1 == production.size() || nextFirst.count("ε") > 0) {
                            follow[symbol].insert(follow[nonTerminal].begin(), follow[nonTerminal].end());
                        }

                        // 检查是否有变更
                        if (follow[symbol].size() > oldSize) {
                            changed = true;
                        }
                    }
                }
            }
        }
    }
    printFollow();  // 打印Follow集合
}

// 构建预测分析表
void LL1Parser::computePredictionsTable(Grammar& grammar) {
    // 遍历每个非终结符的产生式
    for (const auto& [nonTerminal, productions] : grammar.productions) {
        for (const std::string& production : productions) {
            std::set<std::string> productionFirst;

            // 检查空串的情况
            if (production == "ε") {
                for (const auto& symbol : follow[nonTerminal]) {
                    predictionsTable[{nonTerminal, symbol}] = "ε";
                }
                continue;
            }

            // 获取产生式的第一个符号
            std::string firstSymbol;
            if (production.compare(0, 3, "num") == 0) {  // 检查是否为"num"
                firstSymbol = "num";
            } else if (production.size() > 1 && production[1] == '\'') {
                firstSymbol = production.substr(0, 2);  // 带撇符号
            } else {
                firstSymbol = production.substr(0, 1);
            }

            // 处理非终结符
            if (grammar.nonTerminals.count(firstSymbol)) {
                productionFirst = first[firstSymbol];

                // 添加非空条目
                for (const auto& terminal : productionFirst) {
                    if (terminal != "ε") {
                        predictionsTable[{nonTerminal, terminal}] = production;
                    }
                }

                // 如果包含空串ε，添加Follow集
                if (productionFirst.count("ε") > 0) {
                    for (const auto& symbol : follow[nonTerminal]) {
                        predictionsTable[{nonTerminal, symbol}] = production;
                    }
                }
            }
            // 处理终结符和特殊符号
            else {
                predictionsTable[{nonTerminal, firstSymbol}] = production;
                // std::cout << production << std::endl;
            }
        }
    }

    // 错误处理：加入"synch"条目
    for (const auto& nonTerminal : grammar.nonTerminals) {
        for (const auto& symbol : follow[nonTerminal]) {
            if (predictionsTable.find({nonTerminal, symbol}) == predictionsTable.end()) {
                predictionsTable[{nonTerminal, symbol}] = "synch";
            }
        }
    }

    // 打印预测分析表
    printPredictionsTable(grammar);
}

// 检查是否是LL(1)文法
bool LL1Parser::isLL1(const Grammar& grammar) const {
    for (const auto& [nonTerminal, productions] : grammar.productions) {
        std::set<std::string> seen;
        for (const std::string& production : productions) {
            std::set<std::string> productionFirst;
            std::string firstSymbol = production.substr(0, 1);
            if (grammar.terminals.count(firstSymbol)) {
                productionFirst.insert(firstSymbol);
            } else if (first.find(firstSymbol) != first.end()) {
                productionFirst = first.at(firstSymbol);
            }

            for (const std::string& terminal : productionFirst) {
                if (seen.count(terminal)) {
                    return false;
                }
                seen.insert(terminal);
            }
        }
    }
    return true;
}

// 解析输入字符串
void LL1Parser::parse(const Grammar& grammar, const std::string& inputString) {
    std::stack<std::string> parseStack;
    parseStack.push("$");
    parseStack.push(grammar.startSymbol);
    size_t index = 0;
    int errorCount = 0;

    const int colWidth = 25;  // 设置列宽

    // 打印表头
    std::cout << std::setw(colWidth) << std::left << "Stack"
              << std::setw(colWidth) << "Input"
              << "Output" << std::endl;

    while (!parseStack.empty()) {
        std::string top = parseStack.top();
        std::string currentSymbol = (index < inputString.size())
                                        ? (isdigit(inputString[index]) ? "num" : std::string(1, inputString[index]))
                                        : "$";

        // 打印栈的当前状态
        std::stack<std::string> tempStack = parseStack;
        std::string stackContent;
        while (!tempStack.empty()) {
            stackContent = tempStack.top() + stackContent;  // 逆序输出栈内容
            tempStack.pop();
        }
        std::cout << std::setw(colWidth) << std::left << stackContent;

        // 打印输入的当前状态
        std::string inputContent = inputString.substr(index) + "$";
        std::cout << std::setw(colWidth) << std::left << inputContent;

        // 匹配完成
        if (top == "$" && currentSymbol == "$") {
            std::cout << "\n\033[93mComplete!\033[0m";
            if (errorCount == 0) {
                std::cout << "\t\033[92mNo error\033[0m\n";
            } else {
                std::cout << "\t\033[91m" << errorCount << " error(s)\033[0m\n";
            }
            return;
        }

        // 栈顶是终结符或 '$'，进行直接匹配
        if (grammar.terminals.count(top) || top == "$") {
            if (top == currentSymbol) {
                parseStack.pop();
                if (currentSymbol == "num") {
                    // 找到数字串的结尾并更新index
                    size_t nextPos = inputString.find_first_not_of("0123456789", index);
                    index = (nextPos == std::string::npos) ? inputString.size() : nextPos;
                } else {
                    index += 1;  // 非"num"字符只移动一个字符
                }
                std::cout << std::endl;
            } else {
                std::cout << std::setw(colWidth) << std::left << "\033[91mError\033[0m: " << top << " != " << currentSymbol << std::endl;
                errorCount++;
                parseStack.pop();
            }
        } else {
            // 栈顶为非终结符，查找预测分析表
            if (predictionsTable.count({top, currentSymbol})) {
                parseStack.pop();
                std::string production = predictionsTable[{top, currentSymbol}];

                if (production == "synch") {  // 预测分析表中对应的产生式是synch
                    std::cout << std::setw(colWidth) << std::left
                              << "\033[91mError\033[0m: predictions_table[" << top << ", " << currentSymbol << "] is synch" << std::endl;
                    errorCount++;
                } else if (production == "ε") {  // 处理产生式为ε的情况
                    std::cout << top << " -> ε" << std::endl;
                    // 不将ε压入栈，直接跳过
                } else {  // 预测分析表中有对应的产生式
                    std::cout << top << " -> " << production << std::endl;

                    // 将产生式反序入栈
                    std::string reversedProduction = preReversed(production);
                    for (size_t i = 0; i < reversedProduction.size();) {
                        if (i < reversedProduction.size() - 1 && reversedProduction[i + 1] == '\'') {
                            parseStack.push(reversedProduction.substr(i, 2));
                            i += 2;
                        } else if (reversedProduction.substr(i, 3) == "num") {
                            parseStack.push("num");
                            i += 3;
                        } else {
                            parseStack.push(std::string(1, reversedProduction[i]));
                            i++;
                        }
                    }
                }
            } else {  // 预测分析表中没有对应的产生式
                std::cout << std::setw(colWidth) << std::left
                          << "\033[91mError\033[0m: predictions_table[" << top << ", " << currentSymbol << "] is empty" << std::endl;
                errorCount++;
                index++;
            }
        }
    }
    std::cout << "Error: input not fully consumed" << std::endl;
}

// 辅助函数，用于反转产生式字符串，并处理带撇号符号和"num"
std::string LL1Parser::preReversed(const std::string& production) {
    std::string result;
    int i = production.size() - 1;

    while (i >= 0) {
        // 检查带撇号符号的条件
        if (i > 0 && production[i] == '\'') {
            result += production[i - 1];
            result += "'";
            i -= 2;
        }
        // 检查"num"的条件
        else if (i >= 2 && production.substr(i - 2, 3) == "num") {
            result += "num";
            i -= 3;
        }
        // 处理单个字符
        else {
            result += production[i];
            i--;
        }
    }
    return result;
}
