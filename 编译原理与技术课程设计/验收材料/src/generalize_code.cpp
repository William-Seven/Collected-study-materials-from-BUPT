#include <algorithm>
#include <cassert>
#include <regex>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>
#include "ast.h"
#include "symbol.h"
#include "symbol_table.h"
#include "type.h"
typedef enum {
    UNARY_OP_NOT,
    UNARY_OP_MINUS,
    UNARY_OP_PLUS,
    UNARY_OP_ADDRESS,
    UNARY_OP_DEREFERENCE,
    UNARY_OP_SIZEOF
} UnaryOpType;
typedef enum {
    BINARY_OP_ADD,
    BINARY_OP_SUB,
    BINARY_OP_MUL,
    BINARY_OP_DIV,
    BINARY_OP_MOD,
    BINARY_OP_AND,
    BINARY_OP_OR,
    BINARY_OP_XOR,
    BINARY_OP_SHL,
    BINARY_OP_SHR,
    BINARY_OP_EQ,
    BINARY_OP_NEQ,
    BINARY_OP_LT,
    BINARY_OP_LEQ,
    BINARY_OP_GT,
    BINARY_OP_GEQ
} BinaryOpType;
class CodeGenerator {
   private:
    int indentLevel = 0;
    bool needIndent = true;
    SymbolTable* global_symtab;
    SymbolTable* current_symtab;
    string current_subprogrm_id;
    bool is_current_function = false;
    BasicType current_function_return_type = INTEGER;  // 默认值

   public:
    CodeGenerator(int level, bool need, SymbolTable* sym, SymbolTable* current_tab)
        : indentLevel(level), needIndent(need), global_symtab(sym), current_symtab(current_tab) {}
    SymbolTable* get_global_sym_tab() {
        return global_symtab;
    }
    SymbolTable* get_current_sym_tab() {
        return current_symtab;
    }
    std::string generate(ASTNode* node) {
        if (!node)
            return "";

        std::string result;
        switch (node->node_type) {
            case NODE_ARRAY_TYPE:
                result = generateArrayType(static_cast<ArrayTypeNode*>(node));
                break;
            case NODE_ASSIGN_STATEMENT:
                result = generateAssignStatement(static_cast<AssignStatementNode*>(node));
                break;
            case NODE_BASIC_TYPE:
                result = generateBasicType(static_cast<BasicTypeNode*>(node));
                break;
            case NODE_BINARY_OP:
                result = generateBinaryOp(static_cast<BinaryOpNode*>(node));
                break;
            case NODE_CONST_DECLARATION:
                result = generateConstDeclaration(static_cast<ConstDeclarationNode*>(node));
                break;
            case NODE_CONST_DECLARATION_LIST:
                result = generateConstDeclarationList(static_cast<ConstDeclarationListNode*>(node));
                break;
            case NODE_CONTROL_STATEMENT:
                result = generateControlStatement(static_cast<ControlStatementNode*>(node));
                break;
            case NODE_ELSE_PART:
                result = generateElsePart(static_cast<ElsePartNode*>(node));
                break;
            case NODE_EMPTY_STATEMENT:
                result = generateEmptyStatement(static_cast<EmptyStatementNode*>(node));
                break;
            case NODE_EXPRESSION_LIST:
                result = generateExpressionList(static_cast<ExpressionListNode*>(node));
                break;
            case NODE_FIELD:
                result = generateField(static_cast<FieldNode*>(node));
                break;
            case NODE_FIELD_LIST:
                result = generateFieldList(static_cast<FieldListNode*>(node));
                break;
            case NODE_FACTOR:
                result = generateFactor(static_cast<FactorNode*>(node));
                break;
            case NODE_FUNC_ASSIGN_STATEMENT:
                result = generateFuncAssignStatement(static_cast<FuncAssignStatementNode*>(node));
                break;
            case NODE_FOR_STATEMENT:
                result = generateForStatement(static_cast<ForStatementNode*>(node));
                break;
            case NODE_IDENTIFIER_LIST:
                result = generateIdentifierList(static_cast<IdentifierListNode*>(node));
                break;
            case NODE_IF_STATEMENT:
                result = generateIfStatement(static_cast<IfStatementNode*>(node));
                break;
            case NODE_PROGRAM:
                result = generateProgram(static_cast<ProgramNode*>(node));
                break;
            case NODE_PROGRAM_BODY:
                result = generateProgramBody(static_cast<ProgramBodyNode*>(node));
                break;
            case NODE_PROGRAM_HEAD:
                result = generateProgramHead(static_cast<ProgramHeadNode*>(node));
                break;
            case NODE_PROCEDURE_CALL:
                result = generateProcedureCall(static_cast<ProcedureCallNode*>(node));
                break;
            case NODE_READLN_STATEMENT:
                result = generateReadlnStatement(static_cast<ReadlnStatementNode*>(node));
                break;
            case NODE_READ_STATEMENT:
                result = generateReadStatement(static_cast<ReadStatementNode*>(node));
                break;
            case NODE_RECORD_TYPE:
                result = generateRecordType(static_cast<RecordTypeNode*>(node));
                break;
            case NODE_SWITCH_CASE_ITEM:
                result = generateSwitchCaseItem(static_cast<SwitchCaseItemNode*>(node));
                break;
            case NODE_SWITCH_CASE_LIST:
                result = generateSwitchCaseList(static_cast<SwitchCaseListNode*>(node));
                break;
            case NODE_SWITCH_STATEMENT:
                result = generateSwitchStatement(static_cast<SwitchStatementNode*>(node));
                break;
            case NODE_SUBPROGRAM:
                result = generateSubprogram(static_cast<SubprogramNode*>(node));
                break;
            case NODE_SUBPROGRAM_BODY:
                result = generateSubprogramBody(static_cast<SubprogramBodyNode*>(node));
                break;
            case NODE_SUBPROGRAM_DECLARATIONS:
                result = generateSubprogramDeclarations(static_cast<SubprogramDeclarationsNode*>(node));
                break;
            case NODE_SUBPROGRAM_HEAD:
                result = generateSubprogramHead(static_cast<SubprogramHeadNode*>(node));
                break;
            case NODE_STATEMENT_LIST:
                result = generateStatementList(static_cast<StatementListNode*>(node));
                break;
            case NODE_STR_EXPRESSION:
                result = generateStrExpression(static_cast<StrExpressionNode*>(node));
                break;
            case NODE_UNARY_OP:
                result = generateUnaryOp(static_cast<UnaryOpNode*>(node));
                break;
            case NODE_VAR_DECLARATION:
                result = generateVarDeclaration(static_cast<VarDeclarationNode*>(node));
                break;
            case NODE_VAR_DECLARATION_LIST:
                result = generateVarDeclarationList(static_cast<VarDeclarationListNode*>(node));
                break;
            case NODE_WHILE_STATEMENT:
                result = generateWhileStatement(static_cast<WhileStatementNode*>(node));
                break;
            case NODE_WRITE_STATEMENT:
                result = generateWriteStatement(static_cast<WriteStatementNode*>(node));
                break;
            case NODE_WRITELN_STATEMENT:
                result = generateWritelnStatement(static_cast<WritelnStatementNode*>(node));
                break;
            case NODE_PERIOD:
                result = generatePeriod(static_cast<PeriodNode*>(node));
                break;
            case NODE_PERIOD_LIST:
                result = generatePeriodList(static_cast<PeriodListNode*>(node));
                break;
            case NODE_PARAMETER:
                result = generateParameter(static_cast<ParameterNode*>(node));
                break;
            case NODE_PARAMETER_LIST:
                result = generateParameterList(static_cast<ParameterListNode*>(node));
                break;
            case NODE_ID_VAR_PART:
                break;
            case NODE_ID_VAR_PART_LIST:
                // result = generateIdVarPartList(static_cast<IdVarPartListNode*>(node));
                break;
            case NODE_VARIABLE:
                result = generateVariable(static_cast<VariableNode*>(node));
                break;
            case NODE_VARIABLE_LIST:
                result = generateVariableList(static_cast<VariableListNode*>(node));
                break;
            case NODE_STD_TYPE:
                result = generateStdType(static_cast<StdTypeNode*>(node));
                break;
            case NODE_TYPE_DECLARATION_LIST:
                result = generateTypedeclarationList(static_cast<TypeDeclarationListNode*>(node));
                break;
            case NODE_TYPE_DECLARATION:
                result = generateTypedeclaration(static_cast<TypeDeclarationNode*>(node));
                break;
            default:
                result = "/* Unsupported node type */";
        }

        return result;
    }

