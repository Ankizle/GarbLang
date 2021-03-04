#ifndef CONVERT_STATEMENT_H_
#define CONVERT_STATEMENT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>

    void write_statement(FILE *f, char *lbl, char **operands, size_t len);

#ifdef __cplusplus
}
#endif

#endif