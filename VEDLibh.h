
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

void VED3dTriangle (MYP first, MYP second, MYP third);
void makeAllDeforms (double cord [ALLMSX][ALLMSY], bool isper);
int VEDTriangle (MYP first, MYP second, MYP third);
int VEDHorTriangle(MYP left, MYP right, MYP third);
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

int VEDTriangle (MYP first, MYP second, MYP third)
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
//--------------------------------------
    if (first.y < second.y)           //
        {                              //
        if (first.y < third.y)        //
            {                         //
            down = first;             //
            if (second.y < third.y)   //
                {                     //
                mid = second;         //
                up = third;           //
                }                     //
            else                      //
                {                     //
                mid = third;          //
                up = second;          //
                }                     //
            }                         //
        else                          //
            {                         //
            down = third;             //
            if (first.y < second.y)   //
                {                     //
                mid = first;          //
                up = second;          //
                }                     //
            else                      //
                {                     //
                mid = second;         //
                up = first;           //
                }                     //
            }                         //
        }                             //
    else if (second.y < third.y)        // sorting
        {                               // points
        down = second;                //
        if (first.y < third.y)        //
            {                         //
            mid = first;              //
            up = third;               //
            }                         //
        else                          //
            {                         //
            mid = third;              //
            up = first;               //
            }                         //
        }                             //
    else                               //
        {                             //
        down = third;                 //
        if (first.y < second.y)       //
            {                         //
            mid = first;              //
            up = second;              //
            }                         //
        else                          //
            {                         //
            mid = second;             //
            up = first;               //
            }                         //
        }                             //
//--------------------------------------

    double allheight = up.y - down.y;
    double allhwidth = up.x - down.x;
    double sectorheight = mid.y - down.y;
    printf ("mid.y == %f, down.y == %f\n", mid.y, down.y);
    printf ("sech == %f\n", sectorheight);

    VEDHorTriangle ({(sectorheight/allheight)*allhwidth + down.x, down.y + sectorheight, 0}, mid, down);
    VEDHorTriangle ({(sectorheight/allheight)*allhwidth + down.x, down.y + sectorheight, 0}, mid, up);
    return 0;
    }


