
#include "TXLib.h"
#define ctg(x) 1/tan(x)
const int ALLMSX = 4;
const int ALLMSY = 4;
struct ARRSIZ
    {
    const int x;
    const int y;
    };


struct MYP
    {
    double x;
    double y;
    double z;
    };


double TALX = 0;
double TALY = 0;
double TALZ = 0;

int VEDLine (double x1, double y1, double x2, double y2, MYP col1, MYP col2);
void MYPSwap (MYP* pt1, MYP* pt2);
void VED3dTriangle (MYP first, MYP second, MYP third, MYP col1, MYP col2, MYP col3);
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
    double help = sectorheight/allheight;
    //printf ("mid.y == %f, down.y == %f\n", mid.y, down.y);
    //printf ("sech == %f\n", sectorheight);

    txSetColor (TX_WHITE);
    txSetFillColor (RGB(dcol.x, dcol.y, dcol.z));
    txCircle (down.x, down.y, 10);

    txSetFillColor (RGB(mcol.x, mcol.y, mcol.z));
    txCircle (mid.x, mid.y, 10);

    txSetFillColor (RGB(ucol.x, ucol.y, ucol.z));
    txCircle (up.x, up.y, 10);

    VEDHorTriangle ({help*allhwidth + down.x, down.y + sectorheight, 0}, mid, down, {help * (ucol.x - dcol.x) + dcol.x, help * (ucol.y - dcol.y) + dcol.y, help * (ucol.z - dcol.z) + dcol.z}, mcol, dcol);
    VEDHorTriangle ({help*allhwidth + down.x, down.y + sectorheight, 0}, mid,   up, {help * (ucol.x - dcol.x) + dcol.x, help * (ucol.y - dcol.y) + dcol.y, help * (ucol.z - dcol.z) + dcol.z}, mcol, ucol);
    return 0;                        //�������� ������������
    }                                              //x = x0 + t*(x1-x0)


int VEDHorTriangle(MYP left, MYP right, MYP third, MYP lcol, MYP rcol, MYP tcol)
    {
    double allheight = third.y - left.y;
    //printf ("third.y == %f\n left.y == %f", third.y, left.y);
    if (fabs (allheight) < 0.015)
        {
        //getch();
        VEDLine (left.x, left.y, right.x, right.y, lcol, rcol);
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
        if (signum > 0 && nowy + signum > third.y) exit = false;
        if (signum < 0 && nowy + signum < third.y) exit = false;
        //printf ("b\n");
        //getch();
        assert (fabs (allheight) >= 0.015);
        help = nowheight/allheight;
        VEDLine ( left.x + help* leftwidth,  left.y + nowheight,
                 right.x + help*rightwidth, right.y + nowheight,
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

    VEDLine (txGetExtentX()/2 + cord0[0][0],
             txGetExtentY()/2 + cord0[1][0],
             txGetExtentX()/2 + cord1[0][0],
             txGetExtentY()/2 + cord1[1][0], {255, 255, 255}, {200, 200, 200});
    return 0;
    }

void VED3dTriangle (MYP first, MYP second, MYP third, MYP col1, MYP col2, MYP col3)
    {
    double cord1 [ALLMSX][ALLMSY] = {{first.x, 0, 0, 0}, {first.y, 0, 0, 0}, {first.z, 0, 0, 0}, {1, 0, 0, 0}};
    double cord2 [ALLMSX][ALLMSY] = {{second.x, 0, 0, 0}, {second.y, 0, 0, 0}, {second.z, 0, 0, 0}, {1, 0, 0, 0}};
    double cord3 [ALLMSX][ALLMSY] = {{third.x, 0, 0, 0}, {third.y, 0, 0, 0}, {third.z, 0, 0, 0}, {1, 0, 0, 0}};
    makeAllDeforms (cord1, false);
    makeAllDeforms (cord2, false);
    makeAllDeforms (cord3, false);

    VEDTriangle ({txGetExtentX()/2 + cord1[0][0], txGetExtentY()/2 + cord1[1][0], 0},
                 {txGetExtentX()/2 + cord2[0][0], txGetExtentY()/2 + cord2[1][0], 0},
                 {txGetExtentX()/2 + cord3[0][0], txGetExtentY()/2 + cord3[1][0], 0}, col1, col2, col3);
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

int VEDLine (double x1, double y1, double x2, double y2, MYP col1, MYP col2)
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
        if (swapped) txSetPixel (y1 + help*(y2 - y1), xn, RGB (help*(col2.x - col1.x) + col1.x, help*(col2.y - col1.y) + col1.y, help*(col2.z - col1.z) + col1.z));
        else         txSetPixel (xn, y1 + help*(y2 - y1), RGB (help*(col2.x - col1.x) + col1.x, help*(col2.y - col1.y) + col1.y, help*(col2.z - col1.z) + col1.z));
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
    MYP mred = {255, 0, 0};
    MYP mgreen = {0, 255, 0};
    MYP mmid1 = {170, 85, 0};
    MYP mmid2 = {85, 170, 0};
    if (isper) //TODO you know what to do
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
    VED3dTriangle (c4, c3, c7, mmid1, mmid2, mgreen);
    VED3dTriangle (c4, c8, c7, mmid1, mmid2, mgreen);
    VED3dTriangle (c5, c6, c7, mmid1, mmid2, mgreen);
    VED3dTriangle (c5, c8, c7, mmid1, mmid2, mgreen);
    VED3dTriangle (c1, c2, c3, mred, mmid1, mmid2);              //     2/--------/3
    VED3dTriangle (c1, c4, c3, mred, mmid1, mmid2);              //     /|       /|
    VED3dTriangle (c1, c2, c6, mred, mmid1, mmid2);              //red1/-+------/4|
    VED3dTriangle (c1, c5, c6, mred, mmid1, mmid2);              //    | |      | |
    VED3dTriangle (c2, c6, c7, mmid1, mmid2, mgreen);            //    | |      | |
    VED3dTriangle (c2, c3, c7, mmid1, mmid2, mgreen);            //    |6/------|-/7green
    VED3dTriangle (c1, c4, c5, mred, mmid1, mmid1);              //    |/       |/
    VED3dTriangle (c5, c8, c4, mmid1, mmid2, mmid1);             //   5/--------/8
    assert (fabs(mred.x - 255) <= 0.5 && fabs(mred.y) <= 0.5 && fabs(mred.z) <= 0.5);
    assert (fabs(mgreen.x) <= 0.5 && fabs(mgreen.y - 255) <= 0.5 && fabs(mgreen.z) <= 0.5);
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



