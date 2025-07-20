#ifndef AST_H
#define AST_H
#include "type.h"
#include <iostream>
#include <queue>
#include <string>
#include <variant>
#include <vector>

using namespace std;

extern bool caseInsensitiveEqual(const string& str1, const string& str2);

class TokenInfo {
   public:
    BasicType type;
    // 使用std::variant来替代union
    union{
        int int_value;
        float real_value;
        char char_value;
        bool bool_value;
    }value;
    string string_value;
    int line_no;
    int column_no;

    // 构造函数
    TokenInfo() : type(NULL_TYPE), line_no(0), column_no(0) {}

    // 构造函数重载，用于初始化各种类型的值
    TokenInfo(int int_value) : type(INTEGER),line_no(0), column_no(0) {this->value.int_value = int_value;}
    TokenInfo(float real_value) : type(REAL),  line_no(0), column_no(0) {this->value.real_value = real_value;}
    TokenInfo(char char_value) : type(CHAR_),  line_no(0), column_no(0) {this->value.char_value = char_value;}
    TokenInfo(const char *v) : type(STRING_), string_value(std::string(v)), line_no(0), column_no(0) {}
    TokenInfo(string string_value) : type(STRING_), string_value(string_value), line_no(0), column_no(0) {}
    TokenInfo(bool bool_value) : type(BOOLEAN_), line_no(0), column_no(0) {this->value.bool_value = bool_value;}

    // 拷贝构造函数
    TokenInfo(const TokenInfo& other) : type(other.type), value(other.value), line_no(other.line_no), column_no(other.column_no) {}

    // 析构函数
    ~TokenInfo() {}
};

template<typename... Args>
void safeDelete(Args*... args) {
    (..., (delete args, args = nullptr));
}

typedef enum {
    NODE_ARRAY_TYPE,
    NODE_ASSIGN_STATEMENT,
    NODE_BASIC_TYPE,
    NODE_BINARY_OP,
    NODE_CONST_DECLARATION,
    NODE_CONST_DECLARATION_LIST,
    NODE_CONTROL_STATEMENT,
    NODE_ELSE_PART,
    NODE_EMPTY_STATEMENT,
    NODE_EXPRESSION_LIST,
    NODE_FIELD,
    NODE_FIELD_LIST,
    NODE_FACTOR,
    NODE_FUNC_ASSIGN_STATEMENT,
    NODE_FOR_STATEMENT,
    NODE_IDENTIFIER_LIST,
    NODE_IF_STATEMENT,
    NODE_PROGRAM,
    NODE_PROGRAM_BODY,
    NODE_PROGRAM_HEAD,
    NODE_PROCEDURE_CALL,
    NODE_READLN_STATEMENT,
    NODE_READ_STATEMENT,
    NODE_RECORD_TYPE,
    NODE_SWITCH_CASE_ITEM,
    NODE_SWITCH_CASE_LIST,
    NODE_SWITCH_STATEMENT,
    NODE_SUBPROGRAM,
    NODE_SUBPROGRAM_BODY,
    NODE_SUBPROGRAM_DECLARATIONS,
    NODE_SUBPROGRAM_HEAD,
    NODE_STATEMENT_LIST,
    NODE_STR_EXPRESSION,
    NODE_UNARY_OP,
    NODE_VAR_DECLARATION,
    NODE_VAR_DECLARATION_LIST,
    NODE_WHILE_STATEMENT,
    NODE_WRITE_STATEMENT,
    NODE_WRITELN_STATEMENT,
    NODE_PERIOD,
    NODE_PERIOD_LIST,
    NODE_PARAMETER,
    NODE_PARAMETER_LIST,
    NODE_ID_VAR_PART,
    NODE_ID_VAR_PART_LIST,
    NODE_VARIABLE,
    NODE_VARIABLE_LIST,
    NODE_STD_TYPE,
    NODE_TYPE_DECLARATION,
    NODE_TYPE_DECLARATION_LIST
} NodeType;

