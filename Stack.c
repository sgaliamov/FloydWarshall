#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "Stack.h"

static const size_t MinCapacity = 1;
static const size_t DefaultCapacity = 256;

typedef struct stack_t {
    size_t capacity;
    size_t count;
    unsigned item_size;
    PStackItem * items;
} * PStack;

static void stack_set_capacity(PStack const stack, size_t const capacity) {
    assert(stack);

    stack->capacity = capacity == 0 ? MinCapacity : capacity;

    stack->items = realloc(stack->items, stack->capacity * stack->item_size);
}

static PStack stack_new(unsigned const item_size) {
    PStack const stack = calloc(1, sizeof (struct stack_t));
    stack->item_size = item_size;

    stack_set_capacity(stack, DefaultCapacity);

    return stack;
}

static void stack_free(PStack const stack) {
    assert(stack);
    assert(stack->items);

    free(stack->items);
    free(stack);
}

static size_t stack_get_count(PStack const stack) {
    assert(stack);

    return stack->count;
}

static size_t stack_get_capacity(PStack const stack) {
    assert(stack);

    return stack->capacity;
}

static bool stack_pop(PStack const stack, PStackItem const out) {
    assert(stack);
    assert(out);

    if (stack->capacity >= stack->count * 4) {
        stack_set_capacity(stack, stack->capacity / 2);
    }

    if (stack->count == 0) {
        return false;
    }

    memcpy(out, &stack->items[--stack->count], stack->item_size);

    return true;
}

static void stack_push(PStack const stack, PStackItem const item) {
    assert(stack);
    assert(item);

    if (stack->count == stack->capacity) {
        stack_set_capacity(stack, stack->capacity * 2);
    }

    memcpy(&stack->items[stack->count++], item, stack->item_size);
}

static PStackItem * stack_to_array(PStack const stack) {
    assert(stack);
    assert(stack->count);
    assert(stack->items);

    const size_t size = stack->item_size * stack->count;
    PStackItem * const items = malloc(size);
    memcpy(items, stack->items, size);

    return items;
}

inline PStack_Behaviour Stack(void) {
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