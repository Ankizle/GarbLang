#include <cstdlib>

#include "association.hh"
#include "association_bind.h"

#ifdef __cplusplus
extern "C"
{
#endif

    // Inside this "extern C" block, I can implement functions in C++, which will externally
    //   appear as C functions (which means that the function IDs will be their names, unlike
    //   the regular C++ behavior, which allows defining multiple functions with the same name
    //   (overloading) and hence uses function signature hashing to enforce unique IDs),

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