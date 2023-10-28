#include <iostream>


//! Another doxygen comment
//! Sample line
void print_status(std::string status) {
    std::cout << status << std::endl;
}
 
// random comment  // another comment in same line 

/// @brief Check if value is negative  // comment inside doxygen 
/// @param val Value to be checked
/// @return Is the given value negative?
bool isNegative(int val) {
    return val < 0;
}

/*!
Diffrent doxygen comment
*/
int sum(int a, int b) {
    return a + b;  // comment next to code
}

/**
 * Doxygen comment
*/
int main() {
    // one line comment
    std::string fake_string = " // comment in string";
    char c = '//fake_char';
    /* multiline comment
        abc test
    */
}

// comment \
with continuation in another line