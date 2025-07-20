#include <stdio.h>
#include <unistd.h>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include "ast.h"
#include "generalize_code.cpp"
#include "symbol_table.h"
#include "thirdparty/argparse.hpp"
using namespace std;
using namespace argparse;
// 声明由 Bison/Flex 生成的函数和变量
extern int yyparse(ASTNode** rootPtr);
extern FILE* yyin;
extern ASTNode* root;  // 你需要在 bison 文件中定义这个变量，用来接收语法树根节点

SymbolTable* globalSymbolTable;
SymbolTable* currentSymbolTable;

bool caseInsensitiveEqual(const std::string& str1, const std::string& str2) {
    return std::equal(str1.begin(), str1.end(), str2.begin(), str2.end(),
                      [](char a, char b) {
                          return std::tolower(a) == std::tolower(b);
                      });
}

string nodeTypeToString(NodeType type) {
    switch (type) {
        case NODE_ARRAY_TYPE:
            return "NODE_ARRAY_TYPE";
        case NODE_ASSIGN_STATEMENT:
            return "NODE_ASSIGN_STATEMENT";
        case NODE_BASIC_TYPE:
            return "NODE_BASIC_TYPE";
        case NODE_BINARY_OP:
            return "NODE_BINARY_OP";
        case NODE_CONST_DECLARATION:
            return "NODE_CONST_DECLARATION";
        case NODE_CONST_DECLARATION_LIST:
            return "NODE_CONST_DECLARATION_LIST";
        case NODE_CONTROL_STATEMENT:
            return "NODE_CONTROL_STATEMENT";
        case NODE_ELSE_PART:
            return "NODE_ELSE_PART";
        case NODE_EMPTY_STATEMENT:
            return "NODE_EMPTY_STATEMENT";
        case NODE_EXPRESSION_LIST:
            return "NODE_EXPRESSION_LIST";
        case NODE_FIELD:
            return "NODE_FIELD";
        case NODE_FIELD_LIST:
            return "NODE_FIELD_LIST";
        case NODE_FACTOR:
            return "NODE_FACTOR";
        case NODE_FUNC_ASSIGN_STATEMENT:
            return "NODE_FUNC_ASSIGN_STATEMENT";
        case NODE_FOR_STATEMENT:
            return "NODE_FOR_STATEMENT";
        case NODE_IDENTIFIER_LIST:
            return "NODE_IDENTIFIER_LIST";
        case NODE_IF_STATEMENT:
            return "NODE_IF_STATEMENT";
        case NODE_PROGRAM:
            return "NODE_PROGRAM";
        case NODE_PROGRAM_BODY:
            return "NODE_PROGRAM_BODY";
        case NODE_PROGRAM_HEAD:
            return "NODE_PROGRAM_HEAD";
        case NODE_PROCEDURE_CALL:
            return "NODE_PROCEDURE_CALL";
        case NODE_READLN_STATEMENT:
            return "NODE_READLN_STATEMENT";
        case NODE_READ_STATEMENT:
            return "NODE_READ_STATEMENT";
        case NODE_RECORD_TYPE:
            return "NODE_RECORD_TYPE";
        case NODE_SWITCH_CASE_ITEM:
            return "NODE_SWITCH_CASE_ITEM";
        case NODE_SWITCH_CASE_LIST:
            return "NODE_SWITCH_CASE_LIST";
        case NODE_SWITCH_STATEMENT:
            return "NODE_SWITCH_STATEMENT";
        case NODE_SUBPROGRAM:
            return "NODE_SUBPROGRAM";
        case NODE_SUBPROGRAM_BODY:
            return "NODE_SUBPROGRAM_BODY";
        case NODE_SUBPROGRAM_DECLARATIONS:
            return "NODE_SUBPROGRAM_DECLARATIONS";
        case NODE_SUBPROGRAM_HEAD:
            return "NODE_SUBPROGRAM_HEAD";
        case NODE_STATEMENT_LIST:
            return "NODE_STATEMENT_LIST";
        case NODE_STR_EXPRESSION:
            return "NODE_STR_EXPRESSION";
        case NODE_UNARY_OP:
            return "NODE_UNARY_OP";
        case NODE_VAR_DECLARATION:
            return "NODE_VAR_DECLARATION";
        case NODE_VAR_DECLARATION_LIST:
            return "NODE_VAR_DECLARATION_LIST";
        case NODE_WHILE_STATEMENT:
            return "NODE_WHILE_STATEMENT";
        case NODE_WRITE_STATEMENT:
            return "NODE_WRITE_STATEMENT";
        case NODE_WRITELN_STATEMENT:
            return "NODE_WRITELN_STATEMENT";
        case NODE_PERIOD:
            return "NODE_PERIOD";
        case NODE_PERIOD_LIST:
            return "NODE_PERIOD_LIST";
        case NODE_PARAMETER:
            return "NODE_PARAMETER";
        case NODE_PARAMETER_LIST:
            return "NODE_PARAMETER_LIST";
        case NODE_ID_VAR_PART:
            return "NODE_ID_VAR_PART";
        case NODE_ID_VAR_PART_LIST:
            return "NODE_ID_VAR_PART_LIST";
        case NODE_VARIABLE:
            return "NODE_VARIABLE";
        case NODE_VARIABLE_LIST:
            return "NODE_VARIABLE_LIST";
        case NODE_STD_TYPE:
            return "NODE_STD_TYPE";
        case NODE_TYPE_DECLARATION:
            return "NODE_TYPE_DECLARATION";
        case NODE_TYPE_DECLARATION_LIST:
            return "NODE_TYPE_DECLARATION_LIST";
        default:
            return "UNKNOWN_NODE_TYPE";
    }
}

