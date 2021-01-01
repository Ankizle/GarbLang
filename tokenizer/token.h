#ifndef TOKEN_H_
#define TOKEN_H_

#ifdef __cplusplus
extern "C"
{
#endif

    //token data structure (linked list)
    typedef struct token
    {
        char *name;
        struct token *next;
    } token;

#ifdef __cplusplus
}
#endif

#endif