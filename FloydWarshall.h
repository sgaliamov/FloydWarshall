#ifndef FLOYDWARSHALL_H
#define	FLOYDWARSHALL_H

#ifdef	__cplusplus
extern "C" {
#endif


    typedef struct FloydWarshallData * PFloydWarshallData;
    typedef unsigned GraphNodeType;
    typedef int GraphDistance;


    extern const char * const NAN_STRING;
    extern const GraphNodeType UNDEFINED_GRAPH_NODE;
    extern const GraphDistance INFINITY_GRAPH_DISTANCE;


    PFloydWarshallData fw_create(
            const GraphNodeType,
            const size_t,
            const GraphNodeType * const,
            const GraphNodeType * const,
            const GraphDistance * const);
    void fw_free(PFloydWarshallData * const);

    void fw_build(const PFloydWarshallData);
    GraphNodeType fw_size(const PFloydWarshallData);
    GraphNodeType fw_get_next(const PFloydWarshallData, const GraphNodeType, const GraphNodeType);
    GraphDistance fw_get_dist(const PFloydWarshallData, const GraphNodeType, const GraphNodeType);
    

#ifdef	__cplusplus
}
#endif

#endif	/* FLOYDWARSHALL_H */

