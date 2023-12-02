%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define YYDEBUG 1
#define BODY 1234577
int yylex();
void yyerror();
int operator_occured = 0;
int unary_operator = 0;
int number_input = 0;
int input_start = 0;

int error_code = 0;

typedef struct stack {
    char operator;
    int operator_set;
    long long int val;
    struct stack * prev;
} Stack;

typedef struct queue {
    char operator;
    int operator_set;
    long long int val;
    struct queue * next;
} Queue;

Queue* queue = NULL;
Stack* operator_stack = NULL;

void handlePlus();
void handleMinus();
void handleMult();
void handleDiv();
void handleOpen();
void handleClose();
void handlePower();
void calculateResult();
void handleNumber(long long int num);
void reset();

Queue* insert_int(Queue* queue, long long int val);
Queue* insert_char(Queue* queue, char val);
Queue* remove_from_queue(Queue* queue);
Queue* clear_queue(Queue* queue);

Stack* put_int(Stack* stack, long long int val);
Stack* put_char(Stack* stack, char val);
Stack* pop_stack(Stack* stack);
Stack* clear_stack(Stack* stack);

// yydebug = 1;
%}

%union {
    long long int llival;
    }
%token<llival> INTEGER

%%


program 
: sign program
| sign
;

sign
: '#' comment
| '\\' '\n'
| '+' {if(error_code == 0) handlePlus();}
| '-' {if(error_code == 0) handleMinus();}
| '*' {if(error_code == 0) handleMult();}
| '/' {if(error_code == 0) handleDiv();}
| '(' {if(error_code == 0) handleOpen();}
| ')' {if(error_code == 0) handleClose();}
| '^' {if(error_code == 0) handlePower();}
| '\n' {calculateResult();}
| INTEGER {if(error_code == 0) handleNumber($1);}
;

comment
: INTEGER comment
| '\\' '\n' comment
| '\n' {if(input_start) printf("Blad\n"); reset(); }
;

%%

void yyerror() {
    error_code = 1;
}

void handlePlus() {
    operator_occured = 1;
    unary_operator = 0;
    input_start = 1;
    if(operator_stack == NULL) {
        operator_stack = put_char(operator_stack, '+');
    } else {
        while(operator_stack != NULL && operator_stack->operator != '(') {
            queue = insert_char(queue, operator_stack->operator);
            operator_stack = pop_stack(operator_stack);
        }
        operator_stack = put_char(operator_stack, '+');
    }
}

void handleMinus() {
    if(operator_occured == 1 || number_input == 0) {
        unary_operator = 1;
        return;
    } else {
        operator_occured = 1;
        input_start = 1;
    }
    if(operator_stack == NULL) {
        operator_stack = put_char(operator_stack, '-');
    } else {
        while(operator_stack != NULL && operator_stack->operator != '(') {
            queue = insert_char(queue, operator_stack->operator);
            operator_stack = pop_stack(operator_stack);
        }
        operator_stack = put_char(operator_stack, '-');
    }
}

void handleMult() {
    input_start = 1;
    operator_occured = 1;
    unary_operator = 0;
    if(operator_stack == NULL) {
        operator_stack = put_char(operator_stack, '*');
    } else {
        if(operator_stack->operator == '+' | operator_stack->operator == '-') {
            operator_stack = put_char(operator_stack, '*');
        } else {
            while(operator_stack != NULL && operator_stack->operator != '+' &&
             operator_stack->operator != '-' && operator_stack->operator != '(') {
                queue = insert_char(queue, operator_stack->operator);
                operator_stack = pop_stack(operator_stack);
            }
            operator_stack = put_char(operator_stack, '*');
        }
    }
}

void handleDiv() {
    input_start = 1;
    operator_occured = 1;
    unary_operator = 0;
    if(operator_stack == NULL) {
        operator_stack = put_char(operator_stack, '/');
    } else {
        if(operator_stack->operator == '+' | operator_stack->operator == '-') {
            operator_stack = put_char(operator_stack, '/');
        } else {
            while(operator_stack != NULL && operator_stack->operator != '+' &&
             operator_stack->operator != '-' && operator_stack->operator != '(') {
                queue = insert_char(queue, operator_stack->operator);
                operator_stack = pop_stack(operator_stack);
            }
            operator_stack = put_char(operator_stack, '/');
        }
    }
}

