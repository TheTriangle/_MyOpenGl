
#include "VEDLibh.h"
int main()
    {
    txCreateWindow (800, 600);
    MYP firstvec = {12, 5, 1};
    return 0;
    }




#include "VEDLibh.h"
#include "Windows.h"
#include <vector>

void drawVec (MYP Vector[]);
int FillVec (MYP Vector[]);

int main()
    {
    VEDStart ();
    //VEDTranslate (8000, 6000, 1);
    VEDTranslate (0, 0, 100);
    VEDScale (50, 50, 50);

    RGBQUAD *TexturePixels = new RGBQUAD[4000000]; //2000x2000
    HDC TextureDC = txLoadImage ("african_head_diffuse.bmp");
    MYP TextureSize = {1024, 1024, 0};
    //TextureDC = txCreateDIBSection (TextureSize.x, TextureSize.y, &TexturePixels);
    TextureDC = txLoadImage ("african_head_diffuse.bmp");
    SetDIBColorTable(TextureDC, 0, TextureSize.x * TextureSize.y, TexturePixels);

    if (!TextureDC)
        {
        printf ("cannot load image");
        getch();
        }

    for (int x = 0; x < 1024; x++)
        {
        for (int y = 0; y < 1024; y++)
            {
            TexturePixels[x + y * 1024] = {255, 255, 255};
            }
        }

    for (int x = 0; x < 1024; x++)
        {
        for (int y = 0; y < 1024; y++)
            {
            txSetPixel (x, y, RGB(TexturePixels[x + y * 1024].rgbRed, TexturePixels[x + y * 1024].rgbGreen, TexturePixels[x + y * 1024].rgbBlue));
            }
        }
    getch();

    txBitBlt (0, 0, TextureDC);
    getch();
    ObjTriangle *Head = new ObjTriangle[10000];

    int HeadSize = makeObjFigure (Head, "african_head.obj");
    txSetFillColor(TX_BLACK);
    while(!GetAsyncKeyState(VK_ESCAPE))
        {
        control(5);
        if (GetAsyncKeyState('F'))
            {
            txSetFillColor (TX_BLACK, MyScreen);
            txClear(MyScreen);
            }

        if (GetAsyncKeyState('V'))
            {
            txSetFillColor (TX_BLACK, MyScreen);
            VEDObjFigure (Head, HeadSize, TexturePixels, TextureSize);
            txBitBlt (0, 0, MyScreen);
            }


        if (GetAsyncKeyState(VK_LSHIFT)) control (0.1);
        txSleep(10);
        //control(30);
        //getch();
        makeBufferDefault();
        }
    delete [] ZBuffer;
    delete [] Head;
    delete [] TexturePixels;
    txDeleteDC(MyScreen);
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
        if (type[0] == 'v' && type[1] == 0)
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
    int fnum = 0;
    int snum = 0;
    int tnum = 0;

    int fonum = 0;
    int finum = 0;
    int sinum = 0;

    int senum = 0;
    int einum = 0;
    int ninum = 0;
    //int i = 0;
    while (!feof(model))
        {
        fscanf (model, "%s%d/%d/%d %d/%d/%d %d/%d/%d", type, &fnum, &snum, &tnum,
                                                             &fonum, &finum, &sinum,
                                                             &senum, &einum, &ninum);
        if (type[0] == 'f' && type[1] == 0)
            {
            //VEDTriangle ({Vector[fnum].x + SzScr.x/2, Vector[fnum].y + SzScr.y/2, Vector[fnum].z},
            //             {Vector[snum].x + SzScr.x/2, Vector[snum].y + SzScr.y/2, Vector[snum].z},
            //             {Vector[tnum].x + SzScr.x/2, Vector[tnum].y + SzScr.y/2, Vector[tnum].z}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255});
            VEDTriangle (Vector[fnum],
                         Vector[snum],
                         Vector[tnum], {255, 255, 255}, {255, 255, 255}, {255, 255, 255});

            VEDTriangle (Vector[fonum],
                         Vector[finum],
                         Vector[sinum], {255, 255, 255}, {255, 255, 255}, {255, 255, 255});

            VEDTriangle (Vector[senum],
                         Vector[einum],
                         Vector[ninum], {255, 255, 255}, {255, 255, 255}, {255, 255, 255});
            //printf ("%s %d/%d/%d\n", type, fnum, snum, tnum);
            //getch();
            }
        //else printf ("'%s' != 'f'", type);
        }
    }





#include "TXLib.h"
#define ctg(x) (1/tan(x))
#define DEGREEMODIFIER 0.01745
#define PI 3.141593
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct MYP
    {
    double x;
    double y;
    double z;
    double length()
        {
        return sqrt(x * x + y * y + z * z);
        }

    MYP operator- (MYP right)
        {
        return {x - right.x, y - right.y, z - right.z};
        }

    MYP operator+ (MYP right)
        {
        return {x + right.x, y + right.y, z + right.z};
        }

    double operator^ (MYP right)
        {
        return (*this * right)/this->length()/right.length();
        }

    MYP operator/ (double right)
        {
        return {x / right, y / right, z / right};
        }

    MYP operator* (double right)
        {
        return {x * right, y * right, z * right};
        }

    MYP operator* (int right)
        {
        return {x * right, y * right, z * right};
        }

    double operator* (MYP right)
        {
        return {x * right.x + y * right.y + z * right.z};
        }

    MYP operator% (MYP right)
        {
        return {x * right.x, y * right.y, z * right.z};
        }

    MYP operator+ (double right)
        {
        return {x + right, y + right, z + right};
        }

    MYP ():
        x(0),
        y(0),
        z(0)
        {}

    MYP (double first, double second, double third):
        x(first),
        y(second),
        z(third)
        {}

    MYP (RGBQUAD ILoveWindowsH):
        x(ILoveWindowsH.rgbRed),
        y(ILoveWindowsH.rgbGreen),
        z(ILoveWindowsH.rgbBlue)
        {}
    };

struct Triangle
    {
    MYP f;
    MYP s;
    MYP t;
    Triangle ():
        f(),
        s(),
        t()
        {}

    Triangle (MYP gf, MYP gs, MYP gt):
        f(gf),
        s(gs),
        t(gt)
        {}

    };

struct ObjTriangle
    {
    Triangle cords;
    Triangle textures;
    Triangle normales;
    };

POINT SzScr = {0, 0};
double BufferDefault = 4000;
const double ZScalingCoeff = 0.0015;
const double defaultnormal = -5;
const double MaterialReflective = 15;

bool ShowMeZBuffer = false;
HDC MyScreen = NULL;

RGBQUAD *MyPixels = NULL;
double *ZBuffer = NULL;
#define MyPix(_x, _y, _z, _r, _g, _b)  int thisPixPos = (int)((_x) + (int)(SzScr.y - _y)*SzScr.x); \
                                                                                                    \
    if (thisPixPos < SzScr.x * SzScr.y && thisPixPos >= 0)                                           \
        {                                                                                             \
        if (_z <= ZBuffer[thisPixPos] || fabs (ZBuffer[thisPixPos] - _z) < 2)                          \
            {                                                                                           \
            if (ShowMeZBuffer) MyPixels[thisPixPos] = RGBQUAD {(BYTE)(_z/2), (BYTE)(_z/2), (BYTE)(_z/2)};\
            else MyPixels[thisPixPos] = RGBQUAD {_b, _g, _r};                                             \
            ZBuffer[thisPixPos] = _z;                                                                      \
            }                                                                                               \
        }


#define MyObjPix(_x, _y, _z, _textx, _texty, _texture, _textsizex, _textsizey) int thisPixPos = (int)((_x) + (int)(SzScr.y - _y)*SzScr.x); \
                                                                                                    \
    if (thisPixPos < SzScr.x * SzScr.y && thisPixPos >= 0)                                           \
        {                                                                                             \
        if (_z <= ZBuffer[thisPixPos] || fabs (ZBuffer[thisPixPos] - _z) < 2)                          \
            {                                                                                           \
            if (ShowMeZBuffer) MyPixels[thisPixPos] = RGBQUAD {(BYTE)(_z/2), (BYTE)(_z/2), (BYTE)(_z/2)};\
            else                                                                                          \
                {                                                                                          \
                plusassig (&MyPixels[thisPixPos], _texture[(int)(_textx + _texty * _textsizex)], 0.385); \
                if (_x < SzScr.x - 1 && _textx < _textsizex + 1) plusassig (&MyPixels[thisPixPos + 1], _texture[(int)(_textx + _texty * _textsizex + 1)], 0.154);  \
                                                                                                                                                                                               \
                if (_x >= 1 && _textx >= 1) plusassig (&MyPixels[thisPixPos - 1], _texture[(int)(_textx + _texty * _textsizex - 1)], 0.154);                         \
                                                                                                                                                                                                 \
                if (_y < SzScr.y - 1 && _texty < _textsizey + 1) plusassig (&MyPixels[thisPixPos + SzScr.x], _texture[(int)(_textx + (_texty + 1) * _textsizex)], 0.154);\
                                                                                                                                                                                                           \
                if (_y >= 1 && _texty >= 1) plusassig (&MyPixels[thisPixPos - SzScr.x], _texture[(int)(_textx + (_texty - 1) * _textsizex)], 0.154);                       \
                } \
            ZBuffer[thisPixPos] = _z;                                                                      \
            }                                                                                               \
        }

