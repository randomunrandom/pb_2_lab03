#include "graphics.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <unistd.h>
#include <cmath>
#include "shapes.h"

using namespace std;
const double PI = 3.14159265358;

int main(){

    int gddriver = DETECT, gmode, errorcode;
    initgraph(&gddriver, &gmode, "");

    Point p(10, 10, 13);
    p.draw();
    Circle c(20, 20, 10, 13);
    c.draw();
    Line l(40, 40, 10, 10, 13);
    l.draw();
    Square s(60, 60, 10, 10, 15);
    s.draw();
    Romb r(10, 50, 10, 10, -10, 13);
    r.draw();
    Rect re(50, 10, 10, 10, 10, 13);
    re.draw();
    Parall pa(100, 100, 10, 10, 10, -10, 13);
    pa.draw();

    getch();
    closegraph();

    return 0;
}