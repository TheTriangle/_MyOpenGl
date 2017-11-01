
#include "VEDLibh.h"
bool control (double speed = 1);


int main()
    {
    tx_auto_func(delete [] ZBuffer);
    SzScr = POINT{GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)};
    ZBuffer = new double[SzScr.x * SzScr.y];
    MakeBufferDefault();
    txCreateWindow (SzScr.x, SzScr.y);
    MyScreen = txCreateDIBSection(SzScr.x, SzScr.y, &MyPixels);
    VEDTranslate (0, 0, 100);
    VEDScale (40, 40, 20);
    VEDCube(false);
    while (!GetAsyncKeyState (VK_ESCAPE))
        {

        txSleep (10);
        //getch();
        txSetFillColor (TX_BLACK, MyScreen);
        //txClearConsole();

        //txSetColor (TX_WHITE);
        //VEDVertex ({100, 100, 0}, {0, 0, 0});
        //txSetColor (TX_GREEN);
        //VEDCube(true);
        txSetColor (TX_WHITE, 1, MyScreen);
        if (control(3))
            {
            txClear(MyScreen);
            VEDCube(false);
            }
        if (GetAsyncKeyState (VK_LSHIFT)) control (5);
        txBitBlt (0, 0, MyScreen);
        MakeBufferDefault();
        }

    return 0;
    }


bool control (double speed)
    {
    bool returning = false;
    if (GetAsyncKeyState ('R'))
        {
        ShowMeZBuffer = true;
        returning = true;
        }
    else
        {
        returning = true;
        ShowMeZBuffer = false;
        }
    if (GetAsyncKeyState (VK_RIGHT))  {returning = true; VEDScale (1.3 * speed,   0,     0);}
    if (GetAsyncKeyState (VK_LEFT ))  {returning = true; VEDScale (0.7 * speed,   0,     0);}
    if (GetAsyncKeyState (VK_UP   ))  {returning = true; VEDScale (  0, 1.3 * speed,     0);}
    if (GetAsyncKeyState (VK_DOWN ))  {returning = true; VEDScale (  0, 0.7 * speed,     0);}
    if (GetAsyncKeyState (VK_RSHIFT)) {returning = true; VEDScale (  0,   0,   1.1 * speed);}
    if (GetAsyncKeyState (VK_RETURN)) {returning = true; VEDScale (  0,   0,   0.9 * speed);}

    if (GetAsyncKeyState ('N'))
        {
        if (GetAsyncKeyState(31)) {returning = true; NPLANE = 1;}
        if (GetAsyncKeyState(32)) {returning = true; NPLANE = 2;}
        if (GetAsyncKeyState(33)) {returning = true; NPLANE = 3;}
        if (GetAsyncKeyState(34)) {returning = true; NPLANE = 4;}
        if (GetAsyncKeyState(35)) {returning = true; NPLANE = 5;}
        if (GetAsyncKeyState(36)) {returning = true; NPLANE = 6;}
        if (GetAsyncKeyState(37)) {returning = true; NPLANE = 7;}
        if (GetAsyncKeyState(38)) {returning = true; NPLANE = 8;}
        if (GetAsyncKeyState(39)) {returning = true; NPLANE = 9;}
        }
    if (GetAsyncKeyState ('F'))
        {
        if (GetAsyncKeyState(31)) {returning = true; FPLANE = 1;}
        if (GetAsyncKeyState(32)) {returning = true; FPLANE = 2;}
        if (GetAsyncKeyState(33)) {returning = true; FPLANE = 3;}
        if (GetAsyncKeyState(34)) {returning = true; FPLANE = 4;}
        if (GetAsyncKeyState(35)) {returning = true; FPLANE = 5;}
        if (GetAsyncKeyState(36)) {returning = true; FPLANE = 6;}
        if (GetAsyncKeyState(37)) {returning = true; FPLANE = 7;}
        if (GetAsyncKeyState(38)) {returning = true; FPLANE = 8;}
        if (GetAsyncKeyState(39)) {returning = true; FPLANE = 9;}
        }


    if (GetAsyncKeyState ('D')) {returning = true; VEDTranslate ( 4 * speed,  0,   0);}
    if (GetAsyncKeyState ('A')) {returning = true; VEDTranslate (-4 * speed,  0,   0);}
    if (GetAsyncKeyState ('W')) {returning = true; VEDTranslate ( 0, -4 * speed,   0);}
    if (GetAsyncKeyState ('S')) {returning = true; VEDTranslate ( 0,  4 * speed,   0);}
    if (GetAsyncKeyState ('Q')) {returning = true; VEDTranslate ( 0,  0,   4 * speed);}
    if (GetAsyncKeyState ('E')) {returning = true; VEDTranslate ( 0,  0,  -4 * speed);}


    if (GetAsyncKeyState ('O'))
        {
        if (GetAsyncKeyState ('Z')) {VEDRotateZ (-0.0175 * speed); returning = true;}
        if (GetAsyncKeyState ('X')) {VEDRotateX (-1.75 * speed); returning = true;}
        if (GetAsyncKeyState ('Y')) {VEDRotateY (-1.75 * speed); returning = true;}
        }
    if (GetAsyncKeyState ('P'))
        {
        if (GetAsyncKeyState ('Z')) {VEDRotateZ (0.0175 * speed); returning = true;}
        if (GetAsyncKeyState ('X')) {VEDRotateX (1.75 * speed); returning = true;}
        if (GetAsyncKeyState ('Y')) {VEDRotateY (1.75 * speed); returning = true;}
        }
    return returning;
    }

