import sys
import os
import unittest
from io import StringIO
from unittest.mock import patch

# 添加 src 目录到 sys.path 中
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../src')))

from src.parser import parse_script
from src.interpreter import Interpreter


class TestInterpreter(unittest.TestCase):

    @patch('builtins.input', side_effect=["投诉", "没有", "提交", "买药水", ""])  # 模拟用户输入
    def test_interpreter_with_mocked_input(self, mock_input):
        test_input = '''
        Step welcome
            Listen 5, 10
            Case "投诉"
                goto complainProc
            Case "查询"
                goto billProc
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

        # 使用模拟的解析脚本
        interpreter = Interpreter(parse_script(test_input).script)
        interpreter.run()

        # 断言输入和步骤的行为符合预期
        self.assertEqual(interpreter.step_index, -1)  # 应该已经跳转到thanks步骤并结束

    @patch.object(Interpreter, 'replace_variables', return_value="欢迎来到冒险者协会，请问有什么可以帮您?")  # 重写变量替换方法
    @patch('builtins.input', side_effect=["查询", "离开"])  # 模拟用户输入
    def test_interpreter_with_mocked_variables(self, mock_input, mock_replace_variables):
        test_input = '''
        Step welcome
            Speak "尊敬的勇者，欢迎来到冒险者协会，请问有什么可以帮您?"
            Listen 5, 10
            Case "查询"
                goto billProc
            Case "离开"
                goto thanks
            Default
        Step billProc
            Speak "您的账户当前有" + $amount + "枚金币。"
            goto welcome
        '''

        # 使用模拟的解析脚本
        interpreter = Interpreter(parse_script(test_input).script)

        # 捕获解释器输出
        with patch('sys.stdout', new_callable=StringIO) as fake_out:
            # 执行解释器
            interpreter.run()
            output = fake_out.getvalue()

        # 确保每次 Speak 都调用了 replace_variables
        mock_replace_variables.assert_any_call("尊敬的勇者，欢迎来到冒险者协会，请问有什么可以帮您?")  # 第一次 Speak
        mock_replace_variables.assert_any_call("您的账户当前有" "+" "$amount" "+" "枚金币。")  # 第二次 Speak
        mock_replace_variables.assert_any_call("尊敬的勇者，欢迎来到冒险者协会，请问有什么可以帮您?")  # 第三次 Speak

        # 验证输出：确保每次替换文本都符合预期
        self.assertIn("欢迎来到冒险者协会，请问有什么可以帮您?", output)  # 第一次 Speak
        self.assertIn("欢迎来到冒险者协会，请问有什么可以帮您?", output)  # 第二次 Speak
        self.assertNotIn("$amount", output)  # 第二次 Speak 中不应出现 $amount
        self.assertIn("欢迎来到冒险者协会，请问有什么可以帮您?", output)  # 第三次 Speak

        # 断言输入和步骤的行为符合预期
        self.assertEqual(interpreter.step_index, -1)  # 应该已经跳转到thanks步骤并结束


if __name__ == '__main__':
    unittest.main()
