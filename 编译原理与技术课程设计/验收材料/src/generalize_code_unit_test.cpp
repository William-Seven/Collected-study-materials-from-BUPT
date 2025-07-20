#include <iostream>
#include "ast.h"
#include "generalize_code.cpp"
#include <cassert>
using namespace std;

void test_2d_array_declaration() {
    // 构建 array [1..2, 3..4] of integer 类型
    PeriodNode* p1 = new PeriodNode(1, 2);
    PeriodNode* p2 = new PeriodNode(3, 4);
    PeriodListNode* periods = new PeriodListNode({p1, p2});
    ArrayTypeNode* arrayType = new ArrayTypeNode(periods, INTEGER);
  
    // 创建变量声明
    IdentifierListNode* ids = new IdentifierListNode({"matrix"});
    VarDeclarationNode* varDecl = new VarDeclarationNode(ids, arrayType);
  
    auto* smytab = new SymbolTable();
    auto gen = new CodeGenerator(
        0,
        1,
        smytab
    );
    string code = gen->generate(varDecl);
   
    cout << "[Test 2D Array] Generated code:\n" << code << endl;
   
    // 预期结果: int matrix[2][2];
    assert(code.find("int matrix[2][2];") != string::npos);
    cout << "2D Array Test Passed!\n\n";
   
    // 清理
    delete varDecl;
}

void test_3d_array_variable() {
    // 构建 array [1..3, 4..6, 7..9] of real
    PeriodListNode* periods = new PeriodListNode({
        new PeriodNode(1, 3),
        new PeriodNode(4, 6),
        new PeriodNode(7, 9)
    });
    ArrayTypeNode* arrayType = new ArrayTypeNode(periods, REAL);
   
    // 创建变量声明
    IdentifierListNode* ids = new IdentifierListNode({"tensor"});
    VarDeclarationNode* varDecl = new VarDeclarationNode(ids, arrayType);
   
    auto* smytab = new SymbolTable();
    auto gen = new CodeGenerator(
        0,
        1,
        smytab
    );
    string code = gen->generate(varDecl);
   
    cout << "[Test 3D Array] Generated code:\n" << code << endl;
   
    // 预期结果: double tensor[3][3][3];
    assert(code.find("double tensor[3][3][3];") != string::npos);
    cout << "3D Array Test Passed!\n\n";
   
    // 清理
    delete varDecl;
}

void test_record_with_array() {
    // 构建记录类型：
    // record
    //   name: array[1..10] of char;
    //   matrix: array[1..2, 1..2] of integer;
    // end
   
    // 创建name字段
    PeriodNode* p1 = new PeriodNode(1, 10);
    ArrayTypeNode* charArray = new ArrayTypeNode(p1, CHAR_);
    IdentifierListNode* nameIds = new IdentifierListNode({"name"});
    FieldNode* nameField = new FieldNode(nameIds, charArray);
   
    // 创建matrix字段
    PeriodListNode* matrixDims = new PeriodListNode({
        new PeriodNode(1, 2),
        new PeriodNode(1, 2)
    });
    ArrayTypeNode* intArray = new ArrayTypeNode(matrixDims, INTEGER);
    IdentifierListNode* matrixIds = new IdentifierListNode({"matrix"});
    FieldNode* matrixField = new FieldNode(matrixIds, intArray);
   
    // 创建记录类型
    FieldListNode* fields = new FieldListNode({nameField, matrixField});
    RecordTypeNode* recordType = new RecordTypeNode(fields);
   
    // 创建类型声明
    TypeDeclarationNode* typeDecl = new TypeDeclarationNode("Student", recordType);
  
    auto* smytab = new SymbolTable();
    auto gen = new CodeGenerator(
        0,
        1,
        smytab
    );
    string code = gen->generate(typeDecl);
  
    cout << "[Test Record with Arrays] Generated code:\n" << code << endl;
  
    // 预期结果包含：
    // struct {
    //   char name[10];
    //   int matrix[2][2];
    // };
    assert(code.find("char name[10];") != string::npos);
    assert(code.find("int matrix[2][2];") != string::npos);
    cout << "Record with Arrays Test Passed!\n\n";
  
    // 清理
    delete typeDecl;
}

void test_function() {
    auto* param1 = new ParameterNode(
        new IdentifierListNode({"x"}),
        INTEGER
    );
    auto* param2 = new ParameterNode(
        new IdentifierListNode({"y"}),
        INTEGER
    );
    string str = "calculate";
    auto param_list = new ParameterListNode({param1,param2});
    auto* head = new SubprogramHeadNode(str,param_list,true,INTEGER);
    auto* body = new SubprogramBodyNode(nullptr,nullptr,nullptr,nullptr);
    auto* prog = new SubprogramNode(head,body);
    auto* smytab = new SymbolTable();
    auto gen = new CodeGenerator(
        0,
        1,
        smytab
    );
    string result = gen->generate(prog);
    cout<<"string:\n"<<result<<endl;
}

void test_expression() {
    auto* left = new FactorNode(10);
    auto* right = new FactorNode(20);
    auto* expr = new BinaryOpNode(">",left,right);
    auto* smytab = new SymbolTable();
    auto gen = new CodeGenerator(
        0,
        1,
        smytab
    );
    string str=gen->generate(expr);
    //cout<<"string"<<str<<endl;

    auto* args = new ExpressionListNode(
        {
            new FactorNode(1),
            new BinaryOpNode("+",new FactorNode(2),new FactorNode(3))
        }
    );
    cout<<"args:\n"<<gen->generate(args)<<endl;
}