const int ALLMSX = 4;
const int ALLMSY = 4;
MYP DefaultLightPos = {0, 0, -2};
struct ARRSIZ
    {
    const int x;
    const int y;
    };




double TALX = 0;
double TALY = 0;
double TALZ = 0;

void VEDStart ();
void VEDLineFigure (Triangle Figure[], int amount);
int  VEDRotateZ    (double   a);
int  VEDjVertex    (double   x, double y, double z, double x1, double y1, double z1);
int  VEDRotateY    (double   a);
int  VEDRotateX    (double   a);
int  VEDTranslate  (double   x, double y, double z);
int  VEDCube       (bool isper);
int  VEDVertex     (MYP    old, MYP NEW, bool isper);
int  VEDObjTriangle   (MYP  first, MYP second, MYP third, MYP fcol, MYP scol, MYP tcol, RGBQUAD* texture, MYP textsize);
int  VEDObjHorTriangle(MYP   left, MYP right, MYP third, MYP lcol, MYP rcol, MYP tcol, RGBQUAD* texture, MYP textsize);
int  VEDTriangle   (MYP  first, MYP second, MYP third, MYP fcol, MYP scol, MYP tcol);
int  VEDHorTriangle(MYP   left, MYP right, MYP third, MYP lcol, MYP rcol, MYP tcol);
int  VEDLine       (double  x1, double y1, double z1, double x2, double y2, double z2, MYP col1, MYP col2);
int  VEDObjLine    (double  x1, double y1, double z1, double x2, double y2, double z2, MYP col1, MYP col2, RGBQUAD* texture, MYP textsize);
int  VEDScale      (double  wx, double wy, double wz);

void VED3dTriangle (MYP first, MYP second, MYP third,
                    MYP  col1,   MYP col2,  MYP col3,
                    MYP lightpos = DefaultLightPos, MYP lightcol = {255, 155, 155}, MYP viewpos = {0, 0, -5});

//void VED3dObjTriangle (MYP first, MYP second, MYP third,
//                    MYP  col1,   MYP col2,  MYP col3, RGBQUAD* texture, MYP textsize,
//                    MYP lightpos = DefaultLightPos, MYP lightcol = {255, 155, 155}, MYP viewpos = {0, 0, -5},
//                    MYP Normal1 = {defaultnormal, 0, 0}, MYP Normal2 = {defaultnormal, 0, 0}, MYP Normal3 = {defaultnormal, 0, 0});

void VED3dObjTriangle (ObjTriangle triangle, RGBQUAD* texture, MYP textsize,
                       MYP lightpos = DefaultLightPos, MYP lightcol = {255, 155, 155}, MYP viewpos = {0, 0, -5});

void VEDFigure     (Triangle Figure[], int TrianglesAmount);

int initSphere (double stepAngle, Triangle Figure[]);

MYP  makeAllVecDeforms (MYP getVec, bool isper = false, bool istran = true, bool issized = true, bool isrot = true);
void makeBufferDefault ();
void makeAllDeforms (double cord [ALLMSX][ALLMSY], bool isper = false, bool istran = true, bool issized = true, bool isrot = true);
int  makeObjFigure (ObjTriangle Figure[], string getName);
int  makemat (ARRSIZ SM, double A[ALLMSX][ALLMSY], double B[ALLMSX][ALLMSY]);

void RotateMatrixY (double GaveMatrix[][ALLMSY], double angle);
MYP  RotateVecY (MYP GaveVec, double angle);

bool control (double speed = 1);

void drawVec (MYP start, MYP vec, COLORREF color = TX_GREEN, COLORREF pointcolor = TX_RED, int width = 1, int pointrad = 15);
MYP  VectorMultip (MYP a, MYP b);

void MYPSwap (MYP* pt1, MYP* pt2);

void plusassig (RGBQUAD *left, RGBQUAD right, double Koeff = 1);
void swap (double* s1, double* s2);

void makePerspective (double mat[ALLMSX][ALLMSY], double n, double f);

void copymatrix (ARRSIZ size, double To[ALLMSX][ALLMSY], double From[ALLMSX][ALLMSY]);
int  printmat (ARRSIZ sm, double m[ALLMSX][ALLMSY]);
void multimat  (ARRSIZ sa, double A[ALLMSX][ALLMSY], ARRSIZ sb, double B[ALLMSX][ALLMSY], ARRSIZ sc, double C[ALLMSX][ALLMSY]);

//double SM [ALLMSX][ALLMSY] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
double TRAN [ALLMSX][ALLMSY] = {{1, 0, 0, 0},
                                {0, 1, 0, 0},
                                {0, 0, 1, 0},
                                {0, 0, 0, 1}};
double ALX [ALLMSX][ALLMSY] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
double ALY [ALLMSX][ALLMSY] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
double ALZ [ALLMSX][ALLMSY] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

ARRSIZ SCORD = {1, 4};
                                   //TODO merge all deformation matrix into one,
                                   //TODO make arrays dynamic
double FPLANE = 5;
double NPLANE = 4;
double PERSPECTIVE [ALLMSX][ALLMSY] = {{ctg(50 * 0.01745)/(4/3), 0, 0, 0},
                      {0, ctg(40 * 0.01745), 0, 0},
                      {0, 0, (FPLANE + NPLANE)/(FPLANE - NPLANE), 1},
                      {0, 0, (-2*FPLANE*NPLANE)/(FPLANE - NPLANE), 0}};


double DEFORMATION [ALLMSX][ALLMSY] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

ARRSIZ SDEF = {4, 4};

ARRSIZ STRAN = {4, 4};


ARRSIZ SAL = {4, 4};

ARRSIZ SS  = {4, 4};

int VEDScale (double wx, double wy, double wz)
    {
    if (ROUND (wx * 1000) == 0) wx = 1;
    if (ROUND (wy * 1000) == 0) wy = 1;
    if (ROUND (wz * 1000) == 0) wz = 1;
    double s [ALLMSX][ALLMSY] = {{wx, 0, 0, 0}, {0, wy, 0, 0}, {0, 0, wz, 0}, {0, 0, 0, 1}};
    multimat (SDEF, DEFORMATION, SS, s, SDEF, DEFORMATION);
    return 1;
    }


int VEDRotateX (double a)
    {
    TALX += a;
    /*double madealx [ALLMSX][ALLMSY] = {{0,      0,       0, 1},
                                       {0,  cos(TALX/57.3), sin(TALX/57.3), 0},
                                       {0, -sin(TALX/57.3), cos(TALX/57.3), 0},
                                       {1,      0,       0, 0}};


    multimat (SDEF, DEFORMATION, SAL, madealx, SDEF, DEFORMATION);
    txClearConsole();
    */
    ALX[1][1] = cos(TALX/60);
    ALX[1][2] =-sin(TALX/60);
    ALX[2][1] = sin(TALX/60);
    ALX[2][2] = cos(TALX/60);
    return 1;
    }


int VEDRotateY (double a)
    {
    TALY += a;

    ALY[0][0] = cos(TALY/60);
    ALY[0][2] = sin(TALY/60);
    ALY[2][0] =-sin(TALY/60);
    ALY[2][2] = cos(TALY/60);
    /*double madealy [ALLMSX][ALLMSY] = {{cos(a/57.3), 0, -sin(a/57.3), 0},
                                       {     0, 1,       0, 0},
                                       {sin(a/57.3), 0,  cos(a/57.3), 0},
                                       {     0, 0,       0, 1}};
    multimat (SDEF, DEFORMATION, SAL, madealy, SDEF, DEFORMATION);
    */return 1;
    }




int VEDRotateZ (double a)
    {
    TALZ += a;
    //printf ("called, a == %f", a);
    ALZ[0][0] = cos(TALZ);
    ALZ[0][1] =-sin(TALZ);
    ALZ[1][0] = sin(TALZ);
    ALZ[1][1] = cos(TALZ);
    return 1;
    }



int VEDTranslate (double x, double y, double z)
    {
    TRAN[0][3] += x;
    TRAN[1][3] += y;
    TRAN[2][3] += z;
    return 1;
    }