   private:
    std::string makeIndent() {
        return std::string(indentLevel * 4, ' ');
    }

    void increaseIndent() {
        indentLevel++;
    }

    void decreaseIndent() {
        if (indentLevel > 0) {
            indentLevel--;
        }
    }
    std::string formatStatement(const std::string& stmt) {
        cout << "formatStatement" << endl;
        std::string result;
        if (needIndent) {
            result += makeIndent();
            needIndent = false;
        }
        result += stmt;
        return result;
    }

    std::string formatBlock(const std::string& block) {
        cout << "forBlock" << endl;
        std::string result;
        increaseIndent();
        result += " {\n" + block;
        decreaseIndent();
        result += makeIndent() + "}";
        needIndent = true;
        return result;
    }

    std::string typeToCType(BasicType type) {
        switch (type) {
            case INTEGER:
                return "int";
            case REAL:
                return "float";
            case CHAR_:
                return "char";
            case BOOLEAN_:
                return "bool";
            case STRING_:
                return "char*";
                // default:
                //     return "void";
        }
    }

    std::string format_identifier(BasicType type) {
        switch (type) {
            case INTEGER:
                return "%d";
            case REAL:
                return "%f";
            case CHAR_:
                return "%c";
            case BOOLEAN_:
                return "%d";
            case STRING_:
                return "%s";
            default:
                return "void";
        }
    }

    std::string generateArrayType(ArrayTypeNode* node) {
        cout << "GAT" << endl;
        std::string cType = typeToCType(node->type);

        if (!node->period_list) {
            return cType;
        }

        std::vector<std::string> dimensions;

        if (node->period_list->node_type == NODE_PERIOD) {
            PeriodNode* period = static_cast<PeriodNode*>(node->period_list);
            dimensions.push_back("[" + std::to_string(period->end - period->start + 1) + "]");
        } else if (node->period_list->node_type == NODE_PERIOD_LIST) {
            PeriodListNode* periods = static_cast<PeriodListNode*>(node->period_list);
            for (auto p : periods->period_list) {
                if (p->node_type == NODE_PERIOD) {
                    PeriodNode* period = static_cast<PeriodNode*>(p);
                    dimensions.push_back("[" + std::to_string(period->end - period->start + 1) + "]");
                }
            }
        }

        return cType;
    }
    std::string generateTypedeclarationList(ASTNode* node) {
        auto* listNode = dynamic_cast<TypeDeclarationListNode*>(node);
        if (!listNode)
            return "/* Invalid type declaration list node */";

        std::string result;
        for (auto decl : listNode->type_decl_list) {
            result += generateTypedeclaration(decl) + "\n";
        }
        return result;
    }
    std::string generateTypedeclaration(ASTNode* node) {
        cout << "TYPEDECLA" << endl;
        auto* typeDecl = dynamic_cast<TypeDeclarationNode*>(node);
        if (!typeDecl)
            return "/* Invalid type declaration node */";

        cout << typeDecl->type << endl;
        std::string baseType = generate(typeDecl->type);

        if (baseType.find('[') != std::string::npos && typeDecl->type->node_type != NODE_RECORD_TYPE) {
            size_t bracketPos = baseType.find('[');
            std::string typeName = baseType.substr(0, bracketPos);
            std::string arrayDim = baseType.substr(bracketPos);

            return "typedef " + typeName + " " + typeDecl->id + arrayDim + ";";
        }

        else {
            return "typedef " + baseType + " " + typeDecl->id + ";";
        }
    }

