#include "mylex.h"
#include <set>
#include "error.h"

Lexer::Lexer(const std::string& input)
    : input(input), position(0), line(1), column(1), totalTokens(0), totalCharacters(0) {
    // 初始化每种token的计数为0
    for (int i = T_EOF; i <= T_STRING_LITERAL; ++i) {
        tokenCounts[static_cast<TokenType>(i)] = 0;
    }
}

// peek() 函数：查看当前字符
char Lexer::peek() const {
    if (position < input.size()) {
        return input[position];  // 返回当前位置的字符
    }
    return '\0';  // 如果已经到达输入末尾，返回空字符
}

// advance() 函数：移动到下一个字符并更新行号、列号和字符计数
char Lexer::advance() {
    char current = peek();
    if (current == '\n') {
        ++line;
        column = 1;
    } else {
        ++column;
    }
    ++position;
    ++totalCharacters;  // 统计每一个处理过的字符
    return current;
}

// skipWhitespaceAndComments() 函数：跳过空白字符、单行注释和多行注释
void Lexer::skipWhitespaceAndComments() {
    while (isspace(peek()) || peek() == '/' || peek() == '#') {
        if (isspace(peek())) {
            advance();  // 空白字符同样需要统计
        } else if (peek() == '/' && input[position + 1] == '/') {
            while (peek() != '\n' && peek() != '\0') {
                advance();  // 跳过单行注释
            }
        } else if (peek() == '/' && input[position + 1] == '*') {
            // 记录注释开始的行和列
            int start_line = line;
            int start_column = column;
            advance();  // '/'
            advance();  // '*'

            bool unterminated = true;  // 标记注释是否未结束
            while (peek() != '\0') {
                if (peek() == '*' && input[position + 1] == '/') {
                    advance();             //  '*'
                    advance();             //  '/'
                    unterminated = false;  // 找到结束符，注释结束
                    break;
                }
                // 检查是否遇到换行符
                if (peek() == '\n') {
                    advance();  // 处理换行符
                    // 跳过行首的空白字符
                    while (isspace(peek())) {
                        advance();
                    }

                    if (peek() != '*') {
                        // 如果下一行不是以'*'开头，则认为注释在上一行结束
                        ErrorHandler::reportError(start_line, start_column, "Unterminated block comment");
                        totalTokens++;
                        tokenCounts[T_ERROR]++;
                        break;  // 结束当前注释的处理，开始新的token识别
                    }
                } else {
                    advance();  // 跳过注释内容
                }
            }
        } else if (peek() == '#') {
            while (peek() != '\n' && peek() != '\0') {
                advance();  // 跳过 # 注释
            }
        } else {
            break;
        }
    }
}

// identifier() 函数：处理标识符或关键字
Token Lexer::identifier() {
    int start_line = line;
    int start_column = column;
    std::string text;
    while (isalnum(peek()) || peek() == '_') {
        text += advance();
    }

    // C语言关键字集合
    static const std::set<std::string> keywords = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "goto", "if", "inline",
        "int", "long", "register", "restrict", "return", "short", "signed", "sizeof",
        "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile",
        "while", "_Alignas", "_Alignof", "_Atomic", "_Bool", "_Complex", "_Generic",
        "_Imaginary", "_Noreturn", "_Static_assert", "_Thread_local"};
    TokenType type = (keywords.find(text) != keywords.end()) ? T_KEYWORD : T_IDENTIFIER;
    totalTokens++;
    tokenCounts[type]++;
    return Token(type, start_line, start_column, text);
}

// number() 函数：处理整数或浮点数
Token Lexer::number() {
    int start_line = line;
    int start_column = column;
    std::string text;

    // 检查是否是八进制或十六进制数
    if (peek() == '0') {
        text += advance();  // '0'
        if (peek() == 'x' || peek() == 'X') {
            text += advance();                                 // 'x' or 'X'
            return hexNumber(start_line, start_column, text);  // 处理十六进制数
        } else if (isdigit(peek())) {
            return octalNumber(start_line, start_column, text);  // 处理八进制数
        }
    }

    // 如果不是八进制或十六进制数，处理十进制数
    while (isdigit(peek())) {
        text += advance();
    }

    // 检查是否有小数点或科学计数法表示（e或E）
    if (peek() == '.' || peek() == 'e' || peek() == 'E') {
        return floatNumber(start_line, start_column, text);  // 调用浮点数处理函数
    }

    totalTokens++;
    tokenCounts[T_INTEGER_CONSTANT]++;
    return Token(T_INTEGER_CONSTANT, start_line, start_column, text);
}

