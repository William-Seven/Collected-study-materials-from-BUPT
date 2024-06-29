#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include "CFG_Simplify.h"

/* 定义文法 */
std::set<char> N;                         // 非终结符集合
std::set<char> T;                         // 终结符集合
std::map<char, std::set<std::string>> P;  // 产生式集合
char S;                                   // 起始符号

using namespace std;

// 定义状态，终结符，符号栈，状态转换和产生式
typedef string State;
typedef string Symbol;
typedef string StackSymbol;
typedef string NonTerminal;
typedef string Terminal;
typedef tuple<State, StackSymbol, State> ProductionRule;

// PDA定义
struct PDA {
    set<State> Q;                                                              // 状态集合
    set<Terminal> T_PDA;                                                       // 终结符集合
    set<StackSymbol> Gamma;                                                    // 符号栈集合
    map<tuple<State, Terminal, StackSymbol>, set<pair<State, string>>> delta;  // 转换函数
    State q0;                                                                  // 初始状态
    StackSymbol z0;                                                            // 初始栈符号
    set<State> Phi;                                                            // 接受状态集合
};

// CFG定义
struct CFG {
    set<NonTerminal> N_CFG;                // 非终结符集合
    set<Terminal> T_CFG;                   // 终结符集合
    set<pair<NonTerminal, string>> P_CFG;  // 产生式集合
    NonTerminal S_CFG;                     // 开始符号
};

class PDAtoCFG {
   public:
    // 将PDA转换为CFG
    CFG convert(const PDA& pda) {
        CFG cfg;
        cfg.T_CFG = pda.T_PDA;        // 终结符集合与PDA相同
        cfg.S_CFG = "S";              // 设置开始符号为S
        cfg.N_CFG.insert(cfg.S_CFG);  // 将S加入到非终结符集合中
        // (0) 构造非终结符集合
        for (const State& q : pda.Q)
            for (const StackSymbol& z : pda.Gamma)
                for (const State& r : pda.Q)
                    cfg.N_CFG.insert("[" + q + "," + z + "," + r + "]");

        // (1) 构造初始产生式
        for (const State& q : pda.Q)
            cfg.P_CFG.insert({cfg.S_CFG, "[" + pda.q0 + "," + pda.z0 + "," + q + "]"});

        // (2) 和 (3) 根据状态转换构造产生式
        for (const auto& [key, valueSet] : pda.delta) {
            const auto& [q, a, z] = key;
            for (const auto& [newState, stackStr] : valueSet) {
                if (stackStr.empty()) {
                    // 处理ε情况，[q, z, newState] -> a
                    cfg.P_CFG.insert({"[" + q + "," + z + "," + newState + "]", a});
                } else {
                    // 处理非ε情况，[q, z, newState] -> a [q1, B1, q2] ... [qk-1, Bk, qk]
                    generateProductions(cfg, q, z, newState, a, stackStr, pda.Q);
                }
            }
        }

        // 删除无用符号，见书P124最后一段
        removeUnusedSymbols(cfg);

        return cfg;
    }

   private:
    // 生成产生式
    void generateProductions(CFG& cfg, const State& q, const StackSymbol& z, const State& newState, const Terminal& a, const string& stackStr, const set<State>& states) {
        //  遍历所有可能的状态序列，构造产生式
        for (const State& q1 : states)
            for (const State& q2 : states) {
                if (stackStr[1] == 'z') {
                    string production = a + "[" + newState + "," + string(1, stackStr[0]) + "," + q1 + "]" +
                                        "[" + q1 + "," + string(1, stackStr[1]) + string(1, stackStr[2]) + "," + q2 + "]";
                    cfg.P_CFG.insert({"[" + q + "," + z + "," + q2 + "]", production});
                } else {
                    string production = a + "[" + newState + "," + string(1, stackStr[0]) + "," + q1 + "]" +
                                        "[" + q1 + "," + string(1, stackStr[1]) + "," + q2 + "]";
                    cfg.P_CFG.insert({"[" + q + "," + z + "," + q2 + "]", production});
                }
            }
    }

