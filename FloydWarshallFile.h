#include "FloydWarshall.h"

#ifndef FLOYDWARSHALLFILE_H
#define	FLOYDWARSHALLFILE_H

#ifdef	__cplusplus
extern "C" {
#endif

    extern const GraphNode UNDEFINED_GRAPH_NODE;
    extern const GraphDistance INFINITY_GRAPH_DISTANCE;

    PFloydWarshallData fw_load(const char * const path);


#ifdef	__cplusplus
}
#endif

#endif	/* FLOYDWARSHALLFILE_H */

