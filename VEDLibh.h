
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

int makemat (ARRSIZ SM, double A[ALLMSX][ALLMSY], double B[ALLMSX][ALLMSY]);
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

ARRSIZ SCORD = {1, 4};
                                   //TODO merge all deformation matrix into one,
                                   //TODO make arrays dynamic
double PERSPECTIVE [ALLMSX][ALLMSY] = {{ctg(40 * 0.01745)/(4/3), 0, 0, 0},
                      {0, ctg(40 * 0.01745), 0, 0},
                      {0, 0, (5 + 3)/(5 - 3), 1},
                      {0, 0, (-2*5*3)/(5 - 3), 0}};


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
    ALX[1][2] = sin(TALX/60);
    ALX[2][1] =-sin(TALX/60);
    ALX[2][2] = cos(TALX/60);
    return 1;
    }


int VEDRotateY (double a)
    {
    TALY += a;

    ALY[0][0] = cos(TALY/60);
    ALY[0][2] =-sin(TALY/60);
    ALY[2][0] = sin(TALY/60);
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




int VEDVertex (MYP old, MYP NEW)
    {
    double cord0 [ALLMSX][ALLMSY] = {{old.x, 0, 0, 0}, {old.y, 0, 0, 0}, {old.z, 0, 0, 0}, {1, 0, 0, 0}};
    double cord1 [ALLMSX][ALLMSY] = {{NEW.x, 0, 0, 0}, {NEW.y, 0, 0, 0}, {NEW.z, 0, 0, 0}, {1, 0, 0, 0}};
    double ncord0 [ALLMSX][ALLMSY] = {{old.x, 0, 0, 0}, {old.y, 0, 0, 0}, {old.z, 0, 0, 0}, {1, 0, 0, 0}};
    double ncord1 [ALLMSX][ALLMSY] = {{NEW.x, 0, 0, 0}, {NEW.y, 0, 0, 0}, {NEW.z, 0, 0, 0}, {1, 0, 0, 0}};

    //multimat (SAL, DEFORMATION, SAL, ALX, SAL, DEFORMATION);
    //multimat (SAL, DEFORMATION, SAL, ALY, SAL, DEFORMATION);
    //multimat (SAL, DEFORMATION, SAL, ALZ, SAL, DEFORMATION);

    //multimat (SAL, DEFORMATION, SCORD, cord0, SCORD, cord0);
    //multimat (SAL, ALZ, SCORD, cord0, SCORD, cord0);
    //multimat (SCORD, cord0, SAL, ALX, SCORD, cord0);
    //multimat (SCORD, cord0, SAL, ALY, SCORD, cord0);
    //multimat (SAL, ALZ, SCORD, cord0, SCORD, cord0);
    //multimat (STRAN, TRAN, SCORD, ncord0, SCORD, ncord0);
    //multimat (SCORD, cord0, STRAN, PERSPECTIVE, SCORD, cord0);

    //multimat (SDEF, DEFORMATION, SCORD, cord1, SCORD, cord1);
    //multimat (SAL, ALZ, SCORD, cord1, SCORD, cord1);
    //multimat (SCORD, cord1, SAL, ALX, SCORD, cord1);
    //multimat (SCORD, cord1, SAL, ALY, SCORD, cord1);
    //multimat (SAL, ALZ, SCORD, cord1, SCORD, cord1);
    //multimat (STRAN, TRAN, SCORD, ncord1, SCORD, ncord1);
    //multimat (SCORD, cord1, STRAN, PERSPECTIVE, SCORD, cord1);

    //if (fabs(ncord0[0][2]) <= 0.0015) cord0[0][2] = 0.0015;
    //if (fabs(ncord1[0][2]) <= 0.0015) cord1[0][2] = 0.0015;
    //printmat(SAL, ALZ);
    double MyDef [ALLMSX][ALLMSY] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
    //multimat (SAL, ALZ, SDEF, MyDef, SDEF, MyDef);
    //multimat (SAL, ALX, SDEF, MyDef, SDEF, MyDef);
    //multimat (SAL, ALY, SDEF, MyDef, SDEF, MyDef);

    //multimat (SAL, MyDef, SCORD, ncord0, SCORD, ncord0);
    multimat (SAL, ALZ, SCORD, cord0, SCORD, ncord0);
    makemat(SCORD, cord0, ncord0);
    multimat (SAL, ALX, SCORD, cord0, SCORD, ncord0);
    makemat(SCORD, cord0, ncord0);
    multimat (SAL, ALY, SCORD, cord0, SCORD, ncord0);
    multimat (SAL, DEFORMATION, SCORD, ncord0, SCORD, ncord0);
    multimat (SAL, TRAN, SCORD, ncord0, SCORD, ncord0);

    //multimat (SAL, ALZ, SCORD, ncord1, SCORD, ncord1);
    //multimat (SAL, ALX, SCORD, ncord1, SCORD, ncord1);
    //multimat (SAL, ALY, SCORD, ncord1, SCORD, ncord1);
    multimat (SAL, ALZ, SCORD, cord1, SCORD, ncord1);
    makemat(SCORD, cord1, ncord1);
    multimat (SAL, ALX, SCORD, cord1, SCORD, ncord1);
    makemat(SCORD, cord1, ncord1);
    multimat (SAL, ALY, SCORD, cord1, SCORD, ncord1);
    multimat (SAL, DEFORMATION, SCORD, ncord1, SCORD, ncord1);
    multimat (SAL, TRAN, SCORD, ncord1, SCORD, ncord1);

    if (fabs(ncord0[2][0])<=0.0015) ncord0[2][0] = 0.0015;
    if (fabs(ncord1[2][0])<=0.0015) ncord1[2][0] = 0.0015;
    txLine (txGetExtentX()/2 + ncord0[0][0]/ncord0[2][0],
            txGetExtentY()/2 + ncord0[1][0]/ncord0[2][0],
            txGetExtentX()/2 + ncord1[0][0]/ncord1[2][0],
            txGetExtentY()/2 + ncord1[1][0]/ncord1[2][0]);

   /* txLine (txGetExtentX()/2 + (cord0[0][0]), // ((0.015*cord0[0][2])),
            txGetExtentY()/2 + (cord0[1][0]), // ((0.015*cord0[0][2])),
            txGetExtentX()/2, // ((0.015*cord1[0][2])),
            txGetExtentY()/2); // ((0.015*cord1[0][2])));  //*/

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
    int minx = sb.y;
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
            C[x][y] = num;
            num = 0;
            }     //C2,3 = A2,1 · B1,3 + A2,2 · B2,3 + A2,3 · B3,3 = 0 · 0 + 0 · 0 + 0 · 2 = 0
        }
    }
//Я вдруг понял, что мой код не содержит НИ ЕДИНОГО КОТА. Нужно было срочно исправлят
//это недоразумение. Я завёз сразу двух. Первый даже решил поискать баги.
//    _.-|   |          |\__/,|   (`\
//   {   |   |          |o o  |__ _) )
//    "-.|___|        _.( T   )  `  /
//     .--'-`-.     _((_ `^--' /_<  \
//   .+|______|__.-||__)`-'(((/  (((/


//            .__....._             _.....__,
//                 .": o :':         ;': o :".
//                 `. `-' .'.       .'. `-' .'
//                   `---'             `---'
//                                                   .
//         _...----...      ...   ...      ...----..._
//      .-'__..-""'----    `.  `"`  .'    ----'""-..__`-.
//    '.-'   _.--"""'       `-._.-'       '"""--._   `-.`
//     '  .-"'                  :                  `"-.  `
//       '   `.              _.'"'._              .'   `
//             `.       ,.-'"       "'-.,       .'
//               `.                           .'
//          jgs    `-._                   _.-'
//                     `"'--...___...--'"`
//