// 递归函数，用于打印每个节点的类型
void printNodeType(ASTNode* node, int indent = 0) {
    if (!node)
        return;

    // 打印当前节点的类型
    cout << string(indent, ' ') << "Node Type: " << nodeTypeToString(node->node_type) << endl;

    // 根据节点类型递归打印子节点
    switch (node->node_type) {
        case NODE_STD_TYPE:
            break;
        case NODE_ARRAY_TYPE:
            printNodeType(static_cast<ArrayTypeNode*>(node)->period_list, indent + 2);
            break;
        case NODE_ASSIGN_STATEMENT:
            printNodeType(static_cast<AssignStatementNode*>(node)->variable, indent + 2);
            printNodeType(static_cast<AssignStatementNode*>(node)->expr, indent + 2);
            break;
        case NODE_BINARY_OP:
            printNodeType(static_cast<BinaryOpNode*>(node)->left, indent + 2);
            printNodeType(static_cast<BinaryOpNode*>(node)->right, indent + 2);
            break;
        case NODE_CONST_DECLARATION:
            printNodeType(static_cast<ConstDeclarationNode*>(node)->value, indent + 2);
            break;
        case NODE_CONST_DECLARATION_LIST:
            for (auto child : static_cast<ConstDeclarationListNode*>(node)->const_list) {
                printNodeType(child, indent + 2);
            }
            break;
        case NODE_EXPRESSION_LIST:
            for (auto child : static_cast<ExpressionListNode*>(node)->expr_list) {
                printNodeType(child, indent + 2);
                // cout<<child->node_type<<endl;
            }
            break;
        case NODE_FIELD:
            printNodeType(static_cast<FieldNode*>(node)->id_list, indent + 2);
            printNodeType(static_cast<FieldNode*>(node)->type, indent + 2);
            break;
        case NODE_FIELD_LIST:
            for (auto child : static_cast<FieldListNode*>(node)->field_list) {
                printNodeType(child, indent + 2);
            }
            break;
        case NODE_FOR_STATEMENT:
            printNodeType(static_cast<ForStatementNode*>(node)->first_expr, indent + 2);
            printNodeType(static_cast<ForStatementNode*>(node)->second_expr, indent + 2);
            printNodeType(static_cast<ForStatementNode*>(node)->statement, indent + 2);
            break;
        case NODE_IF_STATEMENT:
            printNodeType(static_cast<IfStatementNode*>(node)->condition, indent + 2);
            printNodeType(static_cast<IfStatementNode*>(node)->then_statement, indent + 2);
            printNodeType(static_cast<IfStatementNode*>(node)->else_statement, indent + 2);
            break;
        case NODE_PROGRAM:
            printNodeType(static_cast<ProgramNode*>(node)->head, indent + 2);
            // printf("%d\n",&static_cast<ProgramNode*>(node)->body);
            printNodeType(static_cast<ProgramNode*>(node)->body, indent + 2);
            break;
        case NODE_PROGRAM_BODY:
            printNodeType(static_cast<ProgramBodyNode*>(node)->const_decls, indent + 2);
            printNodeType(static_cast<ProgramBodyNode*>(node)->type_decls, indent + 2);
            printNodeType(static_cast<ProgramBodyNode*>(node)->var_decls, indent + 2);
            printNodeType(static_cast<ProgramBodyNode*>(node)->subprogram_decls, indent + 2);
            printNodeType(static_cast<ProgramBodyNode*>(node)->body, indent + 2);
            break;
        case NODE_STATEMENT_LIST:
            for (auto child : static_cast<StatementListNode*>(node)->statement_list) {
                printNodeType(child, indent + 2);
            }
            break;
        case NODE_WRITE_STATEMENT:
            printNodeType(static_cast<WriteStatementNode*>(node)->expr_list, indent + 2);
            break;
        case NODE_SUBPROGRAM:
            printNodeType(static_cast<SubprogramNode*>(node)->head, indent + 2);
            printNodeType(static_cast<SubprogramNode*>(node)->body, indent + 2);
            break;
        case NODE_SUBPROGRAM_HEAD:
            printNodeType(static_cast<SubprogramHeadNode*>(node)->param_list, indent + 2);
            break;
        case NODE_SUBPROGRAM_BODY:
            printNodeType(static_cast<SubprogramBodyNode*>(node)->const_declarations, indent + 2);
            printNodeType(static_cast<SubprogramBodyNode*>(node)->type_declarations, indent + 2);
            printNodeType(static_cast<SubprogramBodyNode*>(node)->var_declarations, indent + 2);
            printNodeType(static_cast<SubprogramBodyNode*>(node)->statement, indent + 2);
            break;
        case NODE_SUBPROGRAM_DECLARATIONS:
            for (auto child : static_cast<SubprogramDeclarationsNode*>(node)->subprogram_list) {
                printNodeType(child, indent + 2);
            }
            break;
        case NODE_TYPE_DECLARATION:
            printNodeType(static_cast<TypeDeclarationNode*>(node)->type, indent + 2);
            break;
        case NODE_TYPE_DECLARATION_LIST:
            for (auto child : static_cast<TypeDeclarationListNode*>(node)->type_decl_list) {
                printNodeType(child, indent + 2);
            }
            break;
        case NODE_VAR_DECLARATION:
            printNodeType(static_cast<VarDeclarationNode*>(node)->id_list, indent + 2);
            printNodeType(static_cast<VarDeclarationNode*>(node)->type, indent + 2);
            break;
        case NODE_VAR_DECLARATION_LIST:
            for (auto child : static_cast<VarDeclarationListNode*>(node)->var_list) {
                printNodeType(child, indent + 2);
            }
            break;
        case NODE_PERIOD_LIST:
            for (auto child : static_cast<PeriodListNode*>(node)->period_list) {
                printNodeType(child, indent + 2);
            }
            break;
        case NODE_PARAMETER_LIST:
            for (auto child : static_cast<ParameterListNode*>(node)->param_list) {
                printNodeType(child, indent + 2);
            }
            break;
        case NODE_VARIABLE_LIST:
            for (auto child : static_cast<VariableListNode*>(node)->variables) {
                printNodeType(child, indent + 2);
            }
            break;
        case NODE_ID_VAR_PART_LIST:
            for (auto child : static_cast<IdVarPartListNode*>(node)->id_var_part_list) {
                printNodeType(child, indent + 2);
            }
            break;
        case NODE_ID_VAR_PART:
            printNodeType(static_cast<IdVarPartNode*>(node)->expr_list, indent + 2);
            // cout<<static_cast<IdVarPartNode*>(node)->expr_list->node_type<<endl;
            break;
        case NODE_VARIABLE:
            printNodeType(static_cast<VariableNode*>(node)->extend_part, indent + 2);
        default:
            // 其他节点类型不需要递归处理
            break;
    }
}

