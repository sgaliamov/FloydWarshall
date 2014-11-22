#ifndef Stack_H
#define	Stack_H

#ifdef	__cplusplus
extern "C" {
#endif


    typedef struct stack_t * PStack;

    typedef void * StackItem;

    typedef struct Stack_Behaviour const * PStack_Behaviour;
    PStack_Behaviour Stack(void);

    struct Stack_Behaviour {
        PStack(*new)(void);
        void (*free)(PStack const);
        size_t(*get_count)(PStack const);
        void (*set_capacity)(PStack const, size_t const);
        size_t(*get_capacity)(PStack const);
        StackItem(*pop)(PStack const);
        void (*push)(PStack const, StackItem);
        StackItem* (*to_array)(PStack const);
    };


#ifdef	__cplusplus
}
#endif

#endif
