#include <iostream>
#include <graphics.h>

void CircleD(int);
void render(int, int);

int main() {

    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    CircleD(5);

    getch();
    closegraph();

    return 0;
}

void CircleD(int r) {
    int x = 0;
    int y = r;
    int d = 3 - 2*r;
    while(x < y) {
        render(x, y);
        if(d < 0) {
            d = d + 4*x + 6;
        }
        else {
            d = d + 4*(x - y) + 10;
            --y;
        }
        ++x;
    }
    return;
}

void render(int x, int y) {
    std::cout << "x1 = " << x << std::endl << "y1 = " << y << std::endl;
    putpixel(x, y, WHITE);
}