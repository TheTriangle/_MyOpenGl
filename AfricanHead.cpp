
#include "VEDLibh.h"
#include <vector>

bool control (double speed = 1);
void drawVec (MYP Vector[]);
int FillVec (MYP Vector[]);
int main()
    {
    using namespace std;

    tx_auto_func(delete [] ZBuffer);
    tx_auto_func(txDeleteDC(MyScreen));

    SzScr = POINT{GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)};

    ZBuffer = new double[SzScr.x * SzScr.y];
    MakeBufferDefault();

    txCreateWindow (SzScr.x, SzScr.y);

    MyScreen = txCreateDIBSection(SzScr.x, SzScr.y, &MyPixels);

    VEDTranslate (8000, 6000, 1);
    VEDScale (1200, 1200, 20);

    MYP PointsVec[2000];
    FillVec (PointsVec);
    txSetFillColor(TX_BLACK);
    while(!GetAsyncKeyState(VK_ESCAPE))
        {
        txClearConsole();
        drawVec (PointsVec);
        if (GetAsyncKeyState(VK_LSHIFT)) control (2);
        txBitBlt (0, 0, MyScreen);
        control(30);
        getch();
        txClear();
        }
    return 0;
    }

int FillVec (MYP Vector[])
    {
    FILE *model;
    if ((model = fopen ("african_head.obj", "r")) == NULL)
        {
        printf ("Cannot open obj");
        exit(1);
        }
    char type[20];
    double ScX;
    double ScY;
    double ScZ;
    int i = 0;
    while (!feof(model))
        {
        fscanf (model, "%s%lf%lf%lf", type, &ScX, &ScY, &ScZ);
        //printf("%s", type);
        //getch();
        if (type[0] == 'v' && type[1] == NULL)
            {
            //getch();
            Vector[i].x = ScX;
            Vector[i].y = ScY;
            Vector[i].z = ScZ;
            //printf (" %f %f %f\n", Vector[i].x, Vector[i].y, Vector[i].z);
            //getch();
            }
        else
            {
            //getch();
            //printf ("'!= 'v'\n");
            }
        i++;
        }
    fclose(model);
    return i;
    }

void drawVec (MYP Vector[])
    {
    FILE *model;
    if ((model = fopen ("african_head.obj", "r")) == NULL)
        {
        printf ("Cannot open obj");
        exit(1);
        }
    char type[20];
    int fnum;
    int snum;
    int tnum;
    //int i = 0;
    while (!feof(model))
        {
        fscanf (model, "%s%d/%d/%d", type, &fnum, &snum, &tnum);
        if (type[0] == 'f' && type[1] == NULL)
            {
            //VEDTriangle ({Vector[fnum].x + SzScr.x/2, Vector[fnum].y + SzScr.y/2, Vector[fnum].z},
            //             {Vector[snum].x + SzScr.x/2, Vector[snum].y + SzScr.y/2, Vector[snum].z},
            //             {Vector[tnum].x + SzScr.x/2, Vector[tnum].y + SzScr.y/2, Vector[tnum].z}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255});
            VEDTriangle (Vector[fnum],
                         Vector[snum],
                         Vector[tnum], {255, 255, 255}, {255, 255, 255}, {255, 255, 255});
            //printf ("%s %d/%d/%d\n", type, fnum, snum, tnum);
            //getch();
            }
        //else printf ("'%s' != 'f'", type);
        }
    }





