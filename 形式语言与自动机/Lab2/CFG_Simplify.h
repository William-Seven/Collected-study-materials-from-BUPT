#ifndef __CFG_SIMPLIFY_H__
#define __CFG_SIMPLIFY_H__

#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

#define EPSILON '#'      // 定义空字符为 #
#define NEW_STARTER 'T'  // 定义新添加的产生式的起始符为 T

void eli_epsilon(set<char>& N, set<char>& T, map<char, std::set<std::string>>& P, char& S);
void eli_single(set<char>& N, set<char>& T, map<char, std::set<std::string>>& P, char& S);
void eli_useless(set<char>& N, set<char>& T, map<char, std::set<std::string>>& P, char& S);
void printout(set<char>& N, set<char>& T, map<char, std::set<std::string>>& P, char& S);

#endif