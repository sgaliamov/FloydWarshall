#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "FloydWarshall.h"

const GraphNode UNDEFINED_GRAPH_NODE = UINT_MAX;
const GraphDistance INFINITY_GRAPH_DISTANCE = INT_MAX;

typedef struct FloydWarshallData {
    GraphDistance **dist;
    GraphNode **next;
    GraphSize size;
} * PFloydWarshallData;

static PFloydWarshallData _fw_create(const GraphSize size) {
    PFloydWarshallData data = malloc(sizeof (struct FloydWarshallData));
    data->size = size;
    data->dist = malloc(size * sizeof (GraphDistance*));
    data->next = malloc(size * sizeof (GraphNode*));

    for (GraphSize i = 0; i < size; i++) {
        data->dist[i] = calloc(size, sizeof (GraphDistance));
        data->next[i] = calloc(size, sizeof (GraphNode));

        for (GraphSize j = 0; j < size; j++) {
            data->dist[i][j] = INFINITY_GRAPH_DISTANCE;
            data->next[i][j] = UNDEFINED_GRAPH_NODE;
        }
    }

    return data;
}

PFloydWarshallData fw_create(
        const GraphSize size,
        const size_t length,
        const GraphNode * const pFrom,
        const GraphNode * const pTo,
        const GraphDistance * const pDist) {
    assert(size);
    assert(length);
    assert(pFrom);
    assert(pTo);
    assert(pDist);

    const PFloydWarshallData data = _fw_create(size);

    for (size_t i = 0; i < length; i++) {
        GraphNode from = pFrom[i];
        GraphNode to = pTo[i];
        GraphDistance dist = pDist[i];

        assert(from != UNDEFINED_GRAPH_NODE);
        assert(to != UNDEFINED_GRAPH_NODE);
        assert(dist != INFINITY_GRAPH_DISTANCE);

        data->next[from][to] = to;
        data->dist[from][to] = dist;
    }

    return data;
}

void fw_free(PFloydWarshallData * const ppData) {
    assert(ppData);
    const PFloydWarshallData pData = *ppData;
    assert(pData);

    for (GraphSize i = 0; i < pData->size; i++) {
        free(pData->dist[i]);
        free(pData->next[i]);
    }

    free(pData->dist);
    free(pData->next);

    *ppData = NULL;
}

inline static GraphDistance _summ(GraphDistance a, GraphDistance b) {
    if (a == INFINITY_GRAPH_DISTANCE || b == INFINITY_GRAPH_DISTANCE) {
        return INFINITY_GRAPH_DISTANCE;
    } else if (a == -INFINITY_GRAPH_DISTANCE || b == -INFINITY_GRAPH_DISTANCE) {
        return -INFINITY_GRAPH_DISTANCE;
    }

    long c = (long) a + b;
    if (c > INFINITY_GRAPH_DISTANCE) {
        c = INFINITY_GRAPH_DISTANCE;
    } else if (c <-INFINITY_GRAPH_DISTANCE) {
        c = -INFINITY_GRAPH_DISTANCE;
    }

    return (GraphDistance) c;
}

void fw_build(const PFloydWarshallData data) {
    assert(data);

    GraphDistance * const * const dist = data->dist;
    GraphNode * const * const next = data->next;

    for (GraphSize k = 0; k < data->size; k++) {
        for (GraphSize i = 0; i < data->size; i++) {
            for (GraphSize j = 0; j < data->size; j++) {

                const GraphDistance val = _summ(dist[i][k], dist[k][j]);
                if (dist[i][j] > val) {
                    dist[i][j] = val;
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    free(data);
}

GraphSize fw_size(const PFloydWarshallData data) {
    assert(data);

    return data->size;
}

GraphNode fw_get_next(const PFloydWarshallData data, const GraphNode from, const GraphNode to) {
    assert(data);

    return data->next[from][to];
}

GraphDistance fw_get_dist(const PFloydWarshallData data, const GraphNode from, const GraphNode to) {
    assert(data);

    return data->dist[from][to];
}