int VEDHorTriangle(MYP left, MYP right, MYP third)
    {
    double allheight = third.y - left.y;
    //printf ("third.y == %f\n left.y == %f", third.y, left.y);
    if (fabs (allheight) < 0.015)
        {
        //getch();
        txLine (left.x, left.y, right.x, right.y);
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
    for (double nowy = left.y; exit; nowy += signum)
        {
        //txSleep(10);
        nowheight = third.y - nowy;
        if (signum > 0 && nowy + signum > third.y) exit = false;
        if (signum < 0 && nowy + signum < third.y) exit = false;
        //printf ("b\n");
        //getch();
        assert (fabs (allheight) >= 0.015);
        txLine (left.x + (nowheight/allheight)*leftwidth, left.y + nowheight, right.x + (nowheight/allheight)*rightwidth, right.y + nowheight);
        }
    return 0;
    }

int VEDVertex (MYP old, MYP NEW, bool isper)
    {
    double cord0 [ALLMSX][ALLMSY] = {{old.x, 0, 0, 0}, {old.y, 0, 0, 0}, {old.z, 0, 0, 0}, {1, 0, 0, 0}};
    double cord1 [ALLMSX][ALLMSY] = {{NEW.x, 0, 0, 0}, {NEW.y, 0, 0, 0}, {NEW.z, 0, 0, 0}, {1, 0, 0, 0}};
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
    //double MyDef [ALLMSX][ALLMSY] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
    //multimat (SAL, ALZ, SDEF, MyDef, SDEF, MyDef);
    //multimat (SAL, ALX, SDEF, MyDef, SDEF, MyDef);
    //multimat (SAL, ALY, SDEF, MyDef, SDEF, MyDef);

    //multimat (SAL, MyDef, SCORD, ncord0, SCORD, ncord0);

    //multimat (SAL, DEFORMATION, SCORD, cord0, SCORD, cord0);
    //copymatrix (SCORD, cord0, cord0);

    //multimat (SAL, ALY, SCORD, cord0, SCORD, cord0);
    //copymatrix (SCORD, cord0, cord0);

    //multimat (SAL, ALX, SCORD, cord0, SCORD, cord0);
    //copymatrix (SCORD, cord0, cord0);

    //multimat (SAL, ALZ, SCORD, cord0, SCORD, cord0);
    //copymatrix (SCORD, cord0, cord0);

    //multimat (SAL, TRAN, SCORD, cord0, SCORD, cord0);
    //if (isper) multimat (STRAN, PERSPECTIVE, SCORD, cord0, SCORD, cord0);

    makeAllDeforms(cord0, isper);
    makeAllDeforms(cord1, isper);

    //multimat (SAL, ALZ, SCORD, cord1, SCORD, cord1);
    //multimat (SAL, ALX, SCORD, cord1, SCORD, cord1);
    //multimat (SAL, ALY, SCORD, cord1, SCORD, cord1);

    //multimat (SAL, DEFORMATION, SCORD, cord1, SCORD, cord1);
    //copymatrix (SCORD, cord1, cord1);

    //multimat (SAL, ALY, SCORD, cord1, SCORD, cord1);
    //copymatrix (SCORD, cord1, cord1);

    //multimat (SAL, ALX, SCORD, cord1, SCORD, cord1);
    //copymatrix (SCORD, cord1, cord1);

    //multimat (SAL, ALZ, SCORD, cord1, SCORD, cord1);
    //copymatrix (SCORD, cord1, cord1);

    //multimat (SAL, TRAN, SCORD, cord1, SCORD, cord1);
    //if (isper) multimat (STRAN, PERSPECTIVE, SCORD, cord1, SCORD, cord1);

    if (fabs(cord0[2][0]) <= 0.0015) cord0[2][0] = 0.0015;
    if (fabs(cord1[2][0]) <= 0.0015) cord1[2][0] = 0.0015;
    txLine (txGetExtentX()/2 + cord0[0][0]/0.0015/cord0[2][0],
            txGetExtentY()/2 + cord0[1][0]/0.0015/cord0[2][0],
            txGetExtentX()/2 + cord1[0][0]/0.0015/cord1[2][0],
            txGetExtentY()/2 + cord1[1][0]/0.0015/cord1[2][0]);

   /* txLine (txGetExtentX()/2 + (cord0[0][0]), // ((0.015*cord0[0][2])),
            txGetExtentY()/2 + (cord0[1][0]), // ((0.015*cord0[0][2])),
            txGetExtentX()/2, // ((0.015*cord1[0][2])),
            txGetExtentY()/2); // ((0.015*cord1[0][2])));  //*/

    return 0;
    }

void VED3dTriangle (MYP first, MYP second, MYP third)
    {
    double cord1 [ALLMSX][ALLMSY] = {{first.x, 0, 0, 0}, {first.y, 0, 0, 0}, {first.z, 0, 0, 0}};
    double cord2 [ALLMSX][ALLMSY] = {{second.x, 0, 0, 0}, {second.y, 0, 0, 0}, {second.z, 0, 0, 0}};
    double cord3 [ALLMSX][ALLMSY] = {{third.x, 0, 0, 0}, {third.y, 0, 0, 0}, {third.z, 0, 0, 0}};

    }

void makeAllDeforms (double cord[ALLMSX][ALLMSY], bool isper)
    {
    multimat (SAL, DEFORMATION, SCORD, cord, SCORD, cord);

    multimat (SAL, ALY, SCORD, cord, SCORD, cord);

    multimat (SAL, ALX, SCORD, cord, SCORD, cord);

    multimat (SAL, ALZ, SCORD, cord, SCORD, cord);

    multimat (SAL, TRAN, SCORD, cord, SCORD, cord);

    if (isper) multimat (STRAN, PERSPECTIVE, SCORD, cord, SCORD, cord);
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
    VEDVertex ({-1, -1, -1}, {-1, -1, +1}, isper);
    VEDVertex ({-1, -1, +1}, {+1, -1, +1}, isper);
    VEDVertex ({+1, -1, +1}, {+1, -1, -1}, isper);
    VEDVertex ({+1, -1, -1}, {-1, -1, -1}, isper);
    //       /----------/
    //      /          /
    //     /----------/
    VEDVertex ({-1, -1, -1}, {-1, +1, -1}, isper);
    VEDVertex ({-1, +1, -1}, {-1, +1, +1}, isper);
    VEDVertex ({-1, +1, +1}, {-1, -1, +1}, isper);


    //       /----------/
    //      /|         /
    //     /-+--------/
    //     | |
    //     | /
    //     |/
    //     /

    VEDVertex ({-1, +1, -1}, {+1, +1, -1}, isper);
    VEDVertex ({+1, +1, -1}, {+1, +1, +1}, isper);
    VEDVertex ({+1, +1, +1}, {-1, +1, +1}, isper);

    //       /----------/
    //      /|         /
    //     /-+--------/
    //     | |
    //     | /---------/
    //     |/         /
    //     /---------/


    VEDVertex ({+1, +1, -1}, {+1, -1, -1}, isper);
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



