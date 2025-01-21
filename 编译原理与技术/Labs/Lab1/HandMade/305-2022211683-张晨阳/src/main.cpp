#include <fstream>
#include <sstream>
#include "mylex.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile) {
        std::cerr << "Error: cannot open file " << argv[1] << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    Lexer lexer(buffer.str());

    Token token = lexer.getNextToken();
    while (token.getType() != T_EOF) {
        token.print();
        token = lexer.getNextToken();
    }

    lexer.printStatistics();  // 输出统计信息

    return 0;
}
