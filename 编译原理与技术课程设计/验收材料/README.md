# 使用说明

```bash
flex NEW_PASCC.l
bison -d NEW_PASCC.y
g++ main.cc lex.yy.c NEW_PASCC.tab.c ast.cpp -std=c++17 -o pascc
```

或者尝试直接执行 auto.bat

# 项目结构

```
BUPT-PASCC-
|
├─ 📁correct_test                               # 正确性测试文件    
│  ├─ 📄correct1.pas
│  ├─ 📄correct2.pas
│  ├─ 📄correct3.pas
│  ├─ 📄correct4.pas
│  ├─ 📄correct5.pas
│  ├─ 📄correct6.pas
│  ├─ 📄correct_2.pas
│  ├─ 📄correct_all.pas                         # 完整正确功能的整合测试
│  ├─ 📄valid_ascii_1.pas
│  ├─ 📄valid_ascii_2.pas
│  ├─ 📄valid_bracket_1.pas
│  ├─ 📄valid_bracket_2.pas
│  ├─ 📄valid_identifier_1.pas
│  ├─ 📄valid_identifier_2.pas
│  ├─ 📄valid_number_1.pas
│  └─ 📄valid_number_2.pas
|
├─ 📁error_test_bison                           # 用于语法分析错误检测
│  ├─ 📄error1.pas
│  ├─ 📄error10.pas
│  ├─ 📄error2.pas
│  ├─ 📄error3.pas
│  ├─ 📄error4.pas
│  ├─ 📄error5.pas
│  ├─ 📄error6.pas
│  ├─ 📄error7.pas
│  ├─ 📄error8.pas
│  └─ 📄error9.pas
|
├─ 📁error_test_lex                             # 用于词法分析错误检测
│  ├─ 📄invalid_ascii_1.pas
│  ├─ 📄invalid_ascii_2.pas
│  ├─ 📄invalid_brack_1.pas
│  ├─ 📄invalid_brack_2.pas
│  ├─ 📄invalid_identifier_1.pas
│  ├─ 📄invalid_identifier_2.pas
│  ├─ 📄invalid_number_1.pas
│  └─ 📄invalid_number_2.pas
|
├─ 📁src
│  ├─ 📁thirdparty
│  │  └─ 📄argparse.hpp                         # 第三方库
│  ├─ 📄ast.cpp                                 # 拷贝构造函数
│  ├─ 📄ast.h                                   # AST文件
│  ├─ 📄auto.bat                                # 自动编译脚本
│  ├─ 📄generalize_code.cpp                     # 代码生成模块
│  ├─ 📄generalize_code_unit_test.cpp           # 代码生成模块的单元测试
│  ├─ 📄lex.yy.c                                # 编译后的词法分析文件
│  ├─ 📄main.cc                                 # 主程序
│  ├─ 📄NEW_PASCC.l                             # 词法分析模块     
│  ├─ 📄NEW_PASCC.tab.c                         # 编译后的语法分析文件
│  ├─ 📄NEW_PASCC.tab.h                         # 编译后的语法分析文件
│  ├─ 📄NEW_PASCC.y                             # 语法分析模块
│  ├─ 📄symbol.h                                # 符号表相关类的定义
│  ├─ 📄symbol_table.h                          # 符号表定义及相关函数
│  ├─ 📄test.py                                 # 批量测试脚本
│  ├─ 📄type.h                                  # 基础符号类型定义
│  └─ 📄parser.exe                              # 可执行程序
|
└─ 📄README.md                                  # 使用说明及项目结构
```