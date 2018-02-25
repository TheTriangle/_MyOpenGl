
#include "TXLib.h"

int main()
    {
    txCreateWindow (1024, 1024);

    txSetFillColor (TX_WHITE);
    txClear();
    txSetColor (TX_BLACK, 1);
    txSetFillColor (TX_BLACK);
    int stepper = 1;
    int rectsize = 40;
    for (int x = 0; x < 1024; x += rectsize)
        {
        stepper = -stepper;
        for (int y = 0 + (stepper + 1)/2 * rectsize; y < 1024; y += 2 * rectsize)
            {
            txRectangle (x, y, x + rectsize, y + rectsize);
            }
         }
    txSaveImage ("african_head_white.bmp");

    return 0;
    }
