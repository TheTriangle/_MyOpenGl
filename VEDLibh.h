
#include "TXLib.h"
#define ctg(x) (1/tan(x))
#define DEGREEMODIFIER 0.01745
#define PI 3.141593
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
    };
POINT SzScr = {0, 0};
int BufferDefault = 5000;

const double MaterialReflective = 35;

bool ShowMeZBuffer = false;
HDC MyScreen = NULL;

RGBQUAD *MyPixels = NULL;
double *ZBuffer = NULL;
#define MyPix(_x, _y, _z, _r, _g, _b)  int thisPixPos = (int)((_x) + (int)(SzScr.y - _y)*SzScr.x);\
    if (_z < ZBuffer[thisPixPos]) \
        {     \
        if (ShowMeZBuffer) MyPixels[thisPixPos] = RGBQUAD {(BYTE)(_z/2), (BYTE)(_z/2), (BYTE)(_z/2)}; \
        else MyPixels[thisPixPos] = RGBQUAD {(BYTE)(_b), (BYTE)(_g), (BYTE)(_r)}; \
        ZBuffer[thisPixPos] = _z;     \
        }                                  \
    //else \
        { \
        MyPixels[thisPixPos] = RGBQUAD {255, 255, 255}; \
        }
const int ALLMSX = 4;
const int ALLMSY = 4;
struct ARRSIZ
    {
    const int x;
    const int y;
    };




double TALX = 0;
double TALY = 0;
double TALZ = 0;

bool control (double speed = 1);
void MakeBufferDefault ();
MYP VectorMultip (MYP a, MYP b);
int VEDLine (double x1, double y1, double z1, double x2, double y2, double z2, MYP col1, MYP col2);
void MYPSwap (MYP* pt1, MYP* pt2);
void VED3dTriangle (MYP first, MYP second, MYP third, MYP col1, MYP col2, MYP col3, MYP lightpos = {270, 270, 3}, MYP lightcol = {255, 255, 255}, MYP viewpos = {0, 0, -5});
void makeAllDeforms (double cord [ALLMSX][ALLMSY], bool isper);
int VEDTriangle (MYP first, MYP second, MYP third, MYP fcol, MYP scol, MYP tcol);
void swap (double* s1, double* s2);
int VEDHorTriangle(MYP left, MYP right, MYP third, MYP lcol, MYP rcol, MYP tcol);
void makePerspective (double mat[ALLMSX][ALLMSY], double n, double f);
void copymatrix (ARRSIZ size, double To[ALLMSX][ALLMSY], double From[ALLMSX][ALLMSY]);
int makemat (ARRSIZ SM, double A[ALLMSX][ALLMSY], double B[ALLMSX][ALLMSY]);
int printmat (ARRSIZ sm, double m[ALLMSX][ALLMSY]);
int VEDRotateZ (double a);
int VEDjVertex (double x, double y, double z, double x1, double y1, double z1);
int VEDRotateY (double a);
int VEDRotateX (double a);
int VEDTranslate (double x, double y, double z);
int VEDCube (bool isper);
int VEDVertex (MYP old, MYP NEW, bool isper);
int VEDScale (double wx, double wy, double wz);
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

