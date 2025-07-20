%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unordered_map>

/* 抽象语法树头文件 */
#include "ast.h"
//#include "ast_class.h"

#include "symbol_table.h"
extern SymbolTable* globalSymbolTable;
extern SymbolTable* currentSymbolTable;

SymbolType* dealType(ASTNode* node);
unordered_map<string, ASTNode*> FieldNameToType;

// void yyerror(const char *s);
// extern int yylex();
// extern FILE *yyin;
extern "C"			
{					
    void yyerror(const char *s);
    extern int yylex(void);
    extern int line_count;
    extern bool new_line_flag;
    extern int yyleng;
    extern int last_line_count;
}
using std::string;

extern void printNodeType(ASTNode* node, int indent = 0);

void yyerror(ASTNode** root, const char *msg);
void yyerror_var(ASTNode** root, const char *msg);
void yynote(std::string msg, int line);

#define GET_INT_VAL(ptr) (ptr)->value.int_value
#define GET_REAL_VAL(ptr) (ptr)->value.real_value
#define GET_CHAR_VAL(ptr) (ptr)->value.char_value
#define GET_BOOL_VAL(ptr) (ptr)->value.bool_value
#define GET_STR_VAL(ptr) (ptr)->string_value
#define GET_TYPE(ptr) (ptr)->type
%}

/* 定义词法单元 */
%union {
    class TokenInfo* token_info;
    class ASTNode* ast;
}
%parse-param {ASTNode** rootPtr}//设置yyparse函数的参数
%start programstruct//设置语法起始节点为程序节点

%token <token_info> INT_NUM REAL_NUM CHAR BOO_LEAN STRING BASIC_TYPE IDENTIFIER

/* 关键字 */
%token<token_info> ARRAY BEGIN_ BREAK CASE CONST CONTINUE DO DOWNTO ELSE END
%token<token_info> FOR FUNCTION IF NOT OF
%token<token_info> PROCEDURE PROGRAM RECORD THEN TO
%token<token_info> VAR WHILE READ READLN WRITE WRITELN DOT TYPE

/* 标准库函数 */
%token<token_info> STD_FUNC 

/* 运算符 */
%token<token_info> ASSIGN EQUAL PLUS MINUS ADDING_OP MULTI_OP REL_OP
%token<token_info> COMMA COLON SEMICOLON RANGE LPAREN RPAREN LBRACKET RBRACKET

%type<ast> switch_statement switch_case_list switch_case_item while_statement
%type<ast> programstruct program_head program_body identifier_list unsigned_const
%type<ast> const_declarations const_declaration const_value array_type record_type record_declarations
%type<ast> var_declarations var_declaration type period field_list type_declarations type_declaration
%type<ast> subprogram_declarations subprogram subprogram_head id_varpart_n
%type<ast> formal_parameter parameter_list parameter var_parameter value_parameter
%type<ast> subprogram_body compound_statement statement_list statement
%type<ast> variable_list variable id_varpart procedure_call else_part
%type<ast> expression_list expression str_expression simple_expression term factor
%type<ast> empty_statement if_statement for_statement read_statement write_statement
%type<ast> assign_statement func_assign_statement

%left ADDING_OP MULTI_OP PLUS MINUS NOT
%right EQUAL ASSIGN
%%

programstruct : program_head SEMICOLON program_body DOT
                {   
                  cout << "Program" << endl;
                  *rootPtr = new ProgramNode($1, $3);
                  // printNodeType(*rootPtr, 0);
                  safeDelete($2, $4);
                }

program_head : PROGRAM IDENTIFIER LPAREN identifier_list RPAREN 
                {
                  cout << "Program Head with parameters: " << GET_STR_VAL($2) << endl;
                  $$ = new ProgramHeadNode(GET_STR_VAL($2), $4);
                  
                  ProcSymbol* programSymbol = new ProcSymbol(GET_STR_VAL($2), $$);
                  vector<string> idList = dynamic_cast<IdentifierListNode*>($4)->identifier_list;
                  for (const auto& s : idList) {
                    SymbolType* idType = new SymbolType(NULL_TYPE);
                    VarSymbol* id = new VarSymbol(s, idType);
                    programSymbol->addParameter(id);
                  }
                  globalSymbolTable->addSymbol(programSymbol);
                  currentSymbolTable = globalSymbolTable->getChildTable(GET_STR_VAL($2));
                  
                  safeDelete($1, $2, $3, $5);
                }
                | PROGRAM IDENTIFIER
                {
                  cout << "Program Head: " << GET_STR_VAL($2) << endl;
                  $$ = new ProgramHeadNode(GET_STR_VAL($2), nullptr);
                  
                  Symbol* programSymbol = new ProcSymbol(GET_STR_VAL($2), $$);
                  globalSymbolTable->addSymbol(programSymbol);
                  currentSymbolTable = globalSymbolTable->getChildTable(GET_STR_VAL($2));

                  safeDelete($1, $2);
                }

program_body : const_declarations type_declarations var_declarations subprogram_declarations compound_statement
                {
                  cout << "Program Body" << endl;
                  $$ = new ProgramBodyNode($1, $2, $3, $4, $5);

                  currentSymbolTable = currentSymbolTable->getParent();
                }

identifier_list : IDENTIFIER 
                {
                  cout << "Identifier: " << GET_STR_VAL($1) << endl;
                  $$ = new IdentifierListNode(vector<string>{GET_STR_VAL($1)});
                  safeDelete($1);
                }
                | identifier_list COMMA IDENTIFIER
                {
                  cout << "Adding Identifier: " << GET_STR_VAL($3) << endl;
                  dynamic_cast<IdentifierListNode*>($1)->identifier_list.push_back(GET_STR_VAL($3));
                  $$ = $1;
                  safeDelete($2, $3);
                }

const_declarations :  { $$ = nullptr; }
                    | CONST const_declaration SEMICOLON
                    {
                      cout << "Const Declarations" << endl;
                      $$ = $2;
                      safeDelete($1, $3);
                    }

