#ifndef Stack_H
#define	Stack_H

#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif


    typedef struct stack_t * PStack;

    typedef void * PStackItem;

    typedef struct Stack_Behaviour const * PStack_Behaviour;
    PStack_Behaviour Stack(void);

    struct Stack_Behaviour {
        PStack(*new)(unsigned const);
        void (*free)(PStack const);
        size_t(*get_count)(PStack const);
        void (*set_capacity)(PStack const, size_t const);
        size_t(*get_capacity)(PStack const);
        bool(*pop)(PStack const, PStackItem const);
        void (*push)(PStack const, PStackItem const);
        PStackItem* (*to_array)(PStack const);
    };


#ifdef	__cplusplus
}
#endif

#endif
