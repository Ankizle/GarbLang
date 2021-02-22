#ifndef FETCH_ALL_VARS_H_
#define FETCH_ALL_VARS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>
#include <string.h>
#include "../parser/action.h"

    struct fetch_vars_ret
    {
        char **vars;
        struct action **associated_acts; //actions associated with each of the variables (used for function declaration)
        size_t len;
    };

    void merge_s(struct fetch_vars_ret *a, struct fetch_vars_ret b) //merge the two structs
    {

        size_t p = a->len + b.len;
        a->vars = (char **)realloc(a->vars, sizeof(char *) * p);
        a->associated_acts = (struct action **)realloc(a->associated_acts, sizeof(struct action *) * p);

        for (int i = a->len; i < p; i++)
        {
            a->vars[i] = b.vars[i - a->len];
            a->associated_acts[i] = b.associated_acts[i - a->len];
        }

        a->len = p;
    }

    void add_varname(struct fetch_vars_ret *r, char *newname, struct action *act)
    {
        r->vars = (char **)realloc(r->vars, (r->len + 1) * sizeof(char *));
        r->associated_acts = (struct action **)realloc(r->associated_acts, (r->len + 1) * sizeof(struct action *));
        r->vars[r->len] = newname;
        r->associated_acts[r->len] = act;
        r->len++;
    }

    struct fetch_vars_ret fetch_vars(struct action *acts, size_t a_len)
    {

        struct fetch_vars_ret r;

        //alloc basic things to not segfault
        r.vars = (char **)malloc(1);
        r.associated_acts = (struct action **)malloc(1);
        r.len = 0;
        ////////////////////////////////////

        for (int i = 0; i < a_len; i++)
        {
            if (strcmp(acts[i].name, "function") == 0)
            {

                //heap allocate it
                struct action *tmp = (struct action *)calloc(1, sizeof(struct action));
                *tmp = acts[i];
                //////////////////

                add_varname(&r, acts[i].fnname, tmp);
                merge_s(&r,
                        fetch_vars(acts[i].nested, acts[i].nested_len));
            }
            else if (strcmp(acts[i].name, "group") == 0)
                merge_s(&r,
                        fetch_vars(acts[i].nested, acts[i].nested_len));
            else if (strcmp(acts[i].name, "var") == 0)
                add_varname(&r, acts[i].operands[0]->name, NULL);
        }

        return r;
    }

#ifdef __cplusplus
}
#endif

#endif