#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "symbol.h"
#include <unordered_map>
#include <vector>
#include <memory>
#include <cassert>
// 前置声明
class SymbolTable;

struct SymbolTableEntry {
    Symbol* symbol;          // 符号对象
    SymbolTable* child_table;// 关联的子符号表（函数/过程才有）
    
    SymbolTableEntry(Symbol* sym, SymbolTable* child = nullptr)
        : symbol(sym), child_table(child) {}
    
    ~SymbolTableEntry() {
        delete symbol;
        delete child_table;
    }
};

class SymbolTable {
    public:
        explicit SymbolTable(SymbolTable* parent = nullptr) 
            : parent_(parent) {}
        
        ~SymbolTable() {
            for (auto& entry : entries_) {
                delete entry.second;
            }
        }
        Symbol* getSymbol(const std::string& name) const {
            SymbolTableEntry* entry = lookupEntry(name);
            return entry ? entry->symbol : nullptr;
        }
        // 添加符号（确保所有作用域都不存在同名符号）
        bool addSymbol(Symbol* symbol) {
            // 检查所有作用域是否已存在
            
            if (lookupEntry(symbol->getName())) {
                //cout<<"Symbol"<<endl;
                return false; // 存在冲突
            }
            // 创建子表（如果是函数/过程）
            SymbolTable* child = nullptr;
            if (dynamic_cast<FuncSymbol*>(symbol) || 
                dynamic_cast<ProcSymbol*>(symbol)) {
                child = new SymbolTable(this);
            }
            
            entries_[symbol->getName()] = new SymbolTableEntry(symbol, child);
            return true;
        }
    
        // 精确查找（仅当前作用域）
        SymbolTableEntry* lookupCurrent(const std::string& name) const {
            cout<<"name:"<<name<<"\n"<<endl;
            auto it = entries_.find(name);
            //assert(it != entries_.end());
            cout<<"in symbol table.h "<<endl;
            for(auto [name,entry]:entries_){
                cout<<name<<endl;
            }
            return it != entries_.end() ? it->second : nullptr;
        }

        // 递归查找（当前作用域 → 父作用域）
        SymbolTableEntry* lookupEntry(const std::string& name) const {
            if (auto entry = lookupCurrent(name)) {
                //cout<<"entry"<<endl;
                return entry;
            }
            return parent_ ? parent_->lookupEntry(name) : nullptr;
        }
    
        // 获取符号的子符号表（如果是函数/过程）
        SymbolTable* getChildTable(const std::string& name) const {
            auto entry = lookupEntry(name);
            return entry ? entry->child_table : nullptr;
        }

        // 获取符号表的父符号表
        SymbolTable* getParent() const {
            return parent_;
        }
    
        void print(int indent = 0) const {
            std::string indentStr(indent, ' ');
            
            // 打印当前符号表头
            std::cout << indentStr << "┌── Symbol Table";
            if (parent_ == nullptr) {
                std::cout << " (Global)";
            }
            std::cout << "\n";
            
            // 打印符号条目
            for (const auto& [name, entry] : entries_) {
                std::cout << indentStr << "│   ";
                entry->symbol->print();
                
                // 如果有子表，递归打印
                if (entry->child_table) {
                    std::cout << indentStr << "│\n";
                    entry->child_table->print(indent + 4);
                }
            }
            
            // 打印表尾
            std::cout << indentStr << "└──\n";
        }
    
    private:
        SymbolTable* parent_;
        std::unordered_map<std::string, SymbolTableEntry*> entries_;
    };

#endif // SYMBOL_TABLE_H