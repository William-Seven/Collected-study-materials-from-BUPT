// -------文件说明：-------
//   此文件实现 NFA 转换 DFA 的核心算法

// ----------最终版本基本不包含以下内容：----------
// ---该处记录实现的心路历程、算法的设计步骤等内容以供参考---
//      NFA: 一个状态经一个输入到达多个状态，包含 ε
//      DFA: 一个状态经一个输入到达一个状态，不包含 ε

// ----- DFA 的组成：-----
//      1.DFA 每个状态对应 NFA 的一个状态集合
//      2.DFA 的输入字符与 NFA 相同
//      3.DFA 初始状态为 NFA 初始状态的 ε 闭包
//      4.状态转移表、函数为 DFA 中的每个状态及每个输入，定义一个转换新状态（也是NFA状态集合的ε闭包）
//      5.DFA 的终止状态：DFA 中包含 NFA 至少一个终止状态的状态皆为终止状态

// --------C++ 实现思路：--------
//      1.ε-NFA 转换为 NFA
//      2.NFA 转换为 DFA

// -----数据结构设计：-----
//      1.状态：使用std::set<int>表示一个状态
//      2.转换表：使用std::map<std::pair<std::set<int>, char>, std::set<int>>
//               存储从一个状态集合通过一个输入符号到另一个状态集合的映射
//      3.ε 闭包：构造一个函数计算得到

// -----算法步骤：-----
//      1.输入 NFA
//      2.计算 ε 闭包
//      3.初始化 DFA
//          使用 NFA 的初始状态的 ε 闭包作为 DFA 的初始状态
//      4.构建 DFA
//          使用 BFS 算法，遍历每个状态集合和输入符号，求得转换后的ε 闭包
//          并更新 DFA 转换表。若遇到新的状态集合，将其添加到队列中
//      5.输出 DFA

//-------NOTE-------
//  1.状态用数字表示
//  2.ɛ 用'e'表示
//  3.输入字符为 char 类型（e 表示 ɛ）

//----------免责声明----------
//  核心功能已实现，还需要美化操作指令，
//      比如自己输入NFA（告诉读者输入格式）
//  美化 DFA 输出格式、选择输出方式等等
//  反正功能越完善越好
//  后续算法如果出现边界问题，你们自己修吧
//  不是史山代码，笔者的代码风格非常好

//------不准用using namespace std;！！！！！！！------

#include <windows.h>  //使用Sleep函数
#include <iomanip>    //填充字符
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

// NFA 结构体定义
struct NFA {
    std::set<int> states;                                       // NFA 的所有状态，即 Q
    std::set<char> inputSymbols;                                // NFA 的所有输入符号，即 T
    std::map<std::pair<int, char>, std::set<int>> transitions;  // NFA 的状态转移函数，即 δ
    int initialState;                                           // NFA 的初始状态，即 q0
    std::set<int> finalStates;                                  // NFA 的终止状态，即 F
};

// DFA 结构体定义
struct DFA {
    std::set<std::set<int>> states;                                       // DFA 的所有状态，即 Q
    std::set<char> inputSymbols;                                          // DFA 的所有输入符号，即 T
    std::map<std::pair<std::set<int>, char>, std::set<int>> transitions;  // DFA 的状态转移函数，即 δ
    std::set<int> initialState;                                           // DFA 的初始状态
    std::set<std::set<int>> finalStates;                                  // DFA 的终止状态，即 F
};

// 计算 ε 闭包(BFS算法, 时间复杂度最差O(N^2*logN))
std::set<int> eClosure(const NFA& nfa, const std::set<int>& states) {
    std::set<int> closure = states;  // ɛ 闭包包含状态本身

    std::queue<int> queue;  // 初始化队列，进行BFS
    for (int state : states)
        queue.push(state);

    while (!queue.empty()) {
        int currentState = queue.front();
        queue.pop();

        // 查找是否有以 currentState 为起点，通过 ε 转移能到达的状态集合
        if (nfa.transitions.find({currentState, 'e'}) != nfa.transitions.end())
            for (int nextState : nfa.transitions.at({currentState, 'e'}))
                if (closure.find(nextState) == closure.end()) {
                    closure.insert(nextState);  // 更新闭包集合
                    queue.push(nextState);      // 更新要进行 BFS 的状态
                }
    }

    return closure;
}

