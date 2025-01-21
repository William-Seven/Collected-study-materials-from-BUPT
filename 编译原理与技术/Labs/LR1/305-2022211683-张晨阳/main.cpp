#include <iostream>
#include <vector>
#include "DFA.h"
#include "Grammar.h"
#include "LR1Parser.h"

int main() {
    // 构造文法
    Grammar grammar;
    grammar.addProduction("E", "E+T");
    grammar.addProduction("E", "E-T");
    grammar.addProduction("E", "T");
    grammar.addProduction("T", "T*F");
    grammar.addProduction("T", "T/F");
    grammar.addProduction("T", "F");
    grammar.addProduction("F", "(E)");
    grammar.addProduction("F", "num");
    grammar.startSymbol = "E";

    std::cout << "Original grammar:" << std::endl;
    grammar.printGrammar();

    std::cout << "Expanded grammar:" << std::endl;
    grammar.expandGrammar();

    // 构造 LR(1) 分析器
    LR1Parser parser;

    // 构造 LR(1) 自动机和分析表
    std::cout << "LR(1) DFA:" << std::endl;
    parser.computeLR1Automaton(grammar);

    std::cout << "LR(1) analysis table:" << std::endl;
    parser.computeAnalysisTable(grammar);

    // 测试输入串
    std::vector<std::string> testInputs = {
        "1+2",            // 正常的输入串
        "1+2*(3-(4/5))",  // 含括号的复杂表达式
        "1+2*/3",         // 含错误的输入串
        "1+(2*9)+3)"      // 含未匹配括号的输入串
    };

    for (const auto& input : testInputs) {
        std::cout << "\nTesting input: \033[93m" << input << "\033[0m" << std::endl;
        parser.parse(grammar, input);
        std::cout << "\n";
    }

    return 0;
}
