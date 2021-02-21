#ifndef VARNAME_ASSOCIATION_H
#define VARNAME_ASSOCIATION_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>

    struct vars_to_free_ret
    {
        char **vars;
        size_t vars_amt;

        char **associated;
        size_t associated_amt;
    };

    void add_varname_association(char *name, char *associate);
    struct vars_to_free_ret vars_to_free(char *fnname, char *retname);

#ifdef __cplusplus
}
#endif

#endif