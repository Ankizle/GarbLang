#ifndef ASSOCIATION_HH_
#define ASSOCIATION_HH_

#include <map>
#include <vector>
#include "association_bind.h"

class varname_assoc
{
private:
    std::map<std::string, std::vector<std::string>> varnames_association;

public:
    void add_varname_association(char *name, char *associate);
    struct vars_to_free_ret vars_to_free(char *fnname, char *retname);
};

#endif