// octalNumber() 函数：处理八进制数，非法八进制数会报错
Token Lexer::octalNumber(int start_line, int start_column, std::string text) {
    bool isError = false;

    // 处理八进制数，只允许数字0-7
    while (isdigit(peek())) {
        if (peek() >= '8') {
            isError = true;  // 如果发现非法的八进制数
        }
        text += advance();
    }

    if (isError) {
        totalTokens++;
        tokenCounts[T_ERROR]++;
        return Token(T_ERROR, start_line, start_column, "Invalid octal number");
    }

    totalTokens++;
    tokenCounts[T_INTEGER_CONSTANT]++;
    return Token(T_INTEGER_CONSTANT, start_line, start_column, text);
}

Token Lexer::hexNumber(int start_line, int start_column, std::string text) {
    while (isxdigit(peek())) {  // 十六进制数字（0-9, a-f, A-F）
        text += advance();
    }

    // 检查是否是十六进制浮点数
    if (peek() == '.') {
        return hexFloatNumber(start_line, start_column, text);  // 调用十六进制浮点数处理函数
    }

    totalTokens++;
    tokenCounts[T_INTEGER_CONSTANT]++;
    return Token(T_INTEGER_CONSTANT, start_line, start_column, text);
}

Token Lexer::hexFloatNumber(int start_line, int start_column, std::string text) {
    text += advance();  // '.'

    while (isxdigit(peek())) {  // 十六进制数字（0-9, a-f, A-F）
        text += advance();
    }

    // 检查指数部分 'p' 或 'P'
    if (peek() == 'p' || peek() == 'P') {
        text += advance();  // 'p' or 'P'

        // 检查是否有正负号
        if (peek() == '+' || peek() == '-') {
            text += advance();  // '+' or '-'
        }

        // p后必须跟数字
        if (!isdigit(peek())) {
            totalTokens++;
            tokenCounts[T_ERROR]++;
            return Token(T_ERROR, start_line, start_column, "Invalid exponent in hexadecimal floating point number");
        }

        while (isdigit(peek())) {
            text += advance();
        }
    }

    totalTokens++;
    tokenCounts[T_FLOATING_CONSTANT]++;
    return Token(T_FLOATING_CONSTANT, start_line, start_column, text);
}

// 处理浮点数
Token Lexer::floatNumber(int start_line, int start_column, std::string text) {
    text += advance();  // '.'

    if (!isdigit(peek())) {
        totalTokens++;
        tokenCounts[T_ERROR]++;
        return Token(T_ERROR, start_line, start_column, "Invalid floating point number");
    }

    while (isdigit(peek())) {
        text += advance();
    }

    // 检查是否有科学计数法表示（e或E）
    if (peek() == 'e' || peek() == 'E') {
        text += advance();  // 'e' or 'E'

        // 检查是否有正负号
        if (peek() == '+' || peek() == '-') {
            text += advance();  // '+' or '-'
        }

        // 科学计数法中 'e' 或 'E' 后面必须跟数字
        if (!isdigit(peek())) {
            totalTokens++;
            tokenCounts[T_ERROR]++;
            return Token(T_ERROR, start_line, start_column, "Invalid exponent in floating point number");
        }

        // 继续处理科学计数法中的数字部分
        while (isdigit(peek())) {
            text += advance();
        }
    }

    totalTokens++;
    tokenCounts[T_FLOATING_CONSTANT]++;
    return Token(T_FLOATING_CONSTANT, start_line, start_column, text);
}

// 处理字符串常量
Token Lexer::stringLiteral() {
    int start_line = line;
    int start_column = column;
    std::string text;
    text += advance();

    while (peek() != '"' && peek() != '\0') {
        if (peek() == '\n') {
            totalTokens++;
            tokenCounts[T_ERROR]++;
            return Token(T_ERROR, start_line, start_column, "Unterminated string literal");
        }
        text += advance();
    }
    if (peek() == '"') {
        text += advance();
    }
    totalTokens++;
    tokenCounts[T_STRING_LITERAL]++;
    return Token(T_STRING_LITERAL, start_line, start_column, text);
}