const_declaration : IDENTIFIER EQUAL const_value 
                    {
                      if (currentSymbolTable->lookupEntry(GET_STR_VAL($1))) {
                          std::cerr <<"LINE["<< $1->line_no << "]ERROR"<<": The constant declaration is duplicated. '" << GET_STR_VAL($1) << "'\n";                      
                      }
                      else{
                        cout << "Const Declaration: " << GET_STR_VAL($1) << endl;
                        ASTNode* const_declaration_node = new ConstDeclarationNode(GET_STR_VAL($1), $3);
                        $$ = new ConstDeclarationListNode(vector<ASTNode*>{const_declaration_node});
                        
                        StdTypeNode* std_node = dynamic_cast<StdTypeNode*>($3);
                        BasicType bt = std_node->getBasicType();
                        switch (bt) {
                            case INTEGER:
                                currentSymbolTable->addSymbol(new ConstSymbol(GET_STR_VAL($1), INTEGER, std_node->getValue<int>()));
                                break;
                            case REAL:
                                currentSymbolTable->addSymbol(new ConstSymbol(GET_STR_VAL($1), REAL, std_node->getValue<float>()));
                                break;
                            case CHAR_:
                                currentSymbolTable->addSymbol(new ConstSymbol(GET_STR_VAL($1), CHAR_, std_node->getValue<char>()));
                                break;
                            case BOOLEAN_:
                                currentSymbolTable->addSymbol(new ConstSymbol(GET_STR_VAL($1), BOOLEAN_, std_node->getValue<bool>()));
                                break;
                            case STRING_:
                                currentSymbolTable->addSymbol(new ConstSymbol(GET_STR_VAL($1), STRING_, std_node->getValue<string>()));
                                break;
                            default:
                                throw invalid_argument("Invalid type for getVal");
                        }

                        safeDelete($1, $2);
                      }
                    }
                    | const_declaration SEMICOLON IDENTIFIER EQUAL const_value
                    {
                      if (currentSymbolTable->lookupEntry(GET_STR_VAL($3))) {
                          std::cerr <<"LINE["<< $3->line_no << "]ERROR" << ": The constant declaration is duplicated. '" << GET_STR_VAL($3) << "'\n";
                      }
                      else{
                        cout << "Adding Const Declaration: " << GET_STR_VAL($3) << endl;
                        ASTNode* const_declaration_node = new ConstDeclarationNode(GET_STR_VAL($3), $5);
                        dynamic_cast<ConstDeclarationListNode*>($1)->const_list.push_back(const_declaration_node);
                        $$ = $1;
                        
                        StdTypeNode* std_node = dynamic_cast<StdTypeNode*>($5);
                        cout<<"get_type"<<endl;
                        BasicType bt = std_node->getBasicType();
                        cout<<"after_get_type"<<endl;
                        switch (bt) {
                            case INTEGER:
                                currentSymbolTable->addSymbol(new ConstSymbol(GET_STR_VAL($3), INTEGER, std_node->getValue<int>()));
                                break;
                            case REAL:
                                currentSymbolTable->addSymbol(new ConstSymbol(GET_STR_VAL($3), REAL, std_node->getValue<float>()));
                                break;
                            case CHAR_:
                                currentSymbolTable->addSymbol(new ConstSymbol(GET_STR_VAL($3), CHAR_, std_node->getValue<char>()));
                                break;
                            case BOOLEAN_:
                                currentSymbolTable->addSymbol(new ConstSymbol(GET_STR_VAL($3), BOOLEAN_, std_node->getValue<bool>()));
                                break;
                            case STRING_:
                                currentSymbolTable->addSymbol(new ConstSymbol(GET_STR_VAL($3), STRING_, std_node->getValue<string>()));
                                break;
                            default:
                                throw invalid_argument("Invalid type for getVal");
                        }
                        
                        cout<<"1"<<endl;

                        safeDelete($2, $3, $4);
                      }
                    }

const_value : PLUS unsigned_const
            {
              cout << "Signed Constant" << endl;
              $$ = new UnaryOpNode(GET_STR_VAL($1), $2);
              safeDelete($1);
            }
            | MINUS unsigned_const
            {
              cout << "Signed Constant" << endl;
              $$ = new UnaryOpNode(GET_STR_VAL($1), $2);
              safeDelete($1);
            }
            | unsigned_const 
            { 
              cout<<"Unsigned Constant" << endl;
              $$ = $1; }
            | CHAR 
            {
              cout << "Char Constant: " << GET_CHAR_VAL($1) << endl;
              $$ = new StdTypeNode(CHAR_, GET_CHAR_VAL($1));
              safeDelete($1);
            }
            | BOO_LEAN
            {
              cout << "Boolean Constant: " << GET_BOOL_VAL($1) << endl;
              $$ = new StdTypeNode(BOOLEAN_, GET_BOOL_VAL($1));
              safeDelete($1);
            }
            | STRING
            {
              cout << "String Constant: " << GET_STR_VAL($1) << endl;
              $$ = new StdTypeNode(STRING_, GET_STR_VAL($1));
              safeDelete($1);
            }

unsigned_const : INT_NUM
                {
                  cout << "Unsigned Integer: " << GET_INT_VAL($1) << endl;
                  $$ = new StdTypeNode(INTEGER, GET_INT_VAL($1));
                  safeDelete($1);
                }
                | REAL_NUM
                {
                  cout << "Unsigned Real: " << GET_REAL_VAL($1) << endl;
                  $$ = new StdTypeNode(REAL, GET_REAL_VAL($1));
                  safeDelete($1);
                }

type_declarations : 
                  { $$ = nullptr; }
                  | TYPE type_declaration COLON
                  {
                    cout << "Type Declarations" << endl;
                    safeDelete($1, $3);
                    $$ = $2;
                  }
                  | TYPE record_declarations {
                    $$ = $2;
                  }

