
#include "VEDLibh.h"


int main()
    {
    tx_auto_func(delete [] ZBuffer);
    tx_auto_func(txDeleteDC(MyScreen));

    SzScr = POINT{GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)};

    ZBuffer = new double[SzScr.x * SzScr.y];

    MakeBufferDefault();

    txCreateWindow (SzScr.x, SzScr.y);

    MyScreen = txCreateDIBSection(SzScr.x, SzScr.y, &MyPixels);

    VEDTranslate (0, 0, 100);
    VEDScale (40, 40, 40);
    //VEDCube(false);

    Triangle Sphere[1000] = {};
    //printf ("a\n");
    //getch();
    int SpherePointsAmount = initSphere(PI/12, Sphere);
    //printf ("a\n");
    VEDFigure (Sphere, SpherePointsAmount);

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
            VEDFigure (Sphere, SpherePointsAmount);
            //VEDCube(false);
            }

        if (GetAsyncKeyState (VK_LSHIFT)) control (5);
        txBitBlt (0, 0, MyScreen);
        MakeBufferDefault();
        }

    return 0;
    }