void handleOpen() {
    input_start = 1;
    operator_occured = 1;
    unary_operator = 0;
    operator_stack = put_char(operator_stack, '(');
}

void handleClose() {
    input_start = 1;
    operator_occured = 1;
    unary_operator = 0;
    if(operator_stack == NULL) {
        error_code = 1;
        return;
    }
    while(operator_stack != NULL && operator_stack->operator != '(') {
        queue = insert_char(queue, operator_stack->operator);
        operator_stack = pop_stack(operator_stack);
    }
    if(operator_stack == NULL) {
        error_code = 1;
        return;
    }
    operator_stack = pop_stack(operator_stack);
}   

void handlePower() {
    input_start = 1;
    operator_occured = 1;
    unary_operator = 0;
    if(operator_stack == NULL) {
        operator_stack = put_char(operator_stack, '^');
    } else {
        if(operator_stack->operator != '^') {
            operator_stack = put_char(operator_stack, '^');
        } else {
            queue = insert_char(queue, operator_stack->operator);
            operator_stack = pop_stack(operator_stack);
            operator_stack = put_char(operator_stack, '^');
        }
    }
}

void calculateResult() {
    if(error_code != 0) {
        printf("Blad\n");
        reset();
        return;
    }
    while(operator_stack != NULL) {
        queue = insert_char(queue, operator_stack->operator);
        operator_stack = pop_stack(operator_stack);
    }
    Queue* tmp = queue;
    long long int result;
    if(tmp != NULL && error_code == 0) {
        Stack* calculations_stack = NULL;
        while(tmp != NULL && error_code == 0) {
            if(tmp->operator_set == 0) {
                calculations_stack = put_int(calculations_stack, tmp->val);
            } else {
                if(tmp->operator == '+') {
                    if(calculations_stack == NULL) {
                        error_code = 1;
                    } else {
                        long long int a = calculations_stack->val;
                        calculations_stack = pop_stack(calculations_stack);
                        if(calculations_stack == NULL) {
                            error_code = 1;
                        } else {
                            long long int b = calculations_stack->val;
                            calculations_stack = pop_stack(calculations_stack);
                            a = (a + b) % BODY;
                            calculations_stack = put_int(calculations_stack, a);
                        }
                    }
                } else if(tmp->operator == '-') {
                    if(calculations_stack == NULL) {
                        error_code = 1;
                    } else {
                        long long int a = calculations_stack->val;
                        calculations_stack = pop_stack(calculations_stack);
                        if(calculations_stack == NULL) {
                            error_code = 1;
                        } else {
                            long long int b = calculations_stack->val;
                            calculations_stack = pop_stack(calculations_stack);
                            a = (b - a) % BODY;
                            while(a < 0) {
                                a += BODY;
                            }
                            calculations_stack = put_int(calculations_stack, a);
                        }
                    }
                } else if(tmp->operator == '*') {
                    if(calculations_stack == NULL) {
                        error_code = 1;
                    } else {
                        long long int a = calculations_stack->val;
                        calculations_stack = pop_stack(calculations_stack);
                        if(calculations_stack == NULL) {
                            error_code = 1;
                        } else {
                            long long int b = calculations_stack->val;
                            calculations_stack = pop_stack(calculations_stack);
                            a = (a * b) % BODY;
                            calculations_stack = put_int(calculations_stack, a);
                        }
                    }
                } else if(tmp->operator == '/') {
                    if(calculations_stack == NULL) {
                        error_code = 1;
                    } else {
                        long long int a = calculations_stack->val;
                        calculations_stack = pop_stack(calculations_stack);
                        if(calculations_stack == NULL) {
                            error_code = 1;
                        } else {
                            long long int b = calculations_stack->val;
                            calculations_stack = pop_stack(calculations_stack);
                            long long int rev = 1;
                            for(rev; (rev * a) % BODY != 1; rev++);
                            a = (b * rev) % BODY;
                            calculations_stack = put_int(calculations_stack, a);
                        }
                    }
                } else {  // tmp->operator == '^'
                    if(calculations_stack == NULL) {
                        error_code = 1;
                    } else {
                        long long int a = calculations_stack->val;
                        calculations_stack = pop_stack(calculations_stack);
                        if(calculations_stack == NULL) {
                            error_code = 1;
                        } else {
                            long long int b = calculations_stack->val;
                            calculations_stack = pop_stack(calculations_stack);
                            long long int multiplier = b;
                            for(int i = 0; i < a - 1; i++) {
                                b *= multiplier;
                                b %= BODY;
                            }
                            if(a == 0)
                                b = 1;
                            calculations_stack = put_int(calculations_stack, b);
                        }
                    }
                }
            }
            tmp = tmp->next;
        }
        if(error_code == 0) {
            if(calculations_stack->prev != NULL)
                error_code = 1;
            else
                result = calculations_stack->val;
        }
        calculations_stack = clear_stack(calculations_stack);
    }
    tmp = queue;
    while(tmp != NULL && error_code == 0) {
        if(tmp->operator_set == 1) {
            printf("%c", tmp->operator);
        } else {
            printf("%lld", tmp->val);
        }
        printf(" ");
        tmp = tmp->next;
    }
    if(error_code == 0) {
        printf("\nWynik: %lld", result);
    } else {
        printf("\nBlad");
    }
    printf("\n");
    reset();
}

