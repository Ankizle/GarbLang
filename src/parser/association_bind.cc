#include <cstdlib>

#include "association.hh"
#include "association_bind.h"

#ifdef __cplusplus
extern "C"
{
#endif

    static varname_assoc *ins = NULL;

    void lazyInit()
    {
        if (ins == NULL)
            ins = new varname_assoc();
    }

    void add_varname_association(char *name, char *associate)
    {
        lazyInit();
        ins->add_varname_association(name, associate);
    }

    struct vars_to_free_ret vars_to_free(char *fnname, char *retname)
    {
        lazyInit();
        return ins->vars_to_free(fnname, retname);
    }

#ifdef __cplusplus
}
#endif