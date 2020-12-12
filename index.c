#ifndef __unix__
#error "GarbLang is Unix Only" //throw error if it is not unix
#endif

#include <stdio.h>
#include "tokenizer/token.h"
#include "tokenizer/tokenizer.h"

int main(int argc, char** argv) {
    //retrieve the .garb file
    char* f = argv[1];

    //output file is out.s (which be compiled and linked by the dev)
    char* out = "out.s";

    token* tokens = lexer(f);
}