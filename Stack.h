/* 
 * File:   Stack.h
 * Author: Administrator
 *
 * Created on November 4, 2014, 10:24 PM
 */

#ifndef STACK_H
#define	STACK_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct Stack * PStack;
    typedef void * StackItem;

    PStack stack_new(void);
    void stack_free(PStack * const stack);

    size_t stack_get_count(const PStack);
    void stack_set_capacity(const PStack, const size_t);
    size_t stack_get_capacity(const PStack);
    StackItem stack_pop(const PStack);
    void stack_push(const PStack, StackItem);
    StackItem* stack_to_array(const PStack);

#ifdef	__cplusplus
}
#endif

#endif	/* STACK_H */

