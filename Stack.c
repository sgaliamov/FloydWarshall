#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "Stack.h"

static const size_t MinCapacity = 1;
static const size_t DefaultCapacity = 256;

typedef struct Stack {
    StackItem * items;
    size_t capacity;
    size_t count;
} * PStack;

PStack stack_new(void) {
     const PStack stack = calloc(1, sizeof (struct Stack));

    stack_set_capacity(stack, DefaultCapacity);

    return stack;
}

void stack_free(PStack * const ppStack) {
    assert(ppStack);
    const PStack pStack = *ppStack;
    assert(pStack);
    assert(pStack->items);

    free(pStack->items);
    free(pStack);
    *ppStack = NULL;
}

size_t stack_get_count(const PStack stack) {
    assert(stack);

    return stack->count;
}

void stack_set_capacity(const PStack stack, const size_t capacity) {
    assert(stack);

    stack->capacity = capacity == 0 ? MinCapacity : capacity;

    stack->items = realloc(stack->items, sizeof (StackItem) * stack->capacity);
}

size_t stack_get_capacity(const PStack stack) {
    assert(stack);

    return stack->capacity;
}

StackItem stack_pop(const PStack stack) {
    assert(stack);

    if (stack->capacity >= stack->count * 4) {
        stack_set_capacity(stack, stack->capacity / 2);
    }

    return stack->count != 0
            ? stack->items[--stack->count]
            : NULL;
}

void stack_push(const PStack stack, StackItem item) {
    assert(stack);

    if (stack->count == stack->capacity) {
        stack_set_capacity(stack, stack->capacity * 2);
    }

    stack->items[stack->count] = item;
    stack->count++;
}

StackItem * stack_to_array(const PStack stack) {
    assert(stack);
    assert(stack->count);
    assert(stack->items);

    const size_t size = sizeof (StackItem) * stack->count;
    StackItem * items = malloc(size);
    memcpy(items, stack->items, size);

    return items;
}