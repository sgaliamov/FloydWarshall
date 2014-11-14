#include "FloydWarshall.h"

#ifndef FLOYDWARSHALLFILE_H
#define	FLOYDWARSHALLFILE_H

#ifdef	__cplusplus
extern "C" {
#endif
    

    PFloydWarshallData fw_load_graph(const char * const);
    void fw_save_matix(PFloydWarshallData, const char * const);


#ifdef	__cplusplus
}
#endif

#endif	/* FLOYDWARSHALLFILE_H */