void VED3dObjTriangle  (ObjTriangle givenTriangle, RGBQUAD* texture, MYP texturesize, MYP lightpos, MYP lightcol, MYP viewpos)
    {
    double cord1 [ALLMSX][ALLMSY] = {{givenTriangle.cords.f.x, 0, 0, 0}, {givenTriangle.cords.f.y, 0, 0, 0}, {givenTriangle.cords.f.z, 0, 0, 0}, {1, 0, 0, 0}};
    double cord2 [ALLMSX][ALLMSY] = {{givenTriangle.cords.s.x, 0, 0, 0}, {givenTriangle.cords.s.y, 0, 0, 0}, {givenTriangle.cords.s.z, 0, 0, 0}, {1, 0, 0, 0}};
    double cord3 [ALLMSX][ALLMSY] = {{givenTriangle.cords.t.x, 0, 0, 0}, {givenTriangle.cords.t.y, 0, 0, 0}, {givenTriangle.cords.t.z, 0, 0, 0}, {1, 0, 0, 0}};
    //MYP environmentcol = {0.2, 0.2, 0.2};
    //printf ("before1col1 == %f, %f, %f\n", col1.x, col1.y, col1.z);
    //makeAllVecDeforms (Normal);

    makeAllDeforms (cord1, false);
    makeAllDeforms (cord2, false);
    makeAllDeforms (cord3, false);

    lightpos.x = lightpos.x/ZScalingCoeff/lightpos.z;
    lightpos.y = lightpos.y/ZScalingCoeff/lightpos.z;

    MYP first  = {cord1[0][0], cord1[1][0], cord1[2][0]};
    MYP second = {cord2[0][0], cord2[1][0], cord2[2][0]};
    MYP third  = {cord3[0][0], cord3[1][0], cord3[2][0]};


    //MYP Normal  = VectorMultip (VecFS, VecFT);
    //if (GetAsyncKeyState ('N'))
    //    {
    //    drawVec (first, Normal);
    //    drawVec (second, Normal);
    //    drawVec (third, Normal);
    //    }
    //MYP Normal2 = VectorMultip (VecFS * -1, VecST);
    //MYP Normal3 = VectorMultip (VecST * -1, VecFT * -1);
    //Normal = Normal / Normal.length();
    //txLine (SzScr.x/2 + first.x, SzScr.y/2 + first.y, SzScr.x/2 + first.x - Normal.x/ZScalingCoeff/Normal.z * 100, SzScr.y/2 + first.y - Normal.y/ZScalingCoeff/Normal.z * 100, MyScreen);
    //txLine (SzScr.x/2 + first.x, SzScr.y/2 + first.y, SzScr.x/2 + first.x + Normal.x/ZScalingCoeff/Normal.z * 100, SzScr.y/2 + first.y + Normal.y/ZScalingCoeff/Normal.z * 100, MyScreen);
    if (GetAsyncKeyState('M'))
        {
        txSetColor (TX_YELLOW, 10, MyScreen);
        drawVec (first, lightpos - first);
        drawVec (second, lightpos - second);
        drawVec (third, lightpos - third);
        }

    VEDObjTriangle ({SzScr.x/2 + cord1[0][0], SzScr.y/2 + cord1[1][0], cord1[2][0]},
                    {SzScr.x/2 + cord2[0][0], SzScr.y/2 + cord2[1][0], cord2[2][0]},
                    {SzScr.x/2 + cord3[0][0], SzScr.y/2 + cord3[1][0], cord3[2][0]},
                    givenTriangle.textures.f, givenTriangle.textures.s, givenTriangle.textures.t, texture, texturesize);
    }


int VEDObjTriangle (MYP first, MYP second, MYP third, MYP ftext, MYP stext, MYP ttext, RGBQUAD* texture, MYP textsize)
    {
    //txSettextor (TX_GREEN);
    //VEDVertex (first, second, false);
    //txSettextor (RGB(0, 204, 204));
    //VEDVertex (second, third, false);
    //txSettextor (TX_WHITE);
    //VEDVertex (first, third, false);

    MYP down;
    MYP mid;
    MYP up;
    MYP dtext;
    MYP mtext;
    MYP utext;

//--------------------------------------
    if (first.y < second.y)           //
        {                              //
        if (first.y < third.y)        //
            {                         //
            down = first;             //
            dtext = ftext;              //
            if (second.y < third.y)   //
                {                     //
                mid = second;         //
                mtext = stext;          //
                up = third;           //
                utext = ttext;          //
                }                     //
            else                      //
                {                     //
                mid = third;          //
                mtext = ttext;          //
                up = second;          //
                utext = stext;          //
                }                     //
            }                         //
        else                          //
            {                         //
            down = third;             //
            dtext = ttext;              //
            if (first.y < second.y)   //
                {                     //
                mid = first;          //
                mtext = ftext;          //
                up = second;          //
                utext = stext;          //
                }                     //
            else                      //
                {                     //
                mid = second;         //
                mtext = stext;          //
                up = first;           //
                utext = ftext;          //
                }                     //
            }                         //
        }                             //
    else if (second.y < third.y)        // sorting
        {                               // points
        down = second;                //
        dtext = stext;                  //
        if (first.y < third.y)        //
            {                         //
            mid = first;              //
            mtext = ftext;              //
            up = third;               //
            utext = ttext;              //
            }                         //
        else                          //
            {                         //
            mid = third;              //
            mtext = ttext;              //
            up = first;               //
            utext = ftext;              //
            }                         //
        }                             //
    else                               //
        {                             //
        down = third;                 //
        dtext = ttext;                  //
        if (first.y < second.y)       //
            {                         //
            mid = first;              //
            mtext = ftext;              //
            up = second;              //
            utext = stext;              //
            }                         //
        else                          //
            {                         //
            mid = second;             //
            mtext = stext;              //
            up = first;               //
            utext = ftext;              //
            }                         //
        }                             //
//--------------------------------------

    double allheight = up.y - down.y;
    double allhwidth = up.x - down.x;

    double sectorheight = mid.y - down.y;

    if (fabs (allheight) < 1) return 0;

    double help = sectorheight/allheight;

    //printf ("mid.y == %f, down.y == %f\n", mid.y, down.y);
    //printf ("sech == %f\n", sectorheight);

    txSetColor (TX_WHITE, 1, MyScreen);
    //txSetFilltextor (RGB(dtext.x, dtext.y, dtext.z), MyScreen);

    //if (GetAsyncKeyState ('C')) txEllipse (down.x - 10, down.y - 10, down.x + 10, down.y + 10, MyScreen);

    //char helpch[16] = {};
    //sprintf (helpch, "%f", down.z);
    //txDrawText (down.x - 80, down.y - 50, down.x + 80, down.y - 20, helpch, DT_CENTER, MyScreen);

    //txSetFilltextor (RGB(mtext.x, mtext.y, mtext.z), MyScreen);

    //if (GetAsyncKeyState ('C')) txEllipse (mid.x - 10, mid.y - 10, mid.x + 10, mid.y + 10, MyScreen);

    //sprintf (helpch, "%f", down.z);
    //txDrawText (mid.x - 80, mid.y - 50, mid.x + 80, mid.y - 20, helpch, DT_CENTER, MyScreen);

    //txSetFilltextor (RGB(utext.x, utext.y, utext.z), MyScreen);

    //if (GetAsyncKeyState ('C')) txEllipse (up.x - 10, up.y - 10, up.x + 10, up.y + 10, MyScreen);

    //sprintf (helpch, "%f", down.z);
    //txDrawText (up.x - 80, up.y - 50, up.x + 80, up.y - 20, helpch, DT_CENTER, MyScreen);

    VEDObjHorTriangle ({help * allhwidth + down.x,
                     down.y + sectorheight + 1,
                     help * (up.z - down.z) + down.z},
                     mid, down,
                    {help * (utext.x - dtext.x) + dtext.x,
                     help * (utext.y - dtext.y) + dtext.y,
                     help * (utext.z - dtext.z) + dtext.z},
                     mtext, dtext, texture, textsize);

    VEDObjHorTriangle ({down.x + help * allhwidth,
                     down.y + sectorheight,
                     down.z + help * (up.z - down.z)},
                     mid, up,
                    {help * (utext.x - dtext.x) + dtext.x,
                     help * (utext.y - dtext.y) + dtext.y,
                     help * (utext.z - dtext.z) + dtext.z},
                     mtext, utext, texture, textsize);
    return 0;                                                               //линейная интерполяция
    }                                                                         //x = x0 + t*(x1-x0)


int VEDObjHorTriangle(MYP left, MYP right, MYP third, MYP ltext, MYP rtext, MYP ttext, RGBQUAD* texture, MYP textsize)
    {
    double allheight = third.y - left.y;
    //printf ("third.y == %f\n left.y == %f", third.y, left.y);
    if (fabs (allheight) <= 1)
        {
        //getch();
        VEDLine (left.x, left.y, left.z, right.x, right.y, right.z, ltext, rtext);
        return 0;
        //printf ("i've returned");
        }
    //printf ("allh == %f\n", allheight);
    //printf ("a\n");
    //getch();
    double signum = allheight/fabs(allheight);
    bool exit = true;
    double nowheight = 0;
    double leftwidth = third.x - left.x;
    double rightwidth = third.x - right.x;
    double help = 0;
    for (double nowy = left.y; exit; nowy += signum)
        {
        //txSleep(10);
        nowheight = third.y - nowy;
        if (signum > 0 && nowy + signum >= third.y) exit = false;
        if (signum < 0 && nowy + signum <= third.y) exit = false;
        //printf ("b\n");
        //getch();
        help = nowheight/allheight;
        VEDObjLine ( left.x + help* leftwidth,  left.y + nowheight,  left.z + help*(third.z -  left.z),
                 right.x + help*rightwidth, right.y + nowheight, right.z + help*(third.z - right.z),
                 {ltext.x + help*(ttext.x - ltext.x), ltext.y + help*(ttext.y - ltext.y), ltext.z + help*(ttext.z - ltext.z)},
                 {rtext.x + help*(ttext.x - rtext.x), rtext.y + help*(ttext.y - rtext.y), rtext.z + help*(ttext.z - rtext.z)}, texture, textsize);
        }
    return 0;
    }



