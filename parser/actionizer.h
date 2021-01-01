#include <stdlib.h>
#include <string.h>
#include "group.h"
#include "action.h"

void push_back_action(struct action **list, size_t curlen, struct action value)
{
    *list = (struct action *)realloc(*list, curlen + 1);
    *list[curlen] = value;
}

struct action *actionizer(group *groups)
{
    struct action *actions;
    size_t action_size = 0;

    group *nested = groups->nested;

    for (int i = 0; i < groups->nested_len; i++)
    {

        if (strcmp(nested[i].name, "group") == 0)
        {
            //its a group
        }
        else if (strcmp(nested[i].name, "fn") == 0)
        {
            //its a function
        }
        else
        {
            //its a default instruction
        }
    }
}