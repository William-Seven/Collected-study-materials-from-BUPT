import pyparsing as pp
from src.lexer import identifier, variable, string, number, keywords, comma, plus_operator

# 定义规则：每个步骤的起始部分，Step 后跟步骤名称
step_name = keywords["Step"] + identifier("step_name")

# 定义表达式规则，处理字符串、变量和拼接操作
expression = (string | variable)

# Speak 动作：输出文本信息，后跟一个或多个表达式（支持拼接符号）
speak_action = keywords["Speak"] + \
    pp.OneOrMore(expression + pp.Optional(plus_operator))("speak_text")

# Listen 动作：等待用户输入，后跟开始和结束位置
listen_action = keywords["Listen"] + \
    number("listen_start") + comma(",") + number("listen_stop")

# Goto 动作：跳转到指定步骤，后跟步骤名称
goto_action = keywords["goto"] + identifier("goto_step")

# Timeout 动作：超时操作，后跟超时时长和相应的动作（可以是 Goto 或 Speak）
timeout_action = keywords["Timeout"] + \
    number("timeout_amount") + (goto_action | speak_action)

# Recharge 动作：充值操作，后跟变量、操作符（add）和金额
recharge_action = keywords["Recharge"] + \
    variable("recharge_var") + keywords["add"] + (number("recharge_amount") | variable("recharge_amount"))

# Consume 动作：消费操作，后跟变量、操作符（reduce）和金额
consume_action = keywords["Consume"] + \
    variable("consume_var") + keywords["reduce"] + number("consume_amount")

getNum_action = keywords["GetNum"] + variable("getNum_var")

# Case 动作：用户输入的分支操作，后跟输入条件和跳转动作
case_action = keywords["Case"] + string("case_input") + goto_action

# Default 动作：默认操作，表示没有匹配的输入时执行的动作
default_action = keywords["Default"]

# Exit 动作：退出脚本
exit_action = keywords["Exit"]("Exit")

# 组合不同的动作
action = pp.Group(speak_action | listen_action | case_action | default_action |
                  goto_action | recharge_action | consume_action | exit_action | timeout_action | getNum_action)

# 完整的步骤定义：包括 Step 和其后的一系列动作，步骤可以有多个动作
step = pp.Group(step_name + pp.ZeroOrMore(action) +
                pp.Optional(pp.LineEnd()))("step")

# 完整脚本：由多个步骤组成
script = pp.OneOrMore(step + pp.Optional(pp.LineEnd()))("script")


# 解析函数：解析脚本文本，返回语法树
def parse_script(input_text):
    """
    解析输入脚本文本，返回语法树（AST）。
    :param input_text: 要解析的文本脚本
    :return: 解析后的结果或 None（如果解析失败）
    """
    try:
        parsed = script.parseString(input_text)
        return parsed
    except pp.ParseException as pe:
        print(f"Parsing error: {pe}")
        return None


# 创建一个函数来处理多个测试案例
def test_parser(test_input):
    """
    运行并输出解析结果，用于验证脚本解析器的功能。
    :param test_input: 要测试的脚本文本
    """
    print("Running test case...\n")
    parsed_result = parse_script(test_input)
    if parsed_result:
        print(parsed_result.dump())
    else:
        print("Parsing failed.")


# 测试用例 1：基本脚本（基本语法种类）
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
Step rechargeProc
    Recharge $balance add 100
    Speak "验证成功！您的账户当前余额是" + $balance + "枚金币"
'''

# 测试用例 2：包含充值操作（变量识别）
test_input_2 = '''
Step rechargeProc
    Recharge $balance add 100
    Speak "验证成功！您的账户当前余额是" + $balance + "枚金币"
'''

# 测试用例 3：包含多个步骤，检查默认操作、退出等复杂脚本
test_input_3 = '''
Step welcome
    Speak "尊敬的勇者，欢迎来到冒险者协会，请问有什么可以帮您?"
    Listen 5, 10
    Case "离开"
        goto thanks
    Default
Step thanks
    Speak "感谢您的光临，祝您生活愉快！"
    Exit
Step wait
    Speak "哈喽您还活着吗？"
    Exit
'''

# 测试用例 4：复杂脚本，包含多个步骤和条件分支，涉及 Case、Default、Goto、Timeout、Recharge 等
test_input_4 = '''
Step welcome
    Speak "尊敬的勇者，欢迎来到冒险者协会，请问有什么可以帮您?"
    Listen 5, 10
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
Step complainProc
    Speak "为勇者大人服务是我的荣幸，请问勇者大人还有什么意见?"
    Listen 5, 10
    Case "没有"
        goto thanks
    Default
Step thanks
    Speak "感谢您的光临，期待您的新的冒险故事，再见！"
    Exit
Step billProc
    Speak "您的账户当前有" + $amount + "枚金币。"
    goto welcome
Step rechargeProc
    Speak "请提供委托所需的材料。"
    Listen 5, 10
    Case "提交"
        goto verifyProc
    Default
Step verifyProc
    Recharge $amount add 75
    Speak "验证成功！您的账户当前余额是" + $amount + "枚金币"
    goto welcome
Step consumeProc
    Speak "请问您今天想消费什么？"
    Speak "今天我们提供所有种类的药水，都只需5金币。"
    Listen 5, 10
    Case "买药水"
        goto medicine
    Default
Step medicine
    Consume $amount reduce 5
    Speak "消费成功，您的新余额是" + $amount + "金币"
    goto welcome
Step wait
    Timeout 15
        Speak "哈喽您还活着吗？"
    Timeout 10
        Speak "您已经很久没有冒险了，即将于30秒后退出"
    Timeout 10
        goto thanks
'''

# 如果作为主程序运行，执行测试
if __name__ == "__main__":
    # test_parser(test_input_1)
    # test_parser(test_input_2)
    test_parser(test_input_3)
    # test_parser(test_input_4)
