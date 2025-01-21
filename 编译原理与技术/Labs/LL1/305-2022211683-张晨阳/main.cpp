#include <iostream>
#include <vector>
#include "Grammar.h"
#include "LL1Parser.h"

int main() {
    // Step 1: 创建文法
    Grammar grammar;

    // 添加产生式
    grammar.addProduction("E", "E+T");
    grammar.addProduction("E", "E-T");
    grammar.addProduction("E", "T");
    grammar.addProduction("T", "T*F");
    grammar.addProduction("T", "T/F");
    grammar.addProduction("T", "F");
    grammar.addProduction("F", "(E)");
    grammar.addProduction("F", "num");

    // 设置起始符号
    grammar.startSymbol = "E";

    std::cout << "Original Grammar:" << std::endl;
    grammar.printGrammar();

    // Step 2: 消除左递归和左公因子
    grammar.eliminateLeftRecursion();
    grammar.eliminateLeftFactor();

    std::cout << "\nGrammar after eliminating left recursion and left factoring:" << std::endl;
    grammar.printGrammar();

    // Step 3: 创建 LL1 解析器
    LL1Parser parser;

    // 计算 First 和 Follow 集合
    parser.computeFirst(grammar);
    parser.computeFollow(grammar);

    // 检查文法是否为 LL(1) 文法
    if (parser.isLL1(grammar)) {
        std::cout << "\nThe grammar is an LL(1) grammar." << std::endl;

        // Step 4: 生成预测分析表
        parser.computePredictionsTable(grammar);

        // Step 5: 测试解析一组输入表达式
        std::vector<std::string> testStrings = {
            "1+2",              // 简单的加法表达式
            "1+2*(3-4)",        // 带括号的复合表达式
            "0+1+2*(3-(4/2))",  // 复杂的嵌套表达式
            "1+2*/(3-4)",       // 包含错误的表达式
        };

        for (const auto& input : testStrings) {
            std::cout << "\nParsing expression: " << input << std::endl;
            parser.parse(grammar, input);
        }
    } else {
        std::cout << "\nThe grammar is not an LL(1) grammar." << std::endl;
    }

    return 0;
}
