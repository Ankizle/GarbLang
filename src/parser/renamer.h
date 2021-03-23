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
        int scope_id;
    };

    struct varname_changer *varnames;
    int varnames_size = 0;
    int varcount = 0;
    int cur_scope_id = 0;

    char *get_new_name(char *oldname, int scope_id)
    {
        for (int i = 0; i < varnames_size; i++)
            if (strcmp(varnames[i].oldname, oldname) == 0 && varnames[i].scope_id <= scope_id && varnames[i].scope_id != -1) //same name, and declared in a higher scope
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

    void name_cleanup(int scope_id)
    {
        for (int i = 0; i < varnames_size; i++)
            if (varnames[i].scope_id == scope_id)
                varnames[i].scope_id = -1; //makes the value unattainable
    }

    void change_varnames(struct action *actions, size_t a_len, int scope_id)
    {

        for (int i = 0; i < a_len; i++)
        {

            //count the labels
            if (strcmp(actions[i].name, "lbl") == 0)
            {
                //label declaration

                if (actions[i].operands_len != 1)
                {
                    //error that there must be a name when declaring a label
                }

                struct varname_changer v;
                v.oldname = actions[i].operands[0]->name;

                int namesize = snprintf(NULL, 0, "%d", varcount); //calculate the length of the new label name
                v.newname = calloc(namesize + 2, sizeof(char));
                snprintf(v.newname, namesize + 2, "l%d", varcount++); //'l' signifies a label

                actions[i].operands[0]->name = v.newname;

                v.scope_id = scope_id;

                add_new_name(v);
            }
        }

        for (int i = 0; i < a_len; i++)
        {

            if (strcmp(actions[i].name, "lbl") == 0) //we counted labels beforehand
                continue;
            else if (strcmp(actions[i].name, "var") == 0)
            {
                //variable declaration

                if (actions[i].operands_len != 1)
                {
                    //error that there must be a variable name when declaring a variale
                }

                struct varname_changer v;
                v.oldname = actions[i].operands[0]->name;

                int namesize = snprintf(NULL, 0, "%d", varcount); //calculate the length of the new variable name
                v.newname = calloc(namesize + 2, sizeof(char));
                snprintf(v.newname, namesize + 2, "v%d", varcount++); //'v' signifies a variable

                actions[i].operands[0]->name = v.newname;

                v.scope_id = scope_id;

                add_new_name(v);
            }
            else if (strcmp(actions[i].name, "group") == 0)
                //its a group
                change_varnames(actions[i].nested, actions[i].nested_len, ++cur_scope_id);

            else if (strcmp(actions[i].name, "function") == 0)
            {
                //its a function

                //functions must be renamed as well

                struct varname_changer v;
                v.oldname = actions[i].fnname;

                if (strcmp(actions[i].fnname, "<main>") == 0)
                {
                    actions[i].fnname = "_main";
                    v.scope_id = scope_id;
                    add_new_name(v);
                }
                else
                {
                    int namesize = snprintf(NULL, 0, "%d", varcount); //calculate the length of the new variable name
                    v.newname = calloc(namesize + 2, sizeof(char));
                    snprintf(v.newname, namesize + 2, "v%d", varcount++); //'v' signifies a variable

                    actions[i].fnname = v.newname;

                    v.scope_id = scope_id;

                    add_new_name(v);

                    ///////////////////////////////////
                }

                //change the variables in the function body
                change_varnames(actions[i].nested, actions[i].nested_len, ++cur_scope_id);
            }
            else
                //its an instruction

                for (int j = 0; j < actions[i].operands_len; j++)

                    if (actions[i].operands[j]->name[0] == '<')
                        //its a variable
                        actions[i]
                            .operands[j]
                            ->name = get_new_name(actions[i].operands[j]->name, scope_id);
        }

        name_cleanup(scope_id);
    }

#ifdef __cplusplus
}
#endif

#endif