void handleNumber(long long int num) {
    number_input = 1;
    input_start = 1;
    if(unary_operator) {
        num *= -1;
        while(num < 0) {
            num += BODY;
        }
    }
    queue = insert_int(queue, num % BODY);
    operator_occured = 0;
    unary_operator = 0;
}

void reset() {
    queue = clear_queue(queue);
    operator_stack = clear_stack(operator_stack);
    error_code = 0;
    number_input = 0;
    operator_occured = 0;
    unary_operator = 0;
    input_start = 0;
}

// Functions for handling queue structure

Queue* insert_int(Queue* queue, long long int val) {
    Queue* new_ptr = (Queue*)malloc(sizeof(Queue));
    new_ptr->val = val;
    new_ptr->operator_set = 0;
    new_ptr->next = NULL;
    if(queue == NULL) {
        return new_ptr;
    }
    Queue* tmp = queue;
    while(tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = new_ptr;
    return queue;
}

Queue* insert_char(Queue* queue, char val) {
    Queue* new_ptr = (Queue*)malloc(sizeof(Queue));
    new_ptr->operator = val;
    new_ptr->operator_set = 1;
    new_ptr->next = NULL;
    if(queue == NULL) {
        return new_ptr;
    }
    Queue* tmp = queue;
    while(tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = new_ptr;
    return queue;
}

Queue* remove_from_queue(Queue* queue) {
    if(queue == NULL)
        return NULL;
    Queue* next = queue->next;
    queue->next = NULL;
    free(queue);
    queue = NULL;
    return next;
}

Queue* clear_queue(Queue* queue) {
    while(queue != NULL) {
        Queue* curr = queue;
        queue = queue->next;
        curr->next = NULL;
        free(curr);
    }
    return NULL;
}

// Functions for handling stack structure

Stack* put_int(Stack* stack, long long int val) {
    Stack* new_ptr = (Stack*)malloc(sizeof(Stack));
    new_ptr->val = val;
    new_ptr->operator_set = 0;
    new_ptr->prev = stack;
    return new_ptr;
}

Stack* put_char(Stack* stack, char val) {
    Stack* new_ptr = (Stack*)malloc(sizeof(Stack));
    new_ptr->operator = val;
    new_ptr->operator_set = 1;
    new_ptr->prev = stack;
    return new_ptr;
}

Stack* pop_stack(Stack* stack) {
    if(stack == NULL)
        return NULL;
    Stack* prev = stack->prev;
    stack->prev = NULL;
    free(stack);
    stack = NULL;
    return prev;
}

Stack* clear_stack(Stack* stack) {
    while(stack != NULL) {
        Stack* curr = stack;
        stack = stack->prev;
        curr->prev = NULL;
        free(curr);
    }
    return NULL;
}


// int main(int argc, char* argv[]) {
//     yyparse();
//     return 0;
// }