// 基础AST节点类
class ASTNode {
   public:
    virtual ~ASTNode() = default;  // 添加虚析构函数
    virtual void free() = 0;  // 每个节点需要实现 free 函数

    int line_no;
    NodeType node_type;
};

// 前置声明
class PeriodListNode;
class PeriodNode;

// ArrayTypeNode: 数组类型节点
class ArrayTypeNode : public ASTNode {
   public:
    ASTNode* period_list;
    BasicType type;

    ArrayTypeNode(ASTNode* p, string t)
        : period_list(p) {
        node_type = NODE_ARRAY_TYPE;
        if(caseInsensitiveEqual(t, "integer")){
            type = INTEGER;
        }
        else if(caseInsensitiveEqual(t, "real")){
            type = REAL;
        }
        else if(caseInsensitiveEqual(t, "char")){
            type = CHAR_;
        }
        else if(caseInsensitiveEqual(t, "boolean")){
            type = BOOLEAN_;
        }
        else if(caseInsensitiveEqual(t, "string")){
            type = STRING_;
        }
    }

    // 深拷贝构造
    ArrayTypeNode(ArrayTypeNode* other);

    ~ArrayTypeNode() {
        free();
    }

    void free() override {
        if (period_list) {
            delete period_list;
            period_list = nullptr;
        }
    }
};

// AssignStatementNode: 赋值语句节点
class AssignStatementNode : public ASTNode {
   public:
    ASTNode* variable;
    ASTNode* expr;

    AssignStatementNode(ASTNode* var, ASTNode* e)
        : variable(var), expr(e) {
        node_type = NODE_ASSIGN_STATEMENT;
    }

    ~AssignStatementNode() {
        free();
    }

    void free() override {
        if (variable) {
            delete variable;
            variable = nullptr;
        }
        if (expr) {
            delete expr;
            expr = nullptr;
        }
    }
};

// BasicTypeNode: 基本类型节点
class BasicTypeNode : public ASTNode {
   public:
    BasicType type;

    BasicTypeNode(string s){
        node_type = NODE_BASIC_TYPE;
        if(caseInsensitiveEqual(s, "integer")){
            type = INTEGER;
        }
        else if(caseInsensitiveEqual(s, "real")){
            type = REAL;
        }
        else if(caseInsensitiveEqual(s, "char")){
            type = CHAR_;
        }
        else if(caseInsensitiveEqual(s, "boolean")){
            type = BOOLEAN_;
        }
        else if(caseInsensitiveEqual(s, "string")){
            type = STRING_;
        }
    }

    // 深拷贝构造
    BasicTypeNode(BasicTypeNode* other);

    ~BasicTypeNode() {
        free();
    }

    void free() override {
        // 不需要释放任何资源
    }
};

// BinaryOpNode: 二元操作节点
class BinaryOpNode : public ASTNode {
   public:
    string op;
    ASTNode* left;
    ASTNode* right;

    BinaryOpNode(string operation, ASTNode* l, ASTNode* r)
        : op(move(operation)), left(l), right(r) {
        node_type = NODE_BINARY_OP;
    }

    ~BinaryOpNode() {
        free();
    }

    void free() override {
        if (left) {
            delete left;
            left = nullptr;
        }
        if (right) {
            delete right;
            right = nullptr;
        }
    }
};

// ConstDeclarationNode: 常量声明节点
class ConstDeclarationNode : public ASTNode {
   public:
    string id;
    ASTNode* value;

    ConstDeclarationNode(string id_name, ASTNode* v)
        : id(id_name), value(v) {
        node_type = NODE_CONST_DECLARATION;
    }

    ~ConstDeclarationNode() {
        free();
    }

    void free() override {
        if (value) {
            delete value;
            value = nullptr;
        }
    }
};

// ConstDeclarationListNode: 常量声明列表节点
class ConstDeclarationListNode : public ASTNode {
   public:
    vector<ASTNode*> const_list;

    ConstDeclarationListNode(vector<ASTNode*> list)
        : const_list(list) {
        node_type = NODE_CONST_DECLARATION_LIST;
    }

    ~ConstDeclarationListNode() {
        free();
    }

