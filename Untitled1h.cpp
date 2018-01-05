
#include "VEDLibh.h"


int main()
    {
    VEDStart ();

    tx_auto_func(delete [] ZBuffer);
    tx_auto_func(txDeleteDC(MyScreen));

    VEDTranslate (0, -100, 100);
    VEDScale (40, 40, 40);
    //VEDCube(false);

    Triangle *Sphere = new Triangle[4000];
    tx_auto_func (delete [] Sphere);
    //printf ("a\n");
    //getch();
    int SpherePointsAmount = initSphere(PI/26, Sphere);
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
            //VEDFigure (Sphere, SpherePointsAmount);
            //VEDCube(false);
            }

        if (GetAsyncKeyState (VK_LSHIFT)) control (5);
        txBitBlt (0, 0, MyScreen);
        makeBufferDefault();
        }

    return 0;
    }






