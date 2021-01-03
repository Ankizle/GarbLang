#ifndef GROUP_H_
#define GROUP_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "../tokenizer/token.h"

    //group data structure
    typedef struct group
    {

        char *name;

        //if it is a group
        struct group *nested;
        size_t nested_len;
        //////////////////

        //if it is a token
        struct token *token;
        //////////////////

    } group;

#ifdef __cplusplus
}
#endif

#endif