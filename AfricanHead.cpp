
#include "VEDLibh.h"
#include "Windows.h"
#include <vector>

int main()
    {
    VEDStart ();
    //VEDTranslate (8000, 6000, 1);
    VEDTranslate (0, 0, 200);
    VEDScale (50, 50, 50);

    MYP texturesizes = {1024, 1024, 0}; //недостаток bmp->hdc->rgbquad(DIB), а не чтения файла.
    RGBQUAD *TexturePixels = VEDLoadRGBQUADImage ("african_head_diffuse.bmp", texturesizes);
    RGBQUAD *NormalsPixels = VEDLoadRGBQUADImage ("african_head_nm.bmp", texturesizes);
    RGBQUAD *SpecsPixels   = VEDLoadRGBQUADImage ("african_head_spec.bmp", texturesizes);

    //for (int x = 0; x < 1024; x++)
    //    {
    //    for (int y = 0; y < 1024; y++)
    //        {
    //        MyPixels[x + y * SzScr.x] = TexturePixels[x + y * 1024];
    //        }
    //    }
    //txBitBlt (0, 0, MyScreen);
    //getch();

    ObjTriangle  *Head = new ObjTriangle[20000];
    Triangle *JustHead = new Triangle[20000];

    int HeadSize = makeObjFigure (Head, "african_head.obj");
    VEDMakeTriangleFigure (JustHead, Head, HeadSize);
    //printf ("iamhere1\n");
    //getch();
    txSetFillColor(TX_BLACK);
    while(!GetAsyncKeyState(VK_ESCAPE))
        {
        control(5);
        if (GetAsyncKeyState('F'))
            {
            txSetFillColor (TX_BLACK, MyScreen);
            txClear(MyScreen);
            }
        //printf ("iamhere2\n");
        getch();

        if (GetAsyncKeyState('V'))
            {
            txSetFillColor (TX_BLACK, MyScreen);
            VEDObjFigure (Head, HeadSize, TexturePixels, NormalsPixels, SpecsPixels, texturesizes);
            //VEDFigure (JustHead, HeadSize);
            //printf ("iamhere4\n");
            getch();
            txBitBlt (0, 0, MyScreen);
            }

        //printf ("iamhere3\n");
        getch();
        if (GetAsyncKeyState(VK_LSHIFT)) control (0.1);
        txSleep(10);
        //control(30);
        //getch();
        makeBufferDefault();
        }
    delete [] ZBuffer;
    delete [] Head;
    //delete [] TexturePixels;
    txDeleteDC(MyScreen);
    return 0;
    }

