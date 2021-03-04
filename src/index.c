#ifndef __unix__
#error "GarbLang is Unix Only" //throw error if it is not unix
#endif

#include "tokenizer/token.h"
#include "tokenizer/tokenizer.h"
#include "parser/grouper.h"
#include "parser/actionizer.h"
#include "parser/renamer.h"
#include "parser/insert_garbage_collection.h"
#include "compiler/fetch_all_vars.h"
#include "compiler/compiler.h"

int main(int argc, char **argv)
{
    //retrieve the .garb file
    char *f = argv[1];

    token *tokens = lexer(f);

    group *global_layer = (group *)malloc(sizeof(group));
    grouper(tokens, global_layer);

    struct action a = actionize(global_layer);
    change_varnames(a.nested, a.nested_len, 0);
    insert_frees("global", &a.nested, &a.nested_len);

    struct fetch_vars_ret vars = fetch_vars(a.nested, a.nested_len);

    //output file name
    char *output_name = "out.cc";

    FILE *fp = fopen(output_name, "w");
    compile(fp, a.nested, a.nested_len, vars);
}