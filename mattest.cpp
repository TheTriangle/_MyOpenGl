
#include "VEDLibh.h"



void genmat (FILE *f, int s, int mi, int ma);
void scanmat (FILE *fr, FILE *fw, double mat [allmsx][allmsy]);

int main()
    {
    txCreateWindow (800, 600);

    FILE     *fr = fopen ("mattester.txt", "r");

    //FILE     *fw = fopen ("mattester.txt", "w");

    FILE *answer = fopen (   "answer.txt", "w");

    //assert (fr != NULL);
    //for (int i = 0; i < 4; i++)
    //genmat (fw, 5, -6, 8);

    //fclose(fw);
    //fclose(fr);

    //FILE     *fr1 = fopen ("mattester.txt", "w");

    //FILE     *fw1 = fopen ("mattester.txt", "w");

    double mat1 [allmsx][allmsy] = {};
    double mat2 [allmsx][allmsy] = {};
    double mat3 [allmsx][allmsy] = {};


    for (int i = 0; i < 4; i+=2)
        {
        scanmat (fr, answer, mat1);
        scanmat (fr, answer, mat2);
        multimat({5, 5}, mat1, {5, 5}, mat2, {5, 5}, mat3);
        printmat({5, 5}, mat3);
        }
    return 0;
    }



void scanmat (FILE *fr, FILE *fw, double mat [allmsx][allmsy])
    {
    int opsn = 0;
    int sx = 0;
    int sy = 0;

    //fscanf (fr, "%d", &opsn)
    //---
    //double mat[allmsx][allmsy] = {};
    int numx = 0;
    fscanf (fr, "%d %d", &sx, &sy);
    printf ("\n%d s %d\n", sx, sy);
    //int firstpart = 0;
    //int secondpart = 0;
    for (int x = 0; x < sx; x++)
        {
        for (int y = 0; y < sy; y++)
            {
            fscanf (fr, "%lf", &numx);
            //numx = firstpart + secondpart / 6
            printf ("%lf ", numx);
            mat[x][y] = numx;
            }
        }

    //printmat ({5, 5}, mat);
    }


void genmat (FILE *f, int s, int mi, int ma)
    {
    fprintf (f, "\n%d %d\n", s, s);
    double help = 0;
    for (int y = 0; y < s; y++)
        {
        for (int x = 0; x < s; x++)
            {
            help = rand()%((ma - mi + 1)*100)/100 + mi;
            fprintf (f, "%f ", help);
            }
        fprintf (f, "\n");
        }
    }