    std::string generateAssignStatement(AssignStatementNode* node) {
        cout << "G ASS S" << endl;

        std::string expr = generate(node->expr);

        std::string var_code;
        bool is_var_parameter = false;

        if (auto* var_node = dynamic_cast<VariableNode*>(node->variable)) {
            auto* entry = current_symtab->lookupEntry(var_node->id);
            if (entry) {
                if (auto* var_symbol = dynamic_cast<VarSymbol*>(entry->symbol)) {
                    SymbolType* var_type = var_symbol->getType();
                    if (var_type->kind == _BASIC) {
                        if (var_node->extend_part == nullptr) {
                            is_var_parameter = true;
                        }
                    }
                }
            }

            var_code = generate(var_node);
            if (is_var_parameter) {
                var_code = "*" + var_code;
            }
        } else {
            var_code = generate(node->variable);
        }

        std::cout << "[Assign] " << var_code << " := " << expr << std::endl;
        return var_code + " = " + expr + ";";
    }

    std::string generateBasicType(BasicTypeNode* node) {
        cout << "G Basic T" << endl;
        return typeToCType(node->type);
    }

    int getOperatorPrecedence(const std::string& op) {
        if (op == "*" || op == "/" || op == "div" || op == "mod")
            return 2;
        if (op == "+" || op == "-" || op == "or")
            return 1;
        if (op == "=" || op == "<>" || op == "<" || op == ">" || op == "<=" || op == ">=")
            return 0;
        return -1;
    }

    std::string generateBinaryOp(BinaryOpNode* node) {
        cout << "BIN OP" << endl;
        std::string left = generate(node->left);
        std::string right = generate(node->right);

        std::string op = node->op;
        if (op == "div")
            op = "/";
        else if (op == "mod")
            op = "%";
        else if (op == "and")
            op = "&&";
        else if (op == "or")
            op = "||";
        else if (op == "=")
            op = "==";
        else if (op == "<>")
            op = "!=";

        int prec = getOperatorPrecedence(op);

        // 若左右是 BinaryOp 且优先级小于当前，则加括号
        if (auto left_op = dynamic_cast<BinaryOpNode*>(node->left)) {
            if (getOperatorPrecedence(left_op->op) < prec) {
                left = "(" + left + ")";
            }
        }
        if (auto right_op = dynamic_cast<BinaryOpNode*>(node->right)) {
            if (getOperatorPrecedence(right_op->op) < prec) {
                right = "(" + right + ")";
            }
        }

        return "(" + left + " " + op + " " + right + ")";
    }

    std::string generateConstDeclaration(ConstDeclarationNode* node) {
        cout << "G const decl" << endl;
        string type = search_Ctype(node->id, current_symtab);
        cout << "generate cpp 391" << endl;
        return "const " + type + " " + node->id + " = " + generate(node->value) + ";";
    }

    std::string generateConstDeclarationList(ConstDeclarationListNode* node) {
        cout << "G const decl list" << endl;
        std::string result;
        for (auto decl : node->const_list) {
            result += generate(decl) + "\n";
        }
        return result;
    }

    std::string toLower(const std::string& s) {
        std::string res = s;
        std::transform(res.begin(), res.end(), res.begin(), ::tolower);
        return res;
    }

    std::string generateControlStatement(ControlStatementNode* node) {
        cout << "G Ctrl statement" << endl;
        std::string content = toLower(node->content);  // 转为小写
        if (content == "break")
            return "break;";
        if (content == "continue")
            return "continue;";
        if (content == "exit")
            return "return;";
        return "/* " + node->content + " */;";
    }

    std::string generateElsePart(ElsePartNode* node) {
        cout << "G else" << endl;
        // thenPart = ensureSemicolon(thenPart, node->then_statement);
        if (!node->statement)
            return "";
        return "else {\n" + ensureSemicolon(generate(node->statement), node->statement) + "\n" + makeIndent() + "}";
    }

    std::string generateEmptyStatement(EmptyStatementNode* node) {
        cout << "G empty" << endl;
        return "";
    }

    std::string generateExpressionList(ExpressionListNode* node) {
        cout << "G ecpress list" << endl;
        std::string result;
        for (size_t i = 0; i < node->expr_list.size(); ++i) {
            if (i != 0)
                result += ", ";
            result += generate(node->expr_list[i]);
        }
        return result;
    }

    std::string generateField(FieldNode* node) {
        cout << "G field" << endl;
        std::string ids = generate(node->id_list);
        std::string typeInfo;

        if (node->type->node_type == NODE_ARRAY_TYPE) {
            ArrayTypeNode* arrayType = static_cast<ArrayTypeNode*>(node->type);
            std::string baseType = typeToCType(arrayType->type);
            std::vector<std::string> dimensions;

            if (arrayType->period_list) {
                if (arrayType->period_list->node_type == NODE_PERIOD_LIST) {
                    PeriodListNode* periods = static_cast<PeriodListNode*>(arrayType->period_list);
                    for (auto p : periods->period_list) {
                        if (p->node_type == NODE_PERIOD) {
                            PeriodNode* period = static_cast<PeriodNode*>(p);
                            dimensions.push_back("[" + std::to_string(period->end - period->start + 1) + "]");
                        }
                    }
                } else if (arrayType->period_list->node_type == NODE_PERIOD) {
                    PeriodNode* period = static_cast<PeriodNode*>(arrayType->period_list);
                    dimensions.push_back("[" + std::to_string(period->end - period->start + 1) + "]");
                }
            }

            std::string dimStr;
            for (const auto& dim : dimensions) {
                dimStr += dim;
            }

            typeInfo = baseType + " " + ids + dimStr;
        }

        else {
            typeInfo = generate(node->type) + " " + ids;
        }

        return typeInfo + ";";
    }
    std::string generateFieldList(FieldListNode* node) {
        cout << "G field list" << endl;

        std::string result;
        for (auto field : node->field_list) {
            std::string fieldCode = generate(field);
            if (!fieldCode.empty()) {
                result += makeIndent() + fieldCode + "\n";
            }
        }
        return result;
    }

    std::string generateFactor(FactorNode* node) {
        cout << "G factor" << endl;
        return std::to_string(node->num);
    }

    std::string generateFuncAssignStatement(FuncAssignStatementNode* node) {
        cout << "G func assign state" << endl;
        std::string expr = generate(node->expr);
        if (node->func_id == current_subprogrm_id && is_current_function) {
            return "__ret_val = " + expr + ";";
        } else {
            return node->func_id + " = " + expr + ";";
        }
    }

