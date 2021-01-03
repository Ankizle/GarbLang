#ifndef GROUPER_H_
#define GROUPER_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>
#include <string.h>
#include "../tokenizer/token.h"
#include "group.h"

    void grouper(token *tokens, group *parent)
    {
        parent->nested = NULL;
        size_t size = 0;
        token *cur = tokens->next;

        int cbCnt = 0;

        while (cur != NULL)
        {

            if (parent->nested == NULL)
                parent->nested = calloc(1, sizeof(group));

            // puts(cur->name);

            if (strcmp(cur->name, "{") == 0)
                cbCnt++;
            else if (strcmp(cur->name, "}") == 0)
                cbCnt--;

            if (cbCnt != 0)
            {
                token *nested = (token *)malloc(sizeof(token));
                token *nestcur = &nested[0];
                cur = cur->next;

                while (cur != NULL)
                {

                    if (strcmp(cur->name, "{") == 0)
                        cbCnt++;
                    else if (strcmp(cur->name, "}") == 0)
                        cbCnt--;

                    if (cbCnt == 0)
                    {
                        cur = cur->next;
                        nestcur->next = NULL;
                        break;
                    }

                    nestcur->next = cur;
                    nestcur = nestcur->next;
                    cur = cur->next;
                }

                parent->nested = (group *)realloc(parent->nested, sizeof(group) * (size + 1));
                group *curparent = (group *)malloc(sizeof(group));
                grouper(nested, curparent);
                curparent->name = "group";
                parent->nested[size++] = *curparent;
                free(curparent);

                continue;
            }
            else
            {

                parent->nested = (group *)realloc(parent->nested, sizeof(group) * (size + 1));

                group g;
                g.name = cur->name;
                g.token = cur;
                g.nested_len = 0;

                parent->nested[size++] = g;
            }

            cur = cur->next;
        }

        parent->nested_len = size;
    }

#ifdef __cplusplus
}
#endif

#endif