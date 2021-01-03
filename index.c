#ifndef __unix__
#error "GarbLang is Unix Only" //throw error if it is not unix
#endif

#include "tokenizer/token.h"
#include "tokenizer/tokenizer.h"
#include "parser/grouper.h"
#include "parser/actionizer.h"

int main(int argc, char **argv)
{
    //retrieve the .garb file
    char *f = argv[1];

    //output file is out.s (which be compiled and linked by the dev)
    char *out = "out.s";

    token *tokens = lexer(f);

    token *cur = tokens->next;

    group *global_layer = (group *)malloc(sizeof(group));
    grouper(tokens, global_layer);

    struct action a = actionize(global_layer);
}