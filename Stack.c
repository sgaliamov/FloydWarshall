#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "Stack.h"

static const size_t MinCapacity = 1;
static const size_t DefaultCapacity = 256;

typedef struct stack_t {
    StackItem * items;
    size_t capacity;
    size_t count;
} * PStack;

static void stack_set_capacity(const PStack stack, const size_t capacity) {
    assert(stack);

    stack->capacity = capacity == 0 ? MinCapacity : capacity;

    stack->items = realloc(stack->items, sizeof (StackItem) * stack->capacity);
}

static PStack stack_new(void) {
    const PStack stack = calloc(1, sizeof (struct stack_t));

    stack_set_capacity(stack, DefaultCapacity);

    return stack;
}

static void stack_free(PStack const stack) {
    assert(stack);
    assert(stack->items);

    free(stack->items);
    free(stack);
}

static size_t stack_get_count(const PStack stack) {
    assert(stack);

    return stack->count;
}

static size_t stack_get_capacity(const PStack stack) {
    assert(stack);

    return stack->capacity;
}

static StackItem stack_pop(const PStack stack) {
    assert(stack);

    if (stack->capacity >= stack->count * 4) {
        stack_set_capacity(stack, stack->capacity / 2);
    }

    return stack->count != 0
            ? stack->items[--stack->count]
            : NULL;
}

static void stack_push(const PStack stack, StackItem item) {
    assert(stack);

    if (stack->count == stack->capacity) {
        stack_set_capacity(stack, stack->capacity * 2);
    }

    stack->items[stack->count] = item;
    stack->count++;
}

static StackItem * stack_to_array(const PStack stack) {
    assert(stack);
    assert(stack->count);
    assert(stack->items);

    const size_t size = sizeof (StackItem) * stack->count;
    StackItem * items = malloc(size);
    memcpy(items, stack->items, size);

    return items;
}

PStack_Behaviour Stack(void) {
    static struct Stack_Behaviour const behaviour = {
        .new = stack_new,
        .free = stack_free,
        .get_count = stack_get_count,
        .set_capacity = stack_set_capacity,
        .get_capacity = stack_get_capacity,
        .pop = stack_pop,
        .push = stack_push,
        .to_array = stack_to_array
    };

    return &behaviour;
}