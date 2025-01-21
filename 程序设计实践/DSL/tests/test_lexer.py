import unittest
from unittest.mock import MagicMock
import pyparsing as pp
from src.lexer import lex_input


class TestLexer(unittest.TestCase):
    # 测试空输入
    def test_lex_input_empty(self):
        input_text = ''' 
        '''

        # 模拟 MatchFirst 和 scanString 的行为
        mocked_match_first = MagicMock()
        mocked_match_first.scanString.return_value = []

        # 替换 pyparsing 中的 MatchFirst 为我们模拟的版本
        pp.MatchFirst = MagicMock(return_value=mocked_match_first)

        result = lex_input(input_text)

        # 断言分析结果为空
        self.assertEqual(len(result), 0)  # 应该没有任何 token

    # 测试基本脚本，确保能够识别常见的关键词
    def test_lex_input_basic_script(self):
        input_text = '''
        Step start
            Speak "你好"
            Listen 10, 20
            Case "查询"
                goto processQuery
            Timeout 10
                Speak "超时了"
        '''

        # 模拟 MatchFirst 和 scanString 的行为
        mocked_match_first = MagicMock()
        mocked_match_first.scanString.return_value = [
            (pp.ParseResults([pp.Keyword('Step')]), 0),
            (pp.ParseResults([pp.Keyword('Speak')]), 5),
            (pp.ParseResults([pp.Keyword('Listen')]), 11),
            (pp.ParseResults([pp.Keyword('Case')]), 18),
            (pp.ParseResults([pp.Keyword('Timeout')]), 30),
        ]

        # 替换 pyparsing 中的 MatchFirst 为我们模拟的版本
        pp.MatchFirst = MagicMock(return_value=mocked_match_first)

        result = lex_input(input_text)

        # 断言分析结果
        self.assertGreater(len(result), 0)
        self.assertIn('Step', [item[0][0] for item in result])
        self.assertIn('Speak', [item[0][0] for item in result])
        self.assertIn('Timeout', [item[0][0] for item in result])

    # 测试忽略空白字符
    def test_lex_input_ignore_whitespace(self):
        input_text = '''
        Step    start
            Speak    "你好"
            Listen    10,    20
            Case    "查询"
                goto    processQuery
        '''

        # 模拟 MatchFirst 和 scanString 的行为
        mocked_match_first = MagicMock()
        mocked_match_first.scanString.return_value = [
            (pp.ParseResults([pp.Keyword('Step')]), 0),
            (pp.ParseResults([pp.Keyword('Speak')]), 5),
            (pp.ParseResults([pp.Keyword('Listen')]), 11),
            (pp.ParseResults([pp.Keyword('Case')]), 18),
        ]

        pp.MatchFirst = MagicMock(return_value=mocked_match_first)

        result = lex_input(input_text)

        # 断言分析结果
        self.assertGreater(len(result), 0)
        self.assertIn('Step', [item[0][0] for item in result])
        self.assertIn('Speak', [item[0][0] for item in result])
        self.assertIn('Listen', [item[0][0] for item in result])

    # 测试标识符与关键词的区分
    def test_lex_input_identifier_vs_keyword(self):
        input_text = '''
        Step validStep
            Case invalidCase
            Exit exitCmd
        '''

        # 模拟 MatchFirst 和 scanString 的行为
        mocked_match_first = MagicMock()
        mocked_match_first.scanString.return_value = [
            (pp.ParseResults([pp.Keyword('Step')]), 0),
            (pp.ParseResults([pp.Keyword('validStep')]), 5),
            (pp.ParseResults([pp.Keyword('Exit')]), 17),
            (pp.ParseResults([pp.Keyword('exitCmd')]), 22),
        ]

        pp.MatchFirst = MagicMock(return_value=mocked_match_first)

        result = lex_input(input_text)

        # 断言分析结果，检查标识符和保留字
        tokens = [item[0][0] for item in result]
        self.assertIn('Step', tokens)  # 'Step' 应该被识别为关键词
        self.assertIn('validStep', tokens)  # validStep 应该被识别为标识符
        self.assertIn('Exit', tokens)  # 'Exit' 应该被识别为关键词
        self.assertIn('exitCmd', tokens)  # exitCmd 应该被识别为标识符

    # 测试变量与拼接符号
    def test_lex_input_variable_and_operator(self):
        input_text = '''
        Step processPayment
            Recharge $balance add 100
            Speak "余额为：" + $balance
        '''

        # 模拟 MatchFirst 和 scanString 的行为
        mocked_match_first = MagicMock()
        mocked_match_first.scanString.return_value = [
            (pp.ParseResults([pp.Keyword('Step')]), 0),
            (pp.ParseResults([pp.Keyword('processPayment')]), 5),
            (pp.ParseResults([pp.Keyword('Recharge')]), 20),
            (pp.ParseResults([pp.Keyword('$balance')]), 29),
            (pp.ParseResults([pp.Keyword('add')]), 39),
            (pp.ParseResults([pp.Keyword('100')]), 43),
            (pp.ParseResults([pp.Keyword('+')]), 47),
        ]

        pp.MatchFirst = MagicMock(return_value=mocked_match_first)

        result = lex_input(input_text)

        # 断言分析结果，检查变量和操作符
        tokens = [item[0][0] for item in result]
        self.assertIn('$balance', tokens)  # $balance 应该被识别为变量
        self.assertIn('+', tokens)  # '+' 应该被识别为拼接操作符
        self.assertIn('Recharge', tokens)  # 'Recharge' 应该被识别为关键词


if __name__ == '__main__':
    unittest.main()
