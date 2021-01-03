#ifndef ACTIONIZER_H_
#define ACTIONIZER_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <string.h>
#include <stdio.h>
#include "action.h"
#include "group.h"

    struct action actionize(group *groups)
    {

        struct action *fin = NULL;
        size_t action_len = 0;

        for (int i = 0; i < groups->nested_len; i++)
        {

            if (strcmp(groups->nested[i].name, "fn") == 0)
            {
                //function

                struct action a;
                a.name = "function";
                a.fnname = groups->nested[++i].name;

                struct action actionized = actionize(&groups->nested[i + 1]);

                a.nested = actionized.nested;
                a.nested_len = actionized.nested_len;
                push_back_actions(&fin, &action_len, a);
            }
            else if (strcmp(groups->nested[i].name, "group") == 0)
            {
                //group
                struct action a = actionize(groups->nested[i].nested);
                free(groups->nested[i].nested);
                push_back_actions(&fin, &action_len, a);
            }
            else
            {
                //regular instruction
                struct action a;
                a.name = groups->nested[i++].name;

                token **operands = NULL;
                size_t operands_len = 0;

                for (; i < groups->nested_len; i++)
                {
#define isComma (strcmp(groups->nested[i].name, ",") == 0)
#define isNextComma (strcmp(groups->nested[i + 1].name, ",") == 0)

                    if (!isComma)
                        push_back_operands(&operands, &operands_len, groups->nested[i].token);

                    if (i + 1 != groups->nested_len && isComma == isNextComma)
                        break;
                }

                a.operands = operands;
                a.operands_len = operands_len;

                push_back_actions(&fin, &action_len, a);
            }
        }

        free(groups->nested);

        //action struct to store the final list
        struct action ret;
        ret.nested = fin;
        ret.nested_len = action_len;

        return ret;
    }

#ifdef __clusplus
}
#endif

#endif