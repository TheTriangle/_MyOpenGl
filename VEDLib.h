


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
    ObjTriangle():
        cords(),
        textures(),
        normales()
        {}
    };

POINT SzScr = {0, 0};
double BufferDefault = 4000;
const double ZScalingCoeff = 0.0015;
const double defaultnormal = -5;
const double MaterialReflective = 25;

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



const int ALLMSX = 4;
const int ALLMSY = 4;

MYP DefaultLightPos = {0, 0, -2};
MYP DefaultLightCol = {255, 255, 255};
MYP DefaultViewPos  = {0, 0, -5};

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
void VEDObjFigure  (ObjTriangle Figure[], int TrianglesAmount, RGBQUAD* texture, RGBQUAD* normales, RGBQUAD* specular, MYP texturesize);
int  VEDRotateZ    (double   a);
int  VEDjVertex    (double   x, double y, double z, double x1, double y1, double z1);
int  VEDRotateY    (double   a);
int  VEDRotateX    (double   a);
int  VEDTranslate  (double   x, double y, double z);
int  VEDCube       (bool isper);
int  VEDVertex     (MYP    old, MYP NEW, bool isper);
int  VEDObjTriangle   (MYP  first, MYP second, MYP third, MYP fcol, MYP scol, MYP tcol, RGBQUAD* texture, RGBQUAD* normales, RGBQUAD* specular, MYP textsize);
int  VEDObjHorTriangle (MYP first, MYP second, MYP third, MYP ftext, MYP stext, MYP ttext, RGBQUAD* texture, RGBQUAD* normales, RGBQUAD* specular, MYP textsize);
int  VEDTriangle   (MYP  first, MYP second, MYP third, MYP fcol, MYP scol, MYP tcol);
int  VEDHorTriangle(MYP   left, MYP right, MYP third, MYP lcol, MYP rcol, MYP tcol);
int  VEDLine       (double  x1, double y1, double z1, double x2, double y2, double z2, MYP col1, MYP col2);
int  VEDObjLine    (int  x1, int y1, double z1, int x2, int y2, double z2, MYP col1, MYP col2, RGBQUAD* texture, RGBQUAD* normales, RGBQUAD* specular, MYP textsize);
void VEDMakeTriangleFigure (Triangle* figure, ObjTriangle* objfigure, int size);
int  VEDObjPix      (int x, int y, int z,
                    int textx, int texty,
                    RGBQUAD* texture, RGBQUAD* normales, RGBQUAD* specular,
                    int textsizex, int textsizey,
                    MYP viewpos = DefaultViewPos, MYP lightpos = DefaultLightPos, MYP lightcol = DefaultLightCol);

int  VEDScale      (double  wx, double wy, double wz);

void VED3dTriangle (MYP first, MYP second, MYP third,
                    MYP  col1,   MYP col2,  MYP col3,
                    MYP lightpos = DefaultLightPos, MYP lightcol = DefaultLightCol, MYP viewpos = DefaultViewPos);

void VED3dObjTriangle (ObjTriangle givenTriangle,
                       RGBQUAD* texture, RGBQUAD* normales, RGBQUAD* specular, MYP texturesize,
                       MYP lightpos = DefaultLightPos, MYP lightcol = {255, 155, 155}, MYP viewpos = {0, 0, -5});

void VEDFigure     (Triangle Figure[], int TrianglesAmount);
RGBQUAD* VEDLoadRGBQUADImage (string getName, MYP sizes);


int initSphere (double stepAngle, Triangle Figure[]);

RGBQUAD makeColorWithLight (MYP pos, MYP color, MYP normal, int matspec, MYP viewpos = DefaultViewPos, MYP lightpos = DefaultLightPos, MYP lightcol = DefaultLightCol);
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
void swap (int* s1, int* s2);
void swap (double* s1, double* s2);

void makePerspective (double mat[ALLMSX][ALLMSY], double n, double f);

