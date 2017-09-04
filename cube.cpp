
#include "VEDLib.h"

int main()
    {
    txCreateWindow (800, 600);
    int x = 400, y = 300, z = 50;
    int diffx = 50;
    int diffy = 50;
    int extrax = 0;
    int extray = 0;
    //int dist = 150;
    while (!GetAsyncKeyState (VK_ESCAPE))
        {
        printf ("x == %d            y == %d\n wx == %d          wy == %d", x, y, diffx, diffy);
        txClearConsole();
        txSleep (1);
        txSetFillColor (TX_BLACK);
        txClear ();
        txSetColor (TX_WHITE);
        VEDcube (x, y, z, /*x + dist, y + dist, z + dist,*/ diffx, diffy, 10, extrax, extray);
        if (GetAsyncKeyState (VK_RIGHT)) diffx += 10;
        if (GetAsyncKeyState (VK_LEFT )) diffx -= 10;
        if (GetAsyncKeyState (VK_UP   )) diffy += 10;
        if (GetAsyncKeyState (VK_DOWN )) diffy -= 10;

        if (GetAsyncKeyState ('D')) x+=10;
        if (GetAsyncKeyState ('S')) y+=10;
        if (GetAsyncKeyState ('A')) x-=10;
        if (GetAsyncKeyState ('W')) y-=10;

        if (GetAsyncKeyState ('Q')) {extray-=10; /*diffx++; diffy++;*/}
        if (GetAsyncKeyState ('E')) {extray+=10; /*diffx--; diffy--;*/}
        if (GetAsyncKeyState ('Z')) {extrax-=10; /*diffx--; diffy--;*/}
        if (GetAsyncKeyState ('C')) {extrax+=10; /*diffx--; diffy--;*/}


        }

    return 0;
    }