int VEDTriangle (MYP first, MYP second, MYP third, MYP fcol, MYP scol, MYP tcol)
    {
    //txSetColor (TX_GREEN);
    //VEDVertex (first, second, false);
    //txSetColor (RGB(0, 204, 204));
    //VEDVertex (second, third, false);
    //txSetColor (TX_WHITE);
    //VEDVertex (first, third, false);

    MYP down = {};
    MYP mid = {};
    MYP up = {};
    MYP dcol = {};
    MYP mcol = {};
    MYP ucol = {};

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

    if (fabs (allheight) <= 0.00015) return 0;

    double help = sectorheight/allheight;

    //printf ("mid.y == %f, down.y == %f\n", mid.y, down.y);
    //printf ("sech == %f\n", sectorheight);

    txSetColor (TX_WHITE, 1, MyScreen);
    txSetFillColor (RGB(dcol.x, dcol.y, dcol.z), MyScreen);

    txEllipse (down.x - 10, down.y - 10, down.x + 10, down.y + 10, MyScreen);

    char helpch[16] = {};
    sprintf (helpch, "%f", down.z);
    txDrawText (down.x - 80, down.y - 50, down.x + 80, down.y - 20, helpch, DT_CENTER, MyScreen);

    txSetFillColor (RGB(mcol.x, mcol.y, mcol.z), MyScreen);

    txEllipse (mid.x - 10, mid.y - 10, mid.x + 10, mid.y + 10, MyScreen);

    sprintf (helpch, "%f", down.z);
    txDrawText (mid.x - 80, mid.y - 50, mid.x + 80, mid.y - 20, helpch, DT_CENTER, MyScreen);

    txSetFillColor (RGB(ucol.x, ucol.y, ucol.z), MyScreen);

    txEllipse (up.x - 10, up.y - 10, up.x + 10, up.y + 10, MyScreen);

    sprintf (helpch, "%f", down.z);
    txDrawText (up.x - 80, up.y - 50, up.x + 80, up.y - 20, helpch, DT_CENTER, MyScreen);

    VEDHorTriangle ({help * allhwidth + down.x,
                     down.y + sectorheight,
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
    return 0;                                                               //�������� ������������
    }                                                                         //x = x0 + t*(x1-x0)


int VEDHorTriangle(MYP left, MYP right, MYP third, MYP lcol, MYP rcol, MYP tcol)
    {
    double allheight = third.y - left.y;
    //printf ("third.y == %f\n left.y == %f", third.y, left.y);
    if (fabs (allheight) < 0.015)
        {
        //getch();
        VEDLine (left.x, left.y, left.z, right.x, right.y, right.z, lcol, rcol);
        return 0;
        //printf ("i've returned");
        }
    //printf ("allh == %f\n", allheight);
    assert (fabs (allheight) >= 0.015);
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
        assert (fabs (allheight) >= 0.015);
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

void VED3dTriangle (MYP first, MYP second, MYP third, MYP col1, MYP col2, MYP col3, MYP lightpos, MYP lightcol, MYP viewpos)
    {
    double cord1 [ALLMSX][ALLMSY] = {{first.x, 0, 0, 0}, {first.y, 0, 0, 0}, {first.z, 0, 0, 0}, {1, 0, 0, 0}};
    double cord2 [ALLMSX][ALLMSY] = {{second.x, 0, 0, 0}, {second.y, 0, 0, 0}, {second.z, 0, 0, 0}, {1, 0, 0, 0}};
    double cord3 [ALLMSX][ALLMSY] = {{third.x, 0, 0, 0}, {third.y, 0, 0, 0}, {third.z, 0, 0, 0}, {1, 0, 0, 0}};

    col1 = col1 * (0.003922);//1/255
    col2 = col2 * (0.003922);
    col3 = col3 * (0.003922);
    lightcol = lightcol * (0.003922);
    MYP environmentcol = {0.2, 0.2, 0.2};
    //printf ("before1col1 == %f, %f, %f\n", col1.x, col1.y, col1.z);

    makeAllDeforms (cord1, false);
    makeAllDeforms (cord2, false);
    makeAllDeforms (cord3, false);

    first = {cord1[0][0], cord1[1][0], cord1[2][0]};
    second = {cord2[0][0], cord2[1][0], cord2[2][0]};
    third = {cord3[0][0], cord3[1][0], cord3[2][0]};

    MYP VecFS = second - first;
    MYP VecFT = third  - first;

    MYP Normal  = VectorMultip (VecFS, VecFT);
    //Normal = Normal / Normal.length();
    //txLine (SzScr.x/2 + first.x, SzScr.y/2 + first.y, SzScr.x/2 + first.x + Normal.x/0.0015/Normal.z * 100, SzScr.y/2 + first.y + Normal.y/0.0015/Normal.z * 100, MyScreen);
    //txSetColor (TX_YELLOW, 10);
    //txLine (lightpos.x/0.0015/lightpos.z, lightpos.y/0.0015/lightpos.z, SzScr.x/2, SzScr.y/2, MyScreen);

    MYP View1Dir = viewpos - first;
    MYP View2Dir = viewpos - second;
    MYP View3Dir = viewpos - third;

    MYP Light1Dir = first - lightpos;
    MYP Light2Dir = second - lightpos;
    MYP Light3Dir = third - lightpos;

    if (acos(Normal^Light1Dir) > PI/2) Normal = Normal * -1;

    MYP Light1DirRef = Normal * 2 * (Light1Dir * Normal) - Light1Dir;
    MYP Light2DirRef = Normal * 2 * (Light2Dir * Normal) - Light2Dir;
    MYP Light3DirRef = Normal * 2 * (Light3Dir * Normal) - Light3Dir;
    //��������� ��������
    double Spec1 = Light1DirRef^View1Dir;
    double Spec2 = Light2DirRef^View2Dir;
    double Spec3 = Light3DirRef^View3Dir;
    if (Spec1 < 0) Spec1 = 0;
    if (Spec2 < 0) Spec2 = 0;
    if (Spec3 < 0) Spec3 = 0;
    double MatSpec1 = pow (Spec1, MaterialReflective);
    double MatSpec2 = pow (Spec2, MaterialReflective);
    double MatSpec3 = pow (Spec3, MaterialReflective);

    double BrightnessMultiplier = 1;

    double diffuse1 = Normal^(Light1Dir/Light1Dir.length());
    double diffuse2 = Normal^(Light2Dir/Light2Dir.length());
    double diffuse3 = Normal^(Light3Dir/Light3Dir.length());
    if (diffuse1 < 0) diffuse1 = 0;
    if (diffuse2 < 0) diffuse2 = 0;
    if (diffuse3 < 0) diffuse3 = 0;
    //printf ("\nenv0/0col1.x                 == %f\n", (environmentcol % col1).x);
    //printf ("lightcol * MatSpec1.x          == %f\n", (lightcol * MatSpec1).x);

    //getch();
    //printf ("before col1 == %f, %f, %f\n", col1.x, col1.y, col1.z);

    /*printf ("col1.x == %f, col1.y == %f, col1.z == %f. \nDiffuse == %f (angle == %f)\n == Normal(%f, %f, %f)^\n^Light1Dir(%f, %f, %f)\n"
            "col1 0/0 lightcol * diffuse1.x == %f\n", col1.x * 255, col1.y * 255, col1.z * 255,
                                                      diffuse1, acos(diffuse1)/DEGREEMODIFIER,
                                                      Normal.x, Normal.y, Normal.z,
                                                      Light1Dir.x * 100, Light1Dir.y * 100, Light1Dir.z * 100,
                                                      (col1 % lightcol * diffuse1).x * 255);
    txSetFillColor (TX_WHITE);
    txSetColor (RGB((col1 % lightcol * diffuse1).x * 255, (col1 % lightcol * diffuse1).y * 255, (col1 % lightcol * diffuse1).z));
    txCircle (SzScr.x/2 + cord1[0][0], SzScr.y/2 + cord1[1][0], 10);
    getch();
    txSetFillColor (TX_BLACK);
    txClear();
    txClearConsole();    */

    col1 = /*(environmentcol % col1) + */col1 % lightcol * diffuse1 + lightcol * MatSpec1;
    col2 = /*(environmentcol % col2) + */col2 % lightcol * diffuse2 + lightcol * MatSpec2;
    col3 = /*(environmentcol % col3) + */col3 % lightcol * diffuse3 + lightcol * MatSpec3;

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

    //if (col1.x > 255) {BrightnessMultiplier = 255/col1.x; col1 = col1 * BrightnessMultiplier;}
    //if (col1.y > 255) {BrightnessMultiplier = 255/col1.y; col1 = col1 * BrightnessMultiplier;}
    //if (col1.z > 255) {BrightnessMultiplier = 255/col1.z; col1 = col1 * BrightnessMultiplier;}

    //col2 = (col2 + lightcol * (1/255)) + lightcol * MatSpec2;
    //if (col2.x > 255) {BrightnessMultiplier = 255/col2.x; col2 = col2 * BrightnessMultiplier;}
    //if (col2.y > 255) {BrightnessMultiplier = 255/col2.y; col2 = col2 * BrightnessMultiplier;}
    //if (col2.z > 255) {BrightnessMultiplier = 255/col2.z; col2 = col2 * BrightnessMultiplier;}

    //col3 = (col3 + lightcol * (1/255)) + lightcol * MatSpec3;
    //if (col3.x > 255) {BrightnessMultiplier = 255/col3.x; col3 = col3 * BrightnessMultiplier;}
    //if (col3.y > 255) {BrightnessMultiplier = 255/col3.y; col3 = col3 * BrightnessMultiplier;}
    //if (col3.z > 255) {BrightnessMultiplier = 255/col3.z; col3 = col3 * BrightnessMultiplier;}


    VEDTriangle ({SzScr.x/2 + cord1[0][0], SzScr.y/2 + cord1[1][0], cord1[2][0]},
                 {SzScr.x/2 + cord2[0][0], SzScr.y/2 + cord2[1][0], cord2[2][0]},
                 {SzScr.x/2 + cord3[0][0], SzScr.y/2 + cord3[1][0], cord3[2][0]}, col1, col2, col3);
    }

void makeAllDeforms (double cord[ALLMSX][ALLMSY], bool isper)
    {
    multimat (SAL, DEFORMATION, SCORD, cord, SCORD, cord);

    multimat (SAL, ALY, SCORD, cord, SCORD, cord);

    multimat (SAL, ALX, SCORD, cord, SCORD, cord);

    multimat (SAL, ALZ, SCORD, cord, SCORD, cord);

    multimat (SAL, TRAN, SCORD, cord, SCORD, cord);

    if (isper) multimat (STRAN, PERSPECTIVE, SCORD, cord, SCORD, cord);

    if (fabs(cord[2][0]) <= 0.0015) cord[2][0] = 0.0015;
    cord[0][0] = cord[0][0]/0.0015/cord[2][0];
    cord[1][0] = cord[1][0]/0.0015/cord[2][0];
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
    if (fabs(x2 - x1) < 1 && fabs (y2 - y1) < 1) return 0;
    bool swapped = false;
    if (fabs(x2 - x1) < fabs(y2 - y1))
        {
        swapped = true;
        swap (&x1, &y1);
        swap (&x2, &y2);
        }

    double help = 0;
    for (int xn = (int)x1; xn < x2; xn++)
        {
        //if (big2 - big1 == 0)
        //    {
            //if (swapped) printf ("swapped\n");
            //else printf ("not swapped\n");
            //printf ("x/y1 == %d (-) x/y2 == %d", big2, big1);
            //getch();
        //    }
        help = (xn - x1)/(x2 - x1);
        if (swapped)
            {
            if (y1 + help*(y2 - y1) < SzScr.x && y1 + help*(y2 - y1) > 0 &&
                xn < SzScr.y && xn > 0)
                {
                MyPix (y1 + help * (y2 - y1), xn, (help*(z2 - z1) + z1)*10,
                      (help * (col2.x - col1.x) + col1.x),
                      (help * (col2.y - col1.y) + col1.y),
                      (help * (col2.z - col1.z) + col1.z));
                }
            }
        else
            {
            if (y1 + help*(y2 - y1) < SzScr.y && y1 + help*(y2 - y1) > 0 &&
                xn < SzScr.x && xn > 0)
                {
                //printf ("thisz == %lf\n", (double)(help*(z2 - z1) + z1));
                //getch();
                //printf ("buffer[half][half] == %lf\n", (double)(ZBuffer[SzScr.x/2 + SzScr.y/2 * SzScr.x]));
                //getch();
                //printf ("colorof[half][half] == %d, %d, %d", (int)(MyPixels[SzScr.x/2 + SzScr.y/2 * SzScr.x].rgbRed), (int)(MyPixels[SzScr.x/2 + SzScr.y/2 * SzScr.x].rgbBlue), (int)(MyPixels[SzScr.x/2 + SzScr.y/2 * SzScr.x].rgbGreen));
                //getch();
                MyPix (xn, y1 + help * (y2 - y1), (help*(z2 - z1) + z1)*10,
                       (help * (col2.x - col1.x) + col1.x),
                       (help * (col2.y - col1.y) + col1.y),
                       (help * (col2.z - col1.z) + col1.z));
                }
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
    VED3dTriangle (c5, c4, c8, fifcol, fifcol, fifcol);
    VED3dTriangle (c5, c4, c8, fifcol, fifcol, fifcol);              //   1/-+------/4|//   5/--------/8
    VED3dTriangle (c1, c4, c5, fifcol, fifcol, fifcol);              //    |/  fr   |/
    VED3dTriangle (c1, c5, c6, fircol, fircol, fircol);              //    | |   sx | |
    VED3dTriangle (c2, c6, c7, sixcol, sixcol, sixcol);              //    |f| fv   |s|
    VED3dTriangle (c5, c6, c7, forcol, forcol, forcol);
    VED3dTriangle (c4, c8, c7, seccol, seccol, seccol);              //     /| t     /|
    VED3dTriangle (c5, c8, c7, forcol, forcol, forcol);              //     2/--------/3
    VED3dTriangle (c1, c2, c6, fircol, fircol, fircol);              //    |6/------|-/7
    VED3dTriangle (c4, c3, c7, seccol, seccol, seccol);
    VED3dTriangle (c1, c4, c3, thicol, thicol, thicol);
    VED3dTriangle (c1, c2, c3, thicol, thicol, thicol);
    VED3dTriangle (c2, c3, c7, sixcol, sixcol, sixcol);


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
            }     //C2,3 = A2,1 � B1,3 + A2,2 � B2,3 + A2,3 � B3,3 = 0 � 0 + 0 � 0 + 0 � 2 = 0
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

void MakeBufferDefault ()
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


    return returning;
    }


/*� ����� �����, ��� ��� ��� �� �������� �� ������� ����. ����� ���� ������ ����������
��� �������������.    _    -,    /|
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

//�������� ���������


//=============================================================================

    /*VEDVertex ({-1, -1, -1}, {-1, -1, +1}, isper);
    //VEDVertex ({-1, -1, +1}, {+1, -1, +1}, isper);
    //VEDVertex ({+1, -1, +1}, {+1, -1, -1}, isper);
    //VEDVertex ({+1, -1, -1}, {-1, -1, -1}, isper);
    //       /----------/
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



    */