void copymatrix (ARRSIZ size, double To[ALLMSX][ALLMSY], double From[ALLMSX][ALLMSY]);
int  printmat (ARRSIZ sm, double m[ALLMSX][ALLMSY]);
void multimat  (ARRSIZ sa, double A[ALLMSX][ALLMSY], ARRSIZ sb, double B[ALLMSX][ALLMSY], ARRSIZ sc, double C[ALLMSX][ALLMSY]);

double TRAN [ALLMSX][ALLMSY] = {{1, 0, 0, 0},
                                {0, 1, 0, 0},
                                {0, 0, 1, 0},
                                {0, 0, 0, 1}};
double ALX [ALLMSX][ALLMSY] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
double ALY [ALLMSX][ALLMSY] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
double ALZ [ALLMSX][ALLMSY] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

ARRSIZ SCORD = {1, 4};

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
    return 1;
    }




int VEDRotateZ (double a)
    {
    TALZ += a;
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

void VED3dObjTriangle  (ObjTriangle givenTriangle,
                        RGBQUAD* texture, RGBQUAD* normales, RGBQUAD* specular, MYP texturesize,
                        MYP lightpos, MYP lightcol, MYP viewpos)
    {
    lightpos.x = lightpos.x/ZScalingCoeff/lightpos.z;
    lightpos.y = lightpos.y/ZScalingCoeff/lightpos.z;

    MYP first  = makeAllVecDeforms(givenTriangle.cords.f);
    MYP second = makeAllVecDeforms(givenTriangle.cords.s);
    MYP third  = makeAllVecDeforms(givenTriangle.cords.t);

    if (GetAsyncKeyState('M'))
        {
        txSetColor (TX_YELLOW, 10, MyScreen);
        drawVec (first, lightpos - first);
        drawVec (second, lightpos - second);
        drawVec (third, lightpos - third);
        }

    assert (givenTriangle.textures.f.x >= 0);
    assert (givenTriangle.textures.f.y >= 0);
    assert (givenTriangle.textures.s.x >= 0);
    assert (givenTriangle.textures.s.y >= 0);
    assert (givenTriangle.textures.t.x >= 0);
    assert (givenTriangle.textures.t.y >= 0);

    VEDObjTriangle ({SzScr.x/2 + first.x, SzScr.y/2 + first.y, first.z},
                    {SzScr.x/2 + second.x, SzScr.y/2 + second.y, second.z},
                    {SzScr.x/2 + third.x, SzScr.y/2 + third.y, third.z},
                    givenTriangle.textures.f, givenTriangle.textures.s, givenTriangle.textures.t, texture, normales, specular, texturesize);

    }


int VEDObjTriangle (MYP first, MYP second, MYP third, MYP ftext, MYP stext, MYP ttext, RGBQUAD* texture, RGBQUAD* normales, RGBQUAD* specular, MYP textsize)
    {
    MYP down;
    MYP mid;
    MYP up;
    MYP dtext;
    MYP mtext;
    MYP utext;

    assert (ftext.x >= 0);
    assert (ftext.y >= 0);
    assert (stext.x >= 0);
    assert (stext.y >= 0);
    assert (ttext.x >= 0);
    assert (ttext.y >= 0);

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
    txSetColor (TX_WHITE, 1, MyScreen);

    assert (utext.x >= 0);
    assert (utext.y >= 0);
    assert (dtext.x >= 0);
    assert (dtext.y >= 0);
    assert (mtext.x >= 0);
    assert (mtext.y >= 0);

    VEDObjHorTriangle ({help * allhwidth + down.x,
                       down.y + sectorheight + 1,
                       help * (up.z - down.z) + down.z},
                       mid, down,
                      {help * (utext.x - dtext.x) + dtext.x,
                       help * (utext.y - dtext.y) + dtext.y, 0},
                       mtext, dtext, texture, normales, specular, textsize);

    VEDObjHorTriangle ({down.x + help * allhwidth,
                       down.y + sectorheight,
                       down.z + help * (up.z - down.z)},
                       mid, up,
                      {help * (utext.x - dtext.x) + dtext.x,
                       help * (utext.y - dtext.y) + dtext.y, 0},
                       mtext, utext, texture, normales, specular, textsize);
    return 0;
    }


int VEDObjHorTriangle(MYP left, MYP right, MYP third, MYP ltext, MYP rtext, MYP ttext, RGBQUAD* texture, RGBQUAD* normales, RGBQUAD* specular, MYP textsize)
    {
    double allheight = third.y - left.y;

    if (fabs (allheight) <= 1)
        {
        VEDLine (left.x, left.y, left.z, right.x, right.y, right.z, ltext, rtext);
        return 0;
        }

    double signum = allheight/fabs(allheight);

    int lbr = (left.x > right.x)? -1:1;

    bool exit = true;

    double nowheight = 0;
    double leftwidth = third.x - left.x;
    double rightwidth = third.x - right.x;

    double help = 0;

    for (double nowy = left.y; exit; nowy += signum)
        {
        assert (ltext.x >= 0);
        assert (ltext.y >= 0);
        assert (ttext.x >= 0);
        assert (ttext.y >= 0);
        assert (rtext.x >= 0);
        assert (rtext.y >= 0);

        if (signum > 0 && nowy + signum >= third.y) exit = false;
        if (signum < 0 && nowy + signum <= third.y) exit = false;

        nowheight = third.y - nowy;
        help = nowheight/allheight;

        VEDObjLine ( left.x + help*leftwidth - 1 * lbr,   left.y + nowheight,  left.z + help*(third.z -  left.z),
                    right.x + help*rightwidth + 1 * lbr, right.y + nowheight, right.z + help*(third.z - right.z),
                   {ltext.x + help*(ttext.x - ltext.x), ltext.y + help*(ttext.y - ltext.y), 0},
                   {rtext.x + help*(ttext.x - rtext.x), rtext.y + help*(ttext.y - rtext.y), 0}, texture, normales, specular, textsize);
        }
    return 0;
    }



int VEDTriangle (MYP first, MYP second, MYP third, MYP fcol, MYP scol, MYP tcol)
    {
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

    txSetColor (TX_WHITE, 1, MyScreen);

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
    return 0;                                                               //линейна€ интерпол€ци€
    }                                                                         //x = x0 + t*(x1-x0)


int VEDHorTriangle(MYP left, MYP right, MYP third, MYP lcol, MYP rcol, MYP tcol)
    {
    double allheight = third.y - left.y;

    if (fabs (allheight) <= 1)
        {
        VEDLine (left.x, left.y, left.z, right.x, right.y, right.z, lcol, rcol);
        return 0;
        }

    double signum = allheight/fabs(allheight);

    bool exit = true;

    double nowheight = 0;

    double leftwidth = third.x - left.x;
    double rightwidth = third.x - right.x;

    double help = 0;

    for (double nowy = left.y; exit; nowy += signum)
        {
        nowheight = third.y - nowy;
        help = nowheight/allheight;

        if (signum > 0 && nowy + signum >= third.y) exit = false;
        if (signum < 0 && nowy + signum <= third.y) exit = false;

        VEDLine ( left.x + help* leftwidth - 1,  left.y + nowheight,  left.z + help*(third.z -  left.z),
                 right.x + help*rightwidth + 1, right.y + nowheight, right.z + help*(third.z - right.z),
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
    double cord1 [ALLMSX][ALLMSY] = {{first.x, 0, 0, 0}, {first.y, 0, 0, 0}, {first.z, 0, 0, 0}, {1, 0, 0, 0}};
    double cord2 [ALLMSX][ALLMSY] = {{second.x, 0, 0, 0}, {second.y, 0, 0, 0}, {second.z, 0, 0, 0}, {1, 0, 0, 0}};
    double cord3 [ALLMSX][ALLMSY] = {{third.x, 0, 0, 0}, {third.y, 0, 0, 0}, {third.z, 0, 0, 0}, {1, 0, 0, 0}};

    col1 = col1 / 255;
    col2 = col2 / 255;
    col3 = col3 / 255;
    lightcol = lightcol / 255;

    MYP VecFS = second - first;
    MYP VecFT = third  - first;
    MYP Normal  = VectorMultip (VecFS, VecFT);

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

    if (GetAsyncKeyState('M'))
        {
        txSetColor (TX_YELLOW, 10, MyScreen);
        drawVec (first, lightpos - first);
        drawVec (second, lightpos - second);
        drawVec (third, lightpos - third);
        }

    MYP Light1Dir = first - lightpos;
    MYP Light2Dir = second - lightpos;
    MYP Light3Dir = third - lightpos;

    MYP View1Dir = first - viewpos;
    MYP View2Dir = second - viewpos;
    MYP View3Dir = third - viewpos;

    MYP Light1DirRef = Normal * 2 * (Light1Dir * Normal) - Light1Dir;
    MYP Light2DirRef = Normal * 2 * (Light2Dir * Normal) - Light2Dir;
    MYP Light3DirRef = Normal * 2 * (Light3Dir * Normal) - Light3Dir;

    double Spec1 = Light1DirRef^View1Dir;
    double Spec2 = Light2DirRef^View2Dir;
    double Spec3 = Light3DirRef^View3Dir;

    if (Spec1 < 0) Spec1 = 0;
    if (Spec2 < 0) Spec2 = 0;
    if (Spec3 < 0) Spec3 = 0;

    double MatSpec1 = pow (Spec1, MaterialReflective);
    double MatSpec2 = pow (Spec2, MaterialReflective);
    double MatSpec3 = pow (Spec3, MaterialReflective);

    double diffuse1 = Normal^(Light1Dir);
    double diffuse2 = Normal^(Light2Dir);
    double diffuse3 = Normal^(Light3Dir);

    if (diffuse1 < 0) diffuse1 = 0;
    if (diffuse2 < 0) diffuse2 = 0;
    if (diffuse3 < 0) diffuse3 = 0;

    col1 = /*(environmentcol % col1) + */col1 % lightcol * diffuse1;/* + lightcol * MatSpec1; //*/
    col2 = /*(environmentcol % col2) + */col2 % lightcol * diffuse2;/* + lightcol * MatSpec2; //*/
    col3 = /*(environmentcol % col3) + */col3 % lightcol * diffuse3;/* + lightcol * MatSpec3; //*/

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

    if (isper)  multimat (STRAN, PERSPECTIVE, SCORD, cord, SCORD, cord);

    if (fabs(cord[2][0]) <= 0.0015) cord[2][0] = ZScalingCoeff;
    cord[0][0] = cord[0][0]/ZScalingCoeff/cord[2][0];
    cord[1][0] = cord[1][0]/ZScalingCoeff/cord[2][0];
    }


int VEDObjLine (int x1, int y1, double z1, int x2, int y2, double z2, MYP text1, MYP text2, RGBQUAD* texture, RGBQUAD* normales, RGBQUAD* specular, MYP texturesize)
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
        help = (double)(xn - x1)/(double)(x2 - x1);
        assert (help >= 0 && help <= 1);
        assert (text2.x >= 0);
        assert (text2.y >= 0);
        assert (text1.x >= 0);
        assert (text1.y >= 0);
        if (swapped)
            {
            VEDObjPix ((int)(y1 + help * (y2 - y1)), (int)xn,
                       (int)((help * (z2 - z1) + z1) * 10),
                       (int)((help * (text2.x - text1.x) + text1.x) * (texturesize.x - 1)),
                       (int)((help * (text2.y - text1.y) + text1.y) * (texturesize.y - 1)), texture, normales, specular, (int)texturesize.x, (int)texturesize.y);
            }
        else
            {
            VEDObjPix ((int)xn, (int)(y1 + help * (y2 - y1)), (int)((help*(z2 - z1) + z1)*10),
                       (int)((help * (double)(text2.x - text1.x) + text1.x) * (texturesize.x - 1)),
                       (int)((help * (double)(text2.y - text1.y) + text1.y) * (texturesize.y - 1)), texture, normales, specular, (int)texturesize.x, (int)texturesize.y);
            }
        }
    return 0;
    }


int VEDLine (double x1, double y1, double z1, double x2, double y2, double z2, MYP col1, MYP col2)
    {
    if (x1 > x2)
        {
        swap (&x1, &x2);
        MYPSwap (&col1, &col2);
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
        help = (xn - x1)/(x2 - x1);
        if (swapped)
            {
            MyPix ((int)(y1 + help * (y2 - y1)), xn, (help*(z2 - z1) + z1)*10,
                    (BYTE)(help * (col2.x - col1.x) + col1.x),
                    (BYTE)(help * (col2.y - col1.y) + col1.y),
                    (BYTE)(help * (col2.z - col1.z) + col1.z));
            }
        else
            {
            MyPix (xn, (int)(y1 + help * (y2 - y1)), (help*(z2 - z1) + z1)*10,
                    (BYTE)(help * (col2.x - col1.x) + col1.x),
                    (BYTE)(help * (col2.y - col1.y) + col1.y),
                    (BYTE)(help * (col2.z - col1.z) + col1.z));
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

void swap (int* s1, int* s2)
    {
    int help = *s1;
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

    MYP fircol = {255, 0, 0};
    MYP seccol = {0, 255, 0};
    MYP thicol = {0, 0, 255};
    MYP forcol = {255, 255, 0};
    MYP fifcol = {0, 255, 255};
    MYP sixcol = {255, 0, 255};

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

    return 0;
    }

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
    int pointsnum = (int)(PI * 2/stepAngle + 0.5);
    MYP *rotatedPoints = new MYP[(pointsnum + 2) * (pointsnum + 2)];

    tx_auto_func (delete [] rotatedPoints);
    int turnover = 0;

    for (double Angle = 0; Angle <= PI * 2 + stepAngle; Angle += stepAngle)
        {
        rotatedPoints[turnover] = {0, sin(Angle), cos(Angle)};
        turnover++;
        }

    pointsnum = turnover;
    MYP pointBeforeRotation;

    for (double Angle = stepAngle; Angle <= PI * 2 + stepAngle; Angle += stepAngle)
        {
        for (int i = 0; i < pointsnum; i++)
            {
            if (turnover == pointsnum *  (pointsnum + 1)) turnover--;

            rotatedPoints[turnover] = RotateVecY (rotatedPoints[i], Angle);

            if (fabs (pointBeforeRotation.y) > 0.0015) printf ("yisnotthesame\n");

            turnover++;
            }
        }

    turnover = 0;
    MYP helpPoint;
    MYP upperPoint = rotatedPoints[0];
    VED3dTriangle (upperPoint,
                  {upperPoint.x + 0.25, upperPoint.y + 0.25, upperPoint.z},
                  {upperPoint.x - 0.25, upperPoint.y - 0.25, upperPoint.z}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255});


    for (int latitude = pointsnum / 4; latitude < (pointsnum)*3/4 - 1; latitude++)
        {
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
        }
    }


void VEDObjFigure (ObjTriangle Figure[], int TrianglesAmount, RGBQUAD* texture, RGBQUAD* normales, RGBQUAD* specular, MYP texturesize)
    {
    for (int i = 0; i < TrianglesAmount; i++)
        {
        VED3dObjTriangle (Figure[i], texture, normales, specular, texturesize);
        }
    }



int makemat (ARRSIZ SM, double A[ALLMSX][ALLMSY], double B[ALLMSX][ALLMSY])
    {
    for (int x = 0; x < SM.y; x++)
        {
        for (int y = 0; y < SM.x; y++)
            {
            A[x][y] = B[x][y];
            }
        }
    return 1;
    }

void multimat (ARRSIZ sa, double A[ALLMSX][ALLMSY], ARRSIZ sb, double B[ALLMSX][ALLMSY], ARRSIZ sc, double C[ALLMSX][ALLMSY])
    {
    double CCopy [ALLMSX][ALLMSY];

    copymatrix (sa, CCopy, C);

    int minx = sa.x;
    int miny = sb.y;
    int minhv = sb.y;

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
            }
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

//MYP VectorMultip (MYP a, MYP b)
//    {
//    return {a.y * b.z - a.z * b.y,
//            a.z * b.x - a.x * b.z,
//            a.x * b.y - a.y * b.x};
//    }

void drawVec (MYP start, MYP vec, COLORREF color, COLORREF pointcolor, int width, int pointrad)
    {
    txSetColor (color, width);
    txLine (start.x, start.y,
            start.x + vec.x,
            start.y + vec.y, MyScreen);

    txSetColor (pointcolor, 1);
    txSetFillColor (pointcolor);
    txEllipse (start.x + vec.x + pointrad,
               start.y + vec.y + pointrad,
               start.x + vec.x - pointrad,
               start.y + vec.y - pointrad, MyScreen);
    }

bool control (double speed)
    {
    bool returning = false;
    static POINT OldMousePos = {0, 0};
    POINT NewMousePos = txMousePos();
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

    OldMousePos = NewMousePos;

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

    const int getLineSize = 100;
    //char getLine[getLineSize] = {};
    char getType[4] = {};

    char partone [getLineSize] = {};
    char parttwo [getLineSize] = {};
    char partthree [getLineSize] = {};
    char allline [getLineSize] = {};

    MYP *getPoints = new MYP[10000];
    MYP *getTextures = new MYP[10000];
    MYP *getNormals = new MYP[10000];

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

    while (!feof(model))
        {
        fscanf (model, "%[^\n]\n", allline);
        if (allline[0] != 0 && allline[0] != '#')
            {
            sscanf (allline, "%s %s %s %s", getType, partone, parttwo, partthree);
            //printf ("%s %s %s %s\n", getType, partone, parttwo, partthree);
            if (getType[0] == 'v')
                {
                //getch();
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
                        getNormals[normalsturnover].y = ScY;
                        getNormals[normalsturnover].z = ScZ;
                        normalsturnover++;
                        }
                    else
                    if (getType[1] == 't')
                        {
                        getTextures[texturesturnover].x = ScX;
                        getTextures[texturesturnover].y = ScY;
                        getTextures[texturesturnover].z = ScZ;
                        texturesturnover++;
                        }
                    }
                }
            if (getType[0] == 'f')
                {
                sscanf (partone, "%d/%d/%d", &fft, &sft, &tft);
                sscanf (parttwo, "%d/%d/%d", &fst, &sst, &tst);
                sscanf (partthree, "%d/%d/%d", &ftt, &stt, &ttt);

                Figure[figurecounter].cords = {getPoints[fft - 1], getPoints[fst - 1], getPoints[ftt - 1]};

                Figure[figurecounter].textures = {getTextures[sft - 1], getTextures[sst - 1], getTextures[stt - 1]};

                Figure[figurecounter].normales = {getNormals[tft - 1], getNormals[tst - 1], getNormals[ttt - 1]};
                figurecounter++;
                }                         //*/
            }
        }
    printf ("this is the end... there are %d triangles contained of %d points\n", figurecounter, pointsturnover);
    getch();

    delete [] getPoints;
    delete [] getTextures;
    delete [] getNormals;

    return figurecounter;
    }