// 处理字符常量
Token Lexer::charConstant() {
    int start_line = line;
    int start_column = column;
    std::string text;
    text += advance();

    // 检查字符常量的内容
    char current = advance();

    if (current == '\\') {
        // 检测到转义字符，继续处理
        char escape_char = advance();
        text += '\\';         // 加入反斜杠
        text += escape_char;  // 加入转义后的字符

        // 检查是否以'结束
        if (peek() == '\'') {
            advance();
        } else {
            totalTokens++;
            tokenCounts[T_ERROR]++;

            // 跳过直到遇到下一个单引号为止
            while (peek() != '\'' && peek() != '\0') {
                advance();
            }

            // 如果找到了单引号，继续跳过它
            if (peek() == '\'') {
                advance();
            }

            return Token(T_ERROR, start_line, start_column, "Invalid character constant");
        }
    } else {
        // 没有转义字符，检查是否是合法的单字符常量
        text += current;

        // 检查下一个字符是否为'
        if (peek() == '\'') {
            advance();
        } else {
            totalTokens++;
            tokenCounts[T_ERROR]++;

            // 跳过直到遇到下一个单引号为止
            while (peek() != '\'' && peek() != '\0') {
                advance();
            }

            // 如果找到了单引号，继续跳过它
            if (peek() == '\'') {
                advance();
            }

            return Token(T_ERROR, start_line, start_column, "Invalid character constant");
        }
    }

    // 如果字符常量内容长度不对，则报错（如'ab'）
    if (text.length() > 2) {
        totalTokens++;
        tokenCounts[T_ERROR]++;

        // 跳过到下一个单引号
        while (peek() != '\'' && peek() != '\0') {
            advance();
        }

        if (peek() == '\'') {
            advance();
        }

        return Token(T_ERROR, start_line, start_column, "Invalid character constant");
    }

    text += '\'';
    totalTokens++;
    tokenCounts[T_CHAR_CONSTANT]++;
    return Token(T_CHAR_CONSTANT, start_line, start_column, text);
}

Token Lexer::punctuator() {
    int start_line = line;
    int start_column = column;
    std::string text;
    char current = advance();
    text += current;

    // 定义C语言中的合法标点符号
    static const std::set<char> validPunctuators = {
        '+', '-', '*', '/', '%', '=', '<', '>', '!', '&', '|', '^', '~',
        '(', ')', '[', ']', '{', '}', ',', ';', ':', '.', '?', '#'};

    // 检查当前符号是否是合法标点符号
    if (validPunctuators.find(current) == validPunctuators.end()) {
        // 当前符号不在合法标点符号集合中，报错
        totalTokens++;
        tokenCounts[T_ERROR]++;
        return Token(T_ERROR, start_line, start_column, text);
    }

    // 检查复合运算符的第二个字符
    switch (current) {
        case '+':
            if (peek() == '+' || peek() == '=') {
                text += advance();
            }
            break;
        case '-':
            if (peek() == '-' || peek() == '=') {
                text += advance();
            }
            break;
        case '=':
            if (peek() == '=') {
                text += advance();
            }
            break;
        case '!':
            if (peek() == '=') {
                text += advance();
            }
            break;
        case '&':
            if (peek() == '&' || peek() == '=') {
                text += advance();
            }
            break;
        case '|':
            if (peek() == '|' || peek() == '=') {
                text += advance();
            }
            break;
        case '>':
            if (peek() == '=' || peek() == '>') {
                text += advance();
                if (text.back() == '>' && peek() == '=') {
                    text += advance();
                }
            }
            break;
        case '<':
            if (peek() == '=' || peek() == '<') {
                text += advance();
                if (text.back() == '<' && peek() == '=') {
                    text += advance();
                }
            }
            break;
    }

    totalTokens++;
    tokenCounts[T_PUNCTUATOR]++;
    return Token(T_PUNCTUATOR, start_line, start_column, text);
}

Token Lexer::getNextToken() {
    skipWhitespaceAndComments();

    char current = peek();
    if (current == '\0') {
        return Token(T_EOF, line, column, "");
    } else if (isalpha(current) || current == '_') {
        return identifier();
    } else if (isdigit(current)) {
        return number();
    } else if (current == '"') {
        return stringLiteral();
    } else if (current == '\'') {
        return charConstant();
    } else {
        return punctuator();
    }
}

// 输出统计信息
void Lexer::printStatistics() const {
    std::cout << std::endl;
    std::cout << tokenCounts.at(T_KEYWORD) << "         keyword\n";
    std::cout << tokenCounts.at(T_IDENTIFIER) << "         identifier\n";
    std::cout << tokenCounts.at(T_PUNCTUATOR) << "         punctuator\n";
    std::cout << tokenCounts.at(T_INTEGER_CONSTANT) << "         integer constant\n";
    std::cout << tokenCounts.at(T_FLOATING_CONSTANT) << "         floating constant\n";
    std::cout << tokenCounts.at(T_CHAR_CONSTANT) << "         char constant\n";
    std::cout << tokenCounts.at(T_STRING_LITERAL) << "         string literal\n";
    std::cout << tokenCounts.at(T_ERROR) << "         error\n";
    std::cout << "total: " << totalTokens << " tokens, " << totalCharacters << " characters, " << line << " lines\n";
}