#ifndef RENAMER_H_
#define RENAMER_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "action.h"

    struct varname_changer
    {
        char *oldname;
        char *newname;
        int scope_level;
    };

    struct varname_changer *varnames;
    int varnames_size = 0;
    int varcount = 0;

    char *get_new_name(char *oldname, int scope_level)
    {
        for (int i = 0; i < varnames_size; i++)
            if (strcmp(varnames[i].oldname, oldname) == 0 && varnames[i].scope_level == scope_level)
                return varnames[i].newname;

        //error that the variable was not yet declared
    }

    void add_new_name(struct varname_changer v)
    {

        if (varnames_size == 0)
            varnames = calloc(1, sizeof(struct varname_changer));
        else
            varnames = realloc(varnames, (varnames_size + 1) * sizeof(struct varname_changer));

        varnames[varnames_size++] = v;
    }

    void change_varnames(struct action *actions, size_t a_len, int scope_level)
    {

        for (int i = 0; i < a_len; i++)
        {

            if (strcmp(actions[i].name, "var") == 0)
            {
                //variable declaration

                if (actions[i].operands_len != 1)
                {
                    //error that there must be a variable name when declaring a variale
                }

                struct varname_changer v;
                v.oldname = actions[i].operands[0]->name;

                int namesize = snprintf(NULL, 0, "%d", varcount);
                v.newname = calloc(namesize + 1, sizeof(char));
                snprintf(v.newname, namesize + 1, "%d", varcount++);

                v.scope_level = scope_level;

                add_new_name(v);
            }
            else if (actions[i].operands != NULL)
            {
                //its an instruction

                for (int j = 0; j < actions[i].operands_len; j++)
                {

                    if (actions[i].operands[j]->name[0] == '<')
                        //its a variable
                        actions[i].operands[j]->name = get_new_name(actions[i].operands[j]->name, scope_level);
                }
            }
            else if (strcmp(actions[i].name, "group"))
                //its a group
                change_varnames(actions[i].nested, actions[i].nested_len, scope_level + 1);

            else if (strcmp(actions[i].name, "function"))
            {
                //its a function

                //change the variables in the function body
                change_varnames(actions[i].nested, actions[i].nested_len, scope_level + 1);
            }
        }
    }

#ifdef __cplusplus
}
#endif

#endif