RGBQUAD* VEDLoadRGBQUADImage (string getName, MYP sizes)
    {
    RGBQUAD *returning = new RGBQUAD[(int)(sizes.x * sizes.y)];

    HDC helpDC = txLoadImage (getName.c_str());

    if (!helpDC) txMessageBox ("cannot load %s", getName.c_str());

    HDC retDC = txCreateDIBSection ((int)(sizes.x), (int)(sizes.y), &returning);

    txBitBlt (retDC, 0, 0, sizes.x, sizes.y, helpDC);

    txClearConsole();
    txSetFillColor(TX_BLACK);

    txClear();
    return returning;
    }

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
    left->rgbRed   += (int)(right.rgbRed   * Koeff);
    left->rgbGreen += (int)(right.rgbGreen * Koeff);
    left->rgbBlue  += (int)(right.rgbBlue  * Koeff);
    }

void VEDStart ()
    {
    SzScr = POINT{GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)};

    ZBuffer = new double[(SzScr.x + 1) * (SzScr.y + 1)];

    makeBufferDefault();

    txCreateWindow (SzScr.x, SzScr.y);

    MyScreen = txCreateDIBSection(SzScr.x, SzScr.y, &MyPixels);
    }

int VEDObjPix(int x, int y, int z, int textx, int texty, RGBQUAD* texture, RGBQUAD* normales, RGBQUAD* specular,
              int textsizex, int textsizey, MYP viewpos, MYP lightpos, MYP lightcol)
    {
    int thisPixPos = (int)((x) + (SzScr.y - y)*SzScr.x);


    if (thisPixPos > SzScr.x * SzScr.y || thisPixPos < 0) return 0;

    if (z <= ZBuffer[thisPixPos] || fabs (ZBuffer[thisPixPos] - z) < 0.01)
        {
        if (ShowMeZBuffer) MyPixels[thisPixPos] = RGBQUAD {(BYTE)(z/2), (BYTE)(z/2), (BYTE)(z/2)};
        else
            {
            RGBQUAD needcol;

            int textpos = (int)(textx + texty * textsizex);
            assert (textpos >= 0);
            if (texty >= 1024) return 0;
            RGBQUAD textcol = texture[textpos];
            needcol = makeColorWithLight ({(double)x, (double)y, (double)z},
                                          {(double)textcol.rgbRed - 1, (double)textcol.rgbGreen - 1, (double)textcol.rgbBlue - 1},
                                          {(double)normales[textpos].rgbRed - 128, (double)normales[textpos].rgbGreen - 128, normales[textpos].rgbBlue - 128},
                                          (double)(specular[textpos].rgbRed - 1), viewpos, lightpos, lightcol);
            MyPixels[thisPixPos] = needcol;
            }
        ZBuffer[thisPixPos] = z;
        }
    return 1;
    }

