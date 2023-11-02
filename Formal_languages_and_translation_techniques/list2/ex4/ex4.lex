%{
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "stack.c"
int yywrap();
int yylex();
struct node* stack = NULL;
int current_read_val = 0;
int space_occured = 0;
int error_status = 0;
int digit_input = 0;
int sign_input = 1;
%}
%x ERROR_STATUS

DIGIT [0-9]
SPACE [ ]
PLUS \+
MINUS \-
MINUS_DIGIT \-[0-9]
MULT \*
DIV \/
MOD \%
POW \^
OTHERS .

%%

{DIGIT} {
    current_read_val = current_read_val * 10 + atoi(yytext);
    space_occured = 0;
    digit_input = 1;
    }
{MINUS_DIGIT} {
    current_read_val = current_read_val * 10 + abs(atoi(yytext));
    space_occured = 0;
    digit_input = 1;
    sign_input = -1;
}
{SPACE} {
    if(space_occured == 0 && digit_input == 1) {
        stack = push(stack, current_read_val * sign_input); 
        current_read_val = 0;
        space_occured = 1;
        }
    digit_input = 0;
    sign_input = 1;
    }
{PLUS} {
    if(digit_input == 1) {
        stack = push(stack, current_read_val); 
        current_read_val = 0;
        space_occured = 1;
        digit_input = 0;
    }
    if(error_status == 0) {
        if(stack == NULL) {
            printf("Blad: za mala liczba argumentow\n");
            error_status = 1;
        } else {
            int a = stack->val;
            stack = pop(stack);
            if(stack == NULL) {
                printf("Blad: za mala liczba argumentow\n");
                error_status = 1;
            } else {
                int b = stack->val;
                stack = pop(stack);
                int result = b + a;
                stack = push(stack, result);
            }
        }
    }
}
{MINUS} {
    if(digit_input == 1) {
        stack = push(stack, current_read_val); 
        current_read_val = 0;
        space_occured = 1;
        digit_input = 0;
    }
    if(error_status == 0) {
        if(stack == NULL) {
            printf("Blad: za mala liczba argumentow\n");
            error_status = 1;
        } else {
            int a = stack->val;
            stack = pop(stack);
            if(stack == NULL) {
                printf("Blad: za mala liczba argumentow\n");
                error_status = 1;
            } else {
                int b = stack->val;
                stack = pop(stack);
                int result = b - a;
                stack = push(stack, result);
            }
        }
    }
}
{MULT} {
    if(digit_input == 1) {
        stack = push(stack, current_read_val); 
        current_read_val = 0;
        space_occured = 1;
        digit_input = 0;
    }
    if(error_status == 0) {
        if(stack == NULL) {
            printf("Blad: za mala liczba argumentow\n");
            error_status = 1;
        } else {
            int a = stack->val;
            stack = pop(stack);
            if(stack == NULL) {
                printf("Blad: za mala liczba argumentow\n");
                error_status = 1;
            } else {
                int b = stack->val;
                stack = pop(stack);
                int result = b * a;
                stack = push(stack, result);
            }
        }
    }
}
{DIV} {
    if(digit_input == 1) {
        stack = push(stack, current_read_val); 
        current_read_val = 0;
        space_occured = 1;
        digit_input = 0;
    }
    if(error_status == 0) {
        if(stack == NULL) {
            printf("Blad: za mala liczba argumentow\n");
            error_status = 1;
        } else {
            int a = stack->val;
            stack = pop(stack);
            if(stack == NULL) {
                printf("Blad: za mala liczba argumentow\n");
                error_status = 1;
            } else {
                int b = stack->val;
                if(a == 0) {
                    printf("Blad: nie mozna dzielic przez zero\n");
                    error_status = 1;
                } else {
                    stack = pop(stack);
                    int result = b / a;
                    stack = push(stack, result);
                }
            }
        }
    }
}
{MOD} {
    if(digit_input == 1) {
        stack = push(stack, current_read_val); 
        current_read_val = 0;
        space_occured = 1;
        digit_input = 0;
    }
    if(error_status == 0) {
        if(stack == NULL) {
            printf("Blad: za mala liczba argumentow\n");
            error_status = 1;
        } else {
            int a = stack->val;
            stack = pop(stack);
            if(stack == NULL) {
                printf("Blad: za mala liczba argumentow\n");
                error_status = 1;
            } else {
                int b = stack->val;
                if(a == 0) {
                    printf("Blad: nie mozna obliczyc reszty z dzielenia przez zero\n");
                    error_status = 1;
                } else {
                    stack = pop(stack);
                    int result = b % a;
                    stack = push(stack, result);
                }
            }
        }
    }
}
{POW} {
    if(digit_input == 1) {
        stack = push(stack, current_read_val); 
        current_read_val = 0;
        space_occured = 1;
        digit_input = 0;
    }
    if(error_status == 0) {
        if(stack == NULL) {
            printf("Blad: za mala liczba argumentow\n");
            error_status = 1;
        } else {
            int a = stack->val;
            stack = pop(stack);
            if(stack == NULL) {
                printf("Blad: za mala liczba argumentow\n");
                error_status = 1;
            } else {
                if(a < 0) {
                    printf("Blad: wykladnik potegi musi byc liczba nieujemna\n");
                    error_status = 1;
                } else {
                    int b = stack->val;
                    stack = pop(stack);
                    int result = pow(b, a);
                    stack = push(stack, result);
                }
            }
        }
    }
}
\n {
    if(error_status) {
        printf("");
    } else {
        if(stack == NULL) {
            printf("Blad: nie wprowadzono dzialania\n");
        } else {
            if(stack->prev != NULL) {
                printf("Blad: za mala liczba operatorow\n");
            } else {
                int result = stack->val;
                printf("= %d\n", result);
            }
        }
    }
    stack = delete_stack(stack);
    current_read_val = 0;
    space_occured = 0;
    error_status = 0;
    digit_input = 0;
}
{OTHERS} {
    printf("Blad: zly symbol \"%s\"\n", yytext);
    error_status = 1;
}

%%

int yywrap() {
    return 1;
}

int main(int argc, char* argv[]) {
    yylex();
    stack = delete_stack(stack);
}