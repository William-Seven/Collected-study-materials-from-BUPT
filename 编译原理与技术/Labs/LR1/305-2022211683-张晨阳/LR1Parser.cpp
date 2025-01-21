#include "LR1Parser.h"
#include <iomanip>

LR1Parser::LR1Parser()
    : dfa() {}

// 初始化 I0 状态
void LR1Parser::computeFirst(Grammar& grammar) {
    // 构造初始产生式：E' -> ·E
    std::string right = "@" + grammar.productionCount[0].begin()->second;

    // 初始化状态 I0
    dfa.states[0].insert({{grammar.startSymbol, right}, {"$"}});
    dfa.stateCount++;

    // 初始化状态 I0
    dfa.states[0] = dfa.getClosure(grammar, dfa.states[0]);
    // dfa.showDFA();

    // 合并状态
    dfa.states[0] = dfa.mergeStates(dfa.states[0]);
}

// 构造 LR(1) 自动机
void LR1Parser::computeLR1Automaton(Grammar& grammar, int number) {
    if (number == 0)
        computeFirst(grammar);  // 初始化 I0 状态

    if (number == dfa.stateCount) {  // 如果所有状态都已计算完成
        dfa.showDFA();
        return;
    }

    const auto& state = dfa.states[number];
    std::unordered_map<std::string, std::set<std::pair<std::pair<std::string, std::string>, std::set<std::string>>>> classified;

    // 根据 `·` 后面的符号分类
    for (const auto& item : state) {
        const auto& right = item.first.second;
        size_t dotIndex = right.find('@');

        if (dotIndex != std::string::npos && dotIndex + 1 < right.size()) {
            std::string key(1, right[dotIndex + 1]);
            if (key == "n" && right.substr(dotIndex + 1) == "num")  // 特殊处理 "num"
                key = "num";

            classified[key].insert(item);
        }
    }

    for (const auto& [symbol, subset] : classified) {
        auto newState = std::set<std::pair<std::pair<std::string, std::string>, std::set<std::string>>>();

        // 生成新的状态
        for (const auto& tpl : subset) {
            const auto& left = tpl.first.first;
            const auto& right_str = tpl.first.second;
            auto lookahead = tpl.second;

            size_t dotIndex = right_str.find('@');
            std::string newRightStr;

            // 将 `·` 向右移动
            if (dotIndex != std::string::npos && dotIndex + 1 < right_str.size()) {
                if (right_str.substr(dotIndex + 1) == "num")
                    newRightStr = "num@";
                else
                    newRightStr = right_str.substr(0, dotIndex) + right_str[dotIndex + 1] + "@" + right_str.substr(dotIndex + 2);
            }

            newState.insert({{left, newRightStr}, lookahead});
        }

        // 计算闭包并合并状态
        newState = dfa.getClosure(grammar, newState);
        newState = dfa.mergeStates(newState);

        bool exists = false;
        int existingState = -1;

        // 检查新状态是否已存在
        for (const auto& [key, value] : dfa.states)
            if (value == newState) {
                exists = true;
                existingState = key;
                break;
            }

        if (!exists) {
            dfa.states[dfa.stateCount] = newState;        // 添加新状态
            dfa.addEdge(number, dfa.stateCount, symbol);  // 添加状态转移边
            dfa.stateCount++;
        } else
            dfa.addEdge(number, existingState, symbol);  // 添加已有状态的转移边
    }

    computeLR1Automaton(grammar, number + 1);  // 递归处理下一个状态
}