    std::string generateForStatement(ForStatementNode* node) {
        cout << "G for state" << endl;
        std::string init = node->variable_id + " = " + generate(node->first_expr);
        std::string condition = node->variable_id +
                                (node->id_down ? " >= " : " <= ") +
                                generate(node->second_expr);
        std::string increment = node->variable_id +
                                (node->id_down ? "--" : "++");

        std::string forHead = "for (" + init + "; " + condition + "; " + increment + ")";
        std::string body = generate(node->statement);

        if (body.find('{') != std::string::npos) {
            return formatStatement(forHead) + formatBlock("\n" + body + "\n");
        } else {
            return formatStatement(forHead + formatBlock("\n" + body + "\n"));
        }
    }

    std::string generateIdentifierList(IdentifierListNode* node) {
        cout << "G ident L" << endl;
        std::string result;
        for (size_t i = 0; i < node->identifier_list.size(); ++i) {
            if (i != 0)
                result += ", ";
            result += node->identifier_list[i];
        }
        return result;
    }

    std::string ensureSemicolon(std::string code, ASTNode* node) {
        if (code.empty())
            return code;
        if ((node->node_type == NODE_PROCEDURE_CALL ||
             node->node_type == NODE_ASSIGN_STATEMENT ||
             node->node_type == NODE_FUNC_ASSIGN_STATEMENT) &&
            code.back() != ';') {
            return code + ";";
        }
        return code;
    }

    std::string generateIfStatement(IfStatementNode* node) {
        // cout<<"G if state"<<endl;
        std::string condition = generate(node->condition);
        std::string thenPart = generate(node->then_statement);
        thenPart = ensureSemicolon(thenPart, node->then_statement);
        std::string elsePart = generate(node->else_statement);

        std::string result = "if (" + condition + ") {\n" + thenPart + "\n" + makeIndent() + "}";
        if (!elsePart.empty()) {
            result += " " + elsePart;
        }
        return result;
    }

    std::string generateProgram(ProgramNode* node) {
        cout << "G program" << endl;
        std::string head = generate(node->head);
        std::string body = generate(node->body);
        current_symtab = current_symtab->getParent();
        return "#include <stdio.h>\n#include <stdbool.h>\n\n" +
               head + "\n\n" + body;
    }

    std::string generateProgramBody(ProgramBodyNode* node) {
        cout << "G program body" << endl;
        increaseIndent();
        std::string result;

        if (node->const_decls) {
            result += makeIndent() + "/* Constants */\n" +
                      makeIndent() + generate(node->const_decls) + "\n\n";
        }

        if (node->var_decls) {
            result += makeIndent() + "/* Variables */\n" +
                      makeIndent() + generate(node->var_decls) + "\n\n";
        }

        if (node->subprogram_decls) {
            result += makeIndent() + "/* Functions */\n" +
                      makeIndent() + generate(node->subprogram_decls) + "\n\n";
        }

        result += "int main() {\n";

        result += makeIndent() + "/* Main program */\n" +
                  makeIndent() + generate(node->body) + "\n";

        result += "\nreturn 0;\n";
        result += "}";

        decreaseIndent();
        return result;
    }

    std::string generateProgramHead(ProgramHeadNode* node) {
        current_symtab = current_symtab->getChildTable(node->name);
        cout << "G Program Head" << endl;
        std::string params;
        cout << "param" << endl;
        if (node->param_list) {
            params = generate(node->param_list);
        }
        return "/* Program " + node->name + "(" + params + ") */";
    }

    std::string generateProcedureCall(ProcedureCallNode* node) {
        cout << "G procedure call" << endl;
        std::string args = node->expr_list ? generate(node->expr_list) : "";
        return node->proc_id + "(" + args + ")";
    }

    std::string generateReadlnStatement(ReadlnStatementNode* node) {
        cout << "G readln" << endl;
        std::string result = "";
        auto* var_list = static_cast<VariableListNode*>(node->variable_list);
        auto vars = var_list->variables;
        std::string formatSpectifier = "";
        std::string addressPrefix = "";
        for (auto* var : vars) {
            auto* var_1 = static_cast<VariableNode*>(var);
            auto* entry = current_symtab->lookupEntry(var_1->id);
            auto* var_symbol = dynamic_cast<VarSymbol*>(entry->symbol);
            if (var_symbol) {
                SymbolType* var_type = var_symbol->getType();
                formatSpectifier += typeToReadAndWrite(var_type) + ",";
            }
            addressPrefix += "&" + generate(static_cast<VariableNode*>(var)) + ",";
        }
        // cout<<"2222"<<endl;
        formatSpectifier.pop_back();
        addressPrefix.pop_back();
        string inner = "scanf(\"" + formatSpectifier + "\"," + addressPrefix + ");\n";
        std::string whileGetchar = "while (getchar() != '\\n');";
        return inner + whileGetchar;
    }

    std::string generateReadStatement(ReadStatementNode* node) {
        cout << "G read" << endl;
        std::string result = "";
        auto* var_list = static_cast<VariableListNode*>(node->variable_list);
        auto vars = var_list->variables;
        std::string formatSpectifier = "";
        std::string addressPrefix = "";
        for (auto* var : vars) {
            auto* var_1 = static_cast<VariableNode*>(var);
            auto* entry = current_symtab->lookupEntry(var_1->id);
            auto* var_symbol = dynamic_cast<VarSymbol*>(entry->symbol);
            if (var_symbol) {
                SymbolType* var_type = var_symbol->getType();
                formatSpectifier += typeToReadAndWrite(var_type) + ",";
            }
            addressPrefix += "&" + generate(static_cast<VariableNode*>(var)) + ",";
        }
        // cout<<"2222"<<endl;
        formatSpectifier.pop_back();
        addressPrefix.pop_back();
        return "scanf(\"" + formatSpectifier + "\"," + addressPrefix + ");";
    }

