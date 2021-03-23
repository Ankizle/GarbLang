#ifndef COMPILER_H_
#define COMPILER_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include "fetch_all_vars.h"
#include "write_function.h"

    void compile(FILE *out, struct action *acts, size_t acts_len, struct fetch_vars_ret vars)
    {

        fputs("//////////////////////////////////////////////////////////////////////////////////////////////\n", out);
        fputs("#include <vector>\n", out);
        fputs("#include <map>\n", out);
        fputs("#include <chrono>\n", out);
        fputs("#include <iostream>\n", out);
        fputs("#include <stdlib.h>\n", out);

        fputs(R"(

            typedef long long* (*genf)();

            std::map<void*, std::vector<void*>> links;

            void gfree(void* p) {

                std::vector<void*> b = links[p];

                for (void* i : b) free(i);
            }

            void gbind(void* p0, void* p1) {

                if (links.find(p1) == links.end()) {
                    std::vector<void*> v = std::vector<void*>();
                    links[p1] = v;
                }

                links[p1].push_back(p0);
            }
        )",
              out);

        fputs("//////////////////////////////////////////////////////////////////////////////////////////////\n", out);

        //declare all the variables at the global scope
        for (int i = 0; i < vars.len; i++)
        {
            if (vars.associated_acts[i] != NULL)
                //it is a function
                fprintf(out, "long long* %s();\n", vars.vars[i]);
            else
                fprintf(out, "long long* %s;\n", vars.vars[i]);
        }

        //flesh out the functions now
        for (int i = 0; i < vars.len; i++)
        {
            if (vars.associated_acts[i] != NULL)
            {
                //it is a function
                fprintf(out, "long long* %s() {\n", vars.vars[i]);
                write_function(out, vars.associated_acts[i]->nested, vars.associated_acts[i]->nested_len);
            }
        }

        fputs("int main() { _main(); }", out);
    }

#ifdef __cplusplus
}
#endif

#endif