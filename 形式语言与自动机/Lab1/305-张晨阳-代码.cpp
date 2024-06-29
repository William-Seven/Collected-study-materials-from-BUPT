// -------文件说明：-------
//   此文件实现 NFA 转换 DFA

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

// 计算 ε 闭包
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

// 从 NFA 状态集合 + 输入符号计算 DFA 状态
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
    // nfa.states = {0, 1, 2};
    // nfa.inputSymbols = {'a', 'b','c', 'e'};
    // nfa.transitions = {
    //     {{0, 'a'}, {0}},
    //     {{0, 'e'}, {1}},
    //     {{1, 'b'}, {1}},
    //     {{1, 'e'}, {2}},
    //     {{2, 'c'}, {2}}
    // };
    // nfa.initialState = 0;
    // nfa.finalStates = {2};

    int temp_int = 0;
    char temp_char = '\0';
    bool isFirst = true;
    bool isFirst2 = true;
    bool isCorrect = true;

    // 键盘输入
    std::cout << "Please input states, using the number -1 as the end\ne.g: 0 1 2 -1\nThis shows that Q={0,1,2}" << std::endl;
    std::cin >> temp_int;
    while (temp_int != -1) {
        nfa.states.insert(temp_int);
        std::cin >> temp_int;
    }
    isFirst = true;
    std::cout << "Q={";
    for (int state : nfa.states) {
        if (!isFirst)
            std::cout << ",";
        std::cout << state;
        isFirst = false;
    }
    std::cout << "}" << std::endl;

    isCorrect = false;
    while (!isCorrect) {
        isCorrect = true;
        std::cout << "\nPlease input input symbols, using the char # as the end\ne.g: a b c #\nThis shows that T={a,b,c}" << std::endl;
        std::cin >> temp_char;
        while (temp_char != '#') {
            if ((temp_char >= 'a' && temp_char <= 'z') || (temp_char >= 'A' && temp_char <= 'Z'))
                nfa.inputSymbols.insert(temp_char);
            else {
                std::cout << temp_char << " is illegal!" << std::endl;  // 告诉用户输入无效，同时让用户重新输入
                isCorrect = false;
            }
            std::cin >> temp_char;
        }
        if (!isCorrect)
            std::cout << "\nPlease input again!" << std::endl;
    }
    isFirst = true;
    std::cout << "T={";
    for (char symbol : nfa.inputSymbols) {
        if (!isFirst)
            std::cout << ",";
        std::cout << symbol;
        isFirst = false;
    }
    std::cout << "}" << std::endl;

    temp_int = 1;
    std::cout << "\nIs there a transition function available?\nInput 1 to indicate yes, input 0 to indicate no: ";
    std::cin >> temp_int;
    while (temp_int != 0) {
        int insert = 0;  // 用于控制是否插入新的生成式
        std::cout << "\nPlease input a transition function\ne.g: \n0 a 1\n-1\nThis shows that δ(0,a)=1" << std::endl;
        std::cout << "\nPlease input the first state\ne.g: 0" << std::endl;
        int temp_int_1 = 0;
        std::cin >> temp_int_1;
        while (nfa.states.find(temp_int_1) == nfa.states.end()) {
            std::cout << "\nPlease input again!" << std::endl;  // 告诉用户输入错误，重新输入
            std::cin >> temp_int_1;
        }
        std::cout << "\nPlease input the input symbol\ne.g: a" << std::endl;
        char temp_char_1 = '\0';
        std::cin >> temp_char_1;
        while (nfa.inputSymbols.find(temp_char_1) == nfa.inputSymbols.end()) {
            std::cout << "\nPlease input again!" << std::endl;  // 同上
            std::cin >> temp_char_1;
        }
        std::cout << "\nPlease input the next state, using the number -1 as the end, you can input more than one number\ne.g: 1 2 -1" << std::endl;
        int temp_int_2 = 0;
        std::set<int> next_state;
        std::cin >> temp_int_2;
        while (temp_int_2 != -1) {
            if (nfa.states.find(temp_int_2) == nfa.states.end()) {
                std::cout << "\nPlease input again!" << std::endl;  // 告诉用户输入无效并提醒他重新输入
            } else {
                if (nfa.transitions.find(std::make_pair(temp_int_1, temp_char_1)) == nfa.transitions.end()) {
                    if (next_state.find(temp_int_2) == next_state.end()) {
                        next_state.insert(temp_int_2);
                        std::cout << "A transition function δ(" << temp_int_1 << "," << temp_char_1 << ")=" << temp_int_2 << " has been established!" << std::endl;
                    } else
                        std::cout << "The new next state " << temp_int_2 << " has been added to the existing transition function δ(" << temp_int_1 << "," << temp_char_1 << ")" << std::endl;
                } else {
                    nfa.transitions.find(std::make_pair(temp_int_1, temp_char_1))->second.insert(temp_int_2);
                    std::cout << "The new next state " << temp_int_2 << " has been added to the existing transition function δ(" << temp_int_1 << "," << temp_char_1 << ")" << std::endl;
                    insert = 1;
                }
            }
            std::cin >> temp_int_2;
        }
        if (insert == 0)
            nfa.transitions.insert({{temp_int_1, temp_char_1}, next_state});
        std::cout << "\nIs there another transition function available?\nInput 1 to indicate Yes, input 0 to indicate No: ";
        std::cin >> temp_int;
    }

    temp_int = 0;
    std::cout << "\nPlease input initial state\ne.g: 0\nTHis shows that q0=0" << std::endl;
    std::cin >> temp_int;
    while (nfa.states.find(temp_int) == nfa.states.end()) {
        std::cout << "\nPlease input again!" << std::endl;  // 同上
        std::cin >> temp_int;
    }
    nfa.initialState = temp_int;

    temp_int = 0;
    std::cout << "\nPlease input final states, using the number -1 as the end\ne.g: 0 1 2 -1\nThis shows that F={0,1,2}" << std::endl;
    std::cin >> temp_int;
    while (temp_int != -1) {
        if (nfa.states.find(temp_int) == nfa.states.end())
            std::cout << "\nPlease input again!" << std::endl;  // 同上
        else
            nfa.finalStates.insert(temp_int);
        std::cin >> temp_int;
    }

    DFA dfa = convertNFAtoDFA(nfa);

    std::cout << "Converting...\n";
    for (int i = 0; i < 101; i++) {
        std::cout << std::setfill('-') << std::setw(4) << i << "%";
        Sleep(5);
        std::cout << "\b\b\b\b";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    // 输出 DFA 函数
    for (auto& transition : dfa.transitions) {
        isFirst = true;
        std::cout << "{";
        for (int state : transition.first.first) {
            if (!isFirst)
                std::cout << ",";
            std::cout << state;
            isFirst = false;
        }

        std::cout << "} --" << transition.first.second << "--> {";
        isFirst = true;
        for (int state : transition.second) {
            if (!isFirst)
                std::cout << ",";
            std::cout << state;
            isFirst = false;
        }
        std::cout << "}" << std::endl;
    }

    // 输出 DFA 初始状态
    std::cout << "Initial state: ";
    for (int state : dfa.initialState)
        std::cout << state;
    std::cout << std::endl;

    // 输出 DFA 终态状态
    std::cout << "Final states: ";
    isFirst = true;
    isFirst2 = true;
    std::cout << "{";
    for (std::set<int> states : dfa.finalStates) {
        if (!isFirst2)
            std::cout << ",";
        isFirst2 = false;
        std::cout << "[";
        for (int state : states) {
            if (!isFirst)
                std::cout << ",";
            std::cout << state;
            isFirst = false;
        }
        std::cout << "]";
        isFirst = true;
    }
    std::cout << "}" << std::endl;

    return 0;
}