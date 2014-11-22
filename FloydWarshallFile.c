#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "FloydWarshallFile.h"
#include "Stack.h"

static const unsigned BUFFER_SIZE = 256;

inline static GraphNodeType _max(GraphNodeType one, GraphNodeType other) {
    return one > other ? one : other;
}

inline static void _close_file(FILE * * const file) {
    assert(file);
    assert(*file);

    fclose(*file);
    *file = NULL;
}

inline static void _stack_free(PStack * const stack) {
    Stack()->free(*stack);
    *stack = NULL;
}

PFloydWarshallData fw_load_graph(const char * const path) {
    assert(path);

    PStack stackFrom __attribute__((cleanup(_stack_free))) = Stack()->new();
    PStack stackTo __attribute__((cleanup(_stack_free))) = Stack()->new();
    PStack stackDist __attribute__((cleanup(_stack_free))) = Stack()->new();
    FILE * pFile __attribute__((cleanup(_close_file))) = fopen(path, "r");
    assert(pFile);

    GraphNodeType from = 0;
    GraphNodeType to = 0;
    GraphNodeType distance = 0;
    GraphNodeType max = 0;
    char line[BUFFER_SIZE];
    memset(line, 0, BUFFER_SIZE);

    while (fgets(line, BUFFER_SIZE, pFile) != NULL) {
        sscanf(line, "%u\t%u\t%i", (unsigned*) &from, (unsigned*) &to, (int*) &distance);
        memset(line, 0, BUFFER_SIZE);

        Stack()->push(stackFrom, (StackItem) from);
        Stack()->push(stackTo, (StackItem) to);
        Stack()->push(stackDist, (StackItem) distance);
        max = _max(max, _max(from, to));
    }

    const GraphNodeType * const pFrom = (const GraphNodeType * const) Stack()->to_array(stackFrom);
    const GraphNodeType * const pTo = (const GraphNodeType * const) Stack()->to_array(stackTo);
    const GraphDistance * const pDist = (const GraphDistance * const) Stack()->to_array(stackDist);
    size_t length = Stack()->get_count(stackFrom);

    return fw_create(max + 1, length, pFrom, pTo, pDist);
}

static void _node_to_string(const GraphNodeType * const node, char * const buffer_out) {
    memset(buffer_out, 0, BUFFER_SIZE);
    if (*node == UNDEFINED_GRAPH_NODE) {
        strcpy(buffer_out, NAN_STRING);
    } else {
        sprintf(buffer_out, "%X", *node);
    }
}

static void _distance_to_string(const GraphDistance * const dist, char * const buffer_out) {
    memset(buffer_out, 0, BUFFER_SIZE);
    if (*dist >= INFINITY_GRAPH_DISTANCE || *dist <= -INFINITY_GRAPH_DISTANCE) {
        sprintf(buffer_out, "(%s)", NAN_STRING);
    } else {
        sprintf(buffer_out, "(%i)", *dist);
    }
}

void fw_save_matix(PFloydWarshallData data, const char * const path) {
    assert(data);
    assert(path);

    FILE * file __attribute__((cleanup(_close_file))) = fopen(path, "w");
    assert(file);
    GraphNodeType size = fw_size(data);
    assert(size);

    char nodeString[BUFFER_SIZE];
    char distString[BUFFER_SIZE];
    for (GraphNodeType r = 0; r < size; r++) {
        for (GraphNodeType c = 0; c < size; c++) {
            GraphNodeType next = fw_get_next(data, r, c);
            GraphDistance dist = fw_get_dist(data, r, c);

            _node_to_string(&next, nodeString);
            _distance_to_string(&dist, distString);

            fprintf(file, "%8s%8s", nodeString, distString);
        }

        fputc('\n', file);
    }
}