int VEDTriangle (MYP first, MYP second, MYP third, MYP fcol, MYP scol, MYP tcol)
    {
    //txSetColor (TX_GREEN);
    //VEDVertex (first, second, false);
    //txSetColor (RGB(0, 204, 204));
    //VEDVertex (second, third, false);
    //txSetColor (TX_WHITE);
    //VEDVertex (first, third, false);

    MYP down;
    MYP mid;
    MYP up;
    MYP dcol;
    MYP mcol;
    MYP ucol;

//--------------------------------------
    if (first.y < second.y)           //
        {                              //
        if (first.y < third.y)        //
            {                         //
            down = first;             //
            dcol = fcol;              //
            if (second.y < third.y)   //
                {                     //
                mid = second;         //
                mcol = scol;          //
                up = third;           //
                ucol = tcol;          //
                }                     //
            else                      //
                {                     //
                mid = third;          //
                mcol = tcol;          //
                up = second;          //
                ucol = scol;          //
                }                     //
            }                         //
        else                          //
            {                         //
            down = third;             //
            dcol = tcol;              //
            if (first.y < second.y)   //
                {                     //
                mid = first;          //
                mcol = fcol;          //
                up = second;          //
                ucol = scol;          //
                }                     //
            else                      //
                {                     //
                mid = second;         //
                mcol = scol;          //
                up = first;           //
                ucol = fcol;          //
                }                     //
            }                         //
        }                             //
    else if (second.y < third.y)        // sorting
        {                               // points
        down = second;                //
        dcol = scol;                  //
        if (first.y < third.y)        //
            {                         //
            mid = first;              //
            mcol = fcol;              //
            up = third;               //
            ucol = tcol;              //
            }                         //
        else                          //
            {                         //
            mid = third;              //
            mcol = tcol;              //
            up = first;               //
            ucol = fcol;              //
            }                         //
        }                             //
    else                               //
        {                             //
        down = third;                 //
        dcol = tcol;                  //
        if (first.y < second.y)       //
            {                         //
            mid = first;              //
            mcol = fcol;              //
            up = second;              //
            ucol = scol;              //
            }                         //
        else                          //
            {                         //
            mid = second;             //
            mcol = scol;              //
            up = first;               //
            ucol = fcol;              //
            }                         //
        }                             //
//--------------------------------------

    double allheight = up.y - down.y;
    double allhwidth = up.x - down.x;

    double sectorheight = mid.y - down.y;

    if (fabs (allheight) < 1) return 0;

    double help = sectorheight/allheight;

    //printf ("mid.y == %f, down.y == %f\n", mid.y, down.y);
    //printf ("sech == %f\n", sectorheight);

    txSetColor (TX_WHITE, 1, MyScreen);
    //txSetFillColor (RGB(dcol.x, dcol.y, dcol.z), MyScreen);

    //if (GetAsyncKeyState ('C')) txEllipse (down.x - 10, down.y - 10, down.x + 10, down.y + 10, MyScreen);

    //char helpch[16] = {};
    //sprintf (helpch, "%f", down.z);
    //txDrawText (down.x - 80, down.y - 50, down.x + 80, down.y - 20, helpch, DT_CENTER, MyScreen);

    //txSetFillColor (RGB(mcol.x, mcol.y, mcol.z), MyScreen);

    //if (GetAsyncKeyState ('C')) txEllipse (mid.x - 10, mid.y - 10, mid.x + 10, mid.y + 10, MyScreen);

    //sprintf (helpch, "%f", down.z);
    //txDrawText (mid.x - 80, mid.y - 50, mid.x + 80, mid.y - 20, helpch, DT_CENTER, MyScreen);

    //txSetFillColor (RGB(ucol.x, ucol.y, ucol.z), MyScreen);

    //if (GetAsyncKeyState ('C')) txEllipse (up.x - 10, up.y - 10, up.x + 10, up.y + 10, MyScreen);

    //sprintf (helpch, "%f", down.z);
    //txDrawText (up.x - 80, up.y - 50, up.x + 80, up.y - 20, helpch, DT_CENTER, MyScreen);

    VEDHorTriangle ({help * allhwidth + down.x,
                     down.y + sectorheight + 1,
                     help * (up.z - down.z) + down.z},
                     mid, down,
                    {help * (ucol.x - dcol.x) + dcol.x,
                     help * (ucol.y - dcol.y) + dcol.y,
                     help * (ucol.z - dcol.z) + dcol.z},
                     mcol, dcol);

    VEDHorTriangle ({down.x + help * allhwidth,
                     down.y + sectorheight,
                     down.z + help * (up.z - down.z)},
                     mid, up,
                    {help * (ucol.x - dcol.x) + dcol.x,
                     help * (ucol.y - dcol.y) + dcol.y,
                     help * (ucol.z - dcol.z) + dcol.z},
                     mcol, ucol);
    return 0;                                                               //линейная интерполяция
    }                                                                         //x = x0 + t*(x1-x0)


int VEDHorTriangle(MYP left, MYP right, MYP third, MYP lcol, MYP rcol, MYP tcol)
    {
    double allheight = third.y - left.y;
    //printf ("third.y == %f\n left.y == %f", third.y, left.y);
    if (fabs (allheight) <= 1)
        {
        //getch();
        VEDLine (left.x, left.y, left.z, right.x, right.y, right.z, lcol, rcol);
        return 0;
        //printf ("i've returned");
        }
    //printf ("allh == %f\n", allheight);
    //printf ("a\n");
    //getch();
    double signum = allheight/fabs(allheight);
    bool exit = true;
    double nowheight = 0;
    double leftwidth = third.x - left.x;
    double rightwidth = third.x - right.x;
    double help = 0;
    for (double nowy = left.y; exit; nowy += signum)
        {
        //txSleep(10);
        nowheight = third.y - nowy;
        if (signum > 0 && nowy + signum >= third.y) exit = false;
        if (signum < 0 && nowy + signum <= third.y) exit = false;
        //printf ("b\n");
        //getch();
        help = nowheight/allheight;
        VEDLine ( left.x + help* leftwidth,  left.y + nowheight,  left.z + help*(third.z -  left.z),
                 right.x + help*rightwidth, right.y + nowheight, right.z + help*(third.z - right.z),
                 {lcol.x + help*(tcol.x - lcol.x), lcol.y + help*(tcol.y - lcol.y), lcol.z + help*(tcol.z - lcol.z)},
                 {rcol.x + help*(tcol.x - rcol.x), rcol.y + help*(tcol.y - rcol.y), rcol.z + help*(tcol.z - rcol.z)});
        }
    return 0;
    }

int VEDVertex (MYP old, MYP NEW, bool isper)
    {
    double cord0 [ALLMSX][ALLMSY] = {{old.x, 0, 0, 0}, {old.y, 0, 0, 0}, {old.z, 0, 0, 0}, {1, 0, 0, 0}};
    double cord1 [ALLMSX][ALLMSY] = {{NEW.x, 0, 0, 0}, {NEW.y, 0, 0, 0}, {NEW.z, 0, 0, 0}, {1, 0, 0, 0}};

    makeAllDeforms(cord0, isper);
    makeAllDeforms(cord1, isper);

    VEDLine (SzScr.x/2 + cord0[0][0],
             SzScr.y/2 + cord0[1][0], cord0[2][0],
             SzScr.x/2 + cord1[0][0],
             SzScr.y/2 + cord1[1][0], cord1[2][0], {255, 255, 255}, {200, 200, 200});
    return 0;
    }

