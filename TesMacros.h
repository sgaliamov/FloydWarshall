#pragma once

#define TEST_INIT(name) \
    static const char * const __testSuiteName = name; \
    static const char * __testName = NULL;

#define TEST_BEGIN \
    int main() { \
    printf("\n%%SUITE_STARTING%% %s\n", __testSuiteName); \
    printf("%%SUITE_STARTED%%\n");

#define TEST_END printf("\n%%SUITE_FINISHED%% time=0\n"); \
    }

#define TEST(test) \
    printf("\n%%TEST_STARTED%% "#test" (%s)\n", __testSuiteName); \
    __testName = #test; \
    test(); \
    printf("%%TEST_FINISHED%% time=0 "#test" (%s) \n", __testSuiteName);

#define TEST_FAIL(message) \
    printf("%%TEST_FAILED%% time=0 testname=%s (%s) message=%s\n", \
        __testName ,__testSuiteName, message);

#define TEST_ASSERT(assert) \
    if(!(assert)) { TEST_FAIL(#assert); }