    void free() override {
        for (auto node : const_list) {
            if (node) {
                delete node;
            }
        }
        const_list.clear();
    }
};

// ControlStatementNode: 控制语句节点
class ControlStatementNode : public ASTNode {
   public:
    string content;

    ControlStatementNode(string c)
        : content(move(c)) {
        node_type = NODE_CONTROL_STATEMENT;
    }

    ~ControlStatementNode() {
        free();
    }

    void free() override {
        // 没有需要递归释放的资源
    }
};

// ElsePartNode: else 部分节点
class ElsePartNode : public ASTNode {
   public:
    ASTNode* statement;

    ElsePartNode(ASTNode* stmt)
        : statement(stmt) {
        node_type = NODE_ELSE_PART;
    }

    ~ElsePartNode() {
        free();
    }

    void free() override {
        if (statement) {
            delete statement;
            statement = nullptr;
        }
    }
};

// EmptyStatementNode: 空语句节点
class EmptyStatementNode : public ASTNode {
   public:
    EmptyStatementNode() {
        node_type = NODE_EMPTY_STATEMENT;
    }

    ~EmptyStatementNode() {
        free();
    }

    void free() override {
        // 无需递归释放
    }
};

// ExpressionListNode: 表达式列表节点
class ExpressionListNode : public ASTNode {
   public:
    vector<ASTNode*> expr_list;

    ExpressionListNode(vector<ASTNode*> list)
        : expr_list(list) {
        node_type = NODE_EXPRESSION_LIST;
    }

    ~ExpressionListNode() {
        free();
    }

    void free() override {
        for (auto node : expr_list) {
            if (node) {
                delete node;
            }
        }
        expr_list.clear();
    }
};


// 前置声明
class IdentifierListNode;
// FieldNode: 字段节点
class FieldNode : public ASTNode {
   public:
    ASTNode* id_list;
    ASTNode* type;

    FieldNode(ASTNode* id, ASTNode* t)
        : id_list(id), type(t) {
        node_type = NODE_FIELD;
    }

    // 深拷贝构造
    FieldNode(FieldNode* oth);
    FieldNode(ASTNode* oth, IdentifierListNode* othId);

    ~FieldNode() {
        free();
    }

    void free() override {
        if (id_list) {
            delete id_list;
            id_list = nullptr;
        }
        if (type) {
            delete type;
            type = nullptr;
        }
    }
};

// FieldListNode: 字段列表节点
class FieldListNode : public ASTNode {
   public:
    vector<ASTNode*> field_list;

    FieldListNode(vector<ASTNode*> list)
        : field_list(list) {
        node_type = NODE_FIELD_LIST;
    }

    ~FieldListNode() {
        free();
    }

    void free() override {
        for (auto node : field_list) {
            if (node) {
                delete node;
            }
        }
        field_list.clear();
    }
};

// FactorNode: 因子节点（如常数值节点）
class FactorNode : public ASTNode {
   public:
    float num;

    FactorNode(float number) : num(number) {
        node_type = NODE_FACTOR;
    }

    ~FactorNode() {
        free();
    }

    void free() override {
        // 仅包含基本数据类型，不需要递归释放
    }
};

// FuncAssignStatementNode: 函数赋值语句节点
class FuncAssignStatementNode : public ASTNode {
   public:
    string func_id;
    ASTNode* expr;

    FuncAssignStatementNode(string id, ASTNode* e)
        : func_id(move(id)), expr(e) {
        node_type = NODE_FUNC_ASSIGN_STATEMENT;
    }

    ~FuncAssignStatementNode() {
        free();
    }

    void free() override {
        if (expr) {
            delete expr;
            expr = nullptr;
        }
    }
};

// ForStatementNode: for 语句节点
class ForStatementNode : public ASTNode {
   public:
    string variable_id;
    ASTNode* first_expr;
    ASTNode* second_expr;
    ASTNode* statement;
    bool id_down;