void VED3dTriangle (MYP first, MYP second, MYP third,
                    MYP  col1, MYP   col2, MYP  col3,
                    MYP lightpos, MYP lightcol, MYP viewpos)
    {
    viewpos = {0, 0, 0};
    viewpos = viewpos; // i hate warnings
    double cord1 [ALLMSX][ALLMSY] = {{first.x, 0, 0, 0}, {first.y, 0, 0, 0}, {first.z, 0, 0, 0}, {1, 0, 0, 0}};
    double cord2 [ALLMSX][ALLMSY] = {{second.x, 0, 0, 0}, {second.y, 0, 0, 0}, {second.z, 0, 0, 0}, {1, 0, 0, 0}};
    double cord3 [ALLMSX][ALLMSY] = {{third.x, 0, 0, 0}, {third.y, 0, 0, 0}, {third.z, 0, 0, 0}, {1, 0, 0, 0}};

    col1 = col1 / 255;//1/255
    col2 = col2 / 255;
    col3 = col3 / 255;
    lightcol = lightcol / 255;
    //MYP environmentcol = {0.2, 0.2, 0.2};
    //printf ("before1col1 == %f, %f, %f\n", col1.x, col1.y, col1.z);
    //makeAllVecDeforms (Normal);

    MYP VecFS = second - first;
    MYP VecFT = third  - first;
    MYP VecST = third  - second;
    MYP Normal  = VectorMultip (VecFS, VecFT);
    makeAllVecDeforms (viewpos);

    Normal = makeAllVecDeforms (Normal, false, false, false, true);
    Normal = Normal / Normal.length();

    makeAllDeforms (cord1, false);
    makeAllDeforms (cord2, false);
    makeAllDeforms (cord3, false);

    lightpos.x = lightpos.x/ZScalingCoeff/lightpos.z;
    lightpos.y = lightpos.y/ZScalingCoeff/lightpos.z;

    first  = {cord1[0][0], cord1[1][0], cord1[2][0]};
    second = {cord2[0][0], cord2[1][0], cord2[2][0]};
    third  = {cord3[0][0], cord3[1][0], cord3[2][0]};


    //if (GetAsyncKeyState ('N'))
    //    {
    //    drawVec (first, Normal);
    //    drawVec (second, Normal);
    //    drawVec (third, Normal);
    //    }
    //MYP Normal2 = VectorMultip (VecFS * -1, VecST);
    //MYP Normal3 = VectorMultip (VecST * -1, VecFT * -1);
    //Normal = Normal / Normal.length();
    //txLine (SzScr.x/2 + first.x, SzScr.y/2 + first.y, SzScr.x/2 + first.x - Normal.x/ZScalingCoeff/Normal.z * 100, SzScr.y/2 + first.y - Normal.y/ZScalingCoeff/Normal.z * 100, MyScreen);
    //txLine (SzScr.x/2 + first.x, SzScr.y/2 + first.y, SzScr.x/2 + first.x + Normal.x/ZScalingCoeff/Normal.z * 100, SzScr.y/2 + first.y + Normal.y/ZScalingCoeff/Normal.z * 100, MyScreen);
    if (GetAsyncKeyState('M'))
        {
        txSetColor (TX_YELLOW, 10, MyScreen);
        drawVec (first, lightpos - first);
        drawVec (second, lightpos - second);
        drawVec (third, lightpos - third);
        }
        //txLine (SzScr.x/2 + lightpos.x/ZScalingCoeff/lightpos.z, SzScr.y/2 + lightpos.y/ZScalingCoeff/lightpos.z, SzScr.x/2, SzScr.y/2, MyScreen);

    //MYP View1Dir = viewpos - first;
    //MYP View2Dir = viewpos - second;
    //MYP View3Dir = viewpos - third;

    MYP Light1Dir = first - lightpos;
    MYP Light2Dir = second - lightpos;
    MYP Light3Dir = third - lightpos;

    MYP View1Dir = first - viewpos;
    MYP View2Dir = second - viewpos;
    MYP View3Dir = third - viewpos;
    //if (acos(Normal2^Light1Dir) > PI/2) Normal2 = Normal2 * -1;
    //if (acos(Normal3^Light1Dir) > PI/2) Normal3 = Normal3 * -1;

    //assert (fabs (Normal2.x - Normal.x) < 0.00015 && fabs (Normal3.x - Normal.x) < 0.00015);
    //assert (fabs (Normal2.z - Normal.z) < 0.00015 && fabs (Normal3.z - Normal.z) < 0.00015);
    //assert (fabs (Normal2.y - Normal.y) < 0.00015 && fabs (Normal3.y - Normal.y) < 0.00015);

    MYP Light1DirRef = Normal * 2 * (Light1Dir * Normal) - Light1Dir;
    MYP Light2DirRef = Normal * 2 * (Light2Dir * Normal) - Light2Dir;
    MYP Light3DirRef = Normal * 2 * (Light3Dir * Normal) - Light3Dir;

    //if (GetAsyncKeyState ('T'))
    //    {
    //    Light1DirRef += rand()%100/8000;
    //    }

    double Spec1 = Light1DirRef^View1Dir;
    double Spec2 = Light2DirRef^View2Dir;
    double Spec3 = Light3DirRef^View3Dir;

    if (Spec1 < 0) Spec1 = 0;
    if (Spec2 < 0) Spec2 = 0;
    if (Spec3 < 0) Spec3 = 0;
    //printf ("cos (LightDirRef^ViewDir) == %f\n", Spec1);
    double MatSpec1 = pow (Spec1, MaterialReflective);
    double MatSpec2 = pow (Spec2, MaterialReflective);
    double MatSpec3 = pow (Spec3, MaterialReflective);

    //double BrightnessMultiplier = 1;

    double diffuse1 = Normal^(Light1Dir);
    double diffuse2 = Normal^(Light2Dir);
    double diffuse3 = Normal^(Light3Dir);

    if (diffuse1 < 0) diffuse1 = 0;
    if (diffuse2 < 0) diffuse2 = 0;
    if (diffuse3 < 0) diffuse3 = 0;

    col1 = /*(environmentcol % col1) + */col1 % lightcol * diffuse1 + lightcol * MatSpec1; //*/
    col2 = /*(environmentcol % col2) + */col2 % lightcol * diffuse2 + lightcol * MatSpec2; //*/
    col3 = /*(environmentcol % col3) + */col3 % lightcol * diffuse3 + lightcol * MatSpec3; //*/

    //printf ("after  col1 == %f, %f, %f\n", col1.x, col1.y, col1.z);
    //getch();
    col1 = col1 *  255;
    col2 = col2 *  255;
    col3 = col3 *  255;

    if (col1.x > 254) col1.x = 254;
    if (col1.y > 254) col1.y = 254;
    if (col1.z > 254) col1.z = 254;

    if (col2.x > 254) col2.x = 254;
    if (col2.y > 254) col2.y = 254;
    if (col2.z > 254) col2.z = 254;

    if (col3.x > 254) col3.x = 254;
    if (col3.y > 254) col3.y = 254;
    if (col3.z > 254) col3.z = 254;

    VEDTriangle ({SzScr.x/2 + cord1[0][0], SzScr.y/2 + cord1[1][0], cord1[2][0]},
                 {SzScr.x/2 + cord2[0][0], SzScr.y/2 + cord2[1][0], cord2[2][0]},
                 {SzScr.x/2 + cord3[0][0], SzScr.y/2 + cord3[1][0], cord3[2][0]}, col1, col2, col3);
    }

MYP makeAllVecDeforms (MYP getVec, bool isper, bool istran, bool issized, bool isrot)
    {
    double getVecMat[ALLMSX][ALLMSY] = {{getVec.x, 0, 0, 0}, {getVec.y, 0, 0, 0}, {getVec.z, 0, 0, 0}, {1, 0, 0, 0}};
    makeAllDeforms (getVecMat, isper, istran, issized, isrot);
    getVec.x = getVecMat[0][0];
    getVec.y = getVecMat[1][0];
    getVec.z = getVecMat[2][0];
    return getVec;
    }



void makeAllDeforms (double cord[ALLMSX][ALLMSY], bool isper, bool istran, bool issized, bool isrot)
    {
    if (issized) multimat (SAL, DEFORMATION, SCORD, cord, SCORD, cord);

    if (isrot)  multimat (SAL, ALY, SCORD, cord, SCORD, cord);

    if (isrot)  multimat (SAL, ALX, SCORD, cord, SCORD, cord);

    if (isrot)  multimat (SAL, ALZ, SCORD, cord, SCORD, cord);

    if (istran) multimat (SAL, TRAN, SCORD, cord, SCORD, cord);
    else
        {
        double alternativeTranKostyl[ALLMSX][ALLMSY] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 100}, {0, 0, 0, 1}};
        multimat (SAL, alternativeTranKostyl, SCORD, cord, SCORD, cord);
        }
    //printmat (SAL, TRAN);

    if (isper)  multimat (STRAN, PERSPECTIVE, SCORD, cord, SCORD, cord);

    if (fabs(cord[2][0]) <= 0.0015) cord[2][0] = ZScalingCoeff;
    cord[0][0] = cord[0][0]/ZScalingCoeff/cord[2][0];
    cord[1][0] = cord[1][0]/ZScalingCoeff/cord[2][0];
    }


int VEDObjLine (double x1, double y1, double z1, double x2, double y2, double z2, MYP text1, MYP text2, RGBQUAD* texture, MYP texturesize)
    {
    if (x1 > x2)
        {
        swap (&x1, &x2);
        MYPSwap (&text1, &text2);
        swap (&y1, &y2);
        swap (&z1, &z2);
        }

    if (fabs(x2 - x1) < 1 && fabs (y2 - y1) < 1) return 0;
    bool swapped = false;
    if (fabs(x2 - x1) < fabs(y2 - y1))
        {
        swapped = true;
        swap (&x1, &y1);
        swap (&x2, &y2);
        }

    double help = 0;
    for (int xn = (int)x1; xn < (int)(x2 - 0.5); xn++)
        {
        help = (xn - x1)/(x2 - x1);   //
        if (swapped)
            {                       //
            MyObjPix ((int)(y1 + help * (y2 - y1)), xn, (help*(z2 - z1) + z1)*10,
                    (BYTE)(help * (text2.x - text1.x) + text1.x) * texturesize.x,
                    (BYTE)(help * (text2.y - text1.y) + text1.y) * texturesize.y, texture, texturesize.x, texturesize.y);
            }
        else
            {
            MyObjPix (xn, (int)(y1 + help * (y2 - y1)), (help*(z2 - z1) + z1)*10,
                    (BYTE)(help * (text2.x - text1.x) + text1.x) * texturesize.x,
                    (BYTE)(help * (text2.y - text1.y) + text1.y) * texturesize.y, texture, texturesize.x, texturesize.y);
            }
        }
    return 0;
    }


