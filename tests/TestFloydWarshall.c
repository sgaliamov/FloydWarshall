#include <stdio.h>
#include <stdlib.h>

#include "TesMacros.h"
#include "FloydWarshallFile.h"

TEST_INIT("FloydWarshall Build Tests")

void Test_FloydWarshall_Build_Simple() {

    PFloydWarshallData data = fw_load_graph("tests/test-simple.grh");

    fw_build(data);

    TEST_ASSERT(fw_get_dist(data, 0, 3) == 0);
    TEST_ASSERT(fw_get_next(data, 0, 3) == 1);
    TEST_ASSERT(fw_get_next(data, 1, 3) == 2);
    TEST_ASSERT(fw_get_next(data, 2, 3) == 3);
}

void Test_FloydWarshall_Build_Simple_Infinity() {
    PFloydWarshallData data = fw_load_graph("tests/test-simple-infinity.grh");
    fw_build(data);

    fw_save_matix(data, "build/tests/test-simple-infinity.gmx");

    TEST_ASSERT(fw_get_next(data, 0, 4) == 2);
    TEST_ASSERT(fw_get_next(data, 2, 4) == 4);
    TEST_ASSERT(fw_get_next(data, 2, 10) == 4);
    TEST_ASSERT(fw_get_next(data, 0, 10) == UNDEFINED_GRAPH_NODE);
    TEST_ASSERT(fw_get_next(data, 0, 6) == UNDEFINED_GRAPH_NODE);
    TEST_ASSERT(fw_get_next(data, 0, 8) == UNDEFINED_GRAPH_NODE);

    TEST_ASSERT(fw_get_next(data, 0, 3) == 1);
    TEST_ASSERT(fw_get_next(data, 1, 3) == 3);
    TEST_ASSERT(fw_get_next(data, 1, 9) == 9);
    TEST_ASSERT(fw_get_next(data, 0, 9) == UNDEFINED_GRAPH_NODE);
    TEST_ASSERT(fw_get_next(data, 0, 5) == UNDEFINED_GRAPH_NODE);
    TEST_ASSERT(fw_get_next(data, 0, 7) == UNDEFINED_GRAPH_NODE);

    TEST_ASSERT(fw_get_dist(data, 0, 4) == 2147483646);
    TEST_ASSERT(fw_get_dist(data, 2, 10) == 2147483646);
    TEST_ASSERT(fw_get_dist(data, 0, 10) == INFINITY_GRAPH_DISTANCE);
    TEST_ASSERT(fw_get_dist(data, 0, 6) == INFINITY_GRAPH_DISTANCE);
    TEST_ASSERT(fw_get_dist(data, 0, 8) == INFINITY_GRAPH_DISTANCE);

    TEST_ASSERT(fw_get_dist(data, 0, 3) == -2147483646);
    TEST_ASSERT(fw_get_dist(data, 1, 9) == -2147483646);
    TEST_ASSERT(fw_get_dist(data, 0, 9) == INFINITY_GRAPH_DISTANCE);
    TEST_ASSERT(fw_get_dist(data, 0, 5) == INFINITY_GRAPH_DISTANCE);
    TEST_ASSERT(fw_get_dist(data, 0, 7) == INFINITY_GRAPH_DISTANCE);
}

void Test_FloydWarshall_Build() {
    PFloydWarshallData data = fw_load_graph("tests/test-build.grh");
    fw_build(data);

    TEST_ASSERT(fw_get_dist(data, 4, 0) == 7);
    TEST_ASSERT(fw_get_next(data, 4, 0) == 2);
    TEST_ASSERT(fw_get_next(data, 2, 0) == 3);
    TEST_ASSERT(fw_get_next(data, 3, 0) == 1);
    TEST_ASSERT(fw_get_next(data, 1, 0) == 0);
}

TEST_BEGIN

TEST(Test_FloydWarshall_Build_Simple)
TEST(Test_FloydWarshall_Build)
//TEST(Test_FloydWarshall_Build_Simple_Infinity)

TEST_END