type_declaration : IDENTIFIER EQUAL type
                  {
                    cout << "Type Declaration: " << GET_STR_VAL($1) << endl;
                    ASTNode* type_dec_list_node = new TypeDeclarationListNode(vector<ASTNode*>{new TypeDeclarationNode(GET_STR_VAL($1), $3)});
                    $$ = type_dec_list_node;

                    if (($3)->node_type == NODE_BASIC_TYPE) {
                      SymbolType* type = new SymbolType(dynamic_cast<BasicTypeNode*>($3)->type);
                      VarSymbol* var = new VarSymbol(GET_STR_VAL($1), type);
                      currentSymbolTable->addSymbol(var);
                    } else if (($3)->node_type == NODE_ARRAY_TYPE) {
                      ArrayTypeNode* arrTypeNode = dynamic_cast<ArrayTypeNode*>($3);
                      SymbolType* elementType = new SymbolType(arrTypeNode->type);
                      vector<ASTNode*> pariodList = dynamic_cast<PeriodListNode*>(arrTypeNode->period_list)->period_list;
                      ArrayType* arrType = new ArrayType(elementType);
                      for (const auto& it : pariodList) {
                        PeriodNode* pariod = dynamic_cast<PeriodNode*>(it);
                        arrType->addDimension(pariod->start, pariod->end);
                      }
                      SymbolType* type = new SymbolType(arrType);
                      VarSymbol* var = new VarSymbol(GET_STR_VAL($1), type);
                      currentSymbolTable->addSymbol(var);
                    } else if (($3)->node_type == NODE_RECORD_TYPE) {
                      SymbolType* type = dealType($3);
                      VarSymbol* var = new VarSymbol(GET_STR_VAL($1), type);
                      currentSymbolTable->addSymbol(var);
                    }

                    safeDelete($1, $2);
                  }
                  | type_declaration SEMICOLON IDENTIFIER EQUAL type
                  {
                    cout << "Adding Type Declaration: " << GET_STR_VAL($3) << endl;
                    dynamic_cast<TypeDeclarationListNode*>($1)->type_decl_list.push_back(new TypeDeclarationNode(GET_STR_VAL($3), $5));
                    $$ = $1;

                    if (($5)->node_type == NODE_BASIC_TYPE) {
                      SymbolType* type = new SymbolType(dynamic_cast<BasicTypeNode*>($5)->type);
                      VarSymbol* var = new VarSymbol(GET_STR_VAL($3), type);
                      currentSymbolTable->addSymbol(var);
                    } else if (($5)->node_type == NODE_ARRAY_TYPE) {
                      ArrayTypeNode* arrTypeNode = dynamic_cast<ArrayTypeNode*>($5);
                      SymbolType* elementType = new SymbolType(arrTypeNode->type);
                      vector<ASTNode*> pariodList = dynamic_cast<PeriodListNode*>(arrTypeNode->period_list)->period_list;
                      ArrayType* arrType = new ArrayType(elementType);
                      for (const auto& it : pariodList) {
                        PeriodNode* pariod = dynamic_cast<PeriodNode*>(it);
                        arrType->addDimension(pariod->start, pariod->end);
                      }
                      SymbolType* type = new SymbolType(arrType);
                      VarSymbol* var = new VarSymbol(GET_STR_VAL($3), type);
                      currentSymbolTable->addSymbol(var);
                    } else if (($5)->node_type == NODE_RECORD_TYPE) {
                      SymbolType* type = dealType($5);
                      VarSymbol* var = new VarSymbol(GET_STR_VAL($3), type);
                      currentSymbolTable->addSymbol(var);
                    }

                    safeDelete($2, $3, $4);
                  }

var_declarations :  { $$ = nullptr; }
                    | VAR var_declaration SEMICOLON
                    {
                      cout << "Var Declarations" << endl;
                      $$ = $2;
                      safeDelete($1, $3);
                    }