int VEDLine (double x1, double y1, double z1, double x2, double y2, double z2, MYP col1, MYP col2)
    {
    //printf ("%f, %f, %f, %f\n", x2, y2, x1, y1);
    //txSetFillColor (RGB (col1.x, col1.y, col1.z));
    //txSetColor (RGB (col1.x, col1.y, col1.z));
    //txCircle (x1, y1, 10);
    //txSetFillColor (RGB (col2.x, col2.y, col2.z));
    //txSetColor (RGB (col2.x, col2.y, col2.z));
    //txCircle (x2, y2, 10);
    //getch();
    if (x1 > x2)
        {
        swap (&x1, &x2);
        MYPSwap (&col1, &col2);
        swap (&y1, &y2);
        swap (&z1, &z2);
        }

    //assert (x1 >= 0);
    //assert (x1 <= SzScr.x);
    //assert (y1 >= 0);
    //assert (y1 <= SzScr.y);

    //assert (x2 >= 0);
    //assert (x2 <= SzScr.x);
    //assert (y2 >= 0);
    //assert (y2 <= SzScr.y);


    if (fabs(x2 - x1) < 1 && fabs (y2 - y1) < 1) return 0;
    bool swapped = false;
    if (fabs(x2 - x1) < fabs(y2 - y1))
        {
        swapped = true;
        swap (&x1, &y1);
        swap (&x2, &y2);
        }

    double help = 0;
    for (int xn = (int)x1; xn < (int)(x2 - 0.5); xn++)
        {
        //if (big2 - big1 == 0)
        //    {
            //if (swapped) printf ("swapped\n");
            //else printf ("not swapped\n");
            //printf ("x/y1 == %d (-) x/y2 == %d", big2, big1);
            //getch();
        //    }
        help = (xn - x1)/(x2 - x1);   //
        if (swapped)
            {                       //swaa
            //if (y1 + help*(y2 - y1) < SzScr.x && y1 + help*(y2 - y1) > 0 &&
            //    xn < SzScr.y && xn > 0)
            //    {
                MyPix ((int)(y1 + help * (y2 - y1)), xn, (help*(z2 - z1) + z1)*10,
                      (BYTE)(help * (col2.x - col1.x) + col1.x),
                      (BYTE)(help * (col2.y - col1.y) + col1.y),
                      (BYTE)(help * (col2.z - col1.z) + col1.z));
            //    }
            //printf ("sx = %d(from %d to %d)\n", xn, (int)x1, (int)x2);
            //printf ("sy = %d\n", (int)(y1 + help*(y2 - y1)));
            //return 0;
            }
        else
            {
            //if (y1 + help*(y2 - y1) < SzScr.y && y1 + help*(y2 - y1) > 0 &&
            //    xn < SzScr.x && xn > 0)
            //    {
                //printf ("thisz == %lf\n", (double)(help*(z2 - z1) + z1));
                //getch();
                //printf ("buffer[half][half] == %lf\n", (double)(ZBuffer[SzScr.x/2 + SzScr.y/2 * SzScr.x]));
                //getch();
                //printf ("colorof[half][half] == %d, %d, %d", (int)(MyPixels[SzScr.x/2 + SzScr.y/2 * SzScr.x].rgbRed), (int)(MyPixels[SzScr.x/2 + SzScr.y/2 * SzScr.x].rgbBlue), (int)(MyPixels[SzScr.x/2 + SzScr.y/2 * SzScr.x].rgbGreen));
                //getch();
                MyPix (xn, (int)(y1 + help * (y2 - y1)), (help*(z2 - z1) + z1)*10,
                       (BYTE)(help * (col2.x - col1.x) + col1.x),
                       (BYTE)(help * (col2.y - col1.y) + col1.y),
                       (BYTE)(help * (col2.z - col1.z) + col1.z));
            //    }
            //printf ("nsx = %d(from %d to %d)\n", xn, (int)x1, (int)x2);
            //printf ("nsy = %d\n", (int)(y1 + help*(y2 - y1)));
            //return 0;
            }
        }
    return 0;
    }

void swap (double* s1, double* s2)
    {
    double help = *s1;
    *s1 = *s2;
    *s2 = help;
    }

void MYPSwap (MYP* pt1, MYP* pt2)
    {
    MYP help = *pt1;
    *pt1 = *pt2;
    *pt2 = help;
    }



void makePerspective (double mat[ALLMSX][ALLMSY], double n, double f)
    {
    mat[0][0] = ctg(50 * 0.01745)/(4/3);
    mat[1][1] = ctg(40 * 0.01745);
    mat[2][2] = (f + n)/(f - n);
    mat[2][3] = 1;
    mat[3][2] = (-2 * f * n)/(f - n);
    mat[3][3] = 0;
    }


int VEDCube (bool isper)
    {
    MYP c1 = {-1, -1, -1};             //    2/--------/3
    MYP c2 = {-1, -1,  1};             //    /|       /|
    MYP c3 = { 1, -1,  1};             //  1/-+------/4|
    MYP c4 = { 1, -1, -1};             //   | |      | |
    MYP c5 = {-1,  1, -1};             //   | |      | |
    MYP c6 = {-1,  1,  1};             //   |6/------|-/7
    MYP c7 = { 1,  1,  1};             //   |/       |/
    MYP c8 = { 1,  1, -1};             //  5/--------/8
    //MYP fircol = {255, 0, 0};
    //MYP mgreen = {0, 255, 0};
    //MYP mmid1 = {170, 85, 0};
    //MYP mmid2 = {85, 170, 0};
    //MYP mred = {255, 0, 0};
    ///MYP mgreen = {0, 0, 0};
    //MYP mmid1 = {0, 0, 0};
    //MYP mmid2 = {0, 0, 0};
    MYP fircol = {255, 0, 0};
    MYP seccol = {0, 255, 0};
    MYP thicol = {0, 0, 255};
    MYP forcol = {255, 255, 0};
    MYP fifcol = {0, 255, 255};
    MYP sixcol = {255, 0, 255};
    if (isper) //TODO you know what to do
    VED3dTriangle (c5, c4, c8, fifcol, fifcol, fifcol);//
    VED3dTriangle (c5, c4, c8, fifcol, fifcol, fifcol);//              //   1/-+------/4|//   5/--------/8
    VED3dTriangle (c1, c4, c5, fifcol, fifcol, fifcol);//              //    |/  fr   |/
    VED3dTriangle (c1, c5, c6, fircol, fircol, fircol);//              //    | |   sx | |
    VED3dTriangle (c2, c6, c7, sixcol, sixcol, sixcol);//              //    |f| fv   |s|
    VED3dTriangle (c7, c6, c5, forcol, forcol, forcol);//
    VED3dTriangle (c7, c4, c8, seccol, seccol, seccol);//              //     /| t     /|
    VED3dTriangle (c5, c8, c7, forcol, forcol, forcol);//              //     2/--------/3
    VED3dTriangle (c6, c2, c1, fircol, fircol, fircol);//              //    |6/------|-/7
    VED3dTriangle (c7, c3, c4, seccol, seccol, seccol);//
    VED3dTriangle (c1, c3, c4, thicol, thicol, thicol);//
    VED3dTriangle (c1, c2, c3, thicol, thicol, thicol);//
    VED3dTriangle (c2, c7, c3, sixcol, sixcol, sixcol);//


    /*VED3dTriangle (c4, c3, c7, mmid1, mmid2, mgreen);
    VED3dTriangle (c4, c8, c7, mmid1, mmid2, mgreen);
    VED3dTriangle (c5, c6, c7, mmid1, mmid2, mgreen);
    VED3dTriangle (c5, c8, c7, mmid1, mmid2, mgreen);              //reddish          //greenish
    VED3dTriangle (c1, c2, c3, mred, mmid1, mmid2);              //     2/--------/3
    VED3dTriangle (c1, c4, c3, mred, mmid1, mmid2);              //     /|       /|
    VED3dTriangle (c1, c2, c6, mred, mmid1, mmid2);              //red1/-+------/4|  //reddish
    VED3dTriangle (c1, c5, c6, mred, mmid1, mmid2);              //    | |      | |
    VED3dTriangle (c2, c6, c7, mmid1, mmid2, mgreen);            //    | |      | |
    VED3dTriangle (c2, c3, c7, mmid1, mmid2, mgreen);            //gree|6/------|-/7green
    VED3dTriangle (c1, c4, c5, mred, mmid1, mmid1);              // nish/       |/
    VED3dTriangle (c5, c8, c4, mmid1, mmid2, mmid1);             //   5/--------/8 //greenish
                                                                   //reddish
    //*///assert (fabs(mred.x - 255) <= 0.5 && fabs(mred.y) <= 0.5 && fabs(mred.z) <= 0.5);
    //assert (fabs(mgreen.x) <= 0.5 && fabs(mgreen.y - 255) <= 0.5 && fabs(mgreen.z) <= 0.5);
    return 0;                                          //*/
    }

//void VEDLine (x1, y1, x2, y2

int printmat (ARRSIZ SM, double m[ALLMSX][ALLMSY])
    {
    printf ("\n");
    for (int x = 0; x < SM.y; x++)
        {
        for (int y = 0; y < SM.x; y++)
            {
            printf ("%f ", m[x][y]);
            }
        printf ("\n");
        }
    return 1;
    }

