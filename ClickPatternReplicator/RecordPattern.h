#pragma once
enum Button {LBUTTON = 997, MBUTTON, RBUTTON};
struct Click
{
    unsigned x;
    unsigned y;
    enum Button button;
};
#ifdef __cplusplus
extern "C"
{
#endif
    void RecordPattern(struct Click **clicks);
#ifdef __cplusplus
}
#endif