// 构造 LR(1) 分析表
void LR1Parser::computeAnalysisTable(Grammar& grammar) {
    // 初始化分析表
    for (int i = 0; i < dfa.stateCount; ++i) {
        for (const auto& terminal : grammar.terminals)
            analysisTable[i][terminal] = "";  // 初始化为未定义

        analysisTable[i]["$"] = "";  // 结束符
        for (const auto& nonTerminal : grammar.nonTerminals)
            analysisTable[i][nonTerminal] = "";  // 初始化为未定义
    }

    // 填充分析表
    for (int i = 0; i < dfa.stateCount; ++i) {
        // 遍历当前状态的所有项目
        for (const auto& item : dfa.states[i]) {
            const auto& left = item.first.first;
            const auto& right = item.first.second;

            // 如果是规约项
            if (right.back() == '@') {
                if (left == grammar.startSymbol)
                    analysisTable[i]["$"] = "ACC";  // 接受状态
                else {
                    for (const auto& lookahead : item.second) {
                        std::string prodNum = grammar.findProduction(left, right.substr(0, right.size() - 1));
                        analysisTable[i][lookahead] = "R" + prodNum;  // Reduce 操作
                    }
                }
            }
        }

        // 遍历当前状态的转移
        if (dfa.transitions.find(i) != dfa.transitions.end())
            for (const auto& [neighbor, transSymbol] : dfa.transitions[i]) {
                if (grammar.terminals.count(transSymbol))
                    analysisTable[i][transSymbol] = "S" + std::to_string(neighbor);  // Shift 操作
                else if (grammar.nonTerminals.count(transSymbol))
                    analysisTable[i][transSymbol] = std::to_string(neighbor);  // GOTO 操作
            }
    }

    // 打印分析表
    std::cout << "Analysis Table:" << std::endl;
    std::cout << "State\t";
    for (const auto& terminal : grammar.terminals)
        std::cout << terminal << "\t";

    std::cout << "$\t";
    for (const auto& nonTerminal : grammar.nonTerminals)
        if (nonTerminal != grammar.startSymbol)
            std::cout << nonTerminal << "\t";

    std::cout << std::endl;

    for (int i = 0; i < dfa.stateCount; ++i) {
        std::cout << i << "\t";
        for (const auto& terminal : grammar.terminals) {
            if (analysisTable[i][terminal].empty())
                std::cout << "\t";
            else
                std::cout << analysisTable[i][terminal] << "\t";
        }

        if (analysisTable[i]["$"].empty())
            std::cout << "\t";
        else
            std::cout << analysisTable[i]["$"] << "\t";

        for (const auto& nonTerminal : grammar.nonTerminals)
            if (nonTerminal != grammar.startSymbol) {
                if (analysisTable[i][nonTerminal].empty())
                    std::cout << "\t";
                else
                    std::cout << analysisTable[i][nonTerminal] << "\t";
            }
        std::cout << std::endl;
    }
}

// 使用分析表分析输入串
void LR1Parser::parse(Grammar& grammar, const std::string& inputString) {
    std::vector<std::pair<int, std::string>> stack = {{0, "$"}};  // 初始化栈
    std::string input = inputString + "$";                        // 输入串加上结束符
    size_t ptr = 0;

    // 输出表头
    std::cout << std::right << std::setw(23) << "Stack (States)" << "\t"
              << std::setw(33) << "Input" << "\tAction" << std::endl;

    while (true) {
        // 栈中状态和符号
        std::string stateStack, symbolStack;
        for (const auto& s : stack) {
            stateStack += std::to_string(s.first) + " ";
            symbolStack += s.second + " ";
        }

        // 当前输入符号
        std::string symbol(1, input[ptr]);
        if (std::isdigit(input[ptr]))
            symbol = "num";

        // 获取动作
        int state = stack.back().first;
        const std::string& action = analysisTable[state][symbol];

        // 输出当前栈状态和符号
        std::cout << "States:  " << stateStack << "\n";
        std::cout << "Symbols: " << std::left << std::setw(28) << symbolStack
                  << std::right << std::setw(20) << input.substr(ptr)
                  << "\t" << action << std::endl;

        // 错误处理
        if (action.empty()) {
            std::cout << "Error! Current state: " << state << ", symbol: " << symbol << std::endl;
            break;
        }

        // 接受状态
        if (action == "ACC") {
            std::cout << "Accepted!" << std::endl;
            break;
        }

        // Shift 操作
        if (action[0] == 'S') {
            int nextState = std::stoi(action.substr(1));  // 获取目标状态
            stack.emplace_back(nextState, symbol);        // 压入栈
            ptr++;                                        // 输入指针右移
        }

        // Reduce 操作
        else if (action[0] == 'R') {
            int prodNum = std::stoi(action.substr(1));  // 获取产生式编号
            const auto& prod = grammar.productionCount[prodNum];
            const std::string& left = prod.begin()->first;
            const std::string& right = prod.begin()->second;

            // 弹出栈元素
            size_t popCount = (right == "num") ? 1 : right.size();  // 对 num 特殊处理
            for (size_t i = 0; i < popCount; ++i)
                stack.pop_back();

            // 压入产生式左部
            state = stack.back().first;  // 获取当前栈顶状态
            stack.emplace_back(std::stoi(analysisTable[state][left]), left);
        }
    }
}
