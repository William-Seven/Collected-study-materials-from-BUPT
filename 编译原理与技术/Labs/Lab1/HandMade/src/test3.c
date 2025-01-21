/*
 * test3.c - This program contains several intentional lexical errors
 *           to test the error detection and recovery capabilities
 *           of the lexical analyzer.
 */

int main() {
    int number = 123;     // valid integer
    float pi = 3.14;      // valid float
    char ch = 'a';        // valid character constant
    char* str = "Hello";  // valid string literal

    /* Missing closing comment delimiter */
    int x = 10;
    /* This is a valid comment but it's incomplete
    *

    int y = 020; // valid
    char *z = "abcd";

    // Below are some lexical errors

    // Invalid: '09' is not a valid octal number
    int invalid_number = 09;
    
    // Invalid: too many characters in character constant
    char invalid_char = 'ab';  
    
    // Invalid: incomplete exponent part
    float invalid_float = 1.2e+;  

    // Invalid: '@' is not allowed in an identifier
    int incomplete_identifier = @var;  
    
    return 0;
}
