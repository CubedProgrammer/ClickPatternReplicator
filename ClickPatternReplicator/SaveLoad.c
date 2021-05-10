#include <stdio.h>
#include "SaveLoad.h"
void SaveClickPattern(const struct Click* pattern, const char* fname)
{
    FILE* fh = fopen(fname, "w");
    for (const struct Click *it = pattern; it->button != 0; ++it)
        fprintf(fh, "%u %u %s\n", it->x, it->y, it->button == LBUTTON ? "left" : it->button == RBUTTON ? "right" : "middle");
    fclose(fh);
}
void LoadClickPattern(struct Click** pattern, const char* fname);