var_declaration : identifier_list COLON type
                {
                  cout << "Var Declaration" << endl;
                  ASTNode* var_declaration_node = new VarDeclarationNode($1, $3);
                  $$ = new VarDeclarationListNode(vector<ASTNode*>{var_declaration_node});

                  vector<string> idList = dynamic_cast<IdentifierListNode*>($1)->identifier_list;
                  for (auto s : idList) {
                    if (currentSymbolTable->lookupEntry(s)){
                        std::cerr << "LINE[" << $2->line_no << "]ERROR" << ": Duplicate vaiable declaration'" << s << "'\n";
                        continue;
                    }
                    if (($3)->node_type == NODE_BASIC_TYPE) {
                      SymbolType* type = new SymbolType(dynamic_cast<BasicTypeNode*>($3)->type);
                      VarSymbol* var = new VarSymbol(s, type);
                      currentSymbolTable->addSymbol(var);
                    } else if (($3)->node_type == NODE_ARRAY_TYPE) {
                      ArrayTypeNode* arrTypeNode = dynamic_cast<ArrayTypeNode*>($3);
                      SymbolType* elementType = new SymbolType(arrTypeNode->type);
                      vector<ASTNode*> pariodList = dynamic_cast<PeriodListNode*>(arrTypeNode->period_list)->period_list;
                      ArrayType* arrType = new ArrayType(elementType);
                      for (const auto& it : pariodList) {
                        PeriodNode* pariod = dynamic_cast<PeriodNode*>(it);
                        if(pariod->start > pariod->end){
                            std::cerr << "LINE[" << $2->line_no << "]ERROR" << ": Invalid Array Index'" << s << "'\n";
                            int swap_i = pariod->start;
                            pariod->start = pariod->end;
                            pariod->end = swap_i;
                        }
                        arrType->addDimension(pariod->start, pariod->end);
                      }
                      SymbolType* type = new SymbolType(arrType);
                      VarSymbol* var = new VarSymbol(s, type);
                      currentSymbolTable->addSymbol(var);
                    } else if (($3)->node_type == NODE_RECORD_TYPE) {
                      SymbolType* type = dealType($3);
                      VarSymbol* var = new VarSymbol(s, type);
                      currentSymbolTable->addSymbol(var);
                    }
                  }

                  safeDelete($2);
                }
                | var_declaration SEMICOLON identifier_list COLON type
                {
                  cout << "Adding Var Declaration" << endl;
                  ASTNode* var_declaration_node = new VarDeclarationNode($3, $5);
                  dynamic_cast<VarDeclarationListNode*>($1)->var_list.push_back(var_declaration_node);
                  $$ = $1;

                  vector<string> idList = dynamic_cast<IdentifierListNode*>($3)->identifier_list;
                  for (auto s : idList) {
                    if (currentSymbolTable->lookupEntry(s)){
                        std::cerr << "LINE[" << $4->line_no << "]ERROR" << ": Duplicate vaiable declaration '" << s << "'\n";
                        continue;
                    }
                    if (($5)->node_type == NODE_BASIC_TYPE) {
                      SymbolType* type = new SymbolType(dynamic_cast<BasicTypeNode*>($5)->type);
                      VarSymbol* var = new VarSymbol(s, type);
                      currentSymbolTable->addSymbol(var);
                    } else if (($5)->node_type == NODE_ARRAY_TYPE) {
                      ArrayTypeNode* arrTypeNode = dynamic_cast<ArrayTypeNode*>($5);
                      SymbolType* elementType = new SymbolType(arrTypeNode->type);
                      vector<ASTNode*> pariodList = dynamic_cast<PeriodListNode*>(arrTypeNode->period_list)->period_list;
                      ArrayType* arrType = new ArrayType(elementType);
                      for (const auto& it : pariodList) {
                        PeriodNode* pariod = dynamic_cast<PeriodNode*>(it);
                        if(pariod->start > pariod->end){
                            std::cerr << "LINE[" << $4->line_no << "]ERROR" << ": Invalid Array Index '" << s << "'\n";
                            int swap_i = pariod->start;
                            pariod->start = pariod->end;
                            pariod->end = swap_i;
                        }
                        arrType->addDimension(pariod->start, pariod->end);
                      }
                      SymbolType* type = new SymbolType(arrType);
                      VarSymbol* var = new VarSymbol(s, type);
                      currentSymbolTable->addSymbol(var);
                    } else if (($5)->node_type == NODE_RECORD_TYPE) {
                      SymbolType* type = dealType($5);
                      VarSymbol* var = new VarSymbol(s, type);
                      currentSymbolTable->addSymbol(var);
                    }
                  }

                  safeDelete($2, $4);
                }
                | identifier_list COLON IDENTIFIER
                {
                  // cout << "Var Declaration with type identifier: " << GET_STR_VAL($3) << endl;
                  std::cerr << "LINE[" << $3->line_no << "]ERROR" << ": The declared type does not exist '" << GET_STR_VAL($3) << "'\n";
                  ASTNode* var_declaration_node = new VarDeclarationNode($1, GET_STR_VAL($3));
                  $$ = new VarDeclarationListNode(vector<ASTNode*>{var_declaration_node});

                  safeDelete($2, $3);
                }
                |  var_declaration SEMICOLON identifier_list COLON IDENTIFIER
                {
                  // cout << "Adding Var Declaration with type identifier: " << GET_STR_VAL($5) << endl;
                  std::cerr << "LINE[" << $5->line_no << "]ERROR" << ": The declared type does not exist '" << GET_STR_VAL($5) << "'\n";
                  ASTNode* var_declaration_node = new VarDeclarationNode($3, GET_STR_VAL($5));
                  dynamic_cast<VarDeclarationListNode*>($1)->var_list.push_back(var_declaration_node);
                  $$ = $1;

                  safeDelete($2, $4, $5);
                }

type : BASIC_TYPE
    {
      cout << "Basic Type: " << GET_STR_VAL($1) << endl;
      $$ = new BasicTypeNode(GET_STR_VAL($1));
      // cout<<dynamic_cast<BasicTypeNode*>($$)->type<<endl;
      FieldNameToType[GET_STR_VAL($1)] = $$;
      safeDelete($1);
    }
    | array_type
    {
      $$ = $1;
    }
    | record_type
    {
      $$ = $1;
    }

array_type : ARRAY LBRACKET period RBRACKET OF BASIC_TYPE
              {
                cout << "Array Type with base type: " << GET_TYPE($6) << endl;
                $$ = new ArrayTypeNode($3, GET_STR_VAL($6));
                FieldNameToType[GET_STR_VAL($6)] = $$;
                safeDelete($1, $2, $4, $5, $6);
              }

record_declarations : record_type
                      {
                        $$ = $1;
                      }
                    | record_declarations record_type
                      {
                        $$ = $2;
                      }

