
#include "TXLib.h"



int VEDRotate (double alx, double aly, double alz);
int VEDTranslate (double x, double y, double z);
int VEDCnVertex (double x, double y, double z, double l, double alx, double aly, double alz);
int VEDCube (/*, double extrax , double extray , double extraZ*/);
int VEDCentrEdge (double x, double y, double z, double WX, double WY, double WZ, double alx, double alz);
int VEDCentrVertex (double x, double y, double z, double alx, double alz, double hl);
int VEDNewCube   (double x, double y, double Z, double WX, double WY, double WZ, double alx, double alz);
int VEDVertex (double x0, double y0, double Z0, double X1, double Y1, double Z1);
int VEDScale (double wx, double wy, double wz);
void multimat (double A[][100], POINT sa; double B[][100]; POINT sb; double C[][100]; POINT sc);



double cord [1][3] = {};

POINT scord = {1, 3};

double alx [3][3] = {};

double aly [3][3] = {};

double alz [3][3] = {};

POINT sal = {3, 3};

double s   [3][3] = {};

POINT ss  = {3, 3};

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




int VEDScale (double wx, double wy, double wz)
    {
    s[0, 0] += wx/100;
    s[1, 1] += wy/100;
    s[2, 2] += wz/100;
    }









int VEDRotate (double alx, double aly, double alz)
    {
    ALX += alx;
    ALY += aly;
    ALZ += alz;
    }


int VEDTranslate (double x, double y, double z)
    {
    X += x;
    Y += y;
    Z += z;
    }




int VEDVertex (double X0, double Y0, double Z0, double X1, double Y1, double Z1)
    {
    //x0 += cos(45) * 0.6 * (Z1 - Z0);
    //y0 += cos(45) * 0.6 * (Z1 - Z0);
    //signal (8, SIG_IGN);





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



    //assert 0.6 * (Z0 != 0&&Z1 != 0);

    if (fabs (Z + z0) < 0.021) z0 += 0.01;
    if (fabs (Z + z1) < 0.021) z1 += 0.01;




    txLine ((X + x0) / 0.6 * (Z + z0), (Y + y0) / 0.6 * (Z + z0), (X + x1) / 0.6 * (Z + z1), (Y + y1) / 0.6 * (Z + z1));
    if (X > 800) return X;
    if (X < 0)   return X;
    if (Y > 600) return Y;
    if (Y < 0)   return Y;
    if (0.6 * Z < 0.001) Z = 0.001;
    }




int VEDCube (/*, double extrax, double extray , double extraZ */)
    {
    printf ("\nalx %f      aly %f        alZ %f\n ", ALX, ALY, ALZ);



                                       //|                     |
    VEDVertex ( -WX,  -WY,  -WZ,    -WX,  -WY,  +WZ);

    VEDVertex ( -WX,  -WY,  +WZ,    +WX,  -WY,  +WZ);

    VEDVertex ( +WX,  -WY,  +WZ,    +WX,  -WY,  -WZ);
    txSetColor (TX_GREEN);
    VEDVertex ( +WX,  -WY,  -WZ,    -WX,  -WY,  -WZ);
    txSetColor (TX_WHITE);
    //       /----------/
    //      /          /
    //     /----------/

    VEDVertex ( -WX,  -WY,  -WZ,    -WX,  +WY,  -WZ);
    VEDVertex ( -WX,  +WY,  -WZ,    -WX,  +WY,  +WZ);
    VEDVertex ( -WX,  +WY,  +WZ,    -WX,  -WY,  +WZ);


    //       /----------/
    //      /|         /
    //     /-+--------/
    //     | |
    //     | /
    //     |/
    //     /

    VEDVertex ( -WX,  +WY,  -WZ,    +WX,  +WY,  -WZ);
    VEDVertex ( +WX,  +WY,  -WZ,    +WX,  +WY,  +WZ);
    VEDVertex ( +WX,  +WY,  +WZ,    -WX,  +WY,  +WZ);

    //       /----------/
    //      /|         /
    //     /-+--------/
    //     | |
    //     | /---------/
    //     |/         /
    //     /---------/



    VEDVertex ( +WX,  +WY,  -WZ,    +WX,  -WY,  -WZ);
    VEDVertex ( +WX,  +WY,  +WZ,    +WX,  -WY,  +WZ);

    //       /----------/
    //      /|         /|
    //     /----------/ |
    //     | |        | |
    //     | /--------+-/
    //     |/         |/
    //     /----------/

    }









void multimat (double A[][4], POINT sa, double B[][4], POINT sb, double C[][4], POINT sc)
    {
    double help [10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i < sa.x; i++)
        {
        for (int j = 0; j < sa.y; j++)
            {
            if (i < sc.x && j < sc.y)
                {
                if (sc.x <= sc.y)
                    {
                    for (int ni = 0; ni < sc.x; ni++)
                        {
                        help [0] += (A[ni][j]) * (B[i][ni]);
                        }
                    }
                else
                    {
                    for (int ni = 0; ni < sc.y; ni++)
                        {
                        help [0] += (A[ni][j]) * (B[i][ni]);
                        }
                     }
                C[i][j] = help[0];
                help[0] = 0;
                }
            }
        }
    }
