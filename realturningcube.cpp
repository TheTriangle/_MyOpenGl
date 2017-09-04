
#include "VEDLib.h"

int main()
    {
    txCreateWindow (800, 600);

    double x = 0, y = 0, z = 2;
    double wx = 50;
    double wy = 50;
    double wz = 10;
    double alx = 0;
    double alz = 0;
    //double dist = 150;
    while (!GetAsyncKeyState (VK_ESCAPE))
        {
        //printf ("x == %d            y == %d\n wx == %d          wy == %d", x, y, diffx, diffy);
        txClearConsole();
        txSleep (1);
        txSetFillColor (TX_BLACK);
        txClear ();
        txSetColor (TX_WHITE);
        VEDCentrEdge (x, y, z, /*x + dist, y + dist, z + dist,*/  wx, wy, wz, alx, alz/*, wx*/);
        if (GetAsyncKeyState (VK_RIGHT )) wx += 10;
        if (GetAsyncKeyState (VK_LEFT  )) wx -= 10;
        if (GetAsyncKeyState (VK_UP    )) wy += 10;
        if (GetAsyncKeyState (VK_DOWN  )) wy -= 10;
        if (GetAsyncKeyState (VK_SHIFT )) wz -= 10;
        if (GetAsyncKeyState (VK_RETURN)) wz += 10;


        if (GetAsyncKeyState ('D')) x+=10;
        if (GetAsyncKeyState ('S')) y+=10;
        if (GetAsyncKeyState ('A')) x-=10;
        if (GetAsyncKeyState ('W')) y-=10;

        if (GetAsyncKeyState ('B')) alx+=0.01;
        if (GetAsyncKeyState ('N')) alz+=0.001;

        }

    return 0;
    }
