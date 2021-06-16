#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RecordPattern.h"
void RecordPattern(struct Click **clicks)
{
    char lb = 0, mb = 0, rb = 0;
    char llb = 0, lmb = 0, lrb = 0;
    unsigned shft = sizeof(SHORT) * 8 - 1;
    size_t len = 0;
    size_t capa = 5, ocapa = 3;
    struct Click *arr = malloc(capa * sizeof(struct Click));
    struct Click* tmp;
    POINT p;

    while (GetKeyState(VK_SPACE) >> shft == 0)
    {
        lb = GetAsyncKeyState(VK_LBUTTON) >> shft;
        mb = GetAsyncKeyState(VK_MBUTTON) >> shft;
        rb = GetAsyncKeyState(VK_RBUTTON) >> shft;
        GetCursorPos(&p);

        if (capa == len)
        {
            tmp = malloc((capa += ocapa) * sizeof(struct Click));
            memcpy(tmp, arr, len * sizeof(struct Click));
            arr = tmp;
            ocapa = len;
        }
        
        if (llb && !lb)
        {
            arr[len].button = LBUTTON;
            arr[len].x = p.x;
            arr[len].y = p.y;
            ++len;
        }
        else if (lmb && !mb)
        {
            arr[len].button = MBUTTON;
            arr[len].x = p.x;
            arr[len].y = p.y;
            ++len;
        }
        else if (lrb && !rb)
        {
            arr[len].button = RBUTTON;
            arr[len].x = p.x;
            arr[len].y = p.y;
            ++len;
        }

        llb = lb;
        lmb = mb;
        lrb = rb;
        Sleep(16);
    }

    *clicks = malloc((len + 1) * sizeof(struct Click));
    memcpy(*clicks, arr, len * sizeof(struct Click));
    free(arr);
    (*clicks)[len].button = 0;
}