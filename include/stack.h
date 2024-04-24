#ifndef _STACK_H_
#define _STACK_H_

#ifndef stack_t
#define stack_t int
#endif

#include "util.h"

typedef struct stack_node{
    stack_t val;
    struct stack_node* next;
}stack_node;

typedef struct{
    stack_node* head;
    int size;
}stack;

stack stack_create(void);
stack_node* _stk_create_node(stack_t _val);
void stack_push(stack *_stack, stack_t val);
void stack_pop(stack *_stack);
int stack_size(const stack _stack);
void stack_clear(stack *_stack);

#endif // stack.h