record_type : IDENTIFIER EQUAL RECORD field_list END SEMICOLON
              {
                cout << "Record Type" << endl;
                $$ = new RecordTypeNode($4, GET_STR_VAL($1));
                FieldNameToType[GET_STR_VAL($1)] = $$;

                RecordType* recType = new RecordType(GET_STR_VAL($1));
                vector<ASTNode*> fieldList = dynamic_cast<FieldListNode*>($4)->field_list;
                for (const auto& it : fieldList) {
                  FieldNode* field = dynamic_cast<FieldNode*>(it);
                  vector<string> idList = dynamic_cast<IdentifierListNode*>(field->id_list)->identifier_list;
                  ASTNode* type = field->type;
                  auto nodeType = type->node_type;
                  for (const auto& id : idList) {
                    SymbolType* symbolType = nullptr;
                    if (nodeType == NODE_BASIC_TYPE) {
                      symbolType = new SymbolType(dynamic_cast<BasicTypeNode*>(type)->type);
                    } else if (nodeType == NODE_ARRAY_TYPE) {
                      ArrayTypeNode* arrTypeNode = dynamic_cast<ArrayTypeNode*>(type);
                      SymbolType* elementType = new SymbolType(arrTypeNode->type);
                      vector<ASTNode*> pariodList = dynamic_cast<PeriodListNode*>(arrTypeNode->period_list)->period_list;
                      ArrayType* arrType = new ArrayType(elementType);
                      for (const auto& it : pariodList) {
                        PeriodNode* pariod = dynamic_cast<PeriodNode*>(it);
                        if(pariod->start > pariod->end){
                            std::cerr << "LINE[" << $1->line_no << "]ERROR" << ": Invalid Array Index '" << GET_STR_VAL($1) << "'\n";
                            int swap_i = pariod->start;
                            pariod->start = pariod->end;
                            pariod->end = swap_i;
                        }
                        arrType->addDimension(pariod->start, pariod->end);
                      }
                      symbolType = new SymbolType(arrType);
                    } else if (nodeType == NODE_RECORD_TYPE) {
                      symbolType = dealType(type);
                    }
                    recType->addField(id, symbolType);
                  }
                }
                SymbolType* symbolType = new SymbolType(recType);
                currentSymbolTable->addSymbol(new VarSymbol(GET_STR_VAL($1), symbolType));

                safeDelete($1, $2, $3, $5);
              }

field_list : /* 空 */
              {
                cout << "Empty Field List" << endl;
                $$ = new FieldListNode(vector<ASTNode*>{});
              }
            | field_list identifier_list COLON type SEMICOLON
              {   
                cout << "Adding Field" << endl;
                ASTNode* field_node = new FieldNode($2, $4);
                dynamic_cast<FieldListNode*>($1)->field_list.push_back(field_node);
                $$ = $1;
                safeDelete($3, $5);
              }
            | field_list identifier_list COLON IDENTIFIER SEMICOLON
              {
                ASTNode* field_node = new FieldNode(FieldNameToType[GET_STR_VAL($4)], dynamic_cast<IdentifierListNode*>($2));
                dynamic_cast<FieldListNode*>($1)->field_list.push_back(field_node);
                $$ = $1;
                safeDelete($3, $4, $5);
              }

period : INT_NUM RANGE INT_NUM
        {
          cout << "Period: " << GET_INT_VAL($1) << ".." << GET_INT_VAL($3) << endl;
          ASTNode* period_node = new PeriodNode(GET_INT_VAL($1), GET_INT_VAL($3));
          $$ = new PeriodListNode(vector<ASTNode*>{period_node});
          safeDelete($1, $2, $3);
        }
        | period COMMA INT_NUM RANGE INT_NUM
        {
          cout << "Adding Period: " << GET_INT_VAL($3) << ".." << GET_INT_VAL($5) << endl;
          ASTNode* period_node = new PeriodNode(GET_INT_VAL($3), GET_INT_VAL($5));
          dynamic_cast<PeriodListNode*>($1)->period_list.push_back(period_node);
          $$ = $1;
          safeDelete($2, $3, $4, $5);
        }

subprogram_declarations : {
                            cout << "Empty Subprogram Declarations" << endl;
                            $$ = new SubprogramDeclarationsNode(vector<ASTNode*>{});
                          }
                        |subprogram_declarations subprogram SEMICOLON
                        {
                          cout << "Adding Subprogram" << endl;
                          dynamic_cast<SubprogramDeclarationsNode*>($1)->subprogram_list.push_back($2);
                          $$ = $1;
                          safeDelete($3);
                        }

subprogram : subprogram_head SEMICOLON subprogram_body
            {
              cout << "Subprogram" << endl;
              $$ = new SubprogramNode($1, $3);
              safeDelete($2);
            }

subprogram_head : PROCEDURE IDENTIFIER formal_parameter
                  {
                    if (currentSymbolTable->lookupEntry(GET_STR_VAL($2))) {
                          std::cerr << "LINE[" << $2->line_no << "]ERROR: Duplicate procedure definition '" << GET_STR_VAL($2) << "'\n";
                          exit(EXIT_FAILURE);
                    }
                    else{
                      cout << "Procedure: " << GET_STR_VAL($2) << endl;
                      $$ = new SubprogramHeadNode(GET_STR_VAL($2), $3, false, "");

                      ProcSymbol* proc = new ProcSymbol(GET_STR_VAL($2), $$);
                      currentSymbolTable->addSymbol(proc);
                      currentSymbolTable = currentSymbolTable->getChildTable(GET_STR_VAL($2));
                      if ($3) {
                        vector<string> allParamNames;
                        vector<ASTNode*> param_list = dynamic_cast<ParameterListNode*>($3)->param_list;
                        for (const auto& it : param_list) {
                          ParameterNode* param = dynamic_cast<ParameterNode*>(it);
                          vector<string> idList = dynamic_cast<IdentifierListNode*>(param->id_list)->identifier_list;
                          BasicType type = param->type;
                          for (const auto& id : idList) {
                            if (currentSymbolTable->lookupCurrent(id)) {
                            std::cerr << "LINE[" << $1->line_no << "]ERROR: Duplicate procedure parameter '" << id << "'\n";  
                            continue;
                            }
                            allParamNames.push_back(id);
                            SymbolType* varType = new SymbolType(type);
                            VarSymbol* var = new VarSymbol(id, varType);
                            var->setPointer(static_cast<ParameterNode*>(it)->is_pointer);
                            currentSymbolTable->addSymbol(var);
                            proc->addParameter(var);
                          }
                        }
                      }
                    }

                      safeDelete($1, $2);
                  }
                | FUNCTION IDENTIFIER formal_parameter COLON BASIC_TYPE
                  {
                    if (currentSymbolTable->lookupEntry(GET_STR_VAL($2))) {
                        std::cerr << "LINE[" << $2->line_no << "]ERROR: Duplicate function definition '" << GET_STR_VAL($2) << "'\n";
                        exit(EXIT_FAILURE);
                    }
                    else{
                      cout << "Function: " << GET_STR_VAL($2) << " returning " << GET_TYPE($5) << endl;
                      $$ = new SubprogramHeadNode(GET_STR_VAL($2), $3, true, GET_STR_VAL($5));
                      cout<<"1"<<endl;

                      FuncSymbol* func = new FuncSymbol(GET_STR_VAL($2), $$, dynamic_cast<SubprogramHeadNode*>($$)->return_type);
                      currentSymbolTable->addSymbol(func);
                      currentSymbolTable = currentSymbolTable->getChildTable(GET_STR_VAL($2));
                      if ($3) {
                        vector<string> allParamNames;
                        vector<ASTNode*> param_list = dynamic_cast<ParameterListNode*>($3)->param_list;
                        for (const auto& it : param_list) {
                          ParameterNode* param = dynamic_cast<ParameterNode*>(it);
                          vector<string> idList = dynamic_cast<IdentifierListNode*>(param->id_list)->identifier_list;
                          BasicType type = param->type;
                          for (const auto& id : idList) {
                            if (currentSymbolTable->lookupCurrent(id)) {
                              std::cerr << "LINE[" << $1->line_no << "]ERROR: Duplicate function parameter '" << id << "'\n";
                              continue;
                            }
                            allParamNames.push_back(id);
                            SymbolType* varType = new SymbolType(type);
                            VarSymbol* var = new VarSymbol(id, varType);
                            var->setPointer(static_cast<ParameterNode*>(it)->is_pointer);
                            currentSymbolTable->addSymbol(var);
                            func->addParameter(var);
                          }
                        }
                      }
                    }
                    cout<<"--------------"<<endl;
                    safeDelete($1, $2, $4, $5);
                  }

