#include "lib.c"
#include <stdio.h>

int main() {

    // for(int i = 0; i < 100; i++) {
    //     printf("res: %llu\n",silnia(i));
    // }
    struct dioph_res result = diophRecursive(3, 5, -149);
    printf("res: %lld, %lld\n",result.x, result.y);
    printf("Error status: %d\n", result.error_status);

}