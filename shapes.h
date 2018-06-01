//
// Created by danai on 10.05.2018.
//

#ifndef LAB103_PROG_SHAPES_H
#define LAB103_PROG_SHAPES_H
#include "graphics.h"
#include <random>
#include <ctime>


class Point {
protected:
    int x;
    int y;
    int color;

public:
    Point (int _x, int _y, int c) : x(_x), y(_y), color(c) {}
    Point() : x(0), y(0), color(13) {srand(time(NULL));}
    Point(Point& p) = default;
    ~Point() = default;

    virtual void draw() {putpixel (x, y, color);}
    void hide() {putpixel (x, y, 13);}

    void move (int _x, int _y) {x=_x;y=_y;}
    void set (int _x, int _y, int c) {x=_x;y=_y;color=c;}
    Point& operator= (const Point &r) = default;
};

class Line: public Point {
protected:
    int dx;
    int dy;

public:
    Line(int _x, int _y, int _dx, int _dy, int c) : Point(_x, _y, c), dx(_dx), dy(_dy) {}
    Line() : Point(0, 0, 13), dx(0), dy(0) {}
    Line(Line& xx) = default;
    ~Line() = default;

    void draw() {
        setcolor (color);
        line(x, y, x+dx, y+dy);
    }
    void hide() {
        setcolor (13);
        line(x, y, x+dx, y+dy);
    }
    void rotate (double fi){
        int tmp_dx = dx;
        int tmp_dy = dy;
        dx = int(tmp_dx*cos(fi) - tmp_dy*sin(fi));
        dy = int(tmp_dy*cos(fi) + tmp_dx*sin(fi));
    }

    void set (int _x, int _y, int _dx, int _dy, int c) {x=_x;y=_y;color=c;dx=_dx;dy=_dy;}
    Line& operator= (const Line &r) = default;
};

class Circle:public Point {
protected:
    double r;
public:
    Circle (int _x, int _y, double _r, int c) : Point(_x, _y, c), r(_r) {}
    Circle() : Point(0, 0, 13), r(0) {}
    Circle(Circle& xx) = default;
    ~Circle() = default;

    void draw() {
        setcolor(color);
        circle(x, y, r);
    }
    void hide() {
        setcolor(13);
        circle(x, y, r);
    }

    void set (int _x, int _y, int _r, int c) {x=_x;y=_y;color=c;r=_r;};
    Circle& operator= (const Circle &r) = default;
};

class Square:public Line {
public:
    Square (int _x, int _y, int _dx, int _dy, int c) : Line(_x, _y, _dx, _dy, c) {}
    Square() : Line(0, 0, 0, 0, 13) {}
    Square(Square& x) = default;
    ~Square() = default;

    void draw() {
        setcolor(color);
        line(x, y, x+dx, y+dy);
        line (x+dx, y+dy, x, y+dy+dy);
        line (x, y+dy+dy, x-dx, y+dy);
        line (x-dx, y+dy, x, y);
    }
    void hide() {
        setcolor(13);
        line(x, y, x+dx, y+dy);
        line (x, y, x-dx, y+dy);
        line (x+dx, y+dy, x, y+dy+dy);
        line (x-dx, y+dy, x, y+dy+dy);
    }

    void set (int _x, int _y, int _dx, int _dy, int c) {x=_x;y=_y;color=c;dx=_dx;dy=_dy;};
    Square& operator= (const Square &r) = default;
};

class Romb:public virtual Square{
protected:
    double a;
public:
    Romb (int _x, int _y, int _dx, int _dy, double fi, int c): Square(_x, _y, _dx, _dy, c), a(fi) {};
    Romb(): Square(0, 0, 0, 0, 13), a(0) {}
    Romb(Romb& x) = default;
    ~Romb() = default;

    void draw() {
        setcolor(color);

        int x1 = (dx)*cos(a) + (dy)*sin(a) + x;
        int y1 = (dy)*cos(a) - (dx)*sin(a) + y;

        int x2 = x1 + dx;
        int y2 = y1 + dy;

        line(x, y, x+dx, y+dy);
        line(x, y, x1, y1);
        line(x1, y1, x2, y2);
        line(x+dx, y+dy, x2, y2);
    }
    void hide() {
        setcolor(13);

        int x1 = (dx)*cos(a) + (dy)*sin(a) + x;
        int y1 = (dy)*cos(a) - (dx)*sin(a) + y;

        int x2 = x1 + dx;
        int y2 = y1 + dy;

        line(x, y, x+dx, y+dy);
        line(x, y, x1, y1);
        line(x1, y1, x2, y2);
        line(x+dx, y+dy, x2, y2);
    }