    ForStatementNode(string variable_id, ASTNode* first, ASTNode* second, ASTNode* stmt, bool down)
        : variable_id(variable_id), first_expr(first), second_expr(second), statement(stmt), id_down(down) {
        node_type = NODE_FOR_STATEMENT;
    }

    ~ForStatementNode() {
        free();
    }

    void free() override {
        if (first_expr) {
            delete first_expr;
            first_expr = nullptr;
        }
        if (second_expr) {
            delete second_expr;
            second_expr = nullptr;
        }
        if (statement) {
            delete statement;
            statement = nullptr;
        }
    }
};

// IdentifierListNode: 标识符列表节点
class IdentifierListNode : public ASTNode {
   public:
    vector<string> identifier_list;

    IdentifierListNode(vector<string> list)
        : identifier_list(move(list)) {
        node_type = NODE_IDENTIFIER_LIST;
    }

    ~IdentifierListNode() {
        free();
    }

    void free() override {
        // identifier_list.clear();
    }
};

// IfStatementNode: if 语句节点
class IfStatementNode : public ASTNode {
   public:
    ASTNode* condition;
    ASTNode* then_statement;
    ASTNode* else_statement;

    IfStatementNode(ASTNode* cond, ASTNode* then_stmt, ASTNode* else_stmt)
        : condition(cond), then_statement(then_stmt), else_statement(else_stmt) {
        node_type = NODE_IF_STATEMENT;
    }

    ~IfStatementNode() {
        free();
    }

    void free() override {
        if (condition) {
            delete condition;
            condition = nullptr;
        }
        if (then_statement) {
            delete then_statement;
            then_statement = nullptr;
        }
        if (else_statement) {
            delete else_statement;
            else_statement = nullptr;
        }
    }
};

// ProgramNode: 程序节点
class ProgramNode : public ASTNode {
   public:
    ASTNode* head;
    ASTNode* body;

    ProgramNode(ASTNode* h, ASTNode* b)
        : head(h), body(b) {
        node_type = NODE_PROGRAM;
    }

    ProgramNode() {
        node_type = NODE_PROGRAM;
    }

    ~ProgramNode() {
        free();
    }

    void free() override {
        if (head) {
            delete head;
            head = nullptr;
        }
        if (body) {
            delete body;
            body = nullptr;
        }
    }
};

// ProgramBodyNode: 程序体节点
class ProgramBodyNode : public ASTNode {
   public:
    ASTNode* const_decls;
    ASTNode* type_decls;
    ASTNode* var_decls;
    ASTNode* subprogram_decls;
    ASTNode* body;

    ProgramBodyNode(ASTNode* c, ASTNode* t, ASTNode* v, ASTNode* s, ASTNode* b)
        : const_decls(c), type_decls(t), var_decls(v), subprogram_decls(s), body(b) {
        node_type = NODE_PROGRAM_BODY;
    }

    ~ProgramBodyNode() {
        free();
    }

    void free() override {
        if (const_decls) {
            delete const_decls;
            const_decls = nullptr;
        }
        if (var_decls) {
            delete var_decls;
            var_decls = nullptr;
        }
        if (subprogram_decls) {
            delete subprogram_decls;
            subprogram_decls = nullptr;
        }
        if (body) {
            delete body;
            body = nullptr;
        }
    }
};

// ProgramHeadNode: 程序头节点
class ProgramHeadNode : public ASTNode {
   public:
    string name;
    ASTNode* param_list;

    ProgramHeadNode(string id, ASTNode* p)
        : name(move(id)), param_list(p) {
        node_type = NODE_PROGRAM_HEAD;
    }

    ~ProgramHeadNode() {
        free();
    }

    void free() override {
        if (param_list) {
            delete param_list;
            param_list = nullptr;
        }
    }
};

// ProcedureCallNode: 过程调用节点
class ProcedureCallNode : public ASTNode {
   public:
    string proc_id;
    ASTNode* expr_list;

    ProcedureCallNode(string id, ASTNode* exprs)
        : proc_id(move(id)), expr_list(exprs) {
        node_type = NODE_PROCEDURE_CALL;
    }

    ~ProcedureCallNode() {
        free();
    }