void test_if_else(){
    auto* condition = new BinaryOpNode(
        ">",
        new VariableNode("x",nullptr),
        new FactorNode(0)
    );
    auto* ifBody = new ProcedureCallNode(
        "printf",
        new ExpressionListNode({new StrExpressionNode("Pass")})
    );
    auto* elseBody = new ElsePartNode(new ProcedureCallNode(
        "printf",
        new ExpressionListNode({new StrExpressionNode("fail")})
    ));
    auto* if_else_statement = new IfStatementNode(condition,ifBody,elseBody);
    auto* smytab = new SymbolTable();
    auto gen = new CodeGenerator(
        0,
        1,
        smytab
    );
    //cout<<"if_else_statement\n"<<gen.generate(if_else_statement);


   
    auto* outerCond = new BinaryOpNode(
        ">=",
        new VariableNode("a",nullptr),
        new StdTypeNode(INTEGER,15)
    );
    auto* innerCond = new BinaryOpNode(
        "<>",
        new VariableNode("ass",nullptr),
        new StdTypeNode(REAL,1.0)
    );
    auto* innerIf = new IfStatementNode(
        innerCond,
        new AssignStatementNode(new VariableNode("result",nullptr),new StdTypeNode(CHAR_,'i')),
        nullptr
    );
    auto* outerIf = new IfStatementNode(
        outerCond,
        innerIf,
        nullptr
    );
    cout<<"string\n"<<gen->generate(outerIf)<<endl;
}

void test_switch(){
    auto* expr = new VariableNode("day",nullptr);
    auto* cases = new SwitchCaseListNode({
        new SwitchCaseItemNode(
            new StdTypeNode(INTEGER,15),
            new ProcedureCallNode("printf",new ExpressionListNode({new StrExpressionNode("Monday")}))
        ),
        new SwitchCaseItemNode(
            new StdTypeNode(INTEGER,20),
            new ProcedureCallNode("printf",new ExpressionListNode({new StrExpressionNode("Tuesday")}))
        )
    });
    auto* switchnode = new SwitchStatementNode(expr,cases);

    auto* smytab = new SymbolTable();
    auto gen = new CodeGenerator(
        0,
        1,
        smytab
    );
    cout<<"switch_statement\n"<<gen->generate(switchnode);
}
   
void test_for(){
    auto* for_statement = new ForStatementNode(
        "i",
        new StdTypeNode(INTEGER,1),
        new StdTypeNode(INTEGER,10),
        new ProcedureCallNode("printf",new ExpressionListNode({new StrExpressionNode("jjjjj")})),
        false
    );
    auto* smytab = new SymbolTable();
    auto gen = new CodeGenerator(
        0,
        1,
        smytab
    );
    cout<<"for_statement\n"<<gen->generate(for_statement);
}

void test_read_statement(){
    auto* smytab = new SymbolTable();
    auto gen = new CodeGenerator(
        0,
        1,
        smytab
    );
    auto* ST = new SymbolType(CHAR_);
    smytab->addSymbol(
        new VarSymbol(
            "k",
            ST
        )
    );
    smytab->addSymbol(
        new VarSymbol(
            "i",
            new SymbolType(INTEGER)
        )
    );
    //cout<<"符号表OK"<<endl;
    auto* read_node = new ReadlnStatementNode(
        new VariableListNode({
            new VariableNode(
                "i",
                nullptr
            ),
            new VariableNode(
                "k",
                nullptr
            )
        })
    );
    cout<<"read_statement\n"<<gen->generate(read_node);
}

void test_write_statement(){
    auto* smytab = new SymbolTable();
    auto gen = new CodeGenerator(
        0,
        1,
        smytab
    );
    auto* ST = new SymbolType(CHAR_);
    smytab->addSymbol(
        new VarSymbol(
            "k",
            ST
        )
    );
    smytab->addSymbol(
        new VarSymbol(
            "i",
            new SymbolType(INTEGER)
        )
    );
    //cout<<"符号表OK"<<endl;
    auto* write_node = new WritelnStatementNode(
        new VariableListNode({
            new VariableNode(
                "i",
                nullptr
            ),
            new VariableNode(
                "k",
                nullptr
            )
        })
    );
    cout<<"\nwrite_statement\n"<<gen->generate(write_node);
}

void test_while(){
    auto* result=  new WhileStatementNode(
        new BinaryOpNode(
            ">",
            new VariableNode("count",nullptr),
            new StdTypeNode(INTEGER,0)
        ),
        new StatementListNode({
            new ProcedureCallNode("printf",new ExpressionListNode({new StrExpressionNode("55555")}))          
        })
    );
    auto* smytab = new SymbolTable();
    auto gen = new CodeGenerator(
        0,
        1,
        smytab
    );
    cout<<"result_string\n"<<gen->generate(result);
}



int main() {
    // test_2d_array_declaration();
    // test_3d_array_variable();
    // test_record_with_array();
    //test_function();
    //test_expression();
    //test_if_else();
    //test_switch();
    //test_for();
    //test_for();
    //test_while();
    //test_write_statement();
    test_read_statement();
    cout << "\nAll multidimensional array tests passed!" << endl;
    return 0;
}

