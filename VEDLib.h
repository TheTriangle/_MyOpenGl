
#include "TXLib.h"
const int ALLMSX = 4;                                     //s is for "size". if you see another s, please tell me!
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



void deform (double matrix [ALLMSX][ALLMSY]);
void assigm (double matrix1[ALLMSX][ALLMSY], double matrix2[ALLMSX][ALLMSY], ARRSIZ aSSvol);
int printmat (ARRSIZ sm, double m[ALLMSX][ALLMSY]);
int VEDRotateZ (double a);
int VEDjVertex (double x, double y, double z, double x1, double y1, double z1);
int VEDRotateY (double a);                                  //s is for "size". if you see another s, please tell me!
int VEDRotateX (double a);
int VEDTranslate (double x, double y, double z);
int VEDCnVertex (double x, double y, double z, double l, double alx, double aly, double alz);
int VEDCube (/*, double extrax , double extray , double extraZ*/);
int VEDCentrEdge (double x, double y, double z, double wx, double wy, double wz, double alx, double alz);
int VEDCentrVertex (double x, double y, double z, double alx, double alz, double hl);
int VEDNEWCube   (double x, double y, double z, double wx, double wy, double wz, double alx, double alz);
int VEDVertex (MYP old, MYP NEW);
int VEDScale (double wx, double wy, double wz);
void multimati (ARRSIZ sa, double A[ALLMSX][ALLMSY], ARRSIZ sb, double B[ALLMSX][ALLMSY], ARRSIZ sc, double C[ALLMSX][ALLMSY]);
void multimat  (ARRSIZ sa, double A[ALLMSX][ALLMSY], ARRSIZ sb, double B[ALLMSX][ALLMSY], ARRSIZ sc, double C[ALLMSX][ALLMSY]);

double SM [ALLMSX][ALLMSY] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
double TRAN [ALLMSX][ALLMSY] = {{1, 0, 0, 0},
                                {0, 1, 0, 0},
                                {0, 0, 1, 0},
                                {0, 0, 0, 1}};
double ALX [ALLMSX][ALLMSY] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
double ALY [ALLMSX][ALLMSY] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
double ALZ [ALLMSX][ALLMSY] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
//double ALX = 0;
                //s is for "size". if you see another s, please tell me!
//double cord [ALLMSX][ALLMSY] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
//double s [ALLMSX][ALLMSY] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
                //s is for "size". if you see another s, please tell me!
ARRSIZ SCORD = {4, 4};                                              //

double DEFORMATION [ALLMSX][ALLMSY] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

ARRSIZ SDEF = {4, 4};

ARRSIZ STRAN = {4, 4};

            //s is for "size". if you see another s, please tell me!
ARRSIZ SAL = {4, 4};
/*
double s   [ALLMSX][ALLMSY] = {};
*/
ARRSIZ SS  = {4, 4};

/*
double ALX = 0;
double ALY = 0;
double ALZ = 0;

double X = 0;
double Y = 0;
double Z = 1.0001;

double WX = 0;
double WY = 0;
double WZ = 0;
*/




int VEDScale (double wx, double wy, double wz)              //s is for "size". if you see another s, please tell me!
    {
    if (ROUND (wx * 1000) == 0) wx = 1;
    if (ROUND (wy * 1000) == 0) wy = 1;
    if (ROUND (wz * 1000) == 0) wz = 1;
    double s [ALLMSX][ALLMSY] = {{wx, 0, 0, 0}, {0, wy, 0, 0}, {0, 0, wz, 0}, {0, 0, 0, 1}};
    //SM[0][0] *= wx;
    //SM[1][1] *= wy;
    //SM[2][2] *= wz;
    //printmat (, DEFORMATION);
    multimat (SDEF, DEFORMATION, SS, s, SDEF, DEFORMATION);
    //printmat (, DEFORMATION);
    return 1;
    }



int VEDjVertex (double x, double y, double z, double x1, double y1, double z1)
    {
    txLine (x/z, y/z, x1/z1, y1/z1);
    return 1;
    }



          //s is for "size". if you see another s, please tell me!


int VEDRotateX (double a)
    {
    double madealx [ALLMSX][ALLMSY] = {{0,      0,       0, 1},
                                       {0,  cos(a), sin(a), 0},
                                       {0, -sin(a), cos(a), 0},
                                       {1,      0,       0, 0}};


                                       /*{{1,      0,       0, 0},
                                       {0, cos(a), -sin(a), 0},
                                       {0, sin(a),  cos(a), 0},
                                       {0,      0,       0, 1}};*/
    //                              ALX[1][1]+=cos(a); ALX[1][2]-=sin(a);ALX[2][1]+=sin(a); ALX[2][2]+=cos(a);
    multimat (SDEF, DEFORMATION, SAL, madealx, SDEF, DEFORMATION);
    txClearConsole();
    //printmat (SAL, ALX);
    return 1;
    }


