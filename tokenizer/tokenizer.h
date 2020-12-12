#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "token.h"

//read token data at compile-time
const char* raw_tokens = 
{
    #include "tokens.data"
};

typedef struct {
    char* name;
} tokenkey;

typedef struct {
    tokenkey* tokens;
    int tokenamt;
} parse_token_list_ret;

parse_token_list_ret parse_token_list() {
    int tokenamt = 1;
    size_t token_len = strlen(raw_tokens);
    int i;
    int o;

    for (i = 0; i < token_len; i++)
        tokenamt+=raw_tokens[i] == '\n'; //if its a newline add another slot

    tokenkey* tokens = calloc(token_len, sizeof(tokenkey));

    for (i = 0, o = 0; i < token_len; i++) {
        if (raw_tokens[i] == '\n') o++;
        else {
            //append the current character to the name string

            //alloc enough space

            if (tokens[o].name == NULL)
                tokens[o].name = "";

            int space = strlen(tokens[o].name) + 1;
            char* oldname = tokens[o].name;
            tokens[o].name = calloc(space, sizeof(char));

            //copy the string
            strcpy(tokens[o].name, oldname);
            tokens[o].name[strlen(oldname)] = raw_tokens[i];
        }
    }

    parse_token_list_ret r;
    r.tokens = tokens;
    r.tokenamt = tokenamt;
    return r;
}

bool starts_with_from(char* file, char* with, int i) {

    int with_len = strlen(with);

    for (int o = i; o < i + with_len; o++)
        if (file[o] != with[o - i]) return false;

    return true;
}

//function to convert a file into a linked list of tokens
token* lexer(char* filename) {
    //read and parse file tokens.data
    parse_token_list_ret parsed = parse_token_list();
    FILE* f = fopen(filename, "r"); //open the file for reading

    fseek(f, 0, SEEK_END); //seek to end
    int size = ftell(f); //get index (size)
    rewind(f); //go back to start

    char* full_source = calloc(size + 1, sizeof(char)); //alloc space
    fread(full_source, 1, size, f);
    full_source[size] = 0; //put null terminator

    int i, o, j;

    token tokens[1];
    token* prev = &tokens[0];
    
    for (i = 0; i < size; i++) {
        for (o = 0; o < parsed.tokenamt; o++) {
            if (starts_with_from(full_source, parsed.tokens[o].name, i)) {
                token* t = malloc(sizeof(token));
                t->name = parsed.tokens[o].name;
                prev->next = t;

                prev = t;
                i+=strlen(parsed.tokens[o].name);
                goto cont;
            }
        }

        if (isdigit(full_source[i]) || full_source[i] == '+' || full_source[i] == '-') {
            int sign = full_source[i] == '-' ? -1 : 1;

            if (full_source[i] == '-' || full_source[i] == '+') i++;

            #define cond \
            isdigit(full_source[j]) || full_source[j] == '.' || full_source[j] == 'L' || full_source[j] == 'C' || full_source[j] == 'U' || full_source[j] == 'F' || full_source[j] == 'D'

            int size = 0;
            for (j = i; cond; j++, size++);
            char* numstr = calloc(size + 1, sizeof(char));
            numstr[size] = 0; //null terminatpr
            for (;cond; i++)
                numstr[j - size + i] = full_source[i];

            token* t = malloc(sizeof(token));
            t->name = numstr;
            prev->next = t;

            prev = t;
            goto cont;
        }

        cont:;
    }

    token* cur = tokens[0].next;

    while (cur != NULL) {
        printf("%s\n", cur->name);
        cur = cur->next;
    }

    //free data
    for (i = 0; i < parsed.tokenamt; i++)
        free(parsed.tokens[i].name);

    free(parsed.tokens);
}

#ifdef __cplusplus
}
#endif

#endif