    void set (int _x, int _y, int _dx, int _dy, double fi, int c) {x=_x;y=_y;dx=_dx;dy=_dy;color=c;a=fi;};
    Romb& operator= (const Romb &r) = default;
};

class Rect:public virtual Square{
protected:
    double b;
public:
    Rect (int _x, int _y, int _dx, int _dy, double fi, int c) : Square(_x, _y, _dx, _dy, c), b(fi) {}
    Rect() : Square(0, 0, 0, 0, 13), b(0) {}
    Rect(Rect& x) = default;
    ~Rect() = default;

    void draw() {
        setcolor(color);

        double delit = b/sqrt(dy*dy + dx*dx);

        int x1 = (int)(dy*delit*(-1));
        int y1 = (int)(dx*delit);

        x1 = x1 + x;
        y1 = y1 + y;

        int x2 = x1 + dx;
        int y2 = y1 + dy;

        line(x, y, x1, y1);
        line(x1, y1, x2, y2);
        line(x2, y2, x+dx, y+dy);
        line (x+dx, y+dy, x, y);
    }
    void hide() {
        setcolor(13);

        double delit = b/sqrt(dy*dy + dx*dx);

        int x1 = (int)(dy*delit*(-1));
        int y1 = (int)(dx*delit);

        x1 = x1 + x;
        y1 = y1 + y;

        int x2 = x1 + dx;
        int y2 = y1 + dy;

        line(x, y, x1, y1);
        line(x1, y1, x2, y2);
        line(x2, y2, x+dx, y+dy);
        line (x+dx, y+dy, x, y);
    }

    void set (int _x, int _y, int _dx, int _dy, double fi, int c) {x=_x;y=_y;dx=_dx;dy=_dy;color=c;b=fi;};
    Rect& operator = (const Rect &r) = default;
};

class Parall:public Romb, public Rect {
public:
    Parall(int _x, int _y, int _dx, int _dy, double _a, double _b, int c) {x = _x;y = _y;dx = _dx;dy = _dy;a = _a;b = _b;color = c;}
    Parall() : Romb(0, 0, 0, 0, 0, 13),Rect(0, 0, 0, 0, 0, 13) {};
    Parall(Parall& xx) = default;
    ~Parall() = default;

    void show() {std::cout << x << " " << y << " " << dx << " " << dy << " " << a << " " << b << " " << color;}
    void draw() {
        setcolor(color);

        int tmpx = (dx)*cos(a) + (dy)*sin(a) + x;
        int tmpy = (dy)*cos(a) - (dx)*sin(a) + y;

        double otnosh = b*1.0/sqrt((tmpx - x)*(tmpx - x) + (tmpy - y)*(tmpy - y));

        int x1 = int((tmpx - x)*otnosh*(-1));
        int y1 = int((tmpy - y)*otnosh);

        x1 = x1 + x;
        y1 = y1 + y;

        int x2 = x1 + dx;
        int y2 = y1 + dy;

        line(x, y, x1, y1);
        line(x1, y1, x2, y2);
        line(x2, y2, x+dx, y+dy);
        line(x+dx, y+dy, x, y);
    }
    void hide() {
        setcolor(13);

        int tmpx = (dx)*cos(a) + (dy)*sin(a) + x;
        int tmpy = (dy)*cos(a) - (dx)*sin(a) + y;

        double otnosh = b*1.0/sqrt((tmpx - x)*(tmpx - x) + (tmpy - y)*(tmpy - y));

        int x1 = (int)((tmpx - x)*otnosh*(-1));
        int y1 = (int)((tmpy - y)*otnosh);

        x1 = x1 + x;
        y1 = y1 + y;

        int x2 = x1 + dx;
        int y2 = y1 + dy;

        line(x, y, x1, y1);
        line(x1, y1, x2, y2);
        line(x2, y2, x+dx, y+dy);
        line(x+dx, y+dy, x, y);
    }

    void set (int _x, int _y, int _dx, int _dy, double _a, double _b, int c) {x=_x;y=_y;dx=_dx;dy=_dy;color=c;a=_a;b=_b;};
    Parall& operator = (const Parall &r) = default;
};

#endif //LAB103_PROG_SHAPES_H
