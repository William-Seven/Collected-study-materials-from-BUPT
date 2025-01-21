import sys
import os
import unittest
from unittest.mock import patch

# 添加 src 目录到 sys.path 中
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../src')))

from src.parser import parse_script  # 引入你在 parser.py 中的解析函数


# 模拟 lexer 中的规则

def mock_identifier(input_text):
    """模拟 identifier 规则返回的标识符"""
    return input_text.strip()

def mock_variable(input_text):
    """模拟 variable 规则返回的变量"""
    return input_text.strip()

def mock_string(input_text):
    """模拟 string 规则返回的字符串"""
    return input_text.strip('"')

def mock_number(input_text):
    """模拟 number 规则返回的数字"""
    return int(input_text.strip())

def mock_keywords(keyword):
    """模拟 keyword 规则返回的关键字"""
    return keyword

def mock_comma(input_text):
    """模拟 comma 规则返回的逗号"""
    return input_text.strip(',')

def mock_plus_operator(input_text):
    """模拟 plus_operator 规则返回的加号"""
    return input_text.strip('+')


# 测试用例类

class TestParser(unittest.TestCase):

    @patch('lexer.identifier', side_effect=mock_identifier)
    @patch('lexer.variable', side_effect=mock_variable)
    @patch('lexer.string', side_effect=mock_string)
    @patch('lexer.number', side_effect=mock_number)
    @patch('lexer.keywords', side_effect=mock_keywords)
    @patch('lexer.comma', side_effect=mock_comma)
    @patch('lexer.plus_operator', side_effect=mock_plus_operator)
    def test_parse_script_step_welcome(self, *mocked_functions):
        """测试包含 Step 和 Speak 等基本语法的脚本解析"""
        input_text = '''
        Step welcome
            Speak "尊敬的勇者，欢迎来到冒险者协会，请问有什么可以帮您?"
            Listen 5, 30
            Case "投诉"
                goto complainProc
            Default
        '''
        # 调用解析函数
        result = parse_script(input_text)

        # 验证解析结果
        self.assertIsNotNone(result)
        self.assertEqual(result[0][0], 'Step')
        self.assertEqual(result[0][1], 'welcome')
        self.assertEqual(result[0][2][0], 'Speak')
        self.assertEqual(result[0][2][1], '尊敬的勇者，欢迎来到冒险者协会，请问有什么可以帮您?')

    @patch('lexer.identifier', side_effect=mock_identifier)
    @patch('lexer.variable', side_effect=mock_variable)
    @patch('lexer.string', side_effect=mock_string)
    @patch('lexer.number', side_effect=mock_number)
    @patch('lexer.keywords', side_effect=mock_keywords)
    @patch('lexer.comma', side_effect=mock_comma)
    @patch('lexer.plus_operator', side_effect=mock_plus_operator)
    def test_parse_script_with_recharge(self, *mocked_functions):
        """测试包含 Recharge 动作的脚本解析"""
        input_text = '''
        Step rechargeProc
            Recharge $balance add 100
            Speak "验证成功！您的账户当前余额是" + $balance + "枚金币"
            goto welcome
        '''
        # 调用解析函数
        result = parse_script(input_text)

        # 验证解析结果
        self.assertIsNotNone(result)
        self.assertEqual(result[0][0], 'Step')
        self.assertEqual(result[0][1], 'rechargeProc')
        self.assertEqual(result[0][2][0], 'Recharge')
        self.assertEqual(result[0][2][1], '$balance')
        self.assertEqual(result[0][2][2], 'add')
        self.assertEqual(result[0][2][3], '100')

    @patch('lexer.identifier', side_effect=mock_identifier)
    @patch('lexer.variable', side_effect=mock_variable)
    @patch('lexer.string', side_effect=mock_string)
    @patch('lexer.number', side_effect=mock_number)
    @patch('lexer.keywords', side_effect=mock_keywords)
    @patch('lexer.comma', side_effect=mock_comma)
    @patch('lexer.plus_operator', side_effect=mock_plus_operator)
    def test_parse_script_with_invalid_case(self, *mocked_functions):
        """测试解析包含无效输入的脚本"""
        input_text = '''
        wrong invalid
        '''
        # 调用解析函数
        result = parse_script(input_text)

        # 验证解析结果：解析失败，返回 None
        self.assertIsNone(result)


if __name__ == '__main__':
    unittest.main()
