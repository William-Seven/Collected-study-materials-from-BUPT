#include "CFG_Simplify.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// 消除ε产生式
void eli_epsilon(set<char>& N, set<char>& T, map<char, std::set<std::string>>& P, char& S) {
    // 第一步，找到所有可以直接推出 ε 的非终结符
    std::set<char> canEpsilon;
    for (auto it = P.begin(); it != P.end(); ++it)
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
            if (*it2 == "#") {
                canEpsilon.insert(it->first);
                break;
            }

    // 第二步，不断找到新的可以推出 ε 的非终结符，直到集合不再变化
    while (true) {
        auto old_size = canEpsilon.size();
        for (auto it = P.begin(); it != P.end(); ++it) {
            // 当前字符已经在集合中，跳过
            if (canEpsilon.find(it->first) != canEpsilon.end())
                continue;

            for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
                bool canEpsilonFlag = true;
                for (auto it3 = it2->begin(); it3 != it2->end(); ++it3) {
                    // 当前字符不能推出 ε
                    if (canEpsilon.find(*it3) == canEpsilon.end()) {
                        canEpsilonFlag = false;
                        break;
                    }
                }

                // 若右式中的所有字符都能推出 ε，则当前字符也能推出 ε
                if (canEpsilonFlag) {
                    canEpsilon.insert(it->first);
                    break;
                }
            }
        }

        if (old_size == canEpsilon.size())
            break;  // 集合不再变化，退出循环
    }

    // 第三步，根据新的非终结符集合生成新的产生式集合 P1
    std::map<char, std::set<std::string>> P1;

    for (auto it = P.begin(); it != P.end(); ++it) {
        std::set<std::string> new_productions;  // 新的产生式列表

        // 遍历旧产生式列表的每一个产生式
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            int count_epsilon = 0;  // 记录右式中可致空的非终结符个数
            for (auto it3 = it2->begin(); it3 != it2->end(); ++it3)
                if (canEpsilon.find(*it3) != canEpsilon.end())
                    ++count_epsilon;  // 当前符号是可致空的

            // 枚举可致空的非终结符的所有组合：2的 n 次方个
            for (int i = 0; i < (1 << count_epsilon); ++i) {
                std::string new_production;  // 新的产生式
                int charac_index = 0;        // 当前处理的可致空字符的编号
                for (auto it3 = it2->begin(); it3 != it2->end(); ++it3) {
                    // 若当前字符可推出 ε
                    if (canEpsilon.find(*it3) != canEpsilon.end()) {
                        if ((i >> charac_index) & 1)         // 当前字符在当前生成式中被选中
                            new_production.push_back(*it3);  // 加入新的产生式
                        ++charac_index;
                    } else
                        // 若当前字符不可推出 ε
                        new_production.push_back(*it3);
                }
                if (new_production.size() > 0 && new_production != "#")  // 如果新的产生式非空且不是空串产生式
                    new_productions.insert(new_production);              // 加入新的产生式列表
            }
        }

        P1[it->first] = new_productions;  // 加入新的产生式集合
    }

    // 如果起始符号可以推出 ε，则需要增加一个新的起始符号
    if (canEpsilon.count(S) > 0) {
        S = NEW_STARTER;
        P1[NEW_STARTER] = {"#", "S"};
        N.insert(NEW_STARTER);
    }

    P = P1;
}

// 消除单产生式
void eli_single(set<char>& N, set<char>& T, map<char, std::set<std::string>>& P, char& S) {
    // 定义新的产生式集合
    std::map<char, std::set<std::string>> new_P;

    // 遍历旧的产生式集合中的每个非终结符A
    for (auto A : N) {
        // 初始化新的产生式列表和新的非终结符集合
        std::set<char> new_N;
        new_P[A] = {};
        new_N.insert(A);

        // 找出所有可以直接推出单个非终结符的产生式，并将这些非终结符加入new_N
        for (auto it = P[A].begin(); it != P[A].end(); ++it)
            if (it->size() == 1 && N.find(it->at(0)) != N.end())
                new_N.insert(it->at(0));

        // 不断扩展new_N直到不再变化
        std::set<char> prev_N;
        do {
            prev_N = new_N;
            for (auto B : prev_N)
                for (auto it = P[B].begin(); it != P[B].end(); ++it)
                    if (it->size() == 1 && N.find(it->at(0)) != N.end())
                        new_N.insert(it->at(0));
        } while (new_N != prev_N);

        // 构建新的产生式列表
        for (auto B : new_N)
            for (auto it = P[B].begin(); it != P[B].end(); ++it)
                if (it->size() > 1 || T.count(it->at(0)) > 0 || it->at(0) == EPSILON)  // 若当前产生式不是单产生式
                    new_P[A].insert(*it);

        // 去除重复的产生式，若新的产生式列表为空，则加入 A --> #
        if (new_P[A].size() == 0)
            new_P[A].insert("#");
    }

    // 更新P
    P = new_P;
}

