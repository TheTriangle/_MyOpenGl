
//#include "VEDLibh.h"
#include "TXLib.h"
//void multimat (double A[][4], POINT sa, double B[][4], POINT sb, double C[][4], POINT sc);



int main()
    {
    txCreateWindow (800, 600);
    POINT sa = {3, 3};
    POINT sb = {3, 3};
    double a[3][3] = {{12, 10, 5},
                                { 4,  7, 2},
                                { 7,  1, 3}};

    //double b[ALLMSX][ALLMSY] = {{2, 0, 0},
    //                            {0, 3, 0},
    //                            {0, 0, 1}};
    //multimat (sa, a, sb, b, sa, a);
    //printmat (sa, a);
    printf ("%f", a[0][1]);
    return 0;
    }







