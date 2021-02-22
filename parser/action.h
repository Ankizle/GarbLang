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
        char *name; //action name

        char *fnname; //function names

        token **operands;    //operands
        size_t operands_len; //amount of operands

        struct action *nested; //nested actions
        size_t nested_len;     //amount o nested actions
    };

    void push_back_operands(token ***operands, size_t *size, token *val)
    {
        size_t sizep1 = *size + 1; //calculate this value so we dont have to waste time doing it twice later (i am a micro optimizer)

        if (*operands == NULL)
            *operands = (token **)calloc(sizep1, sizeof(token *));
        else
            *operands = (token **)realloc(*operands, sizep1 * sizeof(token *));

        (*operands)[*size] = val;
        *size = sizep1;
    }

    void push_back_actions(struct action **actions, size_t *size, struct action val)
    {

        size_t sizep1 = *size + 1; //calculate this value so we dont have to waste time doing it twice later (i am a micro optimizer)

        if (*actions == NULL)
            *actions = (struct action *)calloc(sizep1, sizeof(struct action));
        else
            *actions = (struct action *)realloc(*actions, sizep1 * sizeof(struct action));

        (*actions)[*size] = val;
        *size = sizep1;
    }

    void insert_into_actions(struct action **actions, size_t *size, struct action val, int idx)
    {
        struct action *nacts = (struct action *)calloc(*size + 1, sizeof(struct action));
        bool past_insert_index = false; //if we past the insertion index in the for loop

        for (int i = 0; i < *size + 1; i++)
        {
            if (i == idx)
            {
                nacts[i] = val;
                past_insert_index = true;
                continue;
            }
            nacts[i] = (*actions)[i - past_insert_index]; //if we past the insertion index, we gotta look one index back in the orig actions
        }

        *actions = nacts;
        *size = *size + 1;
    }

#ifdef __cplusplus
}
#endif

#endif