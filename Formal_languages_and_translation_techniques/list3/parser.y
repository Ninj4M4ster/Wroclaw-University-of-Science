%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define YYDEBUG 1
int yylex();
void yyerror(char* );
int operator_occured = 0;
int unary_operator = 0;

int error_code = 0;

typedef struct stack {
    char operator;
    struct stack * prev;
} Stack;

typedef struct queue {
    char operator;
    int operator_set;
    int val;
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
void handleNumber(int num);

Queue* insert_int(Queue* queue, int val);
Queue* insert_char(Queue* queue, char val);
Queue* remove_from_queue(Queue* queue);
Queue* clear_queue(Queue* queue);

Stack* put_char(Stack* stack, char val);
Stack* pop_stack(Stack* stack);
Stack* clear_stack(Stack* stack);

// yydebug = 1;
%}

%token INTEGER

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
| '\n'
;

%%

void yyerror(char *msg) {
    fprintf(stderr, "%s\n", msg);
}

void handlePlus() {
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
    operator_stack = put_char(operator_stack, '(');
}

void handleClose() {
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
        operator_stack = clear_stack(operator_stack);
        queue = clear_queue(queue);
        return;
    }
    while(operator_stack != NULL) {
        queue = insert_char(queue, operator_stack->operator);
        operator_stack = pop_stack(operator_stack);
    }
    Queue* tmp = queue;
    while(tmp != NULL) {
        if(tmp->operator_set == 1) {
            printf("%c", tmp->operator);
        } else {
            printf("%d", tmp->val);
        }
        printf(" ");
        tmp = tmp->next;
    }
    printf("\n");
    queue = clear_queue(queue);
    operator_stack = clear_stack(operator_stack);
    error_code = 0;
}

void handleNumber(int num) {
    queue = insert_int(queue, num);
}

// Functions for handling queue structure

Queue* insert_int(Queue* queue, int val) {
    Queue* new_ptr = malloc(sizeof(Queue));
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
    Queue* new_ptr = malloc(sizeof(Queue));
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

Stack* put_char(Stack* stack, char val) {
    Stack* new_ptr = malloc(sizeof(Stack));
    new_ptr->operator = val;
    if(stack != NULL) {
        new_ptr->prev = stack;
    }
    return new_ptr;
}

Stack* pop_stack(Stack* stack) {
    if(stack == NULL)
        return NULL;
    Stack* prev = stack->prev;
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