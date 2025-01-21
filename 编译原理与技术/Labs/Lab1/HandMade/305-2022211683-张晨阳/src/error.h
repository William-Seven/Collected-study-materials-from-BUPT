#ifndef ERROR_H
#define ERROR_H

#include <string>
#include "token.h"

class ErrorHandler {
   public:
    static void reportError(int line, int column, const std::string& message);
};

#endif
