#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "FloydWarshall.h"


const GraphNodeType UNDEFINED_GRAPH_NODE = UINT_MAX;
const GraphDistance INFINITY_GRAPH_DISTANCE = INT_MAX;
const char * const NAN_STRING = "NAN";

typedef struct FloydWarshallData {
    GraphDistance **dist;
    GraphNodeType **next;
    GraphNodeType size;
} * PFloydWarshallData;

static PFloydWarshallData _fw_create(const GraphNodeType size) {
    PFloydWarshallData data = malloc(sizeof (struct FloydWarshallData));
    data->size = size;
    data->dist = malloc(size * sizeof (GraphDistance*));
    data->next = malloc(size * sizeof (GraphNodeType*));

    for (GraphNodeType i = 0; i < size; i++) {
        data->dist[i] = calloc(size, sizeof (GraphDistance));
        data->next[i] = calloc(size, sizeof (GraphNodeType));

        for (GraphNodeType j = 0; j < size; j++) {
            data->dist[i][j] = i == j ? 0 : INFINITY_GRAPH_DISTANCE;
            data->next[i][j] = i == j ? 0 : UNDEFINED_GRAPH_NODE;
        }
    }

    return data;
}

PFloydWarshallData fw_create(
        const GraphNodeType size,
        const size_t length,
        const GraphNodeType * const pFrom,
        const GraphNodeType * const pTo,
        const GraphDistance * const pDist) {
    assert(size);
    assert(length);
    assert(pFrom);
    assert(pTo);
    assert(pDist);

    const PFloydWarshallData data = _fw_create(size);

    for (size_t i = 0; i < length; i++) {
        GraphNodeType from = pFrom[i];
        GraphNodeType to = pTo[i];
        GraphDistance dist = pDist[i];

        assert(from != UNDEFINED_GRAPH_NODE);
        assert(to != UNDEFINED_GRAPH_NODE);
        assert(dist < INFINITY_GRAPH_DISTANCE);
        assert(dist > -INFINITY_GRAPH_DISTANCE);

        data->next[from][to] = to;
        data->dist[from][to] = dist;
    }

    return data;
}

void fw_free(PFloydWarshallData * const ppData) {
    assert(ppData);
    const PFloydWarshallData pData = *ppData;
    assert(pData);

    for (GraphNodeType i = 0; i < pData->size; i++) {
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
    GraphNodeType * const * const next = data->next;

    for (GraphNodeType k = 0; k < data->size; k++) {
        for (GraphNodeType i = 0; i < data->size; i++) {
            for (GraphNodeType j = 0; j < data->size; j++) {

                const GraphDistance val = _summ(dist[i][k], dist[k][j]);
                if (dist[i][j] > val) {
                    dist[i][j] = val;
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

GraphNodeType fw_size(const PFloydWarshallData data) {
    assert(data);

    return data->size;
}

GraphNodeType fw_get_next(const PFloydWarshallData data, const GraphNodeType from, const GraphNodeType to) {
    assert(data);
    assert(data->size > from);
    assert(data->size > to);

    return data->next[from][to];
}

GraphDistance fw_get_dist(const PFloydWarshallData data, const GraphNodeType from, const GraphNodeType to) {
    assert(data);
    assert(data->size > from);
    assert(data->size > to);

    return data->dist[from][to];
}