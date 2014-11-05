/* 
 * File:   FloydWarshall.h
 * Author: Administrator
 *
 * Created on November 4, 2014, 9:59 PM
 */

#ifndef FLOYDWARSHALL_H
#define	FLOYDWARSHALL_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct FloydWarshallData * PFloydWarshallData;
    typedef unsigned GraphNode;
    typedef int GraphDistance;
    typedef size_t GraphSize;

    PFloydWarshallData fw_create(
            const GraphSize,
            const size_t,
            const GraphNode * const,
            const GraphNode * const,
            const GraphDistance * const);
    void fw_free(PFloydWarshallData * const);

    void fw_build(const PFloydWarshallData);
    GraphSize fw_size(const PFloydWarshallData);
    GraphNode fw_get_next(const PFloydWarshallData, const GraphNode, const GraphNode);
    GraphDistance fw_get_dist(const PFloydWarshallData, const GraphNode, const GraphNode);

#ifdef	__cplusplus
}
#endif

#endif	/* FLOYDWARSHALL_H */

