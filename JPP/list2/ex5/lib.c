#include <stdio.h>

/**
 * @brief Structure for holding result of diophantine equation.
*/
struct dioph_res {
    int x;
    int y;
    int error_status;
};

/**
 * This function iteratively calculates factorial of given number.
 * 
 * @param arg Argument of factorial.
 * @return Factorial of given argument or 0, if factorial is not possible to calculate.
*/
unsigned int factorial(unsigned int arg) {
    unsigned long long result = 1;
    int it = 2;
    while(it <= arg && result * it > result) {
        result *= it;
        it++;
    }
    if(it <= arg) {
        return 0;
    }
    return result;
}

/**
 * This function iteratively calculates the greatest common measure of two given numbers.
 * 
 * @param a First number.
 * @param b Second number.
 * @return Greatest common measure of two given numbers.
*/
unsigned long long gcm(unsigned long long a, unsigned long long b) {
    unsigned long long help;
    while(b != 0) {
        help = a;
        a = b;
        b = help % b;
    }
    return a;
}

/**
 * This function iteratively finds the result of a diophantine equation of the following form:
 * ax + by = c.
 * 
 * @param a Value a in equation.
 * @param b Value b in equation.
 * @param c Value c in equation.
 * @return Structure holding result x and y of equation and error status. 
 *         If error status == 1 - two zeros for a and b were given and c is != 0. 
 *         If error status == 2 - there is no integral result available.
*/
struct dioph_res dioph(long long a, long long b, long long c) {
    struct dioph_res result;
    result.x = 0;
    result.y = 0;
    result.error_status = 0;
    int reversed = 0;
    unsigned long long a_p = (unsigned long long)(a < 0 ? a * -1 : a);
    unsigned long long b_p = (unsigned long long)(b < 0 ? b * -1 : b);
    unsigned long long d = gcm(a_p, b_p);
    if(d == 0) {  // a and b == 0
        if(c != 0)
            result.error_status = 1;
    } else if(c % (long long)d != 0) {  // no result available
        result.error_status = 2;
    } else {
        if(a < b) {
            long long p = a;
            a = b;
            b = p;
            reversed = 1;
        }
        long long x = 1;
        long long y = 0;
        if(b != 0) {  
            long long div_result;
            long long div_rest = 1;
            long long x_temp = 0;
            long long y_temp = 1;
            while(div_rest != 0) {  // extended euklides algorithm
                div_result = a / b;
                div_rest = a % b;
                a = b;
                b = div_rest;
                
                long long helper_x_temp = x_temp;
                long long helper_y_temp = y_temp;
                x_temp = x - div_result * x_temp;
                y_temp = y - div_result * y_temp;
                x = helper_x_temp;
                y = helper_y_temp;
            }
        }
        if(reversed == 1) {
            result.x = y;
            result.y = x;
        } else {
            result.x = x;
            result.y = y;
        }
        long long s = c / d;
        result.x *= s;
        result.y *= s;
    }
    return result;
}

/**
 * This function recursively calculates factorial of given number.
 * 
 * @param arg Argument of factorial.
 * @return Factorial of given argument or 0, if factorial is not possible to calculate.
*/
unsigned long long factorialRecursive(unsigned int arg) {
    if(arg <= 1)
        return 1;
    unsigned long long current_result = factorialRecursive(arg - 1);
    if(current_result * arg <= current_result) {
        return 0;
    }
    return current_result * arg;
}

/**
 * This function recursively calculates the greatest common measure of two given numbers.
 * 
 * @param a First number.
 * @param b Second number.
 * @return Greatest common measure of two given numbers.
*/
unsigned long long gcmRecursive(unsigned long long a, unsigned long long b) {
    if(b == 0)
        return a;
    return gcmRecursive(b, a % b);
}

/**
 * This is a helper function. It implements recursive extended euclides algorithm.
 * It finds results of following equation: ax + by = gcm(a, b)
 * 
 * @param a Value of a.
 * @param b Value of b.
 * @param x Current result of x.
 * @param y Current result of y.
 * @param x_temp Temporary value of x.
 * @param y_temp Temporary value of y.
*/
struct dioph_res recursiveExtendedEuclides(long long a, 
                               long long b, 
                               long long x, 
                               long long y, 
                               long long x_temp, 
                               long long y_temp) {
    struct dioph_res result;
    result.error_status = 0;
    result.x = x;
    result.y = y;
    if(b != 0) {
        long long div_result = a / b;
        result = recursiveExtendedEuclides(b, a%b, x_temp, y_temp, x - div_result * x_temp, y - div_result * y_temp);
    }
    return result;
}

/**
 * This function recursively finds the result of a diophantine equation of the following form:
 * ax + by = c.
 * 
 * @param a Value a in equation.
 * @param b Value b in equation.
 * @param c Value c in equation.
 * @return Structure holding result x and y of equation and error status. 
 *         If error status == 1 - two zeros for a and b were given and c is != 0. 
 *         If error status == 2 - there is no integral result available.
*/
struct dioph_res diophRecursive(long long a, long long b, long long c) {
    struct dioph_res result;
    result.x = 0;
    result.y = 0;
    result.error_status = 0;
    int reversed = 0;
    unsigned long long a_p = (unsigned long long)(a < 0 ? a * -1 : a);
    unsigned long long b_p = (unsigned long long)(b < 0 ? b * -1 : b);
    unsigned long long d = gcm(a_p, b_p);
    if(d == 0) {  // a and b == 0
        if(c != 0)
            result.error_status = 1;
    } else if(c % (long long)d != 0) {  // no result available
        result.error_status = 2;
    } else {
        if(a < b) {
            long long p = a;
            a = b;
            b = p;
            reversed = 1;
        }
        long long x = 1;
        long long y = 0;
        if(b != 0) {
            long long x_temp = 0;
            long long y_temp = 1;
            result = recursiveExtendedEuclides(a, b, x, y, x_temp, y_temp);
        }
        if(reversed == 1) {
            long long tmp = result.x;
            result.x = result.y;
            result.y = tmp;
        }
        long long s = c / d;
        result.x *= s;
        result.y *= s;
    }
    return result;
}
