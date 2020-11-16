#include <graphics.h>

void drawcircle(int x, int y, int xc, int yc);

int main() {

    int gd = DETECT,gm;
    int r = 70, xc = 100, yc = 100, pk, x, y;
    initgraph(&gd, &gm, NULL);
    int d = (5/4) - r;
    x = 0, y = r;
    drawcircle(x, y, xc, yc);

    while(x < y) {
        if(d < 0) {
            d = d + 2*x + 3;
        }
        else {
            d = d + 2*(x - y) + 5;
        }
        x++;
        drawcircle(x, y, xc, yc);
    }
    getch();
    closegraph();
    return 0;
}

void drawcircle(int x, int y, int xc, int yc) {
    putpixel(x + xc, y + yc, WHITE);
    putpixel(-x + xc, y + yc, WHITE);
    putpixel(x+xc, -y+yc, WHITE);
    putpixel(-x+xc, -y+yc, WHITE);
    putpixel(y+xc, x+yc, WHITE);
    putpixel(y+xc, -x+yc, WHITE);
    putpixel(-y+xc, x+yc, WHITE);
    putpixel(-y+xc, -x+yc, WHITE);
}