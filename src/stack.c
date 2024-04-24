#include "stack.h"

stack stack_create(void){
    stack new_stack;
    new_stack.size = 0;
    new_stack.head = NULL;
}

stack_node* _stk_create_node(stack_t _val){
    stack_node* new_node = (stack_node*)malloc(sizeof(stack_node));
    new_node->next = NULL;
    new_node->val = _val;
    return new_node;
}

void stack_push(stack *_stack, stack_t val){
    stack_node* new_node = _stk_create_node(val);
    new_node->next = _stack->head;
    _stack->head = new_node;
    _stack->size++;
}

void stack_pop(stack *_stack){
    if(_stack->size > 0){
        stack_node* temp = _stack->head;
        _stack->head = _stack->head->next;
        free(temp);
        _stack->size--;
    }
}

int stack_size(const stack _stack){
    return _stack.size;
}

void stack_clear(stack *_stack){
    while(_stack->size > 0){
        stack_pop(_stack);
    }
}