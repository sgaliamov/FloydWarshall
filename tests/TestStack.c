#include <stdio.h>
#include <stdlib.h>

#include "TesMacros.h"
#include "Stack.h"

TEST_INIT("Stack Tests")

void Test_Stack_PushPop() {
    const unsigned count = 5;
    PStack stack = Stack()->new(sizeof (unsigned));
    Stack()->set_capacity(stack, count);

    for (unsigned i = 0; i < count; i++) {
        Stack()->push(stack, &i);
    }

    TEST_ASSERT(Stack()->get_count(stack) == count)

    for (unsigned i = 1; i <= count; i++) {
        unsigned item = 0;
        Stack()->pop(stack, &item);
        TEST_ASSERT(item == (count - i));
    }

    Stack()->free(stack);
}

void Test_Stack_IncreaseCapacity() {
    PStack stack = Stack()->new(sizeof (unsigned));
    Stack()->set_capacity(stack, 3);
    unsigned counter = 0;

    for (unsigned i = 0; i < 3; i++) {
        counter++;
        Stack()->push(stack, &counter);
    }
    TEST_ASSERT(Stack()->get_capacity(stack) == 3);

    counter++;
    Stack()->push(stack, &counter);
    TEST_ASSERT(Stack()->get_capacity(stack) == 6);

    for (unsigned i = 0; i < 5; i++) {
        counter++;
        Stack()->push(stack, &counter);
    }
    TEST_ASSERT(Stack()->get_capacity(stack) == 12);

    while (Stack()->get_count(stack)) {
        unsigned item = 0;
        Stack()->pop(stack, &item);
        TEST_ASSERT(item == counter--);
    }

    TEST_ASSERT(counter == 0);

    Stack()->free(stack);
}

void Test_Stack_DecreaseCapacity() {
    int dummy = 0;
    PStack stack = Stack()->new(sizeof (dummy));
    Stack()->set_capacity(stack, 13);

    Stack()->pop(stack, &dummy);
    TEST_ASSERT(Stack()->get_capacity(stack) == 6);

    Stack()->pop(stack, &dummy);
    TEST_ASSERT(Stack()->get_capacity(stack) == 3);

    Stack()->pop(stack, &dummy);
    TEST_ASSERT(Stack()->get_capacity(stack) == 1);

    Stack()->pop(stack, &dummy);
    TEST_ASSERT(Stack()->get_capacity(stack) == 1);

    Stack()->free(stack);
}

void Test_Stack_PopOnEmpty() {
    int dummy = 0;
    PStack stack = Stack()->new(sizeof (dummy));
    Stack()->set_capacity(stack, 1);

    bool result = Stack()->pop(stack, &dummy);

    TEST_ASSERT(Stack()->get_capacity(stack) != 0);
    TEST_ASSERT(!result);

    Stack()->free(stack);
}

void Test_Stack_Empty() {
    int dummy = 0;
    PStack stack = Stack()->new(sizeof (dummy));
    Stack()->set_capacity(stack, 10);

    TEST_ASSERT(Stack()->get_count(stack) == 0);

    Stack()->push(stack, &dummy);

    TEST_ASSERT(Stack()->get_count(stack) != 0);

    Stack()->pop(stack, &dummy);

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