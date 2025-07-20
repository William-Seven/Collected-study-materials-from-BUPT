#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include <vector>
#include "ast.h"  // ASTNode定义在这里

using namespace std;

// 前向声明
class ArrayType;
class RecordType;

// 类型联合体，可以是基本类型、数组或记录
union TypeUnion {
    BasicType basic_type;
    ArrayType* array_type;
    RecordType* record_type;
};

// 完整的类型描述
class SymbolType {
   public:
    TypeKind kind;
    TypeUnion type;

    SymbolType(BasicType basic) : kind(_BASIC) {
        type.basic_type = basic;
    }

    SymbolType(ArrayType* array) : kind(_ARRAY) {
        type.array_type = array;
    }

    SymbolType(RecordType* record) : kind(_RECORD) {
        type.record_type = record;
    }

    virtual ~SymbolType() = default;
};

// 数组类型定义
class ArrayType {
   public:
    SymbolType* element_type;
    vector<int> start_index, end_index;

    ArrayType(SymbolType* elem_type)
        : element_type(elem_type) {}

    void addDimension(int start, int end) {
        start_index.push_back(start);
        end_index.push_back(end);
    }
};

// 记录类型字段定义
class RecordField {
   public:
    string name;
    SymbolType* type;

    RecordField(const string& n, SymbolType* t) : name(n), type(t) {}
};

// 记录类型定义
class RecordType {
   public:
    string type_name;  // 添加记录类型名称
    vector<RecordField> fields;

    RecordType(const string& name) : type_name(name) {}

    void addField(const string& name, SymbolType* type) {
        fields.emplace_back(name, type);
    }

    const string& getName() const { return type_name; }
};

// 基类 Symbol
class Symbol {
   protected:
    string name;

   public:
    Symbol(const string& n) : name(n) {}
    virtual ~Symbol() {}

    string getName() const { return name; }
    virtual void print() const = 0;
};

// 常量符号类
class ConstSymbol : public Symbol {
    BasicType type;
    union {
        int int_value;
        float real_value;
        char char_value;
        bool bool_value;
    } value;
    string string_value;  // 单独存储字符串

   public:
    ConstSymbol(const string& n, BasicType t, int val)
        : Symbol(n), type(t) {
        value.int_value = val;
    }

    ConstSymbol(const string& n, BasicType t, float val)
        : Symbol(n), type(t) {
        value.real_value = val;
    }

    ConstSymbol(const string& n, BasicType t, char val)
        : Symbol(n), type(t) {
        value.char_value = val;
    }

    ConstSymbol(const string& n, BasicType t, const char* val)
        : Symbol(n), type(t), string_value(val) {}

    ConstSymbol(const string& n, BasicType t, const string& val)
        : Symbol(n), type(t), string_value(val) {}

    ConstSymbol(const string& n, BasicType t, bool val)
        : Symbol(n), type(t) {
        value.bool_value = val;
    }

    ~ConstSymbol() = default;

    BasicType getType() const { return type; }

    // 打印函数
    void print() const override {
        cout << "Const: " << name << " [";
        switch (type) {
            case INTEGER:
                cout << "INTEGER] = " << value.int_value;
                break;
            case REAL:
                cout << "REAL] = " << value.real_value;
                break;
            case CHAR_:
                cout << "CHAR] = '" << value.char_value << "'";
                break;
            case STRING_:
                cout << "STRING] = \"" << string_value << "\"";
                break;
            case BOOLEAN_:
                cout << "BOOLEAN] = " << (value.bool_value ? "true" : "false");
                break;
            default:
                cout << "UNKNOWN]";
        }
        cout << endl;
    }
};

// 变量符号类
class VarSymbol : public Symbol {
    SymbolType* type;
    int* start_pos;  // 为基本类型或记录时为null
    int* end_pos;    // 为基本类型或记录时为null
    bool is_pointer = false;

   public:
    VarSymbol(const string& n, SymbolType* t)
        : Symbol(n), type(t), start_pos(nullptr), end_pos(nullptr) {}

    VarSymbol(const string& n, SymbolType* t, int start, int end)
        : Symbol(n), type(t), start_pos(new int(start)), end_pos(new int(end)), is_pointer(false) {}

    ~VarSymbol() {
        if (start_pos)
            delete start_pos;
        if (end_pos)
            delete end_pos;
        if (type)
            delete type;
    }

    SymbolType* getType() const { return type; }
    int* getStartPos() const { return start_pos; }
    int* getEndPos() const { return end_pos; }

    void setPointer(bool val) { is_pointer = val; }
    bool getPointer() const { return is_pointer; }

    void print() const override {
        cout << "Var: " << name << " [";
        switch (type->kind) {
            case _BASIC:
                cout << "type->type.basic_type:" << type->type.basic_type << endl;
                cout << "BASIC";
                break;
            case _ARRAY:
                cout << "ARRAY";
                break;
            case _RECORD:
                cout << "RECORD";
                break;
        }
        cout << "]";

        if (start_pos && end_pos) {
            cout << " [" << *start_pos << ".." << *end_pos << "]";
        }
        cout << endl;
    }
};

// 函数符号类
class FuncSymbol : public Symbol {
    ASTNode* entry;  // 语法树节点入口
    BasicType return_type;
    vector<VarSymbol*> parameters;

   public:
    FuncSymbol(const string& n, ASTNode* e, BasicType rt)
        : Symbol(n), entry(e), return_type(rt) {}

    ~FuncSymbol() {
        for (auto param : parameters) {
            delete param;
        }
    }

    ASTNode* getEntry() const { return entry; }
    BasicType getReturnType() const { return return_type; }

    void addParameter(VarSymbol* param) {
        parameters.push_back(param);
    }

    const vector<VarSymbol*>& getParameters() const {
        return parameters;
    }

    void print() const override {
        cout << "Function: " << name << " [RETURNS ";
        switch (return_type) {
            case INTEGER:
                cout << "INTEGER";
                break;
            case REAL:
                cout << "REAL";
                break;
            case CHAR_:
                cout << "CHAR";
                break;
            case STRING_:
                cout << "STRING";
                break;
            case BOOLEAN_:
                cout << "BOOLEAN";
                break;
            default:
                cout << "UNKNOWN";
        }
        cout << "] with " << parameters.size() << " parameters" << endl;
    }
};

// 过程符号类
class ProcSymbol : public Symbol {
    ASTNode* entry;  // 语法树节点入口
    vector<VarSymbol*> parameters;

   public:
    ProcSymbol(const string& n, ASTNode* e) : Symbol(n), entry(e) {}

    ~ProcSymbol() {
        for (auto param : parameters) {
            delete param;
        }
    }

    ASTNode* getEntry() const { return entry; }

    void addParameter(VarSymbol* param) {
        parameters.push_back(param);
    }

    const vector<VarSymbol*>& getParameters() const {
        return parameters;
    }

    void print() const override {
        cout << "Procedure: " << name << " with " << parameters.size() << " parameters" << endl;
        for (const auto& param : parameters) {
            cout << "  Param: ";
            param->print();
        }
    }
};

#endif  // SYMBOL_H