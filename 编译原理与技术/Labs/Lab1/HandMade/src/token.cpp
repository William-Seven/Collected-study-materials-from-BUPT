#include "token.h"

Token::Token(TokenType type, int line, int column, const std::string& text)
    : type(type), line(line), column(column), text(text) {}

void Token::print() const {
    static const char* tokenNames[] = {
        "EOF", "error", "identifier", "keyword", "punctuator",
        "integer constant", "floating constant", "char constant", "string literal"};
    std::cout << line << ":" << column << ": <" << tokenNames[type] << ", " << text << ">" << std::endl;
}

TokenType Token::getType() const {
    return type;
}

const std::string& Token::getText() const {
    return text;
}
