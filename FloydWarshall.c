#include <stdlib.h>
#include <assert.h>
#include "FloydWarshall.h"

typedef struct FloydWarshallData {
    GraphDistance **dist;
    GraphNode **next;
    GraphSize size;
} * PFloydWarshallData;

PFloydWarshallData _fw_create(const GraphSize size) {
    PFloydWarshallData data = malloc(sizeof (struct FloydWarshallData));
    data->size = size;
    data->dist = malloc(size * sizeof (GraphDistance*));
    data->next = malloc(size * sizeof (GraphNode*));

    for (GraphSize i = 0; i < size; i++) {
        data->dist[i] = calloc(size, sizeof (GraphDistance));
        data->next[i] = calloc(size, sizeof (GraphNode));
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

void fw_build(const PFloydWarshallData data) {
    assert(data);

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