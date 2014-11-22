#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "TesMacros.h"
#include "FloydWarshallFile.h"

TEST_INIT("FloydWarshall File Tests")

void Test_FloydWarshallFile_Load() {
    PFloydWarshallData data = fw_load_graph("tests/test-load.grh");

    TEST_ASSERT(data);
    TEST_ASSERT(fw_size(data) == 6)

    TEST_ASSERT(fw_get_dist(data, 0, 5) == INFINITY_GRAPH_DISTANCE);
    TEST_ASSERT(fw_get_dist(data, 0, 1) == 1);
    TEST_ASSERT(fw_get_dist(data, 1, 0) == 2);
    TEST_ASSERT(fw_get_dist(data, 1, 2) == 3);
    TEST_ASSERT(fw_get_dist(data, 1, 3) == -4);
    TEST_ASSERT(fw_get_dist(data, 3, 1) == 5);
    TEST_ASSERT(fw_get_dist(data, 2, 3) == 6);
    TEST_ASSERT(fw_get_dist(data, 2, 4) == 7);
    TEST_ASSERT(fw_get_dist(data, 3, 5) == 9);

    TEST_ASSERT(fw_get_next(data, 0, 5) == UNDEFINED_GRAPH_NODE);
    TEST_ASSERT(fw_get_next(data, 0, 1) == 1);
    TEST_ASSERT(fw_get_next(data, 1, 0) == 0);
    TEST_ASSERT(fw_get_next(data, 1, 2) == 2);
    TEST_ASSERT(fw_get_next(data, 1, 3) == 3);
    TEST_ASSERT(fw_get_next(data, 3, 1) == 1);
    TEST_ASSERT(fw_get_next(data, 2, 3) == 3);
    TEST_ASSERT(fw_get_next(data, 2, 4) == 4);
    TEST_ASSERT(fw_get_next(data, 3, 5) == 5);
    
    fw_save_matix(data, "build/tests/test-load.gmx");
}

void Test_FloydWarshallFile_SaveMatrix() {
    PFloydWarshallData data = fw_load_graph("tests/test-load.grh");    
    fw_build(data);
    
    fw_save_matix(data, "build/tests/test-load-and-build.gmx");
}

TEST_BEGIN

TEST(Test_FloydWarshallFile_Load)
TEST(Test_FloydWarshallFile_SaveMatrix)

TEST_END