bool control (double speed)
    {
    bool returning = false;

    if (GetAsyncKeyState ('R'))
        {
        ShowMeZBuffer = true;
        returning = true;
        }
    else
        {
        returning = true;
        ShowMeZBuffer = false;
        }
    if (GetAsyncKeyState (VK_RIGHT))
        {
        returning = true;
        VEDScale (1.3 * speed,   0,     0);
        }

    if (GetAsyncKeyState (VK_LEFT))
        {
        returning = true;
        VEDScale (0.7 * speed,   0,     0);
        }

    if (GetAsyncKeyState (VK_UP))
        {
        returning = true;
        VEDScale (0, 1.3 * speed,     0);
        }

    if (GetAsyncKeyState (VK_DOWN))
        {
        returning = true;
        VEDScale (0, 0.7 * speed,     0);
        }

    if (GetAsyncKeyState (VK_RSHIFT))
        {
        returning = true;
        VEDScale (0,   0,   1.1 * speed);
        }

    if (GetAsyncKeyState (VK_RETURN))
        {
        returning = true;
        VEDScale (0,   0,   0.9 * speed);
        }

    if (GetAsyncKeyState ('N'))
        {
        if (GetAsyncKeyState (31))
            {
            returning = true;
            NPLANE = 1;
            }

        if (GetAsyncKeyState (32))
            {
            returning = true;
            NPLANE = 2;
            }

        if (GetAsyncKeyState (33))
            {
            returning = true;
            NPLANE = 3;
            }

        if (GetAsyncKeyState (34))
            {
            returning = true;
            NPLANE = 4;
            }

        if (GetAsyncKeyState (35))
            {
            returning = true;
            NPLANE = 5;
            }

        if (GetAsyncKeyState (36))
            {
            returning = true;
            NPLANE = 6;
            }

        if (GetAsyncKeyState (37))
            {
            returning = true;
            NPLANE = 7;
            }

        if (GetAsyncKeyState (38))
            {
            returning = true;
            NPLANE = 8;
            }

        if (GetAsyncKeyState (39))
            {
            returning = true;
            NPLANE = 9;
            }
        }

    if (GetAsyncKeyState ('F'))
        {
        if (GetAsyncKeyState (31))
            {
            returning = true;
            FPLANE = 1;
            }

        if (GetAsyncKeyState (32))
            {
            returning = true;
            FPLANE = 2;
            }

        if (GetAsyncKeyState (33))
            {
            returning = true;
            FPLANE = 3;
            }

        if (GetAsyncKeyState (34))
            {
            returning = true;
            FPLANE = 4;
            }

        if (GetAsyncKeyState (35))
            {
            returning = true;
            FPLANE = 5;
            }

        if (GetAsyncKeyState (36))
            {
            returning = true;
            FPLANE = 6;
            }

        if (GetAsyncKeyState (37))
            {
            returning = true;
            FPLANE = 7;
            }

        if (GetAsyncKeyState (38))
            {
            returning = true;
            FPLANE = 8;
            }

        if (GetAsyncKeyState (39))
            {
            returning = true;
            FPLANE = 9;
            }
        }


    if (GetAsyncKeyState ('D'))
        {
        returning = true;
        VEDTranslate (4 * speed,  0,   0);
        }

    if (GetAsyncKeyState ('A'))
        {
        returning = true;
        VEDTranslate (-4 * speed,  0,   0);
        }

    if (GetAsyncKeyState ('W'))
        {
        returning = true;
        VEDTranslate (0, -4 * speed,   0);
        }

    if (GetAsyncKeyState ('S'))
        {
        returning = true;
        VEDTranslate (0,  4 * speed,   0);
        }

    if (GetAsyncKeyState ('Q'))
        {
        returning = true;
        VEDTranslate (0,  0,   4 * speed);
        }

    if (GetAsyncKeyState ('E'))
        {
        returning = true;
        VEDTranslate (0,  0,  -4 * speed);
        }


    if (GetAsyncKeyState ('O'))
        {
        if (GetAsyncKeyState ('Z'))
            {
            VEDRotateZ (-0.0175 * speed);
            returning = true;
            }

        if (GetAsyncKeyState ('X'))
            {
            VEDRotateX (-1.75 * speed);
            returning = true;
            }

        if (GetAsyncKeyState ('Y'))
            {
            VEDRotateY (-1.75 * speed);
            returning = true;
            }
        }

    if (GetAsyncKeyState ('P'))
        {
        if (GetAsyncKeyState ('Z'))
            {
            VEDRotateZ (0.0175 * speed);
            returning = true;
            }

        if (GetAsyncKeyState ('X'))
            {
            VEDRotateX (1.75 * speed);
            returning = true;
            }

        if (GetAsyncKeyState ('Y'))
            {
            VEDRotateY (1.75 * speed);
            returning = true;
            }
        }

    return returning;
    }