int initSphere (double stepAngle, Triangle Figure[])
    {
    int pointsnum = (int)(PI * 2/stepAngle + 0.5);//округление к большему
    MYP *rotatedPoints = new MYP[(pointsnum + 2) * (pointsnum + 2)];
    //Triangle *triangles = new Triangle[pointsnum * pointsnum * pointsnum];
    //tx_auto_func (delete [] triangles);
    tx_auto_func (delete [] rotatedPoints);
    int turnover = 0;

    for (double Angle = 0; Angle <= PI * 2 + stepAngle; Angle += stepAngle)
        {
        rotatedPoints[turnover] = {0, sin(Angle), cos(Angle)};
        turnover++;
        //assert (turnover != pointsnum);
        }
    pointsnum = turnover;
    //turnover = pointsnum;
    MYP pointBeforeRotation;
    for (double Angle = stepAngle; Angle <= PI * 2 + stepAngle; Angle += stepAngle)
        {
        for (int i = 0; i < pointsnum; i++)
            {
            if (turnover == pointsnum *  (pointsnum + 1)) turnover--;
            //pointBeforeRotation = rotatedPoints[i];
            rotatedPoints[turnover] = RotateVecY (rotatedPoints[i], Angle);
            //pointBeforeRotation = rotatedPoints[turnover] - pointBeforeRotation;
            //if (fabs (pointBeforeRotation.x) >0.0015) printf ("xisnotthesame\n");
            if (fabs (pointBeforeRotation.y) > 0.0015) printf ("yisnotthesame\n");
            //if (fabs (pointBeforeRotation.x) >0.0015) printf ("zisnotthesame\n");
            //printf ("rotatedpoint%d{%f, %f, %f}\n", turnover, rotatedPoints[turnover].x, rotatedPoints[turnover].y, rotatedPoints[turnover].z);
            //i++;
            turnover++;
            }
        //turnover++;
        }    //*/

    turnover = 0;
    MYP helpPoint;//есть конструктор
    MYP upperPoint = rotatedPoints[0];
    VED3dTriangle (upperPoint,
                  {upperPoint.x + 0.25, upperPoint.y + 0.25, upperPoint.z},
                  {upperPoint.x - 0.25, upperPoint.y - 0.25, upperPoint.z}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255});


    for (int latitude = pointsnum / 4; latitude < (pointsnum)*3/4 - 1; latitude++)
        {
        //printf ("с\n");
        //getch();
        for (int longitude = 0; longitude < (pointsnum - 1); longitude++)
            {
            Figure[turnover] = {rotatedPoints[latitude + 1 + (longitude + 1) * pointsnum],
                                rotatedPoints[latitude + 1 +  longitude * pointsnum],
                                rotatedPoints[latitude +      longitude * pointsnum]};


            assert (turnover + 1 < pointsnum * pointsnum * pointsnum);
            Figure[turnover + 1] = {rotatedPoints[latitude + 1 + (longitude + 1) * pointsnum],
                                    rotatedPoints[latitude     +  longitude      * pointsnum],
                                    rotatedPoints[latitude     + (longitude + 1) * pointsnum]};
            turnover+=2;

            }
        printf ("f\n");
        //getch();
        turnover++;
        }
    return turnover + 1;
    }

MYP RotateVecY (MYP GaveVec, double angle)
    {
    double VecMatrix[ALLMSX][ALLMSY] = {{GaveVec.x, 0, 0, 0},
                                        {GaveVec.y, 0, 0, 0},
                                        {GaveVec.z, 0, 0, 0},
                                        {1, 0, 0, 0}};
    RotateMatrixY (VecMatrix, angle);
    GaveVec = {VecMatrix[0][0], VecMatrix[1][0], VecMatrix[2][0]};
    return GaveVec;
    }

void RotateMatrixY (double GaveMatrix[][ALLMSY], double angle)
    {
    double RotationYMatrix[ALLMSX][ALLMSY] = {};

    RotationYMatrix[0][0] = cos(angle);
    RotationYMatrix[0][2] = sin(angle);
    RotationYMatrix[1][1] = 1;
    RotationYMatrix[2][0] =-sin(angle);
    RotationYMatrix[2][2] = cos(angle);
    multimat (SAL, RotationYMatrix, SAL, GaveMatrix, SAL, GaveMatrix);
    }


void VEDFigure (Triangle Figure[], int TrianglesAmount)
    {
    for (int i = 0; i < TrianglesAmount; i++)
        {
        VED3dTriangle (Figure[i].f, Figure[i].s, Figure[i].t, {255, 255, 255}, {255, 255, 255}, {255, 255, 255});
        //printf ("a\n");
        }
    }


void VEDObjFigure (ObjTriangle Figure[], int TrianglesAmount, RGBQUAD* texture, MYP texturesize)
    {
    for (int i = 0; i < TrianglesAmount; i++)
        {
        VED3dObjTriangle (Figure[i], texture, texturesize);
        //printf ("a\n");
        }
    }



int makemat (ARRSIZ SM, double A[ALLMSX][ALLMSY], double B[ALLMSX][ALLMSY])
    {
    //printf ("\n");
    for (int x = 0; x < SM.y; x++)
        {
        for (int y = 0; y < SM.x; y++)
            {
            //printf ("%f ", m[x][y]);
            A[x][y] = B[x][y];
            }
        //printf ("\n");
        }
    return 1;
    }
//  */

void multimat (ARRSIZ sa, double A[ALLMSX][ALLMSY], ARRSIZ sb, double B[ALLMSX][ALLMSY], ARRSIZ sc, double C[ALLMSX][ALLMSY])
    {
    double CCopy [ALLMSX][ALLMSY];
    copymatrix (sa, CCopy, C);
    int minx = sa.x;
    int miny = sb.y;
    //if (sb.x <= sa.x && sb.x <= sc.x) minx = sb.x;
    //if (sc.x <= sb.x && sc.x <= sa.x) minx = sc.x;
    //if (sa.x <= sb.x && sa.x <= sc.x) minx = sa.x;
    //if (sb.y <= sa.y && sb.y <= sc.y) miny = sb.y;
    //if (sc.y <= sb.y && sc.y <= sa.y) miny = sc.y;
    //if (sa.y <= sb.y && sa.y <= sc.y) miny = sa.y;
    int minhv = sb.y;
    //if (sa.x <= sb.y) minhv = sa.x;
    //if (sa.x <= sb.y) minhv = sa.x;
    double num = 0;
    for (int x = 0; x < miny; x++)
        {
        for (int y = 0; y < minx; y++)
            {
            for (int i = 0; i < minhv; i++)
                {
                num+= A[x][i] * B[i][y];
                }
            CCopy[x][y] = num;
            num = 0;
            }     //C2,3 = A2,1 · B1,3 + A2,2 · B2,3 + A2,3 · B3,3 = 0 · 0 + 0 · 0 + 0 · 2 = 0
        }
    copymatrix (sc, C, CCopy);
    }

void copymatrix (ARRSIZ size, double To[ALLMSX][ALLMSY], double From[ALLMSX][ALLMSY])
    {
    for (int cx = 0; cx < size.y; cx++)
        {
        for (int cy = 0; cy < size.x; cy++)
            {
            To[cx][cy] = From[cx][cy];
            }
        }
    }

void makeBufferDefault ()
    {
    for (int i = 0; i < SzScr.x * SzScr.y; i++)
        {
        ZBuffer[i] = BufferDefault;
        }
    }

MYP VectorMultip (MYP a, MYP b)
    {
    return {a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x};
    }

void drawVec (MYP start, MYP vec, COLORREF color, COLORREF pointcolor, int width, int pointrad)
    {
    txSetColor (color, width);
    txLine (SzScr.x/2 + start.x, SzScr.y/2 + start.y,
            SzScr.x/2 + start.x + vec.x,
            SzScr.y/2 + start.y + vec.y, MyScreen);

    txSetColor (pointcolor, 1);
    txSetFillColor (pointcolor);
    txEllipse (SzScr.x/2 + start.x + vec.x + pointrad,
               SzScr.y/2 + start.y + vec.y + pointrad,
               SzScr.x/2 + start.x + vec.x - pointrad,
               SzScr.y/2 + start.y + vec.y - pointrad, MyScreen);
    }

