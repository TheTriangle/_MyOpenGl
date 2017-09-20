
#include "VEDLibh.h"
void control (double speed = 1);


int main()
    {
    txCreateWindow (GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
    VEDTranslate (0, 0, 2);
    VEDScale (13,   13,     0);
    while (!GetAsyncKeyState (VK_ESCAPE))
        {

        txSleep (20);
        txSetFillColor (TX_BLACK);
        txClear ();
        txClearConsole();

        txSetColor (TX_WHITE);
        //VEDVertex ({-1, -1, -1}, {1, -1, -1});
        VEDCube();
        control();
        if (GetAsyncKeyState (VK_LSHIFT)) control (3);
        }

    return 0;
    }


void control (double speed)
    {
    if (GetAsyncKeyState (VK_RIGHT))  VEDScale (1.3 * speed,   0,     0);
    if (GetAsyncKeyState (VK_LEFT ))  VEDScale (0.7 * speed,   0,     0);
    if (GetAsyncKeyState (VK_UP   ))  VEDScale (  0, 1.3 * speed,     0);
    if (GetAsyncKeyState (VK_DOWN ))  VEDScale (  0, 0.7 * speed,     0);
    if (GetAsyncKeyState (VK_RSHIFT)) VEDScale (  0,   0,   1.1 * speed);
    if (GetAsyncKeyState (VK_RETURN)) VEDScale (  0,   0,   0.9 * speed);



    if (GetAsyncKeyState ('D')) VEDTranslate ( 1.2 * speed,  0,   0);
    if (GetAsyncKeyState ('A')) VEDTranslate (-1.2 * speed,  0,   0);
    if (GetAsyncKeyState ('W')) VEDTranslate ( 0, -1.2 * speed,   0);
    if (GetAsyncKeyState ('S')) VEDTranslate ( 0,  1.2 * speed,   0);
    if (GetAsyncKeyState ('Q')) VEDTranslate ( 0,  0,   1.2 * speed);
    if (GetAsyncKeyState ('E')) VEDTranslate ( 0,  0,  -1.2 * speed);


    if (GetAsyncKeyState ('O'))
        {
        if (GetAsyncKeyState ('Z')) {VEDRotateZ (-1 * speed); }
        if (GetAsyncKeyState ('X')) {VEDRotateX (-1 * speed); }
        if (GetAsyncKeyState ('Y')) {VEDRotateY (-1 * speed); }
        }
    if (GetAsyncKeyState ('P'))
        {
        if (GetAsyncKeyState ('Z')) {VEDRotateZ (1 * speed); }
        if (GetAsyncKeyState ('X')) {VEDRotateX (1 * speed); }
        if (GetAsyncKeyState ('Y')) {VEDRotateY (1 * speed); }
        }
    }

