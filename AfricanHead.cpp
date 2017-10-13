
#include "VEDLibh.h"
#include <vector>

void control (double speed = 1);
void drawVec (MYP Vector[]);
int FillVec (MYP Vector[]);
int main()
    {
    using namespace std;
    txCreateWindow (800, 600);
    MYP PointsVec[2000];
    FillVec (PointsVec);
    txSetFillColor(TX_BLACK);
    while(!GetAsyncKeyState(VK_ESCAPE))
        {
        txClearConsole();
        control(1);
        if (GetAsyncKeyState(VK_LSHIFT)) control (2);
        drawVec (PointsVec);
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
        printf("%s", type);
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
            VEDTriangle (Vector[fnum], Vector[snum], Vector[tnum]);
            printf ("%s %d/%d/%d\n", type, fnum, snum, tnum);
            getch();
            }
        //else printf ("'%s' != 'f'", type);
        }
    }


void control (double speed)
    {
    if (GetAsyncKeyState (VK_RIGHT))  VEDScale (1.3 * speed,   0,     0);
    if (GetAsyncKeyState (VK_LEFT ))  VEDScale (0.7 * speed,   0,     0);
    if (GetAsyncKeyState (VK_UP   ))  VEDScale (  0, 1.3 * speed,     0);
    if (GetAsyncKeyState (VK_DOWN ))  VEDScale (  0, 0.7 * speed,     0);
    if (GetAsyncKeyState (VK_RSHIFT)) VEDScale (  0,   0,   1.1 * speed);
    if (GetAsyncKeyState (VK_RETURN)) VEDScale (  0,   0,   0.9 * speed);



    if (GetAsyncKeyState ('D')) VEDTranslate ( 12 * speed,  0,   0);
    if (GetAsyncKeyState ('A')) VEDTranslate (-12 * speed,  0,   0);
    if (GetAsyncKeyState ('W')) VEDTranslate ( 0, -12 * speed,   0);
    if (GetAsyncKeyState ('S')) VEDTranslate ( 0,  12 * speed,   0);
    if (GetAsyncKeyState ('Q')) VEDTranslate ( 0,  0,   12 * speed);
    if (GetAsyncKeyState ('E')) VEDTranslate ( 0,  0,  -12 * speed);


    if (GetAsyncKeyState ('O'))
        {
        if (GetAsyncKeyState ('Z')) {VEDRotateZ (-1 * speed); }
        if (GetAsyncKeyState ('X')) {VEDRotateX (-1 * speed); }
        if (GetAsyncKeyState ('Y')) {VEDRotateY (-1 * speed); }
        }
    if (GetAsyncKeyState ('P'))
        {
        if (GetAsyncKeyState ('Z')) {VEDRotateZ (1 * speed); }
        if (GetAsyncKeyState ('X')) {VEDRotateX (1 * speed); }
        if (GetAsyncKeyState ('Y')) {VEDRotateY (1 * speed); }
        }
    }


