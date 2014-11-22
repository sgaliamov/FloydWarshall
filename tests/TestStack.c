#include <stdio.h>
#include <stdlib.h>

#include "TesMacros.h"
#include "Stack.h"

TEST_INIT("Stack Tests")

void Test_Stack_PushPop() {
    const unsigned count = 5;
    PStack stack = Stack()->new();
    Stack()->set_capacity(stack, count);

    for (unsigned i = 0; i < count; i++) {
        Stack()->push(stack, (StackItem) i);
    }

    TEST_ASSERT(Stack()->get_count(stack) == count)

    for (unsigned i = 1; i <= count; i++) {
        unsigned item = (unsigned) Stack()->pop(stack);
        TEST_ASSERT(item == (count - i));
    }

    Stack()->free(stack);
}

void Test_Stack_IncreaseCapacity() {
    PStack stack = Stack()->new();
    Stack()->set_capacity(stack, 3);
    unsigned counter = 0;

    for (unsigned i = 0; i < 3; i++) {
        Stack()->push(stack, (StackItem) counter++);
    }
    TEST_ASSERT(Stack()->get_capacity(stack) == 3);

    Stack()->push(stack, (StackItem) counter++);
    TEST_ASSERT(Stack()->get_capacity(stack) == 6);

    for (unsigned i = 0; i < 5; i++) {
        Stack()->push(stack, (StackItem) counter++);
    }
    TEST_ASSERT(Stack()->get_capacity(stack) == 12);

    while (Stack()->get_count(stack)) {
        unsigned item = (unsigned) Stack()->pop(stack);
        TEST_ASSERT(item == --counter);
    }

    TEST_ASSERT(counter == 0);

    Stack()->free(stack);
}

void Test_Stack_DecreaseCapacity() {
    PStack stack = Stack()->new();
    Stack()->set_capacity(stack, 13);

    Stack()->pop(stack);
    TEST_ASSERT(Stack()->get_capacity(stack) == 6);

    Stack()->pop(stack);
    TEST_ASSERT(Stack()->get_capacity(stack) == 3);

    Stack()->pop(stack);
    TEST_ASSERT(Stack()->get_capacity(stack) == 1);

    Stack()->pop(stack);
    TEST_ASSERT(Stack()->get_capacity(stack) == 1);

    Stack()->free(stack);
}

void Test_Stack_PopOnEmpty() {
    PStack stack = Stack()->new();
    Stack()->set_capacity(stack, 1);

    StackItem item = Stack()->pop(stack);

    TEST_ASSERT(Stack()->get_capacity(stack));
    TEST_ASSERT(item == NULL);

    Stack()->free(stack);
}

void Test_Stack_Empty() {
    PStack stack = Stack()->new();
    Stack()->set_capacity(stack, 10);

    TEST_ASSERT(Stack()->get_count(stack) == 0);

    Stack()->push(stack, NULL);

    TEST_ASSERT(Stack()->get_count(stack) != 0);

    Stack()->pop(stack);

    TEST_ASSERT(Stack()->get_count(stack) == 0);

    Stack()->free(stack);
}

TEST_BEGIN

TEST(Test_Stack_PushPop)
TEST(Test_Stack_IncreaseCapacity)
TEST(Test_Stack_DecreaseCapacity)
TEST(Test_Stack_PopOnEmpty)
TEST(Test_Stack_Empty)

TEST_END