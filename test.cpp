
#include "VEDLibh.h"
int main()
    {
    txCreateWindow (800, 600);
    //VEDLine (500, 350, 600, 300, {255, 255, 255}, {255, 255, 255});
    //VEDLine (500, 300, 600, 350, {255, 255, 255}, {255, 255, 255});
    //VEDLine (600, 300, 600, 400, TX_WHITE, RGB(250, 250, 250));
    //VEDLine (500, 300, 600, 400, TX_WHITE, RGB(250, 250, 250));
    //VEDLine (500, 300, 550, 400, TX_WHITE, RGB(250, 250, 250));
    //VEDLine (500, 300, 600, 350, TX_WHITE, RGB(250, 250, 250));
    VEDTriangle ({300, 70, 0}, {700, 70, 0}, {100, 550, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 255});
    //txSetFillColor (TX_RED);
    //txCircle(300, 70, 50);
    //txSetFillColor (TX_BLACK);
    //txCircle(100, 550, 50);
    //txSetFillColor (TX_BLUE);
    //txCircle(700, 70, 50);
    return 0;
    }
