#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "SaveLoad.h"
void SaveClickPattern(const struct Click* pattern, const char* fname)
{
    FILE* fh = fopen(fname, "w");
    for (const struct Click *it = pattern; it->button != 0; ++it)
        fprintf(fh, "%u %u %s\n", it->x, it->y, it->button == LBUTTON ? "left" : it->button == RBUTTON ? "right" : "middle");
    fputs("end", fh);
    fclose(fh);
}
void LoadClickPattern(struct Click** pattern, const char* fname)
{
    size_t len = 0;
    size_t capa = 5, ocapa = 3;
    struct Click* arr = malloc(capa * sizeof(struct Click));
    struct Click* tmp;
    FILE* fh = fopen(fname, "e");
    char str[20];
    char* remains;
    struct Click click;
    while (strcmp(str, "end"))
    {
        scanf("%s\n", str);
        remains = strchr(str, ' ');
        *remains = '\0';
        ++remains;
        click.x = atoi(str);
        remains = strchr(remains, ' ');
        *remains = '\0';
        ++remains;
        click.y = atoi(remains);
        if (strcmp(remains, "left") == 0)
            click.button = LBUTTON;
        else if (strcmp(remains, "middle") == 0)
            click.button = MBUTTON;
        else if (strcmp(remains, "right") == 0)
            click.button = RBUTTON;
        if (capa == len)
        {
            tmp = malloc((capa += ocapa) * sizeof(struct Click));
            memcpy(tmp, arr, len * sizeof(struct Click));
            arr = tmp;
            ocapa = len;
        }
        arr[len] = click;
        ++len;
    }
    fclose(fh);

    *pattern = malloc((len + 1) * sizeof(struct Click));
    memcpy(*pattern, arr, len * sizeof(struct Click));
    free(arr);
    (*pattern)[len].button = 0;
}