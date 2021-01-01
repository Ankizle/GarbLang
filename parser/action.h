#ifndef ACTION_H_
#define ACTION_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "group.h"

    //action data structure
    struct action
    {
        char *name;

        struct action *group; //sub actions
        size_t group_len;     //length of sub actions
    };

    struct action *actionizer(group *groups);

#ifdef __cplusplus
}
#endif

#endif