formal_parameter : { 
                    cout<<"Empty Formal Parameters" << endl;
                    $$ = nullptr;}
                | LPAREN parameter_list RPAREN
                {
                  cout << "Formal Parameters" << endl;
                  $$ = $2;
                  safeDelete($1, $3);
                }

parameter_list : { 
                  cout << "Empty Parameter List" << endl;
                  $$ = new ParameterListNode();
                }
                | parameter
                {
                  cout << "Parameter" << endl;
                  $$ = new ParameterListNode(vector<ASTNode*>{$1});
                }
                | parameter_list SEMICOLON parameter
                {
                  cout << "Adding Parameter" << endl;
                  dynamic_cast<ParameterListNode*>($1)->param_list.push_back($3);
                  $$ = $1;
                  safeDelete($2);
                }

parameter : var_parameter
            { $$ = $1; }
            | value_parameter
            { $$ = $1; }

var_parameter : VAR value_parameter
              { 
                cout << "Var Parameter" << endl;
                // printNodeType($2);
                $$ = $2;
                dynamic_cast<ParameterNode*>($$)->is_pointer = true;
                safeDelete($1);
              }

value_parameter : identifier_list COLON BASIC_TYPE
                  {
                    cout << "Value Parameter with type: " << GET_TYPE($3) << endl;
                    $$ = new ParameterNode($1, GET_STR_VAL($3));
                    safeDelete($2, $3);
                  }

subprogram_body : const_declarations type_declarations var_declarations compound_statement
                  {
                    cout << "Subprogram Body" << endl;
                    $$ = new SubprogramBodyNode($1, $2, $3, $4);

                    currentSymbolTable = currentSymbolTable->getParent();
                  }

compound_statement : BEGIN_ statement_list END
                    { 
                      cout << "Compound Statement" << endl;
                      $$ = $2;
                      safeDelete($1, $3); 
                    }

statement_list : statement
                {
                  cout << "Statement" << endl;
                  $$ = new StatementListNode(vector<ASTNode*>{$1});
                }
                | statement_list SEMICOLON statement
                {
                  cout << "Adding Statement" << endl;
                  dynamic_cast<StatementListNode*>($1)->statement_list.push_back($3);
                  $$ = $1;
                  safeDelete($2);
                }

statement :  empty_statement
            | assign_statement
            | func_assign_statement
            | procedure_call
            | compound_statement
            | if_statement
            | for_statement
            | read_statement
            | write_statement
            | switch_statement
            | while_statement
            { $$ = $1; }
            | BREAK
            { 
              cout << "Control Statement: " << GET_STR_VAL($1) << endl;
              $$ = new ControlStatementNode(GET_STR_VAL($1));
              safeDelete($1);
            }
            | CONTINUE
            { 
              cout << "Control Statement: " << GET_STR_VAL($1) << endl;
              $$ = new ControlStatementNode(GET_STR_VAL($1));
              safeDelete($1);
            }

empty_statement : {
                    cout << "Empty Statement" << endl;
                    $$ = new EmptyStatementNode();
                  }

assign_statement : variable ASSIGN expression
                  {
                    cout << "Assign Statement" << endl;
                    $$ = new AssignStatementNode($1, $3);
                    safeDelete($2);
                  }

func_assign_statement : IDENTIFIER ASSIGN expression
                  {
                    cout << "Function Assign Statement: " << GET_STR_VAL($1) << endl;
                    $$ = new FuncAssignStatementNode(GET_STR_VAL($1), $3);
                    safeDelete($1, $2);
                  }

if_statement : IF expression THEN statement else_part
              {
                cout << "If Statement" << endl;
                $$ = new IfStatementNode($2, $4, $5);
                safeDelete($1, $3);
              }

for_statement : FOR IDENTIFIER ASSIGN expression TO expression DO statement
                {
                  cout << "For Statement (to): " << GET_STR_VAL($2) << endl;
                  $$ = new ForStatementNode(GET_STR_VAL($2), $4, $6, $8, false);
                  safeDelete($1, $2, $3, $5, $7);
                }
                | FOR IDENTIFIER ASSIGN expression DOWNTO expression DO statement
                {
                  cout << "For Statement (downto): " << GET_STR_VAL($2) << endl;
                  $$ = new ForStatementNode(GET_STR_VAL($2), $4, $6, $8, true);
                  safeDelete($1, $2, $3, $5, $7);
                }