    void free() override {
        if (expr_list) {
            delete expr_list;
            expr_list = nullptr;
        }
    }
};

// ReadlnStatementNode: readln 语句节点
class ReadlnStatementNode : public ASTNode {
   public:
    ASTNode* variable_list;

    ReadlnStatementNode(ASTNode* vars)
        : variable_list(vars) {
        node_type = NODE_READLN_STATEMENT;
    }

    ~ReadlnStatementNode() {
        free();
    }

    void free() override {
        if (variable_list) {
            delete variable_list;
            variable_list = nullptr;
        }
    }
};

// ReadStatementNode: read 语句节点
class ReadStatementNode : public ASTNode {
   public:
    ASTNode* variable_list;

    ReadStatementNode(ASTNode* vars)
        : variable_list(vars) {
        node_type = NODE_READ_STATEMENT;
    }

    ~ReadStatementNode() {
        free();
    }

    void free() override {
        if (variable_list) {
            delete variable_list;
            variable_list = nullptr;
        }
    }
};

// RecordTypeNode: 记录类型节点
class RecordTypeNode : public ASTNode {
   public:
    ASTNode* field_list;
    string name;

    RecordTypeNode(ASTNode* f) : field_list(f) {
        node_type = NODE_RECORD_TYPE;
    }
    RecordTypeNode(ASTNode* f, string s) : field_list(f), name(s) {
        node_type = NODE_RECORD_TYPE;
    }

    ~RecordTypeNode() {
        free();
    }

    void free() override {
        if (field_list) {
            delete field_list;
            field_list = nullptr;
        }
    }
};

// SwitchCaseItemNode: switch case 项目节点
class SwitchCaseItemNode : public ASTNode {
   public:
    ASTNode* label;
    ASTNode* statement;

    SwitchCaseItemNode(ASTNode* lbl, ASTNode* stmt)
        : label(lbl), statement(stmt) {
        node_type = NODE_SWITCH_CASE_ITEM;
    }

    ~SwitchCaseItemNode() {
        free();
    }

    void free() override {
        if (label) {
            delete label;
            label = nullptr;
        }
        if (statement) {
            delete statement;
            statement = nullptr;
        }
    }
};

// SwitchCaseListNode: switch case 列表节点
class SwitchCaseListNode : public ASTNode {
   public:
    vector<ASTNode*> cases;

    SwitchCaseListNode(vector<ASTNode*> case_list)
        : cases(case_list) {
        node_type = NODE_SWITCH_CASE_LIST;
    }

    ~SwitchCaseListNode() {
        free();
    }

    void free() override {
        for (auto node : cases) {
            if (node) {
                delete node;
            }
        }
        cases.clear();
    }
};

// SwitchStatementNode: switch 语句节点
class SwitchStatementNode : public ASTNode {
   public:
    ASTNode* expr;
    ASTNode* case_list;

    SwitchStatementNode(ASTNode* exp, ASTNode* cl)
        : expr(exp), case_list(cl) {
        node_type = NODE_SWITCH_STATEMENT;
    }

    ~SwitchStatementNode() {
        free();
    }

    void free() override {
        if (expr) {
            delete expr;
            expr = nullptr;
        }
        if (case_list) {
            delete case_list;
            case_list = nullptr;
        }
    }
};

// SubprogramNode: 子程序节点
class SubprogramNode : public ASTNode {
   public:
    ASTNode* head;
    ASTNode* body;

    SubprogramNode(ASTNode* h, ASTNode* b)
        : head(h), body(b) {
        node_type = NODE_SUBPROGRAM;
    }

    ~SubprogramNode() {
        free();
    }

    void free() override {
        if (head) {
            delete head;
            head = nullptr;
        }
        if (body) {
            delete body;
            body = nullptr;
        }
    }
};

// SubprogramBodyNode: 子程序体节点
class SubprogramBodyNode : public ASTNode {
   public:
    ASTNode* const_declarations;
    ASTNode* type_declarations;
    ASTNode* var_declarations;
    ASTNode* statement;

