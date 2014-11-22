#include <stdio.h>
#include <stdlib.h>

#include "TesMacros.h"
#include "Stack.h"

TEST_INIT("Stack Tests")

void Test_Stack_PushPop() {
    const unsigned count = 5;
    PStack stack = stack_new();
    stack_set_capacity(stack, count);

    for (unsigned i = 0; i < count; i++) {
        stack_push(stack, (StackItem) i);
    }

    TEST_ASSERT(stack_get_count(stack) == count)

    for (unsigned i = 1; i <= count; i++) {
        unsigned item = (unsigned) stack_pop(stack);
        TEST_ASSERT(item == (count - i));
    }

    stack_free(&stack);
}

void Test_Stack_IncreaseCapacity() {
    PStack stack = stack_new();
    stack_set_capacity(stack, 3);
    unsigned counter = 0;

    for (unsigned i = 0; i < 3; i++) {
        stack_push(stack, (StackItem) counter++);
    }
    TEST_ASSERT(stack_get_capacity(stack) == 3);

    stack_push(stack, (StackItem) counter++);
    TEST_ASSERT(stack_get_capacity(stack) == 6);

    for (unsigned i = 0; i < 5; i++) {
        stack_push(stack, (StackItem) counter++);
    }
    TEST_ASSERT(stack_get_capacity(stack) == 12);

    while (stack_get_count(stack)) {
        unsigned item = (unsigned) stack_pop(stack);
        TEST_ASSERT(item == --counter);
    }

    TEST_ASSERT(counter == 0);

    stack_free(&stack);
}

void Test_Stack_DecreaseCapacity() {
    PStack stack = stack_new();
    stack_set_capacity(stack, 13);

    stack_pop(stack);
    TEST_ASSERT(stack_get_capacity(stack) == 6);

    stack_pop(stack);
    TEST_ASSERT(stack_get_capacity(stack) == 3);

    stack_pop(stack);
    TEST_ASSERT(stack_get_capacity(stack) == 1);

    stack_pop(stack);
    TEST_ASSERT(stack_get_capacity(stack) == 1);

    stack_free(&stack);
}

void Test_Stack_PopOnEmpty() {
    PStack stack = stack_new();
    stack_set_capacity(stack, 1);

    StackItem item = stack_pop(stack);

    TEST_ASSERT(stack_get_capacity(stack));
    TEST_ASSERT(item == NULL);

    stack_free(&stack);
}

void Test_Stack_Empty() {
    PStack stack = stack_new();
    stack_set_capacity(stack, 10);

    TEST_ASSERT(stack_get_count(stack) == 0);

    stack_push(stack, NULL);

    TEST_ASSERT(stack_get_count(stack) != 0);

    stack_pop(stack);

    TEST_ASSERT(stack_get_count(stack) == 0);

    stack_free(&stack);
}

TEST_BEGIN

TEST(Test_Stack_PushPop)
TEST(Test_Stack_IncreaseCapacity)
TEST(Test_Stack_DecreaseCapacity)
TEST(Test_Stack_PopOnEmpty)
TEST(Test_Stack_Empty)

TEST_END