    std::string typeToReadAndWrite(SymbolType* type) {
        if (type->kind == _BASIC) {
            switch (type->type.basic_type) {
                case INTEGER:
                    return "%d";
                    break;

                case CHAR_:
                    return "%c";
                    break;

                case REAL:
                    return "%f";
                    break;

                case STRING_:
                    return "%s";
                    break;

                case BOOLEAN_:
                    return "%d";
                    break;

                default: {
                    return "Unknown Type";
                    break;
                }
            }
        } else if (type->kind == _ARRAY) {
            cout << "[typeToReadAndWrite] array type detected" << std::endl;
            SymbolType* elem_type = type->type.array_type->element_type;
            return typeToReadAndWrite(elem_type);
        }
    }

    std::string generateRecordType(RecordTypeNode* node) {
        cout << "G record type" << endl;
        increaseIndent();
        std::string fields = generate(node->field_list);
        decreaseIndent();

        if (fields.empty()) {
            return "struct {};";
        }

        std::string result = "struct {\n";
        result += fields;
        if (!fields.empty() && fields.back() != '\n') {
            result += "\n";
        }
        result += makeIndent() + "}";
        return result;
    }

    std::string generateSwitchCaseItem(SwitchCaseItemNode* node) {
        cout << "G switch case item" << endl;
        std::string label = generate(node->label);
        std::string stmt = generate(node->statement);

        std::vector<std::string> labels;
        size_t pos = 0;
        while ((pos = label.find(',')) != std::string::npos) {
            labels.push_back(label.substr(0, pos));
            label.erase(0, pos + 1);
        }
        labels.push_back(label);

        std::string result;
        for (const auto& lbl : labels) {
            if (!result.empty())
                result += " ";
            result += "case " + lbl + ":";
        }

        return result + " {\n" + stmt + "\n" + makeIndent() + "    break;\n" + makeIndent() + "}";
    }

    std::string generateSwitchCaseList(SwitchCaseListNode* node) {
        cout << "G case list" << endl;
        std::string result;
        for (auto item : node->cases) {
            result += makeIndent() + generate(item) + "\n";
        }
        return result;
    }

    std::string generateSwitchStatement(SwitchStatementNode* node) {
        cout << "G switch state" << endl;
        std::string expr = generate(node->expr);
        std::string cases = generate(node->case_list);

        return "switch (" + expr + ") {\n" + cases + makeIndent() + "}";
    }

    std::string generateSubprogram(SubprogramNode* node) {
        cout << "G subprogram" << endl;
        std::string head = generate(node->head);
        current_subprogrm_id = dynamic_cast<SubprogramHeadNode*>(node->head)->id;
        std::string body = generate(node->body);
        current_symtab = current_symtab->getParent();

        // 重置函数状态，避免影响下一个子程序
        is_current_function = false;
        current_function_return_type = INTEGER;

        return head + " {\n" + body + "\n" + makeIndent() + "}\n";
    }

    std::string generateSubprogramBody(SubprogramBodyNode* node) {
        cout << "G sub Body" << endl;
        increaseIndent();
        std::string result;

        if (node->const_declarations) {
            result += makeIndent() + "/* Constants */\n" +
                      makeIndent() + generate(node->const_declarations) + "\n\n";
        }

        if (node->var_declarations) {
            result += makeIndent() + "/* Variables */\n" +
                      makeIndent() + generate(node->var_declarations) + "\n\n";
        }

        // 添加 __ret_val 变量用于函数返回值
        if (is_current_function) {
            result += makeIndent() + typeToCType(current_function_return_type) + " __ret_val;\n\n";
        }

        result += makeIndent() + "/* Function body */\n" +
                  makeIndent() + generate(node->statement) + "\n";

        // 添加最终的 return
        if (is_current_function) {
            result += makeIndent() + "return __ret_val;\n";
        }

        decreaseIndent();
        return result;
    }

    std::string generateSubprogramDeclarations(SubprogramDeclarationsNode* node) {
        cout << "G sub decla" << endl;
        std::string result;
        for (auto subprog : node->subprogram_list) {
            result += generate(subprog) + "\n";
        }
        return result;
    }

    std::string generateSubprogramHead(SubprogramHeadNode* node) {
        current_symtab = current_symtab->getChildTable(node->id);
        cout << "G sub head" << endl;

        // 设置当前函数标志和返回类型
        is_current_function = node->is_function;
        current_function_return_type = node->return_type;
        current_subprogrm_id = node->id;

        std::string returnType = node->is_function ? typeToCType(node->return_type) : "void";
        std::string params = node->param_list ? generate(node->param_list) : "";

        return returnType + " " + node->id + "(" + params + ")";
    }

    std::string generateStatementList(StatementListNode* node) {
        cout << "G state list" << endl;
        std::string result;
        for (auto stmt : node->statement_list) {
            std::string stmtCode = generate(stmt);
            if (!stmtCode.empty()) {
                if (stmt->node_type == NODE_PROCEDURE_CALL ||
                    stmt->node_type == NODE_ASSIGN_STATEMENT ||
                    stmt->node_type == NODE_FUNC_ASSIGN_STATEMENT) {
                    if (stmtCode.back() != ';') {
                        stmtCode += ";";
                    }
                }
                result += formatStatement(stmtCode) + "\n";
            }
        }
        return result;
    }

    std::string generateStrExpression(StrExpressionNode* node) {
        cout << "G str express" << endl;
        return "\"" + node->str + "\"";
    }

    std::string generateUnaryOp(UnaryOpNode* node) {
        cout << "G unary" << endl;
        std::string op = node->op;
        std::string expr = generate(node->value);

        // 获取表达式类型：是否是 boolean
        BasicType operand_type = INTEGER;  // 默认
        if (auto* var_node = dynamic_cast<VariableNode*>(node->value)) {
            auto* entry = current_symtab->lookupEntry(var_node->id);
            if (auto* var_symbol = dynamic_cast<VarSymbol*>(entry->symbol)) {
                SymbolType* var_type = var_symbol->getType();
                operand_type = var_type->type.basic_type;
            }
        }

        if (op == "not") {
            if (operand_type == BOOLEAN_) {
                return "!(" + expr + ")";  // 逻辑非
            } else {
                return "~(" + expr + ")";  // 按位非
            }
        }
        if (op == "-")
            return "-(" + expr + ")";
        if (op == "+")
            return "+(" + expr + ")";
        if (op == "&")
            return "&(" + expr + ")";
        if (op == "^")
            return "*(" + expr + ")";
    }