    // 删除无用符号
    void removeUnusedSymbols(CFG& cfg) {
        set<NonTerminal> used;
        set<NonTerminal> unused;

        // 先检查是否出现在生成式左边
        for (const auto& state : cfg.N_CFG) {
            bool isUsed = false;
            for (const auto& [nonTerm, production] : cfg.P_CFG)
                if (nonTerm == state) {
                    used.insert(state);
                    isUsed = true;
                    break;
                }

            // 到最后一个产生式的左边都没有该状态，则无用
            if (!isUsed)
                unused.insert(state);
        }

        // 检查生成式右边是否出现 unused
        for (const auto& unusedState : unused) {
            // bool isUsed = false;
            for (auto it = cfg.P_CFG.begin(); it != cfg.P_CFG.end(); ++it)
                if (it->second.find(unusedState) != string::npos) {
                    unused.insert(it->first);
                    used.erase(it->first);
                }
        }

        // 删除无用的非终结符和相应的产生式
        for (auto it = cfg.N_CFG.begin(); it != cfg.N_CFG.end(); ++it)
            if (used.find(*it) == used.end())
                it = cfg.N_CFG.erase(it);

        for (auto unusedState : unused) {
            for (auto it = cfg.P_CFG.begin(); it != cfg.P_CFG.end(); ++it) {
                if (it->first.find(unusedState) != string::npos || it->second.find(unusedState) != string::npos)
                    it = cfg.P_CFG.erase(it);
            }
        }
    }
};

// 将cfg转换成简化所需的结构
void transfer(CFG& cfg) {
    // 非终结符集合
    int i = 0;
    char name = 'A';
    for (auto state : cfg.N_CFG) {
        if (state != "S") {
            char temp = (char)name + i;
            cout << state << "renamed to:" << temp << endl;
            string newState = {temp};

            for (auto it = cfg.P_CFG.begin(); it != cfg.P_CFG.end();) {
                string lhs = it->first;   // 创建左侧的新副本
                string rhs = it->second;  // 创建右侧的新副本

                // 使用新副本进行替换操作
                size_t pos = lhs.find(state);
                if (pos != string::npos) {
                    lhs.replace(pos, state.length(), newState);
                }
                pos = rhs.find(state);
                if (pos != string::npos) {
                    rhs.replace(pos, state.length(), newState);
                }

                // 更新容器中的元素
                if (lhs != it->first || rhs != it->second) {
                    it = cfg.P_CFG.erase(it);      // 删除旧元素并获取下一个有效迭代器
                    cfg.P_CFG.insert({lhs, rhs});  // 插入新元素
                } else {
                    it++;
                }
            }
            if ((char)name + i == 'R')
                i += 3;
            else
                i++;

            // 加入非终结符集合
            N.insert(temp);
        } else {
            N.insert('S');
        }
    }

    // 终结符集合
    for (auto& sign : cfg.T_CFG) {
        char t = sign[0];
        T.insert(t);
    }

    // 产生式
    for (auto it = cfg.P_CFG.begin(); it != cfg.P_CFG.end(); ++it) {
        string prod = it->second;
        if (prod.empty()) {
            prod = "#";
        }
        char left = it->first[0];

        P[left].insert(prod);
    }

    // 初始状态
    S = (char)cfg.S_CFG[0];
}