read_statement : READ LPAREN variable_list RPAREN
                {
                  cout << "Read Statement" << endl;
                  $$ = new ReadStatementNode($3);
                  safeDelete($1, $2, $4);
                }
                | READLN LPAREN variable_list RPAREN
                {
                  cout << "Readln Statement" << endl;
                  $$ = new ReadlnStatementNode($3);
                  safeDelete($1, $2, $4);
                }

write_statement : WRITE LPAREN expression_list RPAREN
                {
                  //cout << "Write Statement" << endl;
                  $$ = new WriteStatementNode($3);
                  safeDelete($1, $2, $4);
                }
                | WRITELN LPAREN expression_list RPAREN
                {
                  cout << "Writeln Statement" << endl;
                  $$ = new WritelnStatementNode($3);
                  safeDelete($1, $2, $4);
                }

switch_statement : CASE expression OF switch_case_list SEMICOLON END
                  {
                    cout << "Switch Statement" << endl;
                    $$ = new SwitchStatementNode($2, $4);
                    safeDelete($1, $3, $5);
                  }
                ;

switch_case_list : switch_case_item
                  { 
                    cout << "Switch Case" << endl;
                    $$ = new SwitchCaseListNode(vector<ASTNode*>{$1});
                  }
                | switch_case_list SEMICOLON switch_case_item
                  { 
                    cout << "Adding Switch Case" << endl;
                    dynamic_cast<SwitchCaseListNode*>($1)->cases.push_back($3);
                    $$ = $1;
                    safeDelete($2);
                  }
                ;

switch_case_item : expression COLON statement
                  { 
                    cout << "Switch Case Item" << endl;
                    $$ = new SwitchCaseItemNode($1, $3);
                    safeDelete($2);
                  }
                 ;

while_statement : WHILE expression DO statement
                  { 
                    cout << "While Statement" << endl;
                    $$ = new WhileStatementNode($2, $4);
                    safeDelete($1, $3);
                  }
                ;

variable_list : variable 
                {
                  cout << "Variable" << endl;
                  $$ = new VariableListNode(vector<ASTNode*>{$1});
                }
                | variable_list COMMA variable
                {
                  cout << "Adding Variable" << endl;
                  dynamic_cast<VariableListNode*>($1)->variables.push_back($3);
                  $$ = $1;
                  safeDelete($2);
                }

variable : IDENTIFIER id_varpart
            {
              if (!currentSymbolTable->lookupEntry(GET_STR_VAL($1))) {
                std::cerr << "LINE[" << $1->line_no << "]ERROR: Undefined variable or variable of a non-existent type '" 
                 << GET_STR_VAL($1) << "'\n";
                exit(EXIT_FAILURE);
              }
              cout << "Variable: " << GET_STR_VAL($1) << endl;
              $$ = new VariableNode(GET_STR_VAL($1), $2);
              safeDelete($1);
            }

id_varpart : {
              cout<<"id_varpart: nullptr"<<endl; 
              $$ = nullptr; }
            | id_varpart_n
            { 
              cout<<"id_varpart: id_varpart_n"<<endl;
              $$ = $1; }

id_varpart_n : { 
                cout<<"IdVarPartList : nullptr"<<endl;
                $$ = new IdVarPartListNode(); }
            | id_varpart_n LBRACKET expression_list RBRACKET
            {
              cout << "Array Access" << endl;
              // printNodeType($3);
              cout<<endl<<endl;
              ASTNode* idVarPartNode = new IdVarPartNode($3);
              // printNodeType(idVarPartNode);
              dynamic_cast<IdVarPartListNode*>($1)->id_var_part_list.push_back(idVarPartNode);
              $$ = $1;
              safeDelete($2, $4);
            }

procedure_call : IDENTIFIER
                {
                  cout << "Procedure Call: " << GET_STR_VAL($1) << endl;
                  $$ = new ProcedureCallNode(GET_STR_VAL($1), nullptr);
                  safeDelete($1);
                }
                | STD_FUNC
                {
                  cout << "Procedure Call: " << GET_STR_VAL($1) << endl;
                  $$ = new ProcedureCallNode(GET_STR_VAL($1), nullptr);
                  safeDelete($1);
                }
                | IDENTIFIER LPAREN RPAREN
                {
                  cout << "Procedure Call: " << GET_STR_VAL($1) << endl;
                  $$ = new ProcedureCallNode(GET_STR_VAL($1), nullptr);
                  safeDelete($1, $2, $3);
                }
                | STD_FUNC LPAREN RPAREN
                {
                  cout << "Procedure Call: " << GET_STR_VAL($1) << endl;
                  $$ = new ProcedureCallNode(GET_STR_VAL($1), nullptr);
                  safeDelete($1, $2, $3);
                }
                | IDENTIFIER LPAREN expression_list RPAREN
                {
                  cout << "Procedure Call with args: " << GET_STR_VAL($1) << endl;
                  $$ = new ProcedureCallNode(GET_STR_VAL($1), $3);
                  safeDelete($1, $2, $4);
                }
                | STD_FUNC LPAREN expression_list RPAREN
                {
                  cout << "Procedure Call with args: " << GET_STR_VAL($1) << endl;
                  $$ = new ProcedureCallNode(GET_STR_VAL($1), $3);
                  safeDelete($1, $2, $4);
                }

else_part : { $$ = nullptr; }
            | ELSE statement
            {
              cout << "Else Part" << endl;
              $$ = new ElsePartNode($2);
              safeDelete($1);
            }

expression_list : expression
                {
                  cout << "Expression" << endl;
                  $$ = new ExpressionListNode(vector<ASTNode*>{$1});
                }
                | expression_list COMMA expression
                {
                  cout << "Adding Expression" << endl;
                  dynamic_cast<ExpressionListNode*>($1)->expr_list.push_back($3);
                  $$ = $1;
                  safeDelete($2);
                }

