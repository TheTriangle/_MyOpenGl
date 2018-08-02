
#include "VEDLibh.h"
#include "Windows.h"
#include <vector>

int main()
    {
    VEDStart ();
    VEDScale (50, 50, 50);

    MYP texturesizes = {1024, 1024, 0}; //недостаток bmp->hdc->rgbquad(DIB), а не чтения файла.

    RGBQUAD *TexturePixels = VEDLoadRGBQUADImage ("african_head_diffuse.bmp", texturesizes);
    RGBQUAD *NormalsPixels = VEDLoadRGBQUADImage ("african_head_nm.bmp", texturesizes);
    RGBQUAD *SpecsPixels   = VEDLoadRGBQUADImage ("african_head_spec.bmp", texturesizes);

    ObjTriangle  *Head = new ObjTriangle[20000];
    Triangle *JustHead = new Triangle[20000];

    int HeadSize = makeObjFigure (Head, "african_head.obj");
    VEDMakeTriangleFigure (JustHead, Head, HeadSize);

    txSetFillColor(TX_BLACK);

    while(!GetAsyncKeyState(VK_ESCAPE))
        {
        control(3);
        txSetFillColor (TX_BLACK, MyScreen);
        txClear(MyScreen);

        txSetFillColor (TX_BLACK, MyScreen);
        VEDObjFigure (Head, HeadSize, TexturePixels, NormalsPixels, SpecsPixels, texturesizes);
        txBitBlt (0, 0, MyScreen);

        txSleep(1);
        makeBufferDefault();
        }

    VEDFinish();
    delete [] ZBuffer;
    delete [] Head;
    //delete [] TexturePixels;
    return 0;
    }