int main() {
    int mode;
    std::cout << "Please input the mode of the test:(1.Simplify CFG 2.PDA to CFG)" << std::endl;

    std::cin >> mode;
    if (std::cin.fail()) {
        std::cout << "ERROR:Please input number!!" << std::endl;
        std::cout << "number:";
        std::cin >> mode;
    }
    if (mode == 1) {
        std::string inputNtmp, inputTtmp;
        std::cout << "请输入非终结符，首个字符为起始状态：" << std::endl;
        std::cin >> inputNtmp;
        std::cout << "请输入终结符：" << std::endl;
        std::cin >> inputTtmp;

        S = inputNtmp[0];
        for (auto i : inputNtmp) {
            N.insert(i);
        }
        for (auto i : inputTtmp) {
            T.insert(i);
        }

        std::cout << "请输入生成式(程序收取#作为空字符串):" << std::endl;
        std::cout << "输入格式为 S C|aA|aB" << std::endl;
        std::cout << "请输入@结束输入" << std::endl;
        std::string Ptmp;
        while (getline(std::cin, Ptmp) && Ptmp != "@") {
            // std::cout<<"get: "<<Ptmp<<std::endl;
            std::istringstream iss(Ptmp);
            char nonTerminal;
            iss >> nonTerminal;

            std::string Terminal_string;
            iss >> Terminal_string;

            std::istringstream iss_1(Terminal_string);
            std::string ts;
            while (getline(iss_1, ts, '|')) {
                // std::cout<<"ts:"<<ts<<std::endl;
                P[nonTerminal].insert(ts);
            }
        }

        eli_epsilon(N, T, P, S);
        eli_single(N, T, P, S);
        eli_useless(N, T, P, S);
        printout(N, T, P, S);
        return 0;
    } else {
        PDA pda;

        int numStates, numTerminals, numStackSymbols, numFinalStates, numTransitions;

        // 输入PDA的状态数目和状态//2 q0\n q1\n
        cout << "Enter the number of states: ";
        cin >> numStates;
        for (int i = 0; i < numStates; ++i) {
            State q;
            cout << "Enter the states: ";
            cin >> q;
            pda.Q.insert(q);
        }

        // 输入终结符数目和终结符//2 a\n b\n
        cout << "Enter the number of terminals: ";
        cin >> numTerminals;
        for (int i = 0; i < numTerminals; ++i) {
            Terminal t;
            cout << "Enter the terminals: ";
            cin >> t;
            pda.T_PDA.insert(t);
        }

        // 输入符号栈符号数目和符号栈符号//2 A\n z0\n
        cout << "Enter the number of stack symbols: ";
        cin >> numStackSymbols;
        for (int i = 0; i < numStackSymbols; ++i) {
            StackSymbol s;
            cout << "Enter the stack symbols: ";
            cin >> s;
            pda.Gamma.insert(s);
        }

        // 输入初始状态和初始栈符号//q0\nz0\n
        cout << "Enter the start state: ";
        cin >> pda.q0;
        cout << "Enter the start stack symbol: ";
        cin >> pda.z0;

        // 输入最终状态数目和最终状态//0\n
        cout << "Enter the number of final states: ";
        cin >> numFinalStates;
        for (int i = 0; i < numFinalStates; ++i) {
            State f;
            cout << "Enter the final states: ";
            cin >> f;
            pda.Phi.insert(f);
        }

        // 输入转换函数数目和转换函数//6\n
        cout << "Enter the number of transitions(the function take # as ε): ";
        cin >> numTransitions;
        cin.ignore();  // 忽略换行符
        for (int i = 0; i < numTransitions; ++i) {
            cout << "Enter the transitions in the format \"q a z newQ str\" as:(q, a, z) -> (newQ, str): " << endl;
            string line;
            getline(cin, line);
            stringstream ss(line);
            string q, a, z, newQ, str;
            ss >> q >> a >> z >> newQ >> str;
            if (a == "#")
                a = "";
            if (str == "#")
                str = "";
            pda.delta[make_tuple(q, a, z)].insert(make_pair(newQ, str));
        }

        PDAtoCFG converter;
        CFG cfg = converter.convert(pda);

        cout << "Non-terminals (N): ";
        for (auto& n : cfg.N_CFG)
            cout << n << " ";
        cout << endl;

        cout << "Terminals (T): ";
        for (auto& t : cfg.T_CFG)
            cout << t << " ";
        cout << endl;

        cout << "Start Symbol (S): " << cfg.S_CFG << endl;

        cout << "Productions (P): " << endl;
        for (auto& [nonTerm, production] : cfg.P_CFG)
            if (production.empty())
                cout << nonTerm << " -> " << "ε" << endl;
            else
                cout << nonTerm << " -> " << production << endl;

        transfer(cfg);

        eli_epsilon(N, T, P, S);
        eli_single(N, T, P, S);
        eli_useless(N, T, P, S);
        printout(N, T, P, S);

        return 0;
    }
}
