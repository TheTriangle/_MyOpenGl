
#include "TXLib.h"
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

int printmat (ARRSIZ sm, double m[ALLMSX][ALLMSY]);
int VEDRotateZ (double a);
int VEDjVertex (double x, double y, double z, double x1, double y1, double z1);
int VEDRotateY (double a);
int VEDRotateX (double a);
int VEDTranslate (double x, double y, double z);
int VEDCube ();
int VEDVertex (MYP old, MYP NEW);
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

ARRSIZ SCORD = {4, 4};

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
    double madealx [ALLMSX][ALLMSY] = {{0,      0,       0, 1},
                                       {0,  cos(a/57.3), sin(a/57.3), 0},
                                       {0, -sin(a/57.3), cos(a/57.3), 0},
                                       {1,      0,       0, 0}};


    multimat (SDEF, DEFORMATION, SAL, madealx, SDEF, DEFORMATION);
    txClearConsole();
    return 1;
    }


int VEDRotateY (double a)
    {
    double madealy [ALLMSX][ALLMSY] = {{cos(a/57.3), 0, -sin(a/57.3), 0},
                                       {     0, 1,       0, 0},
                                       {sin(a/57.3), 0,  cos(a/57.3), 0},
                                       {     0, 0,       0, 1}};
    multimat (SDEF, DEFORMATION, SAL, madealy, SDEF, DEFORMATION);
    return 1;
    }




int VEDRotateZ (double a)
    {
    double madealz [ALLMSX][ALLMSY] = {{cos(a/57.3), -sin(a/57.3), 0, 0},
                                       {sin(a/57.3),  cos(a/57.3), 0, 0},
                                       {     0,       0, 1, 0},
                                       {     0,       0, 0, 1}};
    multimat (SDEF, DEFORMATION, SAL, madealz, SDEF, DEFORMATION);
    return 1;
    }



int VEDTranslate (double x, double y, double z)
    {
    TRAN[3][0] += x;
    TRAN[3][1] += y;
    TRAN[3][2] += z;
    return 1;
    }




int VEDVertex (MYP old, MYP NEW)
    {
    double cord0 [ALLMSX][ALLMSY] = {{old.x, old.y, old.z, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    double cord1 [ALLMSX][ALLMSY] = {{NEW.x, NEW.y, NEW.z, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    //double ncord0 [ALLMSX][ALLMSY] = {};
    //double ncord1 [ALLMSX][ALLMSY] = {};

    multimat (SCORD, cord0, SDEF, DEFORMATION, SCORD, cord0);
    multimat (SCORD, cord0, STRAN, TRAN, SCORD, cord0);
    multimat (SCORD, cord1, SDEF, DEFORMATION, SCORD, cord1);
    multimat (SCORD, cord1, STRAN, TRAN, SCORD, cord1);

    if (fabs(cord0[0][2]) <= 0.0015) cord0[0][2] = 0.0015;
    if (fabs(cord1[0][2]) <= 0.0015) cord1[0][2] = 0.0015;


    txLine (txGetExtentX()/2 + (cord0[0][0]) / (0.05 * (cord0[0][2])),
            txGetExtentY()/2 + (cord0[0][1]) / (0.05 * (cord0[0][2])),
            txGetExtentX()/2 + (cord1[0][0]) / (0.05 * (cord1[0][2])),
            txGetExtentY()/2 + (cord1[0][1]) / (0.05 * (cord1[0][2])));

    return 0;
    }




int VEDCube ()
    {
    VEDVertex ({-1, -1, -1}, {-1, -1, +1});
    VEDVertex ({-1, -1, +1}, {+1, -1, +1});
    VEDVertex ({+1, -1, +1}, {+1, -1, -1});
    VEDVertex ({+1, -1, -1}, {-1, -1, -1});
    //       /----------/
    //      /          /
    //     /----------/
    VEDVertex ({-1, -1, -1}, {-1, +1, -1});
    VEDVertex ({-1, +1, -1}, {-1, +1, +1});
    VEDVertex ({-1, +1, +1}, {-1, -1, +1});


    //       /----------/
    //      /|         /
    //     /-+--------/
    //     | |
    //     | /
    //     |/
    //     /

    VEDVertex ({-1, +1, -1}, {+1, +1, -1});
    VEDVertex ({+1, +1, -1}, {+1, +1, +1});
    VEDVertex ({+1, +1, +1}, {-1, +1, +1});

    //       /----------/
    //      /|         /
    //     /-+--------/
    //     | |
    //     | /---------/
    //     |/         /
    //     /---------/


    txSetColor (TX_GREEN);
    VEDVertex ({+1, +1, -1}, {+1, -1, -1});
    txSetColor (TX_WHITE);
    VEDVertex ({+1, +1, +1}, {+1, -1, +1});

    //       /----------/
    //      /|         /|
    //     /-+--------/ |
    //     | |        | |
    //     | /--------+-/
    //     |/         |/
    //     /----------/

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

void multimat (ARRSIZ sa, double A[ALLMSX][ALLMSY], ARRSIZ sb, double B[ALLMSX][ALLMSY], ARRSIZ sc, double C[ALLMSX][ALLMSY])
    {
    int minx = 0;
    if (sb.x <= sa.x && sb.x <= sc.x) minx = sb.x;
    if (sc.x <= sb.x && sc.x <= sa.x) minx = sc.x;
    if (sa.x <= sb.x && sa.x <= sc.x) minx = sa.x;
    int miny = 0;
    if (sb.y <= sa.y && sb.y <= sc.y) miny = sb.y;
    if (sc.y <= sb.y && sc.y <= sa.y) miny = sc.y;
    if (sa.y <= sb.y && sa.y <= sc.y) miny = sa.y;
    int minhv = 0;
    if (sa.x <= sb.y) minhv = sa.x;
    if (sa.x <= sb.y) minhv = sa.x;
    double num = 0;
    for (int x = 0; x < miny; x++)
        {
        for (int y = 0; y < minx; y++)
            {
            for (int i = 0; i < minhv; i++)
                {
                num+= A[x][i] * B[i][y];
                }
            C[x][y] = num;
            num = 0;
            }     //C2,3 = A2,1 � B1,3 + A2,2 � B2,3 + A2,3 � B3,3 = 0 � 0 + 0 � 0 + 0 � 2 = 0
        }
    }



