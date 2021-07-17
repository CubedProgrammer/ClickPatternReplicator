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
    FILE* fh = fopen(fname, "r");
    char str[20];
    struct Click click;
    fscanf(fh, "%s", str);
    while (strcmp(str, "end"))
    {
        click.x = atoi(str);
        fscanf(fh, "%s", str);
        click.y = atoi(str);
        fscanf(fh, "%s", str);
        if (strcmp(str, "left") == 0)
            click.button = LBUTTON;
        else if (strcmp(str, "middle") == 0)
            click.button = MBUTTON;
        else if (strcmp(str, "right") == 0)
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
        fscanf(fh, "%s", str);
    }
    fclose(fh);

    *pattern = malloc((len + 1) * sizeof(struct Click));
    memcpy(*pattern, arr, len * sizeof(struct Click));
    free(arr);
    (*pattern)[len].button = 0;
}