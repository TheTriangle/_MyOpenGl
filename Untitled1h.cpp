
#include "VEDLibh.h"
void control (double speed = 1);


int main()
    {
    txCreateWindow (GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
    VEDTranslate (0, 0, 50);
    VEDScale (20, 20, 10);
    while (!GetAsyncKeyState (VK_ESCAPE))
        {

        txSleep (20);
        txSetFillColor (TX_BLACK);
        txClear ();
        txClearConsole();

        txSetColor (TX_WHITE);
        //VEDVertex ({100, 100, 0}, {0, 0, 0});
        txSetColor (TX_GREEN);
        VEDCube(true);
        txSetColor (TX_WHITE);
        VEDCube(false);
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

    if (GetAsyncKeyState ('N'))
        {
        if (GetAsyncKeyState(31)) NPLANE = 1;
        if (GetAsyncKeyState(32)) NPLANE = 2;
        if (GetAsyncKeyState(33)) NPLANE = 3;
        if (GetAsyncKeyState(34)) NPLANE = 4;
        if (GetAsyncKeyState(35)) NPLANE = 5;
        if (GetAsyncKeyState(36)) NPLANE = 6;
        if (GetAsyncKeyState(37)) NPLANE = 7;
        if (GetAsyncKeyState(38)) NPLANE = 8;
        if (GetAsyncKeyState(39)) NPLANE = 9;
        }
    if (GetAsyncKeyState ('F'))
        {
        if (GetAsyncKeyState(31)) FPLANE = 1;
        if (GetAsyncKeyState(32)) FPLANE = 2;
        if (GetAsyncKeyState(33)) FPLANE = 3;
        if (GetAsyncKeyState(34)) FPLANE = 4;
        if (GetAsyncKeyState(35)) FPLANE = 5;
        if (GetAsyncKeyState(36)) FPLANE = 6;
        if (GetAsyncKeyState(37)) FPLANE = 7;
        if (GetAsyncKeyState(38)) FPLANE = 8;
        if (GetAsyncKeyState(39)) FPLANE = 9;
        }


    if (GetAsyncKeyState ('D')) VEDTranslate ( 4 * speed,  0,   0);
    if (GetAsyncKeyState ('A')) VEDTranslate (-4 * speed,  0,   0);
    if (GetAsyncKeyState ('W')) VEDTranslate ( 0, -4 * speed,   0);
    if (GetAsyncKeyState ('S')) VEDTranslate ( 0,  4 * speed,   0);
    if (GetAsyncKeyState ('Q')) VEDTranslate ( 0,  0,   4 * speed);
    if (GetAsyncKeyState ('E')) VEDTranslate ( 0,  0,  -4 * speed);


    if (GetAsyncKeyState ('O'))
        {
        if (GetAsyncKeyState ('Z')) {VEDRotateZ (-0.0175 * speed); }
        if (GetAsyncKeyState ('X')) {VEDRotateX (-1.75 * speed); }
        if (GetAsyncKeyState ('Y')) {VEDRotateY (-1.75 * speed); }
        }
    if (GetAsyncKeyState ('P'))
        {
        if (GetAsyncKeyState ('Z')) {VEDRotateZ (0.0175 * speed); }
        if (GetAsyncKeyState ('X')) {VEDRotateX (1.75 * speed); }
        if (GetAsyncKeyState ('Y')) {VEDRotateY (1.75 * speed); }
        }
    }

