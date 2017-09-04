
#include "VEDLibh.h"

int main()
    {
    txCreateWindow (800, 600);
    ARRSIZ s1 = {4, 4};
    ARRSIZ s2 = {4, 4};
    ARRSIZ s3 = {4, 4};

    double num1[allmsx][allmsy] = {{1, 2, 3, 1},
                                   {0, 0, 0, 0},
                                   {0, 0, 0, 0},
                                   {0, 0, 0, 0}};
    double num2[allmsx][allmsy] = {{1, 0, 0, 0},
                                   {0, 1, 0, 0},
                                   {0, 0, 1, 0},
                                   {1, 2, 3, 1}};
    double num3[allmsx][allmsy] = {};

    multimat (s1, num1, s2, num2, s2, num2);
    printmat (s2, num2);
    printf ("%f", num2[3][1]);

    return 0;
    }
