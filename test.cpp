
#include "VEDLibh.h"
//void multimat (double A[][4], POINT sa, double B[][4], POINT sb, double C[][4], POINT sc);



int main()
    {
    txCreateWindow (800, 600);
    ARRSIZ sa = {3, 3};
    ARRSIZ sb = {3, 3};
    double a[ALLMSX][ALLMSY] = {{12, 10, 5},
                                { 4,  7, 2},
                                { 7,  1, 3}};

    double b[ALLMSX][ALLMSY] = {{2, 0, 0},
                                {0, 3, 0},
                                {0, 0, 1}};
    multimat (sa, a, sb, b, sa, a);
    //printmat (sa, a);

    txSetColor (TX_GREEN);
    txLine (100, 100, 700, 140);
    txLine (700, 140, 300, 700);
    txLine (100, 100, 300, 700);
    txSetColor (TX_WHITE);
    VEDTriangle ({100, 100, 0}, {700, 140, 0}, {300, 700, 0});
    return 0;
    }