    std::string generateVarDeclaration(VarDeclarationNode* node) {
        cout << "G var decla" << endl;

        std::string baseType = generate(node->type);
        std::vector<std::string> dimensions;

        // 处理数组维度
        if (node->type->node_type == NODE_ARRAY_TYPE) {
            ArrayTypeNode* arrayType = static_cast<ArrayTypeNode*>(node->type);
            if (arrayType->period_list) {
                if (arrayType->period_list->node_type == NODE_PERIOD) {
                    PeriodNode* period = static_cast<PeriodNode*>(arrayType->period_list);
                    dimensions.push_back("[" + std::to_string(period->end - period->start + 1) + "]");
                } else if (arrayType->period_list->node_type == NODE_PERIOD_LIST) {
                    PeriodListNode* periods = static_cast<PeriodListNode*>(arrayType->period_list);
                    for (auto p : periods->period_list) {
                        if (p->node_type == NODE_PERIOD) {
                            PeriodNode* period = static_cast<PeriodNode*>(p);
                            dimensions.push_back("[" + std::to_string(period->end - period->start + 1) + "]");
                        }
                    }
                }
            }
        }

        std::string dimStr;
        for (const auto& dim : dimensions) {
            dimStr += dim;
        }

        // 生成每个变量的声明
        auto* id_list_node = dynamic_cast<IdentifierListNode*>(node->id_list);
        std::string result;
        for (const std::string& id : id_list_node->identifier_list) {
            result += baseType + " " + id + dimStr + ";\n" + makeIndent();
        }

        return result;
    }

    std::string generateVarDeclarationList(VarDeclarationListNode* node) {
        cout << "G var decla list" << endl;
        std::string result;
        for (auto decl : node->var_list) {
            result += generate(decl) + "\n" + makeIndent();
        }
        return result;
    }

    std::string generateWhileStatement(WhileStatementNode* node) {
        cout << "G while state" << endl;
        std::string cond = generate(node->condition);
        std::string stmt = generate(node->statement);

        return "while " + cond + " {\n" + stmt + "\n" + makeIndent() + "}";
    }

    std::string generateWriteStatement(WriteStatementNode* node) {
        cout << "G write statement" << endl;

        std::string result = "";
        std::string formatSpectifier = "";
        std::string addressPrefix = "";
        auto* var_list = dynamic_cast<ExpressionListNode*>(node->expr_list);
        for (auto var : var_list->expr_list) {
            if (auto* var_node = dynamic_cast<VariableNode*>(var)) {
                cout << "this is a variable" << endl;
                auto* entry = current_symtab->lookupEntry(var_node->id);
                if (!entry) {
                    std::cerr << "Symbol not found: " << var_node->id << std::endl;
                    continue;
                }

                if (auto* func_symbol = dynamic_cast<FuncSymbol*>(entry->symbol)) {
                    BasicType return_type = func_symbol->getReturnType();
                    std::string format = format_identifier(return_type);
                    std::string value = var_node->id + "()";  // 转为函数调用形式
                    formatSpectifier += format + "";
                    addressPrefix += value + ",";
                } else if (auto* var_symbol = dynamic_cast<VarSymbol*>(entry->symbol)) {
                    SymbolType* var_type = var_symbol->getType();
                    cout << "var type:" << typeToReadAndWrite(var_type) << endl;
                    formatSpectifier += typeToReadAndWrite(var_type) + "";
                    addressPrefix += generate(static_cast<VariableNode*>(var)) + ",";
                } else if (auto* const_symbol = dynamic_cast<ConstSymbol*>(entry->symbol)) {
                    BasicType const_type = const_symbol->getType();
                    std::cout << "Const type: " << const_type << std::endl;
                    formatSpectifier += format_identifier(const_type) + "";
                    addressPrefix += generate(static_cast<VariableNode*>(var)) + ",";
                }
            } else if (auto* binary_node = dynamic_cast<BinaryOpNode*>(var)) {
                cout << "this is an express_list" << endl;
                string bin_expr_type = "";
                string bin_expr_express = "";
                if (auto* bin_expr = dynamic_cast<BinaryOpNode*>(var)) {
                    bin_expr_type = binary_type(bin_expr);
                    bin_expr_express = generate(bin_expr);
                    formatSpectifier += bin_expr_type + "";
                    addressPrefix += bin_expr_express + ",";
                }
            } else if (auto* unary_expr = dynamic_cast<UnaryOpNode*>(var)) {
                string unary_type;
                string unary_express;
                unary_type = "%d";
                unary_express = generate(unary_expr);
                formatSpectifier += unary_type + "";
                addressPrefix += unary_express + ",";
            } else if (auto* std_style = dynamic_cast<StdTypeNode*>(var)) {
                string std_type;
                string std_value;
                std_type = format_identifier(std_style->getBasicType());
                std_value = generate(std_style);
                formatSpectifier += std_type + "";
                addressPrefix += std_value + ",";
            } else if (auto* func_style = dynamic_cast<ProcedureCallNode*>(var)) {
                auto* var_sym = current_symtab->lookupCurrent(func_style->proc_id);
                auto* var_symbol = static_cast<FuncSymbol*>(var_sym->symbol);
                cout << "!!!!!!!var_sym:\t" << var_symbol->getName() << endl;
                if (var_symbol) {
                    BasicType return_type = var_symbol->getReturnType();
                    std::string format = format_identifier(return_type);  // 应该调用 format_identifier 而非 typeToCType
                    formatSpectifier += format + "";
                    addressPrefix += generate(func_style) + ",";
                }
            }
        }

        // if (!formatSpectifier.empty()) {
        //     formatSpectifier.pop_back();
        // }
        if (!addressPrefix.empty()) {
            addressPrefix.pop_back();
        }

        return "printf(\"" + formatSpectifier + "\"," + addressPrefix + ");";
    }
    std::string binary_type(BinaryOpNode* node) {
        string left_type;
        string right_type;
        if (node->op == "+" ||
            node->op == "-" ||
            node->op == "*" ||
            node->op == "%" ||
            node->op == "/") {
            if (auto* left_node = dynamic_cast<BinaryOpNode*>(node->left)) {
                left_type = binary_type(left_node);
            } else if (auto* left_node = dynamic_cast<VariableNode*>(node->left)) {
                left_type = search_type(left_node->id, current_symtab);
            }

            if (auto* right_node = dynamic_cast<BinaryOpNode*>(node->right)) {
                right_type = binary_type(right_node);
            } else if (auto* right_node = dynamic_cast<VariableNode*>(node->right)) {
                right_type = search_type(right_node->id, current_symtab);
            }
            if (left_type == "%f" || right_type == "%f") {
                return "%f";
            }
            if (left_type == right_type) {
                return left_type;
            }
            if (left_type == "%c" && right_type == "%d") {
                return "%d";
            }
            if (right_type == "%c" && left_type == "%d") {
                return "%d";
            }
            return "%d";
        } else {
            return "%d";
        }
    }

