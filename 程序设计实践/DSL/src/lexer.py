import pyparsing as pp

# 定义关键词字典，包含所有的保留字
keywords = {
    "Step": pp.Keyword("Step"),
    "Speak": pp.Keyword("Speak"),
    "Listen": pp.Keyword("Listen"),
    "Case": pp.Keyword("Case"),
    "Default": pp.Keyword("Default"),
    "Exit": pp.Keyword("Exit"),
    "add": pp.Keyword("add"),
    "reduce": pp.Keyword("reduce"),
    "goto": pp.Keyword("goto"),
    "Timeout": pp.Keyword("Timeout"),
    "Recharge": pp.Keyword("Recharge"),
    "Consume": pp.Keyword("Consume"),
    "GetNum": pp.Keyword("GetNum"),
}

# 提取所有关键词的名称（字符串形式），用于判断标识符是否是关键词
keyword_names = set(keywords.keys())

# 定义标识符（变量名、步骤名等）
identifier = pp.Word(pp.alphas + "_", pp.alphas + pp.nums + "_").addParseAction(
    lambda t: None if t[0] in keyword_names else t[0])

# 定义变量（以$符号开始，后跟字母或数字的字符串）
variable = pp.Combine(pp.Literal('$') + pp.Word(pp.alphas + "_", pp.alphas + pp.nums + "_"))

# 定义字符串（包括带引号的字符串）
string = pp.QuotedString('"')

# 定义数字（整数）
number = pp.Word(pp.nums)

# 定义拼接符号 "+"（用于字符串连接）
plus_operator = pp.Literal('+')

# 匹配逗号
comma = pp.Literal(',')

# 用来组合所有的词法单元
tokens = {
    "identifier": identifier,  # 标识符，如Step名，变量名
    "variable": variable,  # 变量，如$balance
    "string": string,  # 字符串，如"请提供委托所需的材料。"
    "number": number,  # 数字
    "plus_operator": plus_operator,  # 拼接操作符
    "comma": comma,  # 逗号
}

# 合并所有的关键词和符号到一起
all_tokens = list(keywords.values()) + list(tokens.values())


# 词法分析器：通过正则表达式和pyparsing的API提取单独的token
def lex_input(input_text):
    """
    对输入文本进行词法分析，返回一个token流

    :param input_text: 需要分析的输入文本
    :return: 词法分析结果，包含所有匹配的token
    """
    result = []
    # 使用 MatchFirst 确保关键词优先匹配
    match_first = pp.MatchFirst(all_tokens)
    result.extend(match_first.scanString(input_text))
    return result


# 创建一个函数来处理多个测试案例
def test_lexer(test_input):
    """
    测试词法分析器的功能，并输出分析结果

    :param test_input: 需要测试的输入文本
    """
    print("Running test case...\n")
    lex_result = lex_input(test_input)
    for item in lex_result:
        print(item)


# 测试用例 1：基本脚本
test_input_1 = '''
Step welcome
    Speak "尊敬的勇者，欢迎来到冒险者协会，请问有什么可以帮您?"
    Listen 5, 30
    Case "投诉"
        goto complainProc
    Case "查询"
        goto billProc
    Case "完成冒险"
        goto rechargeProc
    Case "消费"
        goto consumeProc
    Case "离开"
        goto thanks
    Default
        goto wait
    Timeout 15
        Speak "哈喽您还活着吗？"
'''

# 测试用例 2：包含多个超时和充值
test_input_2 = '''
Step rechargeProc
    Speak "请提供委托所需的材料。"
    Listen 5, 30
    Recharge $balance add 100
    Speak "验证成功！您的账户当前余额是" + $balance + "枚金币"
    goto welcome
'''

# 如果作为主程序运行，执行测试
if __name__ == "__main__":
    test_lexer(test_input_1)
    test_lexer(test_input_2)