    SubprogramBodyNode(ASTNode* const_decls, ASTNode* type_decls, ASTNode* var_decls, ASTNode* stmt)
        : const_declarations(const_decls), type_declarations(type_decls), var_declarations(var_decls), statement(stmt) {
        node_type = NODE_SUBPROGRAM_BODY;
    }

    ~SubprogramBodyNode() {
        free();
    }

    void free() override {
        if (const_declarations) {
            delete const_declarations;
            const_declarations = nullptr;
        }
        if (var_declarations) {
            delete var_declarations;
            var_declarations = nullptr;
        }
        if (statement) {
            delete statement;
            statement = nullptr;
        }
    }
};

// SubprogramDeclarationsNode: 子程序声明列表节点
class SubprogramDeclarationsNode : public ASTNode {
   public:
    vector<ASTNode*> subprogram_list;

    SubprogramDeclarationsNode(vector<ASTNode*> list)
        : subprogram_list(list) {
        node_type = NODE_SUBPROGRAM_DECLARATIONS;
    }

    ~SubprogramDeclarationsNode() {
        free();
    }

    void free() override {
        for (auto node : subprogram_list) {
            if (node) {
                delete node;
            }
        }
        subprogram_list.clear();
    }
};

// SubprogramHeadNode: 子程序头节点
class SubprogramHeadNode : public ASTNode {
   public:
    string id;
    ASTNode* param_list;
    bool is_function;
    BasicType return_type;

    SubprogramHeadNode(string id_name, ASTNode* param_list, bool is_func, string return_t)
        : id(move(id_name)), param_list(param_list), is_function(is_func){
        node_type = NODE_SUBPROGRAM_HEAD;
        if(caseInsensitiveEqual(return_t, "integer")){
            return_type = INTEGER;
        }
        else if(caseInsensitiveEqual(return_t, "real")){
            return_type = REAL;
        }
        else if(caseInsensitiveEqual(return_t, "char")){
            return_type = CHAR_;
        }
        else if(caseInsensitiveEqual(return_t, "boolean")){
            return_type = BOOLEAN_;
        }
        else if(caseInsensitiveEqual(return_t, "string")){
            return_type = STRING_;
        }
    }

    ~SubprogramHeadNode() {
        free();
    }

    void free() override {
        if (param_list) {
            delete param_list;
            param_list = nullptr;
        }
    }
};

// StatementListNode: 语句列表节点
class StatementListNode : public ASTNode {
   public:
    vector<ASTNode*> statement_list;

    StatementListNode(vector<ASTNode*> list)
        : statement_list(list) {
        node_type = NODE_STATEMENT_LIST;
    }

    ~StatementListNode() {
        free();
    }

    void free() override {
        for (auto node : statement_list) {
            if (node) {
                delete node;
            }
        }
        statement_list.clear();
    }
};

// StrExpressionNode: 字符串表达式节点
class StrExpressionNode : public ASTNode {
   public:
    string str;

    StrExpressionNode(string s) : str(move(s)) {
        node_type = NODE_STR_EXPRESSION;
    }

    ~StrExpressionNode() {
        free();
    }

    void free() override {}
};

// TypeDeclarationNode: 类型声明节点
class TypeDeclarationNode : public ASTNode {
    public:
        string id;
        ASTNode* type;

        TypeDeclarationNode(string id_name, ASTNode* t)
            : id(move(id_name)), type(t) {
            node_type = NODE_TYPE_DECLARATION;
        }

        ~TypeDeclarationNode() {
            free();
        }

        void free() override {
            if (type) {
                delete type;
                type = nullptr;
            }
        }
};
 
// TypeDeclarationListNode: 类型声明列表节点
class TypeDeclarationListNode : public ASTNode {
    public:
        vector<ASTNode*> type_decl_list;

        TypeDeclarationListNode(vector<ASTNode*> list)
            : type_decl_list(list) {
            node_type = NODE_TYPE_DECLARATION_LIST;
        }

        ~TypeDeclarationListNode() {
            free();
        }