// 消除无用符号
void eli_useless(set<char>& N, set<char>& T, map<char, std::set<std::string>>& P, char& S) {
    // 第一步，生成符号集
    std::set<char> N0, N1;
    // 遍历产生式 P
    for (auto it = P.begin(); it != P.end(); ++it)
        // 遍历产生式右侧
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            bool in_T = true;
            // 检查右侧符号是否都在 T 中
            for (auto it3 = it2->begin(); it3 != it2->end(); ++it3) {
                if (T.find(*it3) == T.end()) {
                    in_T = false;
                    break;
                }
            }
            // 如果右侧符号都在 T 中，则加入 N1
            if (in_T) {
                N1.insert(it->first);
                break;
            }
        }

    // 不断扩展N1，直到N1不再变化
    while (N0 != N1) {
        N0 = N1;
        for (auto it = P.begin(); it != P.end(); ++it)
            for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
                bool in_N0 = true;
                // 检查右侧符号是否都在 N0 中
                for (auto it3 = it2->begin(); it3 != it2->end(); ++it3) {
                    if (N0.find(*it3) == N0.end() && T.find(*it3) == T.end()) {
                        in_N0 = false;
                        break;
                    }
                }
                // 如果右侧符号都在 N1 中，则加入 N1
                if (in_N0) {
                    N1.insert(it->first);
                    break;
                }
            }
    }

    // 更新非终结符集合 N
    N = N1;

    // 创建新的产生式集合 P1
    std::map<char, std::set<std::string>> P1;
    for (auto it = P.begin(); it != P.end(); ++it) {
        if (N.find(it->first) == N.end())
            continue;

        P1[it->first] = {};
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            // 如果产生式右侧的符号不在N和T中，将in_N置为false
            bool in_N = true;
            for (auto it3 = it2->begin(); it3 != it2->end(); ++it3)
                if (*it3 != EPSILON && N.find(*it3) == N.end() && T.find(*it3) == T.end()) {
                    in_N = false;
                    break;
                }

            // 如果产生式右侧的符号都在N和T中，则将产生式加入P1
            if (in_N)
                P1[it->first].insert(*it2);
        }
    }

    // 更新产生式集合P为P1
    P = P1;

    // 第二步，可达符号集，先将起始符号放进可达符号集
    std::set<char> OK_N = {S};
    for (auto it = P[S].begin(); it != P[S].end(); ++it)
        for (auto it2 = it->begin(); it2 != it->end(); ++it2)
            OK_N.insert(*it2);

    // 不断扩展new_N，直到new_N不再变化
    while (N0 != OK_N) {
        N0 = OK_N;
        for (auto A : N0) {
            if (N.find(A) == N.end())
                continue;
            for (auto it = P[A].begin(); it != P[A].end(); ++it)
                for (auto it2 = it->begin(); it2 != it->end(); ++it2)
                    OK_N.insert(*it2);
        }
    }

    // 更新非终结符集合N和终结符集合T
    for (auto it = N.begin(); it != N.end();) {
        if (OK_N.count(*it) == 0)
            it = N.erase(it);
        else
            ++it;
    }
    for (auto it = T.begin(); it != T.end();) {
        if (OK_N.count(*it) == 0)
            it = T.erase(it);
        else
            ++it;
    }

    // 创建新的产生式集合P2
    std::map<char, std::set<std::string>> P2;
    for (auto it = P.begin(); it != P.end(); ++it) {
        // 产生式左侧符号无用
        if (N.find(it->first) == N.end())
            continue;

        P2[it->first] = {};
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            // 如果产生式右侧的符号都在N和T中，则将产生式加入P2
            bool in_N = true;
            for (auto it3 = it2->begin(); it3 != it2->end(); ++it3)
                if (*it3 != EPSILON && N.find(*it3) == N.end() && T.find(*it3) == T.end()) {
                    in_N = false;
                    break;
                }

            if (in_N)
                P2[it->first].insert(*it2);
        }
    }

    // 更新产生式集合P为P2
    P = P2;
}

// 打印简化后的结果
void printout(set<char>& N, set<char>& T, map<char, std::set<std::string>>& P, char& S) {
    std::cout << "The result after simplify:\n";
    // 非终结符集合
    std::cout << "N={";
    for (auto it = N.begin(); it != N.end(); ++it) {
        std::cout << *it;
        if (std::next(it) != N.end())  // 如果不是最后一个元素，输出逗号
            std::cout << ", ";
    }
    std::cout << "}\n";

    // 终结符集合
    std::cout << "T={";
    for (auto it = T.begin(); it != T.end(); ++it) {
        std::cout << *it;
        if (std::next(it) != T.end())  // 如果不是最后一个元素，输出逗号
            std::cout << ", ";
    }
    std::cout << "}\n";

    // 产生式集合
    std::cout << "P:\n";
    for (auto it = P.begin(); it != P.end(); ++it) {
        std::cout << "\t" << it->first << " --> ";
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            if (std::next(it2) != it->second.end())  // 如果不是最后一个元素，输出竖线
                std::cout << *it2 << " | ";
            else
                std::cout << *it2 << "\n";
        }
    }

    // 起始符号
    std::cout << "S = " << S << "\n";
}