// 从 NFA 状态集合 + 输入符号计算 DFA 状态(时间复杂度最差O(N^2*logN))
std::set<int> dfaStateFromNfaStates(const NFA& nfa, const std::set<int>& states, char input) {
    std::set<int> result;

    for (int state : states)
        if (nfa.transitions.find({state, input}) != nfa.transitions.end()) {
            std::set<int> targetStates = nfa.transitions.at({state, input});
            result.insert(targetStates.begin(), targetStates.end());
        }

    return eClosure(nfa, result);
}

// NFA 到 DFA 转换
DFA convertNFAtoDFA(const NFA& nfa) {
    DFA dfa;
    dfa.inputSymbols = nfa.inputSymbols;
    dfa.inputSymbols.erase('e');  // 移除 ɛ 转换

    // 使用 map 来追踪已发现的 DFA 状态，避免重复处理
    std::map<std::set<int>, std::set<int>> dfaStatesMap;
    // 使用队列管理待处理的 DFA 状态
    std::queue<std::set<int>> statesQueue;

    // 计算 NFA 初始状态的 ɛ 闭包作为 DFA 的初始状态
    std::set<int> startStateClosure = eClosure(nfa, {nfa.initialState});
    dfaStatesMap[startStateClosure] = startStateClosure;
    dfa.initialState = startStateClosure;
    statesQueue.push(startStateClosure);

    // 当队列不为空时，处理每个 DFA 状态
    while (!statesQueue.empty()) {
        std::set<int> currentNfaStates = statesQueue.front();
        statesQueue.pop();

        // 对每个输入符号，计算当前 DFA 下的新状态
        for (char symbol : dfa.inputSymbols) {
            std::set<int> newState = dfaStateFromNfaStates(nfa, currentNfaStates, symbol);

            // 如果新状态非空且未出现过，将其加入 map & queue中
            if (!newState.empty() && dfaStatesMap.find(newState) == dfaStatesMap.end()) {
                dfaStatesMap[newState] = newState;
                statesQueue.push(newState);
            }

            // 记录从当前状态到新状态的转换
            if (!newState.empty())
                dfa.transitions[{currentNfaStates, symbol}] = newState;
        }
    }

    // 遍历所有 DFA 状态，将其加入 DFA 状态集合，并识别终点
    for (auto& stateMapping : dfaStatesMap) {
        dfa.states.insert(stateMapping.first);
        // 判断终点状态
        for (int finalState : nfa.finalStates)
            if (stateMapping.first.find(finalState) != stateMapping.first.end()) {
                dfa.finalStates.insert(stateMapping.first);
                break;
            }
    }

    return dfa;
}

int main() {
    NFA nfa;

    // 构建 NFA
    nfa.states = {0, 1, 2};
    nfa.inputSymbols = {'a', 'b', 'e'};
    nfa.transitions = {
        {{0, 'a'}, {1}},
        {{1, 'b'}, {2}},
        {{0, 'e'}, {2}}};
    nfa.initialState = 0;
    nfa.finalStates = {2};

    DFA dfa = convertNFAtoDFA(nfa);

    // 美化界面的小工具，笔者最喜欢在这种题目里加这个东西，最好给哥们保留了
    std::cout << "Converting...";
    for (int i = 0; i < 101; i++) {
        // cout.width(4);
        std::cout << std::setfill('-') << std::setw(4) << i << "%";
        Sleep(50);
        std::cout << "\b\b\b\b";
    }
    std::cout << std::endl;

    // 输出 DFA 函数
    for (auto& transition : dfa.transitions) {
        std::cout << "{";
        for (int state : transition.first.first)
            std::cout << state << " ";

        std::cout << "} --" << transition.first.second << "--> {";
        for (int state : transition.second)
            std::cout << state << " ";

        std::cout << "}" << std::endl;
    }

    // 输出 DFA 初始状态
    std::cout << "Initial state: {";
    for (int state : dfa.initialState)
        std::cout << state << " ";
    std::cout << "}" << std::endl;

    // 输出 DFA 终态状态
    std::cout << "Final states: ";
    for (std::set<int> states : dfa.finalStates) {
        std::cout << "{";
        for (int state : states)
            std::cout << state << " ";
        std::cout << "}";
    }

    return 0;
}