        void free() override {
            for (auto node : type_decl_list) {
                if (node) {
                    delete node;
                }
            }
            type_decl_list.clear();
        }
};

// UnaryOpNode: 一元操作节点
class UnaryOpNode : public ASTNode {
   public:
    string op;
    ASTNode* value;

    UnaryOpNode(string operation, ASTNode* val)
        : op(move(operation)), value(val) {
        node_type = NODE_UNARY_OP;
    }

    ~UnaryOpNode() {
        free();
    }

    void free() override {
        if (value) {
            delete value;
            value = nullptr;
        }
    }
};

// VarDeclarationNode: 变量声明节点
class VarDeclarationNode : public ASTNode {
   public:
    ASTNode* id_list;
    bool is_custom_type = false;
    string custom_type_name = "";
    ASTNode* type;

    VarDeclarationNode(ASTNode* id, string custom_type_name)
        : id_list(id), is_custom_type(true), custom_type_name(custom_type_name) {
        node_type = NODE_VAR_DECLARATION;
    }

    VarDeclarationNode(ASTNode* id, ASTNode* t)
        : id_list(id), type(t) {
        node_type = NODE_VAR_DECLARATION;
    }

    ~VarDeclarationNode() {
        free();
    }

    void free() override {
        if (id_list) {
            delete id_list;
            id_list = nullptr;
        }
        if (type) {
            delete type;
            type = nullptr;
        }
    }
};

// VarDeclarationListNode: 变量声明列表节点
class VarDeclarationListNode : public ASTNode {
   public:
    vector<ASTNode*> var_list;

    VarDeclarationListNode(vector<ASTNode*> list)
        : var_list(list) {
        node_type = NODE_VAR_DECLARATION_LIST;
    }

    ~VarDeclarationListNode() {
        free();
    }

    void free() override {
        for (auto node : var_list) {
            if (node) {
                delete node;
            }
        }
        var_list.clear();
    }
};

// WhileStatementNode: while 语句节点
class WhileStatementNode : public ASTNode {
   public:
    ASTNode* condition;
    ASTNode* statement;

    WhileStatementNode(ASTNode* cond, ASTNode* stmt)
        : condition(cond), statement(stmt) {
        node_type = NODE_WHILE_STATEMENT;
    }

    ~WhileStatementNode() {
        free();
    }

    void free() override {
        if (condition) {
            delete condition;
            condition = nullptr;
        }
        if (statement) {
            delete statement;
            statement = nullptr;
        }
    }
};

// WriteStatementNode: 写入语句节点
class WriteStatementNode : public ASTNode {
   public:
    ASTNode* expr_list;

    WriteStatementNode(ASTNode* exprs)
        : expr_list(exprs) {
        node_type = NODE_WRITE_STATEMENT;
    }

    ~WriteStatementNode() {
        free();
    }

    void free() override {
        if (expr_list) {
            delete expr_list;
            expr_list = nullptr;
        }
    }
};

// WritelnStatementNode: 换行写入语句节点
class WritelnStatementNode : public ASTNode {
   public:
    ASTNode* expr_list;

    WritelnStatementNode(ASTNode* exprs)
        : expr_list(exprs) {
        node_type = NODE_WRITELN_STATEMENT;
    }

    ~WritelnStatementNode() {
        free();
    }

    void free() override {
        if (expr_list) {
            delete expr_list;
            expr_list = nullptr;
        }
    }
};

// PeriodNode: Period 节点
class PeriodNode : public ASTNode {
   public:
    int start;
    int end;

    PeriodNode(int s, int e) : start(s), end(e) {
        node_type = NODE_PERIOD;
    }

    ~PeriodNode() {
        free();
    }

    void free() override {
        // 无需释放额外资源
    }
};

// PeriodListNode: Period 列表节点
class PeriodListNode : public ASTNode {
   public:
    vector<ASTNode*> period_list;

    PeriodListNode(vector<ASTNode*> list)
        : period_list(list) {
        node_type = NODE_PERIOD_LIST;
    }

    ~PeriodListNode() {
        free();
    }

