#ifndef WRITE_FUNCTION_H_
#define WRITE_FUNCTION_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <string.h>
#include "fetch_all_vars.h"
#include "convert_statement.h"

    void write_function(FILE *out, struct action *acts, size_t acts_len)
    {
        for (int i = 0; i < acts_len; i++)
            if (strcmp(acts[i].name, "group") == 0)
                continue;
            else if (strcmp(acts[i].name, "function") != 0)
            {

                char **opstrings = calloc(acts[i].operands_len, sizeof(char *));

                for (int o = 0; o < acts[i].operands_len; o++)
                    if (acts[i].operands[o]->name[0] == '[')
                    {                                                                               //we have to remove the [ and ] surrounding the integer
                        opstrings[o] = calloc(strlen(acts[i].operands[o]->name) - 1, sizeof(char)); //-1 because we need another segment for the null term

                        for (int j = 1; j < strlen(acts[i].operands[o]->name) - 1; j++)
                            opstrings[o][j - 1] = acts[i].operands[o]->name[j];
                    }
                    else
                        opstrings[o] = acts[i].operands[o]->name;

                write_statement(out, acts[i].name, opstrings, acts[i].operands_len);
            }
        fputs("}\n", out);
    }

#ifdef __cplusplus
}
#endif

#endif