    std::string search_type(const std::string& id, SymbolTable* table) {
        auto* entry = table->lookupCurrent(id);
        if (!entry || !entry->symbol) {
            std::cerr << "Error: Symbol not found for id: " << id << std::endl;
            return "/* unknown */";
        }

        if (auto* const_sym = dynamic_cast<ConstSymbol*>(entry->symbol)) {
            cout << "This is const symbol!!!!!" << endl;
            return format_identifier(const_sym->getType());
        }

        if (auto* var_symbol = dynamic_cast<VarSymbol*>(entry->symbol)) {
            SymbolType* type = var_symbol->getType();

            if (type->kind == _ARRAY) {
                auto* elem_type = type->type.array_type->element_type;
                cout << "This is array !!!!" << elem_type << endl;
                if (elem_type->kind == _BASIC) {
                    cout << "++++++++++++++++++++" << endl;
                    return typeToReadAndWrite(elem_type);
                } else {
                    std::cerr << "Unsupported: array element type is not basic\n";
                    return "/* unknown */";
                }
            }

            if (type->kind == _BASIC) {
                return typeToReadAndWrite(type);
            }
        }

        return "/* unsupported symbol */";
    }

    std::string search_Ctype(string id, SymbolTable* table) {
        if (auto var_symbol = dynamic_cast<VarSymbol*>(table->lookupCurrent(id)->symbol)) {
            cout << "var_sym:\t" << var_symbol->getName() << endl;
            if (var_symbol) {
                SymbolType* var_type = var_symbol->getType();
                cout << "var type" << endl;
                cout << "basic:" << var_type->type.basic_type << endl;
                return typeToCType(var_type->type.basic_type);
            }
        }
        if (auto* const_sym = dynamic_cast<ConstSymbol*>(table->lookupCurrent(id)->symbol)) {
            cout << "const_sym:\t" << const_sym->getName() << endl;
            if (const_sym) {
                BasicType const_type = const_sym->getType();
                cout << "var type" << endl;
                cout << "basic:" << const_type << endl;
                return typeToCType(const_type);
            }
        }
    }

    std::string generateWritelnStatement(WritelnStatementNode* node) {
        std::string result = "";
        std::string formatSpectifier = "";
        std::string addressPrefix = "";
        auto* var_list = dynamic_cast<ExpressionListNode*>(node->expr_list);
        for (auto var : var_list->expr_list) {
            if (auto* var_node = dynamic_cast<VariableNode*>(var)) {
                cout << "this is a variable" << endl;
                auto* entry = current_symtab->lookupEntry(var_node->id);
                assert(entry != nullptr);

                if (auto* var_symbol = dynamic_cast<VarSymbol*>(entry->symbol)) {
                    SymbolType* var_type = var_symbol->getType();
                    cout << "var type:" << typeToReadAndWrite(var_type) << endl;
                    formatSpectifier += typeToReadAndWrite(var_type) + ",";
                    addressPrefix += generate(static_cast<VariableNode*>(var)) + ",";
                }
                if (auto* const_symbol = dynamic_cast<ConstSymbol*>(entry->symbol)) {
                    BasicType const_type = const_symbol->getType();
                    std::cout << "Const type: " << const_type << std::endl;
                    formatSpectifier += format_identifier(const_type) + ",";
                    addressPrefix += generate(static_cast<VariableNode*>(var)) + ",";
                }
            } else if (auto* binary_node = dynamic_cast<BinaryOpNode*>(var)) {
                cout << "this is an express_list" << endl;
                string bin_expr_type = "";
                string bin_expr_express = "";
                if (auto* bin_expr = dynamic_cast<BinaryOpNode*>(var)) {
                    bin_expr_type = binary_type(bin_expr);
                    bin_expr_express = generate(bin_expr);
                    formatSpectifier += bin_expr_type + ",";
                    addressPrefix += bin_expr_express + ",";
                }
            } else if (auto* unary_expr = dynamic_cast<UnaryOpNode*>(var)) {
                string unary_type;
                string unary_express;
                unary_type = "%d";
                unary_express = generate(unary_expr);
                formatSpectifier += unary_type + ",";
                addressPrefix += unary_express + ",";
            } else if (auto* std_style = dynamic_cast<StdTypeNode*>(var)) {
                string std_type;
                string std_value;
                std_type = format_identifier(std_style->getBasicType());
                std_value = generate(std_style);
                formatSpectifier += std_type + ",";
                addressPrefix += std_value + ",";
            } else if (auto* func_style = dynamic_cast<ProcedureCallNode*>(var)) {
                string func_type;
                string func_value;
                auto* var_sym = current_symtab->lookupCurrent(func_style->proc_id);
                auto* var_symbol = static_cast<FuncSymbol*>(var_sym->symbol);
                cout << "var_sym:\t" << var_symbol->getName() << endl;
                if (var_symbol) {
                    BasicType var_type = var_symbol->getReturnType();
                    cout << "var type" << endl;
                    func_type = typeToCType(var_type);
                }
                func_value = generate(func_style);
            }
        }

        if (!formatSpectifier.empty()) {
            formatSpectifier.pop_back();
        }
        if (!addressPrefix.empty()) {
            addressPrefix.pop_back();
        }

        return "printf(\"" + formatSpectifier + "\\n" + "\"," + addressPrefix + ");";
    }

