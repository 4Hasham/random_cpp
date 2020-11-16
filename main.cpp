#include "graphics.h"

void formEllipse(int, int, int, int);

int main(int argc, char* argv[]) {
    int gd = DETECT, gm;
    bool flag = true;

    initgraph(&gd, &gm, NULL);
    int x = 180, y = 0;

    while(flag) {
        cleardevice();
        formEllipse(x, y, 50, 50);
        usleep(10000);
        x++;
        y++;
    }

    getch();
    closegraph();
    return 0;
}

void formEllipse(int x1, int y1, int x2, int y2) {
    ellipse(200, 100, x1, y1, x2, y2);
}

    // line(50, 100, 450, 400);
    // putpixel(200, 200, RED);
    // putpixel(200, 201, WHITE);
    // putpixel(200, 202, BLUE);
    // circle(150, 100, 100);
