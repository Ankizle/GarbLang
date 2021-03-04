#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "association.hh"
#include "association_bind.h"

void varname_assoc::add_varname_association(char *name, char *associate)
{

    if (varnames_association.find(std::string(name)) == varnames_association.end())
    {
        std::vector<std::string> v = std::vector<std::string>();
        varnames_association.insert(
            std::pair<std::string, std::vector<std::string>>(
                name, v));
    }

    //make sure its not counted twice
    if (std::find(varnames_association[std::string(name)].begin(), varnames_association[std::string(name)].end(), associate) != varnames_association[std::string(name)].end())
        return;

    varnames_association[std::string(name)].push_back(associate);
}

struct vars_to_free_ret varname_assoc::vars_to_free(char *fnname, char *retname)
{

    struct vars_to_free_ret r;

    std::vector<std::string>
        association = varnames_association[std::string(retname)];

    //format everything into a c string array
    char **c_arr_association = (char **)calloc(association.size(), sizeof(char *));
    for (int i = 0; i < association.size(); i++)
    {
        const char *c = association[i].c_str();                               //tmp const char*
        c_arr_association[i] = (char *)calloc(strlen(c) + 1, sizeof(char *)); //alloc sufficient space
        strcpy(c_arr_association[i], c);                                      //copy the std::string contents
    }

    r.associated = c_arr_association;
    r.associated_amt = association.size();

    std::vector<std::string>
        all_in_scope = varnames_association[std::string(fnname)];

    std::vector<char *> to_free;

    for (int i = 0; i < all_in_scope.size(); i++)
        if (std::find(association.begin(), association.end(), all_in_scope[i]) == association.end()) //if this current variable is associated with the returner, then skip it
        {
            const char *c = all_in_scope[i].c_str();               //tmp const char*
            char *d = (char *)calloc(strlen(c) + 1, sizeof(char)); //alloc sufficient space
            strcpy(d, c);                                          //copy one string into another
            to_free.push_back(d);                                  //add the final c string
        }

    char **to_free_ret = (char **)calloc(to_free.size(), sizeof(char *));

    //copy the vector into the pointer
    for (int i = 0; i < to_free.size(); i++)
        to_free_ret[i] = to_free[i];

    r.vars_amt = to_free.size();
    r.vars = to_free_ret;

    return r;
}