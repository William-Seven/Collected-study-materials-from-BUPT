#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>

enum TokenType {
    T_EOF,
    T_ERROR,
    T_IDENTIFIER,
    T_KEYWORD,
    T_PUNCTUATOR,
    T_INTEGER_CONSTANT,
    T_FLOATING_CONSTANT,
    T_CHAR_CONSTANT,
    T_STRING_LITERAL
};

class Token {
   public:
    Token(TokenType type, int line, int column, const std::string& text);
    void print() const;
    TokenType getType() const;
    const std::string& getText() const;

   private:
    TokenType type;
    int line;
    int column;
    std::string text;
};

#endif