    std::string generatePeriod(PeriodNode* node) {
        cout << "G period" << endl;
        return std::to_string(node->start) + ".." + std::to_string(node->end);
    }

    std::string generatePeriodList(PeriodListNode* node) {
        cout << "G period list" << endl;
        std::string result;
        for (size_t i = 0; i < node->period_list.size(); ++i) {
            if (i != 0)
                result += ", ";
            result += generate(node->period_list[i]);
        }
        return result;
    }

    std::string generateParameter(ParameterNode* node) {
        cout << "G paramter" << endl;
        std::string result;

        // 确保 node->id_list 是 IdentifierListNode
        auto* id_list_node = dynamic_cast<IdentifierListNode*>(node->id_list);
        if (!id_list_node) {
            std::cerr << "[generateParameter] Error: id_list is not IdentifierListNode." << std::endl;
            return "/* invalid parameter */";
        }

        std::string type_str = typeToCType(node->type);

        // 检查是否为指针类型
        std::string pointer_str = node->is_pointer ? "*" : "";

        for (size_t i = 0; i < id_list_node->identifier_list.size(); ++i) {
            if (i > 0)
                result += ", ";
            // 如果是指针类型，添加指针符号
            result += type_str + " " + pointer_str + " " + id_list_node->identifier_list[i];
        }

        return result;
    }

    std::string generateParameterList(ParameterListNode* node) {
        cout << "G param list" << endl;
        std::string result;
        for (size_t i = 0; i < node->param_list.size(); ++i) {
            if (i != 0)
                result += ", ";
            result += generate(node->param_list[i]);
        }
        return result;
    }

    std::string generateIdVarPartList(IdVarPartListNode* node, SymbolType* type) {
        if (!node)
            return "";

        ArrayType* array_type = type->type.array_type;
        std::string result;

        // 倒序访问下标节点
        std::cout << "[ID_VAR_LIST] List size: " << node->id_var_part_list.size() << std::endl;
        for (auto it = node->id_var_part_list.rbegin(); it != node->id_var_part_list.rend(); ++it) {
            auto* id_var_part = dynamic_cast<IdVarPartNode*>(*it);
            if (id_var_part) {
                std::cout << "[ID_VAR_LIST] Found IdVarPartNode" << std::endl;
                std::cout << "[DEBUG] Checking expr_list type..." << std::endl;

                auto* expr_list_node = dynamic_cast<ExpressionListNode*>(id_var_part->expr_list);
                if (expr_list_node) {
                    std::cout << "[ID_VAR_LIST] expr_list size: " << expr_list_node->expr_list.size() << std::endl;
                    // for (auto& expr : expr_list_node->expr_list) {
                    for (auto ite = expr_list_node->expr_list.begin(); ite != expr_list_node->expr_list.end(); ++ite) {
                        std::string part = generate(*ite);
                        std::cout << "  [IDX] = " << part << std::endl;
                        result += "[" + part;
                        stringstream ss;
                        ss << " - " << array_type->start_index[std::distance(expr_list_node->expr_list.begin(), ite)] << "]";
                        result += ss.str();
                    }
                }
            }
        }

        return result;
    }

    std::string generateVariable(VariableNode* node) {
        cout << "G var" << endl;
        auto* entry = current_symtab->lookupEntry(node->id);
        if (entry && dynamic_cast<FuncSymbol*>(entry->symbol)) {
            // 是函数名，返回函数调用
            return node->id + "()";
        }

        // 否则是普通变量或数组访问等
        std::string result = node->id;
        if (node->extend_part) {
            if (node->extend_part->node_type == NODE_ID_VAR_PART_LIST) {
                result += generateIdVarPartList(dynamic_cast<IdVarPartListNode*>(node->extend_part), static_cast<VarSymbol*>(entry->symbol)->getType());
            } else {
                result += "/* Unsupported extend_part */";
            }
            cout << "[generateVariable] id: " << node->id << ", extend_part type: " << (node->extend_part ? node->extend_part->node_type : -1) << endl;
        }
        return result;
    }

    std::string generateVariableList(VariableListNode* node) {
        cout << "G var list" << endl;
        std::string result;
        for (size_t i = 0; i < node->variables.size(); ++i) {
            if (i != 0)
                result += ", ";
            result += generate(node->variables[i]);
        }
        return result;
    }

    std::string generateStdType(StdTypeNode* node) {
        cout << "G stdtype" << endl;
        switch (node->type) {
            case INTEGER:
                return std::to_string(std::get<int>(node->value));
            case REAL:
                return std::to_string(std::get<float>(node->value));
            case CHAR_:
                return "'" + std::string(1, std::get<char>(node->value)) + "'";
            case BOOLEAN_: {
                bool val = std::get<bool>(node->value);
                cout << "BOOLEAN value: " << (val ? "true" : "false") << endl;
                return std::get<bool>(node->value) ? "true" : "false";
            }
            case STRING_:
                return "\"" + std::get<std::string>(node->value) + "\"";
            default:
                return "unknown type";
        }
        // cout<<"1"<<endl;
    }
};
std::string fixFunctionPlacement(const std::string& code) {
    std::regex func_pattern(R"((\b\w+\s*\*\s*\w+\s*\([^)]*\)\s*\{[^\}]*\}))");
    std::smatch matches;

    if (std::regex_search(code, matches, func_pattern)) {
        std::string func_def = matches[1].str();
        std::string func_decl = func_def.substr(0, func_def.find('{')) + ";\n";

        // 移除原函数定义（精确替换）
        std::string new_code = code;
        size_t func_pos = new_code.find(func_def);
        new_code.erase(func_pos, func_def.length());

        // 在#include后插入声明
        size_t include_end = new_code.find("#include");
        include_end = new_code.find("\n", include_end) + 1;
        new_code.insert(include_end, func_decl);

        // 在main()后插入定义
        size_t main_end = new_code.rfind("}");
        return new_code.insert(main_end + 1, "\n\n" + func_def + "\n");
    }
    return code;
}