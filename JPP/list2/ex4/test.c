#include <stdio.h>

struct dioph_result {
    int x;
    int y;
    int error_status;
};
extern unsigned int factorial(unsigned int);
extern unsigned int gcm(unsigned int a, unsigned int b);
extern struct dioph_result dioph(int a, int b, int c);
extern unsigned int factorialRecursive(unsigned int);
extern unsigned int gcmRecursive(unsigned int a, unsigned int b);
extern struct dioph_result diophRecursive(int a, int b, int c);

void iterativeLibTest() {
    printf("Testing iterative functions\n");
    int tests_passed = 1;

    printf("\nFactorial test\n");
    const unsigned int factorial_results[] = {
        1, 1, 2, 6, 24, 120, 720,
        5040, 40320, 362880, 3628800,
        39916800, 479001600
    };
    for(unsigned int i = 0; i < 12; i++) {
        if(factorial(i) != factorial_results[i]) {
            printf("Bad result for n = %d: got %u, expected %u\n", i, factorial(i), factorial_results[i]);
            tests_passed = 0;
        }
    }
    if(tests_passed == 1) {
        printf("Factorial tests passed.\n");
    }
    
    printf("\nGcm test\n");
    tests_passed = 1;
    if(gcm(1002, 1213) != 1) {
        printf("Bad result for a = 1002, b = 1213: got %u, expected %d\n", gcm(1002, 1213), 1);
        tests_passed = 0;
    }
    if(gcm(1002, 1152) != 6) {
        printf("Bad result for a = 1002, b = 1152: got %u, expected %d\n", gcm(1002, 1152), 6);
        tests_passed = 0;
    }
    if(gcm(69, 783255) != 3) {
        printf("Bad result for a = 69, b = 783255: got %u, expected %d\n", gcm(69, 783255), 3);
        tests_passed = 0;
    }
    if(gcm(28, 14) != 14) {
        printf("Bad result for a = 28, b = 14: got %u, expected %d\n", gcm(28, 14), 14);
        tests_passed = 0;
    }
    if(tests_passed == 1) {
        printf("Gcm tests passed.\n");
    }

    printf("\nDiophantive function tests\n");
    tests_passed = 1;
    struct dioph_result d_res = dioph(3, 5, 149);
    if(d_res.x != 298 || d_res.y != -149 || d_res.error_status != 0) {
        printf("Bad result for a = 3, b = 5, c = 149: got x = %d, y = %d, err_status = %d,", d_res.x, d_res.y, d_res.error_status);
        printf(" expected x = %d, y = %d, err_status = %d\n", 298, -149, 0);
        tests_passed = 0;
    }
    d_res = dioph(15, 26, 149);
    if(d_res.x != 1043 || d_res.y != -596 || d_res.error_status != 0) {
        printf("Bad result for a = 15, b = 26, c = 149: got x = %d, y = %d, err_status = %d,", d_res.x, d_res.y, d_res.error_status);
        printf(" expected x = %d, y = %d, err_status = %d\n", 1043, -596, 0);
        tests_passed = 0;
    }
    d_res = dioph(0, 26, 149);
    if(d_res.x != 0 || d_res.y != 0 || d_res.error_status != 2) {
        printf("Bad result for a = 0, b = 26, c = 149: got x = %d, y = %d, err_status = %d,", d_res.x, d_res.y, d_res.error_status);
        printf(" expected x = %d, y = %d, err_status = %d\n", 0, 0, 2);
        tests_passed = 0;
    }
    d_res = dioph(0, 0, 149);
    if(d_res.x != 0 || d_res.y != 0 || d_res.error_status != 1) {
        printf("Bad result for a = 0, b = 0, c = 149: got x = %d, y = %d, err_status = %d,", d_res.x, d_res.y, d_res.error_status);
        printf(" expected x = %d, y = %d, err_status = %d\n", 0, 0, 1);
        tests_passed = 0;
    }
    if(tests_passed == 1) {
        printf("Diophantive function tests passed.\n");
    }
}

void recursiveLibTest() {
    printf("Testing recursive functions\n");
    int tests_passed = 1;

    printf("\nFactorial test\n");
    const unsigned int factorial_results[] = {
        1, 1, 2, 6, 24, 120, 720,
        5040, 40320, 362880, 3628800,
        39916800, 479001600
    };
    for(unsigned int i = 0; i < 12; i++) {
        if(factorialRecursive(i) != factorial_results[i]) {
            printf("Bad result for n = %d: got %u, expected %u\n", i, factorialRecursive(i), factorial_results[i]);
            tests_passed = 0;
        }
    }
    if(tests_passed == 1) {
        printf("Factorial tests passed.\n");
    }
    
    printf("\nGcm test\n");
    tests_passed = 1;
    if(gcmRecursive(1002, 1213) != 1) {
        printf("Bad result for a = 1002, b = 1213: got %u, expected %d\n", gcmRecursive(1002, 1213), 1);
        tests_passed = 0;
    }
    if(gcmRecursive(1002, 1152) != 6) {
        printf("Bad result for a = 1002, b = 1152: got %u, expected %d\n", gcmRecursive(1002, 1152), 6);
        tests_passed = 0;
    }
    if(gcmRecursive(69, 783255) != 3) {
        printf("Bad result for a = 69, b = 783255: got %u, expected %d\n", gcmRecursive(69, 783255), 3);
        tests_passed = 0;
    }
    if(gcmRecursive(28, 14) != 14) {
        printf("Bad result for a = 28, b = 14: got %u, expected %d\n", gcmRecursive(28, 14), 14);
        tests_passed = 0;
    }
    if(tests_passed == 1) {
        printf("Gcm tests passed.\n");
    }

    printf("\nDiophantive function tests\n");
    tests_passed = 1;
    struct dioph_result d_res = diophRecursive(3, 5, 149);
    if(d_res.x != 298 || d_res.y != -149 || d_res.error_status != 0) {
        printf("Bad result for a = 3, b = 5, c = 149: got x = %d, y = %d, err_status = %d,", d_res.x, d_res.y, d_res.error_status);
        printf(" expected x = %d, y = %d, err_status = %d\n", 298, -149, 0);
        tests_passed = 0;
    }
    d_res = diophRecursive(15, 26, 149);
    if(d_res.x != 1043 || d_res.y != -596 || d_res.error_status != 0) {
        printf("Bad result for a = 15, b = 26, c = 149: got x = %d, y = %d, err_status = %d,", d_res.x, d_res.y, d_res.error_status);
        printf(" expected x = %d, y = %d, err_status = %d\n", 1043, -596, 0);
        tests_passed = 0;
    }
    d_res = diophRecursive(0, 26, 149);
    if(d_res.x != 0 || d_res.y != 0 || d_res.error_status != 2) {
        printf("Bad result for a = 0, b = 26, c = 149: got x = %d, y = %d, err_status = %d,", d_res.x, d_res.y, d_res.error_status);
        printf(" expected x = %d, y = %d, err_status = %d\n", 0, 0, 2);
        tests_passed = 0;
    }
    d_res = diophRecursive(0, 0, 149);
    if(d_res.x != 0 || d_res.y != 0 || d_res.error_status != 1) {
        printf("Bad result for a = 0, b = 0, c = 149: got x = %d, y = %d, err_status = %d,", d_res.x, d_res.y, d_res.error_status);
        printf(" expected x = %d, y = %d, err_status = %d\n", 0, 0, 1);
        tests_passed = 0;
    }
    if(tests_passed == 1) {
        printf("Diophantive function tests passed.\n");
    }
}

int main() {
    iterativeLibTest();
    printf("\n");
    recursiveLibTest();
    return 0;
}
