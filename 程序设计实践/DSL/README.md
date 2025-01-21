# DSL For 穿越勇者
## 目录结构
```angular2html
DSL/
│
├── doc/                       # 存放文档
│   └── report.pdf             # 项目报告
│
├── src/                       # 存放源代码
│   ├── interpreter.py         # 解释器，负责根据语法树执行脚本逻辑
│   ├── parser.py              # 语法分析器，使用 pyparsing 解析脚本语言的语法规则
│   └── lexer.py               # 词法分析器，使用 pyparsing 提取基本的词法单元
│
├── scripts/                   # 存放脚本文件
│   ├── script1.txt            # 脚本文件1：完整的脚本示例（冒险者协会）
│   ├── script2.txt            # 脚本文件2：完整的脚本示例（银行客服）
│   ├── script3.txt            # 脚本文件3：简易的脚本示例（欢迎、退出）
│   ├── script4.txt            # 脚本文件4：简易的脚本示例（投诉）
│   └── script5.txt            # 脚本文件5：简易的脚本示例（自定义存钱数字）
│
├── tests/                     # 测试文件夹
│   ├── test_lexer.py          # 词法分析器的测试桩
│   ├── test_parser.py         # 语法分析器的测试桩
│   └── test_interpreter.py    # 解释器的测试桩
│
├── run.py                     # 主程序入口
├── auto_run.py                # 自动运行脚本
└── README.md                  # 项目说明文档
```

## 一些说明
命名规则：Python 的PEP8标准

执行全部测试桩命令：
```bash
python -m unittest discover -s tests
```

执行自动测试脚本：
```bash
python auto_run.py
```

手动执行程序并指定script版本：
```bash
python run.py scripts/script1.txt
```

## 脚本语言语法描述

### 1. **Step**
每个 `Step` 是一个完整的流程步骤，表示一个状态，其中包含多个动作，如 `Speak`、`Listen`、`Case` 等。

`Step` 是脚本的基础单元。

#### 语法：
```
Step <step_name>
    <action>
    <action>
    ...
```

- `<step_name>`：步骤的标识符，表示当前步骤的名称。
- `<action>`：在步骤中执行的操作，如 `Speak`、`Listen`、`Case`、`Timeout` 等。
- 每两个 `step` 之间不需要空行。
- 机器人在任意时刻只会处于一个`Step`。
- 默认第一个初始状态为`welcome`.

### 2. **Speak**
`Speak` 用于输出文本信息，可以是静态文本、动态表达式或变量。符号 `+` 用于将多个字符串连接起来。

#### 语法：
```
Speak "<speak_text>"
```

- `<speak_text>`：输出的文本内容，可以是字符串、变量或包含加法等操作的表达式，支持字符串连接。

### 3. **Listen**
`Listen` 用于监听用户输入。

该操作会在指定的时间段内等待用户输入，若超时则执行 `Default` 操作。

#### 语法：
```
Listen <listen_start>, <listen_stop>
```

- `<listen_start>`：开始监听的时间（单位：秒）。
- `<listen_stop>`：停止监听时间（单位：秒）。如果用户未在此时间内输入，将执行 `Default` 操作。

### 4. **Goto**
`Goto` 用于跳转到指定的步骤，通常是根据 `Case` 或 `Timeout` 等触发的。

#### 语法：
```
goto <goto_step>
```

- `<goto_step>`：目标步骤的标识符。

### 5. **Case**
`Case` 用于判断用户输入并跳转到对应的步骤。

后接一个 `goto` 操作。

#### 语法：
```
Case "<case_input>"
    goto <goto_step>
```

- `<case_input>`：用于匹配用户输入的步骤名。

### 6. **Default**
`Default` 用于在 `Case` 中未匹配到用户输入且 `Listen` 超时，则会跳转到默认步骤。

#### 语法：
```
Default
```

- 根据不同的当前状态，实现不同的默认操作。
- 若处于`welcome`状态，则跳转到`wait`状态。
- 若处于非`welcome`状态，则跳转到`welcome`状态。

### 7. **Timeout**
`Timeout` 用于设置超时操作。

等待指定时间，超时后执行下一条操作。

#### 语法：
```
Timeout <timeout_amount>
    <action>
```

- `<timeout_amount>`：超时的时间（单位：秒）。
- `<action>`：超时后的操作，通常是 `Speak` 或 `goto`。

### 8. **GetNum**
`GetNum` 用于获取用户输入的数字，并将其存储在变量中。

#### 语法：
```
GetNum <variable>
```

- `<variable>`：要存储用户输入的变量名。例如`$depositAmount`

### 9. **Recharge & Consume**
`Recharge` 和 `Consume` 用于修改账户余额或进行数值计算。

新增 `add` 和 `reduce` 操作替代原来的加法和减法符号。

#### 语法：
```
Recharge <variable> add <amount> | <variable>
Consume <variable> reduce <amount> | <variable>
```

- `<variable>`：要更新的变量名，例如 `$balance`。
- `<amount> | <variable>`：要增加或减少的数值，可以为常量，也可以为用户输入的变量。

### 10. **符号：+（字符串连接）**
在 `Speak` 操作中，符号 `+` 表示字符串的连接操作，用于将多个字符串或表达式连接成一个完整的输出。

#### 语法：
```
"<string1>" + "<string2>" + <variable>
```

- `<string1>` 和 `<string2>`：可以是静态字符串、变量或表达式。
- 若为变量，则不需要双引号。

### 11. **Exit**
`Exit` 用于结束会话或对话，通常在流程的最后步骤使用。

#### 语法：
```
Exit
```