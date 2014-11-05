#include <stdio.h>
#include <stdlib.h>

#include "FloydWarshallFile.h"

/*
 * 
 */
int main(int argc, char** argv) {
    if (!argc ){
        return (EXIT_FAILURE);
    }

    PFloydWarshallData data __attribute__((cleanup(fw_free))) = fw_load(argv[1]);
    
    fw_build(data);
    
    
    return (EXIT_SUCCESS);
}

