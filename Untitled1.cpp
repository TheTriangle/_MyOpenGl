
#include "VEDLibh.h"
//#include "glu.lib"


int main()
    {
    txCreateWindow (800, 600);
    int x = 40, y = 30, z = 1;
    int diffx = 500;
    int diffy = 500;
    int diffz = 1;
    int extrax = 0;
    int extray = 0;
    VEDTranslate (x, y, z);


    //int dist = 150;
    while (!GetAsyncKeyState (VK_ESCAPE))
        {

        txSleep (1);
        txSetFillColor (TX_BLACK);
        txClear ();
        txClearConsole();
        //printf ("x == %d            y == %d\n wx == %d          wy == %d", x, y, diffx, diffy);

        txSetColor (TX_WHITE);
        VEDCube ();
        if (GetAsyncKeyState (VK_RIGHT))  VEDScale ( 1,  0,     0);
        if (GetAsyncKeyState (VK_LEFT ))  VEDScale (-1,  0,     0);
        if (GetAsyncKeyState (VK_UP   ))  VEDScale ( 0, -1,     0);
        if (GetAsyncKeyState (VK_DOWN ))  VEDScale ( 0,  1,     0);
        if (GetAsyncKeyState (VK_SHIFT))  VEDScale ( 0,  0, -0.5);
        if (GetAsyncKeyState (VK_RETURN)) VEDScale ( 0,  0,  0.5);



        if (GetAsyncKeyState ('D')) VEDTranslate ( 1,  0,     0);
        if (GetAsyncKeyState ('A')) VEDTranslate (-1,  0,     0);
        if (GetAsyncKeyState ('W')) VEDTranslate ( 0, -1,     0);
        if (GetAsyncKeyState ('S')) VEDTranslate ( 0,  1,     0);
        if (GetAsyncKeyState ('Q')) VEDTranslate ( 0,  0, -0.025);
        if (GetAsyncKeyState ('E')) VEDTranslate ( 0,  0,  0.025);


        if (GetAsyncKeyState ('O'))
            {
            if (GetAsyncKeyState ('Z')) {VEDRotateZ (-0.01); }
            if (GetAsyncKeyState ('X')) {VEDRotateX (-0.01); }
            if (GetAsyncKeyState ('Y')) {VEDRotateY (-0.01); }
            }
        if (GetAsyncKeyState ('P'))
            {
            if (GetAsyncKeyState ('Z')) {VEDRotateZ (0.01); }
            if (GetAsyncKeyState ('X')) {VEDRotateX (0.01); }
            if (GetAsyncKeyState ('Y')) {VEDRotateY (0.01); }
            }



        }

    return 0;
    }



