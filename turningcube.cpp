
#include "TXLib.h"

int main()
    {
    txCreateWindow (800, 600);

    double x = 400;
    double y = 300;

    double wx = 50;
    double wy = 50;

    txLine (x - wx, y - wy, x - wx, y + wy);
    txLine (x - wx, y - wy, x + wx, y - wy);
    txLine (x + wx, y - wy, x + wx, y + wy);
    txLine (x + wx, y + wy, x - wx, y + wy);

    getch ();

    //double alx = 15;
    //double aly = 0;
    txSetFillColor (TX_BLACK);
    txClear();

    //double fa = sqrt (wx * wx + wy * wy);

    //printf ("fa = %f\n", fa);
    //double alox = asin (wx/fa);
    //printf ("alox = %f", alox);
    //double aloy = asin (wy/fa);
    //double biasx = (cos (alox) * wx - cos (alox + alx) * wx);
    double al = 15;


    //biasy = (cos (aloy) * wy - cos (alox + aly) * wy);
    //txLine (x - sin (alox - alx) * fa, y - sin (aloy - aly) * fa, x - sin (alox - alx) * fa, y + sin (aloy - aly) * fa);
    //txLine (x - sin (alox - alx) * fa, y - sin (aloy - aly) * fa, x + sin (alox - alx) * fa, y - sin (aloy - aly) * fa);
    //txLine (x + sin (alox - alx) * fa, y - sin (aloy - aly) * fa, x + sin (alox - alx) * fa, y + sin (aloy - aly) * fa);
    //txLine (x + sin (alox - alx) * fa, y + sin (aloy - aly) * fa, x - sin (alox - alx) * fa, y + sin (aloy - aly) * fa);

    double cosalwx = cos (al) * wx;
    double sinalwy = sin (al) * wy;
    double sinalwx = sin (al) * wx;
    double cosalwy = cos (al) * wy;



    //txLine (x - wx, y - wy, x - wx, y + wy);
    //txLine (x - wx, y - wy, x + wx, y - wy);
    //txLine (x + wx, y - wy, x + wx, y + wy);
    //txLine (x + wx, y + wy, x - wx, y + wy);

    txLine (x + cosalwx - sinalwy, y + sinalwx + cosalwy, x + cosalwx + sinalwy, y + sinalwx - cosalwy);
    txLine (x - cosalwy - sinalwx, y - sinalwy + cosalwx, x - cosalwy + sinalwx, y - sinalwy - cosalwx);
    txLine (x + cosalwx - sinalwy, y + sinalwx + cosalwy, x - cosalwy - sinalwx, y - sinalwy + cosalwx);
    txLine (x + cosalwx + sinalwy, y + sinalwx - cosalwy, x - cosalwy + sinalwx, y - sinalwy - cosalwx);






    return 0;
    }
