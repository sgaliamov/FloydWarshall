#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "FloydWarshallFile.h"
#include "Stack.h"

#define BUFFER_SIZE (256)

//static void _read_file(const char * const path, )

inline static GraphNode _max(GraphNode one, GraphNode other) {
    return one > other ? one : other;
}

inline static void _close_file(FILE * * const file) {
    assert(file);
    assert(*file);

    fclose(*file);
    *file = NULL;
}

PFloydWarshallData fw_load(const char * const path) {
    assert(path);

    PStack stackFrom __attribute__((cleanup(stack_free))) = stack_create();
    PStack stackTo __attribute__((cleanup(stack_free))) = stack_create();
    PStack stackDist __attribute__((cleanup(stack_free))) = stack_create();
    FILE * pFile __attribute__((cleanup(_close_file))) = fopen(path, "r");
    assert(pFile);

    GraphNode from = 0;
    GraphNode to = 0;
    GraphNode distance = 0;
    GraphNode max = 0;
    char line[BUFFER_SIZE] = {0};

    while (fgets(line, BUFFER_SIZE, pFile) != NULL) {
        sscanf(line, "%u\t%u\t%i", (unsigned*) &from, (unsigned*) &to, (int*) &distance);
        memset(line, 0, BUFFER_SIZE);

        stack_push(stackFrom, (StackItem) from);
        stack_push(stackTo, (StackItem) to);
        stack_push(stackDist, (StackItem) distance);
        max = _max(max, _max(from, to));
    }

    const GraphNode * const pFrom = (const GraphNode * const) stack_to_array(stackFrom);
    const GraphNode * const pTo = (const GraphNode * const) stack_to_array(stackTo);
    const GraphDistance * const pDist = (const GraphDistance * const) stack_to_array(stackDist);
    size_t length = stack_count(stackFrom);

    return fw_create(max + 1, length, pFrom, pTo, pDist);
}

