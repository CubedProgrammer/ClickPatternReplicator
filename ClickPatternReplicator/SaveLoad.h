#pragma once
#include "RecordPattern.h"
#ifdef __cplusplus
extern"C"
{
#endif
    void SaveClickPattern(const struct Click* pattern, const char* fname);
    void LoadClickPattern(struct Click ** pattern, const char *fname);
#ifdef __cplusplus
}
#endif