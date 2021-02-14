#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "token.h"

    //read token data at compile-time
    const char *raw_tokens =
#include "tokens.data"
        ;

    typedef struct
    {
        char *name;
    } tokenkey;

    typedef struct
    {
        tokenkey *tokens;
        int tokenamt;
    } parse_token_list_ret;

    parse_token_list_ret parse_token_list()
    {
        int tokenamt = 1;
        size_t token_len = strlen(raw_tokens);
        int i;
        int o;

        for (i = 0; i < token_len; i++)
            tokenamt += raw_tokens[i] == '\n'; //if its a newline add another slot

        tokenkey *tokens = (tokenkey *)calloc(token_len, sizeof(tokenkey));

        for (i = 0, o = 0; i < token_len; i++)
        {
            if (raw_tokens[i] == '\n')
                o++;
            else
            {
                //append the current character to the name string

                //alloc enough space

                if (tokens[o].name == NULL)
                    tokens[o].name = "\0";

                int space = strlen(tokens[o].name) + 1;
                char *oldname = tokens[o].name;
                tokens[o].name = (char *)calloc(space + 1, sizeof(char)); // + 1 is used to add the null terminator

                //copy the string
                strcpy(tokens[o].name, oldname);
                tokens[o].name[strlen(oldname)] = raw_tokens[i];
                tokens[o].name[strlen(oldname) + 1] = 0;
            }
        }

        parse_token_list_ret r;
        r.tokens = tokens;
        r.tokenamt = tokenamt;
        return r;
    }

    bool starts_with_from(char *file, char *with, int i)
    {

        int with_len = strlen(with);

        for (int o = i; o < i + with_len; o++)
            if (file[o] != with[o - i])
                return false;

        return true;
    }

    //function to convert a file into a linked list of tokens
    token *lexer(char *filename)
    {

        //read and parse file tokens.data
        parse_token_list_ret parsed = parse_token_list();
        FILE *f = fopen(filename, "r"); //open the file for reading

        fseek(f, 0, SEEK_END); //seek to end
        int size = ftell(f);   //get index (size)
        rewind(f);             //go back to start

        char *full_source = (char *)calloc(size + 1, sizeof(char)); //alloc space
        fread(full_source, 1, size, f);
        full_source[size] = 0; //put null terminator

        int i, o;

        token *tokens = (token *)malloc(sizeof(token));
        token *prev = &tokens[0];

        for (i = 0; i < size; i++)
        {
            for (o = 0; o < parsed.tokenamt; o++)
            {
                if (starts_with_from(full_source, parsed.tokens[o].name, i))
                {
                    token *t = (token *)malloc(sizeof(token));

                    //copy the token name, to prevent read-after-free errors, when we free the data
                    t->name = calloc(strlen(parsed.tokens[o].name) + 1, sizeof(char));
                    strcpy(t->name, parsed.tokens[o].name);
                    t->next = NULL;

                    prev->next = t;

                    prev = t;
                    i += strlen(parsed.tokens[o].name);
                    goto cont;
                }
            }

//tokens that look like (open)value(closing)
#define open_closing_token(open, close)                                              \
    else if (full_source[i] == open)                                                 \
    {                                                                                \
        char *name;                                                                  \
        int _size = 0;                                                               \
        i++;                                                                         \
        for (int o = i; full_source[o] != close; o++, _size++)                       \
            ;                                           /*get size*/                 \
        name = (char *)calloc(_size + 3, sizeof(char)); /*alloc space for var name*/ \
        name[0] = open;                                                              \
        name[_size + 1] = close;                                                     \
        name[_size + 2] = 0; /*null term*/                                           \
        for (int c = 1; full_source[i] != close; i++, c++)                           \
            name[c] = full_source[i];                                                \
        token *t = (token *)malloc(sizeof(token));                                   \
        t->name = name;                                                              \
        t->next = NULL;                                                              \
        prev->next = t;                                                              \
        prev = t;                                                                    \
        goto cont;                                                                   \
    }

            if (false)
                ;                              //required for the else if chain that will come with the open_closing_token macro
            open_closing_token('[', ']')       //integer
                open_closing_token('\'', '\'') //char
                open_closing_token('\"', '\"') //string
                open_closing_token('<', '>')   //variable

                cont:;
        }

        free(full_source);

        for (int i = 0; i < parsed.tokenamt; i++)
            free(parsed.tokens[i].name);
        free(parsed.tokens);

        return tokens;
    }

#ifdef __cplusplus
}
#endif

#endif