int VEDRotateY (double a)
    {
    double madealy [ALLMSX][ALLMSY] = {{cos(a), 0, -sin(a), 0},
                                       {     0, 1,       0, 0},
                                       {sin(a), 0,  cos(a), 0},
                                       {     0, 0,       0, 1}};
    //                       ALY[0][0]+=cos(a);ALY[0][2]-=sin(a);ALY[2][0]-=sin(a);ALY[2][2]+=cos(a);
    multimat (SDEF, DEFORMATION, SAL, madealy, SDEF, DEFORMATION);
    return 1;
    }




int VEDRotateZ (double a)
    {     //s is for "size". if you see another s, please tell me!
    double madealz [ALLMSX][ALLMSY] = {{cos(a), -sin(a), 0, 0},
                                       {sin(a),  cos(a), 0, 0},
                                       {     0,       0, 1, 0},
                                       {     0,       0, 0, 1}};
    //                    ALZ[0][0]+=cos(a);ALZ[0][1]-=sin(a);ALZ[1][0]+=sin(a);ALZ[1][1]+=cos(a);
    multimat (SDEF, DEFORMATION, SAL, madealz, SDEF, DEFORMATION);
    return 1;
    }



int VEDTranslate (double x, double y, double z)
    {      //s is for "size". if you see another s, please tell me!
    //double TRAN [ALLMSX][ALLMSY] = {{1, 0, 0, 0},
    //                                {0, 1, 0, 0},
    //                                {0, 0, 1, 0},
    //                                {x, y, z, 1}};
    TRAN[3][0] += x;
    TRAN[3][1] += y;
    TRAN[3][2] += z;
    //multimat (, DEFORMATION, SCORD, TRAN, , DEFORMATION);

    //printf ("you've changed cords. now they are x = %f, y = %f, z = %f \n", cord[0][0], cord[0][1], cord[0][2]);
    return 1;
    }


         //s is for "size". if you see another s, please tell me!