bool control (double speed)
    {
    bool returning = false;
    static POINT OldMousePos = txMousePos();
    POINT NewMousePos = txMousePos();
    if (NewMousePos.x != OldMousePos.x)
        {
        if (GetAsyncKeyState (VK_LBUTTON))
            {
            VEDRotateY (0.036 * speed * (OldMousePos.x - NewMousePos.x));
            OldMousePos.x = NewMousePos.x;
            }
        else
            {
            OldMousePos.x = txMousePos().x;
            }
        returning = true;
        }

    if (NewMousePos.y != OldMousePos.y)
        {
        if (GetAsyncKeyState (VK_LBUTTON))
            {
            VEDRotateX (0.036 * speed * (NewMousePos.y - OldMousePos.y));
            OldMousePos.y = NewMousePos.y;
            }
        else
            {
            OldMousePos.y = txMousePos().y;
            }
        returning = true;
        }

    if (GetAsyncKeyState ('Z'))
        {
        VEDRotateZ ( 0.0175 * speed);
        returning = true;
        }

    if (GetAsyncKeyState ('X'))
        {
        VEDRotateZ (-0.0175 * speed);
        returning = true;
        }

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
        VEDScale (1 + 0.1 * speed,   0,     0);
        }

    if (GetAsyncKeyState (VK_LEFT))
        {
        returning = true;
        VEDScale (1 - 0.1 * speed,   0,     0);
        }

    if (GetAsyncKeyState (VK_UP))
        {
        returning = true;
        VEDScale (0, 1 + 0.1 * speed,     0);
        }

    if (GetAsyncKeyState (VK_DOWN))
        {
        returning = true;
        VEDScale (0, 1 - 0.1 * speed,     0);
        }

    if (GetAsyncKeyState (VK_RSHIFT))
        {
        returning = true;
        VEDScale (0,   0,   1 + 0.1 * speed);
        }

    if (GetAsyncKeyState (VK_RETURN))
        {
        returning = true;
        VEDScale (0,   0,   1 - 0.1 * speed);
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

    if (GetAsyncKeyState ('L'))
        {
        DefaultLightPos.x -= 0.05 * speed;
        returning = true;
        }

    if (GetAsyncKeyState ('J'))
        {
        DefaultLightPos.x += 0.05 * speed;
        returning = true;
        }

    if (GetAsyncKeyState ('I'))
        {
        DefaultLightPos.y += 0.05 * speed;
        returning = true;
        }

    if (GetAsyncKeyState ('K'))
        {
        DefaultLightPos.y -= 0.05 * speed;
        returning = true;
        }

    if (GetAsyncKeyState ('U'))
        {
        DefaultLightPos.z -= 0.05 * speed;
        returning = true;
        }

    if (GetAsyncKeyState ('O'))
        {
        DefaultLightPos.z += 0.05 * speed;
        returning = true;
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


    return returning;
    }

int makeObjFigure (ObjTriangle Figure[], string getName)
    {
    FILE *model;
    if ((model = fopen (getName.c_str(), "r")) == NULL)
        {
        printf ("Cannot open obj");
        exit(1);
        }
    double ScX = 0;
    double ScY = 0;
    double ScZ = 0;

    const int getLineSize = 30;
    //char getLine[getLineSize] = {};
    char getType[4] = {};

    char partone[getLineSize] = {};
    char parttwo[getLineSize] = {};
    char partthree[getLineSize] = {};

    MYP *getPoints = new MYP[5000];
    MYP *getTextures = new MYP[5000];
    MYP *getNormals = new MYP[5000];


    //int help = 0;
    //int counter = 0;

    int pointsturnover = 0;
    int texturesturnover = 0;
    int normalsturnover = 0;

    int fft = 0;
    int fst = 0;
    int ftt = 0;

    int sft = 0;
    int sst = 0;
    int stt = 0;

    int tft = 0;
    int tst = 0;
    int ttt = 0;

    int figurecounter = 0;
    //int lastspacepos = 0;

    while (!feof(model))
        {
        fscanf (model, "%s %s %s %s", getType, partone, parttwo, partthree);
        if (getType[0] == 'v')
            {
            //getch();
            //printf ("%s %s %s %s\n", getType, partone, parttwo, partthree);
            ScX = atof (partone);
            ScY = atof (parttwo);
            ScZ = atof (partthree);

            if (getType[1] == 0)
                {
                getPoints[pointsturnover].x = ScX;
                getPoints[pointsturnover].y = -ScY;
                getPoints[pointsturnover].z = -ScZ;
                pointsturnover++;
                }
            else
                {
                if (getType[1] == 'n')
                    {
                    getNormals[normalsturnover].x = ScX;
                    getNormals[normalsturnover].y = -ScY;
                    getNormals[normalsturnover].z = -ScZ;
                    normalsturnover++;
                    }
                else
                if (getType[1] == 't')
                    {
                    getTextures[texturesturnover].x = ScX;
                    getTextures[texturesturnover].y = -ScY;
                    getTextures[texturesturnover].z = -ScZ;
                    texturesturnover++;
                    }
                }
            }



        //if (getType[0] == '#')
        //    {
        //    printf ("HEEEY %s %s %s\n", getType, partone, parttwo, partthree);
        //    getch();
        //    break;
            //return figurecounter;
        //    }
            //printf (" %f %f %f\n", Vector[i].x, Vector[i].y, Vector[i].z);
            //getch();

        if (getType[0] == 'f')
            {
            sscanf (partone, "%d/%d/%d", &fft, &sft, &tft);
            sscanf (parttwo, "%d/%d/%d", &fst, &sst, &tst);
            sscanf (partthree, "%d/%d/%d", &ftt, &stt, &ttt);

            //printf ("%s %f/%f/%f %f/%f/%f %f/%f/%f\n", getType, getPoints[fft].x, getPoints[sft].x, getPoints[tft].x,
            //                                                    getPoints[fst].x, getPoints[sst].x, getPoints[tst].x,
            //                                                    getPoints[ftt].x, getPoints[stt].x, getPoints[ttt].x);
            //printf ("DoYouSeeMe?\n");

            Figure[figurecounter].cords = {getPoints[fft], getPoints[fst], getPoints[ftt]};

            Figure[figurecounter].textures = {getTextures[sft], getTextures[sst], getTextures[stt]};

            Figure[figurecounter].normales = {getNormals[tft], getNormals[tst], getNormals[ttt]};
            figurecounter++;
            }                         //*/

        //printf ("IaMHere!! (%d)\n", figurecounter);
        //getch();
        }
    printf ("this is the end... i shall return %d, while pturnover == %d\n", figurecounter, pointsturnover);
    getch();
    //delete [] getPoints;
    return figurecounter;
    }   //*/



void VEDLineFigure (Triangle Figure[], int amount)
    {
    for (int i = 0; i < amount; i++)
        {
        VEDVertex (Figure[i].f, Figure[i].s, false);
        VEDVertex (Figure[i].s, Figure[i].t, false);
        VEDVertex (Figure[i].t, Figure[i].f, false);
        }
    }

void plusassig (RGBQUAD *left, RGBQUAD right, double Koeff)
    {
    left->rgbRed += (BYTE)(right.rgbRed * Koeff);
    left->rgbGreen += (BYTE)(right.rgbGreen * Koeff);
    left->rgbBlue += (BYTE)(right.rgbBlue * Koeff);
    }

void VEDStart ()
    {

    SzScr = POINT{GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)};

    ZBuffer = new double[(SzScr.x + 1) * (SzScr.y + 1)];

    makeBufferDefault();

    txCreateWindow (SzScr.x, SzScr.y);

    MyScreen = txCreateDIBSection(SzScr.x, SzScr.y, &MyPixels);
    }

/*Я вдруг понял, что мой код не содержит НИ ЕДИНОГО КОТА. Нужно было срочно исправлять
это недоразумение.    _    -,    /|
    _.-|   |          |\__/,|   (`\
   {   |   |          |o o  |__ _) )
    "-.|___|        _.( T   )  `  /
     .--'-`-.     _((_ `^--' /_<  \
   .+|______|__.-||__)`-'(((/  (((/


            .__....._             _.....__,
                 .": o :':         ;': o :".
                 `. `-' .'.       .'. `-' .'
                   `---'             `---'     meow
                                                   .
         _...----...      ...   ...      ...----..._
      .-'__..-""'----    `.  `"`  .'    ----'""-..__`-.
    '.-'   _.--"""'       `-._.-'       '"""--._   `-.`
     '  .-"'                  :                  `"-.  `
       '   `.         -.   _.'"'._   .-           .'   `
             `.         ''"       "''          .'
               `.                           .'
                 `-._        /|\       _.-'
                     `"'--...___...--'"`
*/

//=============================================================================

//кладбище комментов


//=============================================================================

    /*VEDVertex ({-1, -1, -1}, {-1, -1, +1}, isper);
    //VEDVertex ({-1, -1, +1}, {+1, -1, +1}, isper);
    //VEDVertex ({+1, -1, +1}, {+1, -1, -1}, isper);
    //VEDVertex ({+1, -1, -1}, {-1, -1, -1}, isper);
    //       /----------/
    //      /          /
    //      /          /
    //     /----------/
    //VEDVertex ({-1, -1, -1}, {-1, +1, -1}, isper);
    //VEDVertex ({-1, +1, -1}, {-1, +1, +1}, isper);
    //VEDVertex ({-1, +1, +1}, {-1, -1, +1}, isper);


    //       /----------/
    //      /|         /
    //     /-+--------/
    //     | |
    //     | /
    //     |/
    //     /

    //VEDVertex ({-1, +1, -1}, {+1, +1, -1}, isper);
    //VEDVertex ({+1, +1, -1}, {+1, +1, +1}, isper);
    //VEDVertex ({+1, +1, +1}, {-1, +1, +1}, isper);

    //       /----------/
    //      /|         /
    //     /-+--------/
    //     | |
    //     | /---------/
    //     |/         /
    //     /---------/


    //VEDVertex ({+1, +1, -1}, {+1, -1, -1}, isper);
    //txSetColor (TX_WHITE);
    txSetColor (TX_GREEN);
    VEDVertex ({+1, +1, +1}, {+1, -1, +1}, isper);
    txSetColor (TX_WHITE, 5);
    VEDVertex ({0, 0, -2}, {0, 0, 2}, isper);

    //       /----------/
    //      /|         /|
    //     /-+--------/ |
    //     | |        | |
    //     | /--------+-/
    //     |/         |/
    //     /----------/  //*/

/*if (GetAsyncKeyState ('O'))
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


MYP loadTextureArray (LPCSTR Name, MYP* arr)
    {
    int sizex;
    int sizey;

    HBITMAP bitmap = (HBITMAP)LoadImage(0, Name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE or LR_DEFAULTSIZE or LR_COLOR);//Загрузка картинки в hitmap

    tagBITMAP BitMapInfo;

    GetObject(bitmap, sizeof(BitMapInfo), &BitMapInfo);

    sizex = BitMapInfo.bmWidth;
    sizey = BitMapInfo.bmHeight;
    //Получаем информацию о битмапе - размер бит на пиксель  итд..
    //BitmapInfo.bmWidth * BitmapInfo.bmHeight * (BitmapInfo.bmBitsPixel / 4)
    //или лучше массив (bi.bmWidth на bi.bmHeight) элементов размером по BitmapInfo.bmBitsPixel  бит(именно бит
    //последний параметр это число бит на пиксель)

    // вот собственно и загрузка в массив конечно везде нужно целочисленное деление.
    GetBitmapBits(bitmap, BitMapInfo.bmWidth* BitMapInfo.bmHeight* (BitMapInfo.bmBitsPixel / 4), arr);
    DeleteObject(bitmap);//Удаляем объект Bitmap
    }

    */





