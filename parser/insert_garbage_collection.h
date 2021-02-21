#ifndef INSERT_GARBAGE_COLLECTION_H
#define INSERT_GARBAGE_COLLECTION_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <string.h>
#include "action.h"
#include "association_bind.h"
#include "../tokenizer/token.h"

    void insert_frees(char *fnname, struct action **actions, size_t *a_len)
    {
        //calculate, and insert where the free() and bind() statements should be located

        for (int i = 0; i < (*a_len); i++)
        {

            if (strcmp((*actions)[i].name, "var") == 0)
            {
                add_varname_association(fnname, (*actions)[i].operands[0]->name);                          //associate with the function
                add_varname_association((*actions)[i].operands[0]->name, (*actions)[i].operands[0]->name); //associate the host variable with itself
            }
            else if (strcmp((*actions)[i].name, "function") == 0)
            {

                add_varname_association(fnname, (*actions)[i].fnname);               //associate with the function
                add_varname_association((*actions)[i].fnname, (*actions)[i].fnname); //associate the host variable with itself

                insert_frees((*actions)[i].fnname, &(*actions)[i].nested, &(*actions)[i].nested_len);
            }
            else if (strcmp((*actions)[i].name, "group") == 0)
                insert_frees(fnname, &(*actions)[i].nested, &(*actions)[i].nested_len);
            else if (strcmp((*actions)[i].name, "ret") == 0)
            {
                if ((*actions)[i].operands_len != 1 || (*actions)[i].operands[0]->name[0] != '>')
                    ; //panic that it must be returning a variable address

                char *retname = (*actions)[i].operands[0]->name;
                struct vars_to_free_ret d = vars_to_free(fnname, retname);

                for (int o = 0; o < d.vars_amt; o++)
                {
                    struct action a;
                    a.name = "free";

                    a.operands = calloc(1, sizeof(token));
                    a.operands_len = 1;

                    token t;
                    t.name = d.vars[o];

                    a.operands[0] = &t;
                    insert_into_actions(actions, a_len, a, i);
                    i++;
                }

                for (int o = 0; o < d.associated_amt; o++)
                {
                    struct action a;
                    a.name = "bind";

                    a.operands = calloc(1, sizeof(token));
                    a.operands_len = 1;

                    token t;
                    t.name = d.associated[o];

                    a.operands[0] = &t;
                    insert_into_actions(actions, a_len, a, i);
                    i++;
                }
            }
            else
                for (int o = 0; o < (*actions)[i].operands_len; o++)
                    if ((*actions)[i].operands[o]->name[0] == '>') //'>' is a variable
                        add_varname_association(fnname, (*actions)[i].operands[o]->name);
        }
    }

#ifdef __cplusplus
}
#endif

#endif