#include "error.h"
#include <iostream>

void ErrorHandler::reportError(int line, int column, const std::string& message) {
    Token errorToken(T_ERROR, line, column, message);
    errorToken.print();
}
