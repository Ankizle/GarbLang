#ifndef ACTION_HH_
#define ACTION_HH_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>
#include "group.h"
#include "../tokenizer/token.h"

    struct action
    {
        char *name;
        char *fnname;

        token **operands;
        size_t operands_len;

        struct action *nested;
        size_t nested_len;
    };

    void push_back_operands(token ***operands, size_t *size, token *val)
    {
        size_t sizep1 = *size + 1; //calculate this value so we dont have to waste time doing it twice later (i am a micro optimizer)

        if (*operands == NULL)
            *operands = calloc(sizep1, sizeof(token *));
        else
            *operands = (token **)realloc(*operands, sizep1);

        (*operands)[*size] = val;
        *size = sizep1;
    }

    void push_back_actions(struct action **actions, size_t *size, struct action val)
    {

        size_t sizep1 = *size + 1; //calculate this value so we dont have to waste time doing it twice later (i am a micro optimizer)

        if (*actions == NULL)
            *actions = calloc(sizep1, sizeof(struct action));
        else
            *actions = (struct action *)realloc(*actions, sizep1);

        (*actions)[*size] = val;
        *size = sizep1;
    }

#ifdef __cplusplus
}
#endif

#endif