expression :  simple_expression
            { 
              cout<<"Simple Expression"<<endl;
              $$ = $1; }
            | str_expression
            { 
              cout<<"String Expression"<<endl;
              $$ = $1; }
            | simple_expression REL_OP simple_expression
            {
              cout << "Relational Expression: " << GET_STR_VAL($2) << endl;
              $$ = new BinaryOpNode(GET_STR_VAL($2), $1, $3);
              safeDelete($2);
            }
            | simple_expression EQUAL simple_expression
            {
              cout << "Relational Expression: " << GET_STR_VAL($2) << endl;
              $$ = new BinaryOpNode(GET_STR_VAL($2), $1, $3);
              safeDelete($2);
            }

str_expression : STRING
                {
                  cout << "String Expression: " << GET_STR_VAL($1) << endl;
                  $$ = new StrExpressionNode(GET_STR_VAL($1));
                  safeDelete($1);
                }
                | STRING PLUS STRING
                {
                  cout << "String Concatenation" << endl;
                  $$ = new StrExpressionNode(GET_STR_VAL($1) + GET_STR_VAL($3));
                  safeDelete($1, $2, $3);
                }
                | STRING PLUS CHAR
                {
                  cout << "String-Char Concatenation" << endl;
                  $$ = new StrExpressionNode(GET_STR_VAL($1) + string(1, GET_CHAR_VAL($3)));
                  safeDelete($1, $2, $3);
                }

simple_expression : simple_expression MINUS term
                    {
                      cout << "Additive Operation: " << GET_STR_VAL($2) << endl;
                      $$ = new BinaryOpNode(GET_STR_VAL($2), $1, $3);
                      safeDelete($2);
                    }
                    | simple_expression PLUS term
                    {
                      cout << "Additive Operation: " << GET_STR_VAL($2) << endl;
                      $$ = new BinaryOpNode(GET_STR_VAL($2), $1, $3);
                      safeDelete($2);
                    }
                    | simple_expression ADDING_OP term
                    {
                      cout << "Additive Operation: " << GET_STR_VAL($2) << endl;
                      $$ = new BinaryOpNode(GET_STR_VAL($2), $1, $3);
                      safeDelete($2);
                    }
                    | term
                    { 
                      cout<<"Term"<<endl;
                      $$ = $1; }

term : factor
        { 
          cout<<"Factor"<<endl;
          $$ = $1; }
        | term MULTI_OP factor
        {
          cout << "Multiplicative Operation: " << GET_STR_VAL($2) << endl;
          $$ = new BinaryOpNode(GET_STR_VAL($2), $1, $3);
          safeDelete($2);
        }

factor : const_value
        { 
          cout<<"Constant Value"<<endl;
          $$ = $1; }
        | variable
        { 
          cout<<"Variable"<<endl; 
          $$ = $1; }
        | LPAREN expression RPAREN
        { 
          cout << "Parenthesized Expression" << endl;
          $$ = $2;
          safeDelete($1, $3); 
        }
        | procedure_call
        {
          $$ = $1;
        }
        | NOT factor
        {
          cout << "Unary Operation: " << GET_STR_VAL($1) << endl;
          $$ = new UnaryOpNode(GET_STR_VAL($1), $2);
          safeDelete($1);
        }
        | PLUS factor
        {
          cout << "Unary Operation: " << GET_STR_VAL($1) << endl;
          $$ = new UnaryOpNode(GET_STR_VAL($1), $2);
          safeDelete($1);
        }
        | MINUS factor
        {
          cout << "Unary Operation: " << GET_STR_VAL($1) << endl;
          $$ = new UnaryOpNode(GET_STR_VAL($1), $2);
          safeDelete($1);
        }

%%

void yyerror(ASTNode** rootPtr, const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    cout<<"Error: " << msg << endl;
    *rootPtr = nullptr;
}

void yynote(ASTNode** rootPtr, std::string msg, int line) {
    fprintf(stderr, "Note: %s at line %d\n", msg.c_str(), line);
    *rootPtr = nullptr;
}

void yyerror_var(ASTNode** rootPtr, const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    *rootPtr = nullptr;
}

// 辅助处理类型
SymbolType* dealType(ASTNode* node) {
    SymbolType* res = nullptr;
    if (node->node_type == NODE_BASIC_TYPE) {
      res = new SymbolType(dynamic_cast<BasicTypeNode*>(node)->type);
    } else if (node->node_type == NODE_ARRAY_TYPE) {
      ArrayTypeNode* arrTypeNode = dynamic_cast<ArrayTypeNode*>(node);
      SymbolType* elementType = new SymbolType(arrTypeNode->type);
      vector<ASTNode*> pariodList = dynamic_cast<PeriodListNode*>(arrTypeNode->period_list)->period_list;
      ArrayType* arrType = new ArrayType(elementType);
      for (const auto& it : pariodList) {
          PeriodNode* pariod = dynamic_cast<PeriodNode*>(it);
          arrType->addDimension(pariod->start, pariod->end);
      }
      res = new SymbolType(arrType);
    } else if (node->node_type == NODE_RECORD_TYPE) {
      RecordTypeNode* recTypeNode = dynamic_cast<RecordTypeNode*>(node);
      RecordType* temp = new RecordType(recTypeNode->name);
      FieldListNode* fldListNode = dynamic_cast<FieldListNode*>(recTypeNode->field_list);
      vector<ASTNode*> fieldList = fldListNode->field_list;
      for (const auto& it : fieldList) {
        FieldNode* field = dynamic_cast<FieldNode*>(it);
        vector<string> idList = dynamic_cast<IdentifierListNode*>(field->id_list)->identifier_list;
        for (const auto& id : idList) {
            SymbolType* symType = dealType(field->type);
            temp->addField(id, symType);
        }
      }
      res = new SymbolType(temp);
    }
    cerr << '\t' << res << '\n';
    return res;
}