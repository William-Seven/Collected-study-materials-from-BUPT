import time
import re
from src.parser import parse_script


class Interpreter:
    def __init__(self, script):
        """
        初始化解释器实例

        :param script: 解析后的脚本语法树
        """
        self.script = script  # 解析后的脚本语法树
        self.variables = {}  # 用于存储变量的字典
        self.step_index = self.find_step_index("welcome")  # 从Step welcome开始执行
        self.case_actions = []  # 声明用于存储当前步骤的Case动作
        self.has_jumped = False  # 跳转标志，初始为False

    def run(self):
        """
        执行解析后的脚本，直到所有步骤完成或退出
        """
        while self.step_index != -1:  # 使用 -1 表示退出
            step = self.script[self.step_index]
            step_name = step["step_name"]
            self.update_case_actions(step)  # 更新当前步骤的 Case 动作
            self.execute_step(step)  # 执行当前步骤

    def update_case_actions(self, step):
        """
        更新当前步骤中的所有 Case 动作

        :param step: 当前步骤的数据
        """
        self.case_actions = []  # 清空之前的 Case 动作
        actions = step[1:]  # 获取步骤中的所有动作
        for action in actions:
            if "case_input" in action:
                self.case_actions.append(action)  # 收集Case动作

    def execute_step(self, step):
        """
        执行单个步骤的所有动作

        :param step: 当前步骤的数据
        """
        actions = step[1:]  # 获取步骤中的所有动作
        for action in actions:
            self.execute_action(action)  # 执行具体动作
            # 如果发生跳转，退出当前步骤的执行
            if self.has_jumped:
                break
        self.has_jumped = False  # 重置跳转标志

    def execute_action(self, action):
        """
        执行具体的动作

        :param action: 当前动作的数据
        """
        if "timeout_amount" in action:
            self.execute_timeout(action)
        elif "speak_text" in action:
            self.execute_speak(action)
        elif "listen_start" in action:
            self.execute_listen(action)
        elif "goto_step" in action:
            self.execute_goto(action)
        elif "recharge_var" in action:
            self.execute_recharge(action)
        elif "consume_var" in action:
            self.execute_consume(action)
        elif "getNum_var" in action:
            self.execute_get_num(action)
        elif "case_input" in action:
            self.execute_case(action)
        elif "default" in action:
            self.execute_default(action)
        elif "Exit" in action:
            self.execute_exit(action)

    def execute_speak(self, action):
        """
        执行 Speak 动作，打印出需要说的话

        :param action: 包含 speak_text 的动作
        """
        speak_text = ''.join(action["speak_text"])
        speak_text = self.replace_variables(speak_text)  # 变量替换
        speak_text = speak_text.replace("+", "")  # 移除 "+" 号（用于字符串拼接）
        print(f"{speak_text}")

    def replace_variables(self, text):
        """
        替换文本中的变量为其值。如果变量不存在，则初始化为 100。

        :param text: 包含变量的文本
        :return: 替换后的文本
        """
        # return "您的账户当前有100枚金币。"
        pattern = r'\$([a-zA-Z_][a-zA-Z0-9_]*)'  # 匹配变量的正则表达式
        matches = re.findall(pattern, text)

        for match in matches:
            if match not in self.variables:
                self.variables[match] = 100
            text = text.replace(f"${match}", str(self.variables[match]))

        return text

    def execute_listen(self, action):
        """
        执行 Listen 动作，模拟等待用户输入

        :param action: 包含 listen_start 和 listen_stop
        """
        listen_start = int(action["listen_start"])
        listen_stop = int(action["listen_stop"])
        listen_duration = listen_stop - listen_start

        start_time = time.time()  # 记录开始时间
        user_input = None  # 初始化用户输入

        # 等待直到超时或者用户输入
        while time.time() - start_time < listen_duration:
            print("请回复：")
            user_input = input()

            # 如果超时，则执行默认操作
            if time.time() - start_time >= listen_duration:
                print("您似乎不在了....")
                self.execute_default(action)
                return

            if user_input:  # 一旦收到输入，退出循环
                break

            print("我在等您的回复...")

        case_matched = False  # 标记是否匹配到Case
        for case_action in self.case_actions:  # 使用 case_actions 进行匹配
            case_input = case_action["case_input"]
            if case_input in user_input:
                self.step_index = self.find_step_index(
                    case_action['goto_step'])  # 跳转到对应的步骤
                case_matched = True
                self.has_jumped = True  # 标记已跳转
                break

        if not case_matched:
            print("我不明白您在说什么。请再说一遍好吗？")
            self.execute_listen(action)  # 重新让用户输入

    def execute_goto(self, action):
        """
        执行 Goto 动作，跳转到指定步骤

        :param action: 当前 Goto 动作
        """
        goto_step = action["goto_step"]
        self.step_index = self.find_step_index(goto_step)
        self.has_jumped = True  # 标记已跳转

    def find_step_index(self, step_name):
        """
        根据步骤名查找对应步骤的索引

        :param step_name: 步骤名称
        :return: 步骤的索引，如果找不到则返回 -1
        """
        for i, step in enumerate(self.script):
            if step["step_name"] == step_name:
                return i
        return -1  # 如果找不到步骤名，返回 -1 表示退出

    def execute_recharge(self, action):
        """
        执行 Recharge 动作

        :param action: 当前 Recharge 动作
        """
        var = action["recharge_var"].lstrip('$')  # 获取变量名称，去除前缀 $
        if '$' in action["recharge_amount"]:  # 如果 recharge_amount 是变量
            amount_var = action["recharge_amount"].lstrip('$')  # 获取变量名称，去除前缀 $
            amount = self.variables[amount_var]  # 获取变量值
        else:
            amount = int(action["recharge_amount"])
        if var not in self.variables:
            self.variables[var] = 100
        self.variables[var] += amount

    def execute_consume(self, action):
        """
        执行 Consume 动作

        :param action: 当前 Consume 动作
        """
        var = action["consume_var"].lstrip('$')
        amount = int(action["consume_amount"])
        if var not in self.variables:
            self.variables[var] = 100
        self.variables[var] -= amount

    def execute_get_num(self, action):
        """
        执行 GetNum 动作
        :param action: 当前动作
        """
        print("请回复：")
        user_input = input()
        var = action["getNum_var"].lstrip('$')
        self.variables[var] = int(user_input)

    def execute_case(self, action):
        """
        执行 Case 动作，根据用户输入决定跳转

        :param action: 当前 Case 动作
        """
        case_input = action["case_input"]
        user_input = input(f"请回复 {case_input}: ")
        if case_input in user_input:
            self.step_index = self.find_step_index(user_input)  # 跳转到对应的步骤
        else:
            print("我不明白您在说什么。请再说一遍好吗？")
            self.execute_listen(action)  # 重新让用户输入

    def execute_default(self, action):
        """
        执行 Default 动作，执行默认操作

        :param action: 当前 Default 动作
        """
        # 获取当前步骤的名称
        current_step_name = self.script[self.step_index]["step_name"]
        if current_step_name == "welcome":
            # 如果当前步骤是 "welcome"，跳转到 "wait" 步骤
            self.step_index = self.find_step_index("wait")
        else:  # 否则，跳转到 "welcome" 步骤
            self.step_index = self.find_step_index("welcome")
        self.has_jumped = True

    def execute_exit(self, action):
        """
        执行 Exit 动作，退出脚本

        :param action: 当前 Exit 动作
        """
        exit(0)

    def execute_timeout(self, action):
        """
        执行 Timeout 动作，处理超时操作

        :param action: 当前 Timeout 动作
        """
        timeout_duration = int(action["timeout_amount"])  # 获取超时时间

        time.sleep(timeout_duration)  # 模拟等待超时
        if "speak_text" in action:
            self.execute_speak(action)
        elif "goto_step" in action:
            self.execute_goto(action)


def test_interpreter(input_text):
    """
    解析脚本并执行解释器

    :param input_text: 输入的脚本文本
    """
    parsed_script = parse_script(input_text)
    if parsed_script:
        interpreter = Interpreter(parsed_script.script)
        interpreter.run()
    else:
        print("Parsing failed, cannot run the interpreter.")


# 测试用例 1
test_input_1 = '''
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
Step thanks
    Speak "感谢您的光临，祝您生活愉快！"
    Exit
Step wait
    Speak "哈喽您还活着吗？"
    Exit
'''

# 测试用例 2
test_input_2 = '''
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

if __name__ == "__main__":
    # test_interpreter(test_input_1)
    test_interpreter(test_input_2)