int VEDVertex (MYP old, MYP NEW)
    {

    //x0 += cos(45) * 0.6 * (Z1 - Z0);
    //y0 += cos(45) * 0.6 * (Z1 - Z0);
    //signal (8, SIG_IGN);                         //IsawADiffBetween, 0} and , 1{
    double cord0 [ALLMSX][ALLMSY] = {{old.x, old.y, old.z, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    double cord1 [ALLMSX][ALLMSY] = {{NEW.x, NEW.y, NEW.z, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    double ncord0 [ALLMSX][ALLMSY] = {};
    double ncord1 [ALLMSX][ALLMSY] = {};

    txClearConsole ();

    //printmat (SCORD, cord0);

    //printmat (SCORD, DEFORMATION);

    multimat (SCORD, cord0, SDEF, DEFORMATION, SCORD, cord0);
    multimat (SCORD, cord0, STRAN, TRAN, SCORD, cord0);

    multimat (SCORD, cord1, SDEF, DEFORMATION, SCORD, cord1);
    multimat (SCORD, cord1, STRAN, TRAN, SCORD, cord1);

    //deform (cord0);
    //deform (cord1);

    //printmat (SCORD, ncord0);



    /*
    double xn0 = X0  * cos (ALZ) -  Y0 * sin (ALZ);
    double yn0 = X0  * sin (ALZ) +  Y0 * cos (ALZ);

    double y0  = yn0 * cos (ALX) - Z0 * sin (ALX);
    double zn0 = yn0 * sin (ALX) + Z0 * cos (ALX);


    double z0 = zn0  * cos (ALY) -  xn0 * sin (ALY);
    double x0 = zn0  * sin (ALY) +  xn0 * cos (ALY);




    //=============================================================================



    double xn1 = X1  * cos (ALZ) -  Y1 * sin (ALZ);
    double yn1 = X1  * sin (ALZ) +  Y1 * cos (ALZ);

    double y1  = yn1 * cos (ALX) - Z1 * sin (ALX);
    double zn1 = yn1 * sin (ALX) + Z1 * cos (ALX);


    double z1 = zn1  * cos (ALY) -  xn1 * sin (ALY);
    double x1 = zn1  * sin (ALY) +  xn1 * cos (ALY);



    //aSSert 0.6 * (Z0 != 0&&Z1 != 0);

    if (fabs (Z + z0) < 0.021) z0 += 0.01;
    if (fabs (Z + z1) < 0.021) z1 += 0.01;
    */

    //txClearConsole();
    //printf ("%f - xold %f - yold %f - xnew %f - ynew\n (without y)", cord[0][0] + ncord0[0][0],
    //                                                                 cord[0][1] + ncord0[0][1],
    //                                                                 cord[0][0] + ncord1[0][0],
    //                                                                 cord[0][1] + ncord1[0][1]);

    //printmat (SCORD, ncord0);
    if (fabs(cord0[0][2]) <= 0.0015) cord0[0][2] = 0.0015;
    if (fabs(cord1[0][2]) <= 0.0015) cord1[0][2] = 0.0015;
    assert (cord0[0][2] != 0);
    assert (cord1[0][2] != 0);

    //printmat (SCORD, cord0);
    //printmat (SCORD, cord1);

    /*
    printf ("\nLines: |%f %f - %f %f|(%f %f %f | %f %f %f)CanYouSeeIt? |screecords| (world|cords)", (cord0[0][0]) / (0.6 * (cord0[0][2]))  + 100,
                                                                                               (cord0[0][1]) / (0.6 * (cord0[0][2]))  + 100,
                                                                                               (cord1[0][0]) / (0.6 * (cord1[0][2]))  + 100,
                                                                                               (cord1[0][1]) / (0.6 * (cord1[0][2]))  + 100,
                                                                                               cord0[0][0], cord0[0][1], cord0[0][2],
                                                                                               cord1[0][0], cord1[0][1], cord1[0][2]);
    //*/
    txLine (txGetExtentX()/2 + (cord0[0][0]) / (0.05 * (cord0[0][2])),
            txGetExtentY()/2 + (cord0[0][1]) / (0.05 * (cord0[0][2])),
            txGetExtentX()/2 + (cord1[0][0]) / (0.05 * (cord1[0][2])),
            txGetExtentY()/2 + (cord1[0][1]) / (0.05 * (cord1[0][2])));
    /*txCircle ((cord0[0][0]) / (0.6 * (cord0[2][0]) + 100),
              (cord0[1][0]) / (0.6 * (cord0[2][0]) + 100),
              5);
    txCircle ((cord1[0][0]) / (0.6 * (cord1[2][0]) + 100),
              (cord1[1][0]) / (0.6 * (cord1[2][0]) + 100),
              5);   */



            /*
    if (cord[0][0] > 800) return cord[0][0];
    if (cord[0][0] < 0)   return cord[0][0];
    if (cord[1][0] > 600) return cord[1][0];
    if (cord[1][0] < 0)   return cord[1][0];
    if (0.6 * cord[2][0] < 0.001) cord[2][0] = 0.001;
            */
    return 0;
    }



void deform (double matrix [ALLMSX][ALLMSY])
    {                                                                                                                                                          // vszhuh and this is krivo!!!
    double help [ALLMSX][ALLMSY] = {};                                                                                                                  //                /\          *    --
    multimat (SCORD, matrix, SCORD,   SM, SCORD,   help);                                                                                               //              \    /    /
    multimat (SCORD,   help, SCORD,  ALX, SCORD, matrix);                                                                                               //               /  \        /   \   /
    multimat (SCORD, matrix, SCORD,  ALY, SCORD,   help);                                                                                               //              /----\      /     \   -
    multimat (SCORD,   help, SCORD,  ALZ, SCORD, matrix);                                                                                                //              |*  *|     /
    multimat (SCORD, matrix, SCORD, TRAN, SCORD,   help);                                                                                               //               ====    /
    assigm (matrix, help, SCORD);                                                                                                                       //                      /
    }



void assigm (double matrix1[ALLMSX][ALLMSY], double matrix2[ALLMSX][ALLMSY], ARRSIZ aSSvol)
    {
    for (int x = 0; x < aSSvol.y; x++)
        {
        for (int y = 0; y < aSSvol.x; y++)
            {
            matrix1[x][y] = matrix2[x][y];
            }
        }
    }


        //s is for "size". if you see another s, please tell me!
int VEDCube (/*, double extrax, double extray , double extraZ */)
    {
    //printf ("\nALX %f      ALY %f        ALZ %f\n ", ALX, ALY, ALZ);



    //|                     |
    /*int vertexes [ALLMSX][ALLMSY][12] =
    {-1, -1, -1} {-1, -1, +1} {+1, -1, +1} {+1, -1, -1} {-1, -1, -1} {-1, +1, -1} {-1, +1, +1} {-1, +1, +1} {-1, +1, -1} {+1, +1, -1} {+1, +1, +1}{+1, +1, -1}{+1, +1, +1}
    {-1, -1, +1} {+1, -1, +1} {+1, -1, -1} {-1, -1, -1} {-1, +1, -1} {-1, +1, +1} {-1, -1, +1} {-1, -1, +1} {+1, +1, -1} {+1, +1, +1} {-1, +1, +1}{+1, -1, -1}{+1, -1, +1}
                                                                    *//*{{{-1, -1, -1}, {-1, -1, +1}},
                                                                     {{-1, -1, +1}, {+1, -1, +1}},
                                                                     {{+1, -1, +1}, {+1, -1, -1}},
                                                                     {{+1, -1, -1}, {-1, -1, -1}}, /
                                                                     {{-1, -1, -1}, {-1, +1, -1}}, /
                                                                     {{-1, +1, -1}, {-1, +1, +1}}, /
                                                                     {{-1, +1, +1}, {-1, -1, +1}}, /
                                                                     {{-1, +1, -1}, {+1, +1, -1}}, /
                                                                     {{+1, +1, -1}, {+1, +1, +1}},/
                                                                     {{+1, +1, +1}, {-1, +1, +1}},/
                                                                     {{+1, +1, -1}, {+1, -1, -1}},
                                                                     {{+1, +1, +1}, {+1, -1, +1}}};    */
    //txClearConsole();
    //double help [ALLMSX][ALLMSY] = {{1, 1, 1}, {-1, -1, -1}};
    //VEDVertex ({1, 1, 1}, {-1, -1, -1});



    VEDVertex ({-1, -1, -1}, {-1, -1, +1});
    VEDVertex ({-1, -1, +1}, {+1, -1, +1});
    VEDVertex ({+1, -1, +1}, {+1, -1, -1});
    VEDVertex ({+1, -1, -1}, {-1, -1, -1});
    //       /----------/
    //      /          /
    //     /----------/
    VEDVertex ({-1, -1, -1}, {-1, +1, -1});
    VEDVertex ({-1, +1, -1}, {-1, +1, +1});
    VEDVertex ({-1, +1, +1}, {-1, -1, +1});                //s is for "size". if you see another s, please tell me!



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
    //      /|         /                                    //s is for "size". if you see another s, please tell me!
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
    //     /----------/                                     //s is for "size". if you see another s, please tell me!

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



                //s is for "size". if you see another s, please tell me!

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
            }     //C2,3 = A2,1 · B1,3 + A2,2 · B2,3 + A2,3 · B3,3 = 0 · 0 + 0 · 0 + 0 · 2 = 0
        }
    }






void multimati (ARRSIZ sa, double A[ALLMSX][ALLMSY], ARRSIZ sb, double B[ALLMSX][ALLMSY], ARRSIZ sc, double C[ALLMSX][ALLMSY])
    {
    double help [10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};       // ;(  // karma--;
    /*if (A[sa.y][sa.x] == NULL || B[sb.y][sb.x] == NULL) txMeSSageBox ("ÀÍÓ-ÊÀ ÂÅÐÍÓË ÂÑ¨ ÊÀÊ ÁÛËÎ! ÝÒÎ ß ÒÅÁÅ ÃÎÂÎÐÞ! \n"
                                                                      "ÒÛ ÊÓÄÀ ÒÀÊÎÉ ÐÀÇÌÅÐ Ó ÌÀÑÑÈÂÀ  À ÈËÈ Â Â ÔÓÍÊÖÈÈ MULTIMAT ÏÎÑÒÀÂÈË!!\n"
                                                                      "È ÍÅ ÑÌÅÉ ÝÒÎ ÒÀÊ ÎÑÒÀÂËßÒÜ!"); */
    //aSSert (sa.x != sb.y);
    help[0] = sa.y;
    help[1] = sa.x;
    help[2] = sb.y;
    help[3] = sb.x;
//    aSSert (A[help[0]][help[1]] == NULL || B[help[2]][help[3]] == NULL);
    for (int i = 0; i < sa.x; i++)
        {
        for (int j = 0; j < sa.y; j++)
            {
            if (i < sc.x && j < sc.y && i < sb.x && j < sb.y)
                {
                if (sc.x <= sc.y)
                    {
                    for (int ni = 0; ni < sc.x; ni++)
                        {
                        if (ni < sb.y)
                            {
                            help [0] += (A[ni][j]) * (B[i][ni]);
                            }
                        }
                    }
                else
                    {
                    for (int ni = 0; ni < sc.y; ni++)
                        {
                        if (ni < sb.y)
                            {
                            help [0] += (A[ni][j]) * (B[i][ni]);
                            }
                        }
                     }
                C[j][i] = help[0];
                help[0] = 0;
                }
            }
        }
    }