std::string getFileNameWithoutExtension(const std::string& filePath) {
    // 找到最后一个 '/' 的位置（用于处理完整路径）
    size_t lastSlashIndex = filePath.find_last_of("/\\");
    std::string fileName;

    // 如果路径中包含 '/' 或 '\'
    if (lastSlashIndex != std::string::npos) {
        fileName = filePath.substr(lastSlashIndex + 1);  // 提取文件名
    } else {
        fileName = filePath;  // 如果没有路径分隔符，直接使用整个字符串
    }

    // 找到最后一个 '.' 的位置（用于分割扩展名）
    size_t lastDotIndex = fileName.find_last_of('.');
    if (lastDotIndex != std::string::npos) {
        return fileName.substr(0, lastDotIndex);  // 返回文件名主体部分
    }

    return fileName;  // 如果没有扩展名，直接返回文件名
}

void dir_make(string& dir) {
#ifdef WIN32
    std::replace(dir.begin(), dir.end(), '/', '\\');
#else
    std::replace(dir.begin(), dir.end(), '\\', '/');
#endif
}

void file_make(string& file) {
    size_t len = file.length();
    if (file.length() > 2) {
        if (file[len - 1] == 'c' && file[len - 2] == '.') {
            file = file.substr(0, len - 2);
        }
    }
}

int main(int argc, char** argv) {
    // 判断是否指定了输入文件
    argparse::ArgumentParser program("PASCAL Compiler");

    program.add_argument("-i", "--input")
        .help("input file")
        .default_value<std::string>("00_main.pas");

    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        return 1;
    }

    ASTNode* root;
    globalSymbolTable = new SymbolTable;
    currentSymbolTable = globalSymbolTable;

    auto file_name = program.get<std::string>("-i");

    // 打开输入文件
    fstream log("input.log");
    dir_make(file_name);
    log << file_name << endl;
    // return 0;

    // auto openSetPath = "../openSet/"+file_name;

    FILE* inputFile = fopen(file_name.c_str(), "r");
    if (!inputFile) {
        std::cerr << "Error: Cannot open file " << file_name << "\n";
        return 1;
    }

    yyin = inputFile;
    // 启动语法分析
    if (yyparse(&root) == 0) {
        // std::cout << "Parsing completed successfully.\n";
    } else {
        // std::cerr << "Parsing failed due to errors.\n";
    }

    fclose(inputFile);
    printNodeType(root, 1);
    // return 0;

    globalSymbolTable->print();
    auto gen = new CodeGenerator(
        0, 1, globalSymbolTable, currentSymbolTable);

    std::stringstream ss;
    string result = gen->generate(root);
    ss << fixFunctionPlacement(result);
    ofstream outputFile(getFileNameWithoutExtension(file_name) + ".c");
    outputFile << ss.str();
    outputFile.close();
    log.close();

    return 0;
}
