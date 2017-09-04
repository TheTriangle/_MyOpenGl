
#include "VEDLibh.h"


void RotX (double a);
double D2DEFORMATION [ALLMSX][ALLMSY] = {{200, 0, 0},
                                         {0, 200, 0},
                                         {0, 0, 200}};

ARRSIZ MYSDEF = {4, 4};

int main()
    {

    txCreateWindow (GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

    double corda [ALLMSX][ALLMSY] = {{-1, -1,  1, 0}};
    double cordb [ALLMSX][ALLMSY] = {{-1, -1, -1, 0}};
    double cord1 [ALLMSX][ALLMSY] = {{-1, -1,  1, 0}};
    double cord2 [ALLMSX][ALLMSY] = {{ 1, -1, -1, 0}};
    txSetFillColor (TX_BLACK);
    txSetColor (TX_WHITE);
    while (!GetAsyncKeyState (VK_ESCAPE))
        {
        if (GetAsyncKeyState ('A')) RotX (-0.1125);
        if (GetAsyncKeyState ('D')) RotX ( 0.1125);
        txSleep(1);
        //txClear();
        multimat (MYSDEF, corda, MYSDEF, D2DEFORMATION, MYSDEF, cord1);
        multimat (MYSDEF, cordb, MYSDEF, D2DEFORMATION, MYSDEF, cord2);
        txLine (txGetExtentX()/2 + (cord1[0][0] / cord1[0][3] * 100), txGetExtentY()/2 - (cord1[0][1] / cord1[0][3] * 100),
                txGetExtentX()/2 + (cord2[0][0] / cord2[0][3] * 100), txGetExtentY()/2 - (cord2[0][1] / cord2[0][3] * 100));
        }
    return 0;
    }




void RotX (double a)
    {
    double rotation[ALLMSX][ALLMSY] = {{1, 0, 0, 0},
                                       {0, cos(a), -sin(a)},
                                       {0, sin(a), cos(a), 0},
                                       {0, 0, 0, 1}};
    multimat (MYSDEF, D2DEFORMATION, MYSDEF, rotation, MYSDEF, D2DEFORMATION);
    }