RGBQUAD makeColorWithLight (MYP pos, MYP color, MYP normal, int matspec, MYP viewpos, MYP lightpos, MYP lightcol)
    {
    color = color/255;
    lightcol = lightcol/255;

    normal = normal/normal.length();

    lightpos.x = lightpos.x/ZScalingCoeff/lightpos.z;
    lightpos.y = lightpos.y/ZScalingCoeff/lightpos.z;

    MYP lightdir = pos - lightpos;
    MYP viewdir = pos - viewpos;

    MYP lightdirref = normal * 2 * (lightdir * normal) - lightdir;

    double glare = lightdirref^viewdir;
    double matglare = pow (glare, matspec);

    double illum = normal^lightdir;
    if (illum < 0) illum = 0;

    if (matglare < 0) matglare = 0;

    color = color % lightcol * illum;/* + lightcol * matglare; //*/
    color = color * 255;

    if (color.x > 254) color.x = 254;
    if (color.y > 254) color.y = 254;
    if (color.z > 254) color.z = 254;

    if (color.x < 0) color.x = 0;
    if (color.y < 0) color.y = 0;
    if (color.z < 0) color.z = 0;

    return {(BYTE)color.z, (BYTE)color.y, (BYTE)color.x};
    }


void VEDMakeTriangleFigure (Triangle* figure, ObjTriangle* objfigure, int size)
    {
    for (int i = 0; i < size; i++)
        {
        figure[i] = objfigure[i].cords;
        }
    }