    void free() override {
        for (auto node : period_list) {
            if (node) {
                delete node;
            }
        }
        period_list.clear();
    }
};

// ParameterNode: 参数节点
class ParameterNode : public ASTNode {
   public:
    ASTNode* id_list;
    BasicType type;
    bool is_pointer = false;

    ParameterNode(ASTNode* id, string t)
        : id_list(id) {
        node_type = NODE_PARAMETER;
        if(caseInsensitiveEqual(t, "integer")){
            type = INTEGER;
        }
        else if(caseInsensitiveEqual(t, "real")){
            type = REAL;
        }
        else if(caseInsensitiveEqual(t, "char")){
            type = CHAR_;
        }
        else if(caseInsensitiveEqual(t, "boolean")){
            type = BOOLEAN_;
        }
        else if(caseInsensitiveEqual(t, "string")){
            type = STRING_;
        }
    }

    ~ParameterNode() {
        free();
    }

    void free() override {
        if (id_list) {
            delete id_list;
            id_list = nullptr;
        }
    }
};

// ParameterListNode: 参数列表节点
class ParameterListNode : public ASTNode {
   public:
    vector<ASTNode*> param_list;

    ParameterListNode(vector<ASTNode*> list)
        : param_list(list) {
        node_type = NODE_PARAMETER_LIST;
    }

    ParameterListNode() {
        node_type = NODE_PARAMETER_LIST;
    }

    ~ParameterListNode() {
        free();
    }

    void free() override {
        for (auto node : param_list) {
            if (node) {
                delete node;
            }
        }
        param_list.clear();
    }
};

class IdVarPartListNode : public ASTNode {
   public:
    vector<ASTNode*> id_var_part_list;

    IdVarPartListNode(){
        node_type = NODE_ID_VAR_PART_LIST;
    }

    ~IdVarPartListNode() {
        free();
    }

    void free() override {
        for (auto node : id_var_part_list) {
            if (node) {
                delete node;
            }
        }
    }
};

// IdVarPartNode: 标识符变量部分节点
class IdVarPartNode : public ASTNode {
   public:
    ASTNode* expr_list;

    IdVarPartNode(ASTNode* exprs)
        : expr_list(exprs) {
        node_type = NODE_ID_VAR_PART;
    }

    ~IdVarPartNode() {
        free();
    }

    void free() override {
        if (expr_list) {
            delete expr_list;
            expr_list = nullptr;
        }
    }
};

// VariableNode: 变量节点
class VariableNode : public ASTNode {
   public:
    string id;
    ASTNode* extend_part;

    VariableNode(string id_name, ASTNode* part)
        : id(move(id_name)), extend_part(part) {
        node_type = NODE_VARIABLE;
    }

    ~VariableNode() {
        free();
    }

    void free() override {
        if (extend_part) {
            delete extend_part;
            extend_part = nullptr;
        }
    }
};

// VariableListNode: 变量列表节点
class VariableListNode : public ASTNode {
   public:
    vector<ASTNode*> variables;

    VariableListNode(vector<ASTNode*> list)
        : variables(list) {
        node_type = NODE_VARIABLE_LIST;
    }

    ~VariableListNode() {
        free();
    }

    void free() override {
        for (auto node : variables) {
            if (node) {
                delete node;
            }
        }
        variables.clear();
    }
};

// StdTypeNode: 标准类型节点
class StdTypeNode : public ASTNode {
   public:
    BasicType type;
    std::variant<int, float, char, string, bool> value;

    StdTypeNode(BasicType t, std::variant<int, float, char, string, bool> v) : type(t), value(move(v)) {
        node_type = NODE_STD_TYPE;
    }

    ~StdTypeNode() {
        free();
    }

    void free() override {
        // 不需要释放资源，因为没有指针成员
    }

    BasicType getBasicType() const {
        return type;
    }

    template<typename T>
    T getValue() {
        if (!std::holds_alternative<T>(value)) {
            throw std::runtime_error("Type mismatch in StdTypeNode::getValue");
        }
        return std::get<T>(value);
    }
};

#endif  // AST_H