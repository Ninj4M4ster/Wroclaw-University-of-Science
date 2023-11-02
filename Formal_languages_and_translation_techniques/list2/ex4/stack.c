#include <stdio.h>

struct node {
    struct node* prev;
    int val;
};

struct node* push(struct node* last, int new_val) {
    struct node* new_node = malloc(sizeof(struct node));
    new_node->prev = last;
    new_node->val = new_val;
    return new_node;
}

struct node* delete_stack(struct node* stack) {
    if(stack == NULL) {
        return NULL;
    }
    while(stack != NULL) {
        struct node* tmp = stack;
        stack = stack->prev;
        free(tmp);
    }
    return NULL;
}

struct node* pop(struct node* stack) {
    if(stack == NULL)
        return NULL;
    struct node* tmp = stack;
    stack = stack->prev;
    free(tmp);
    return stack;
}