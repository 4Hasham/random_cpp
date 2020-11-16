#include <graphics.h>

void Bresenham(int, int, int, int);
void render(int, int);

int main() {

    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    
    Bresenham(300, 300, 30, 30);

    getch();
    closegraph();

    return 0;
}

void Bresenham(int x1, int y1, int x2, int y2) {
    int d;
    int dx = x2 - x1;
    int dy = y2 - y1;
    d = 2*dy - dx;
    while(x1 != x2) {
        render(x1, y1);
        x1++;
        if(d < 0) {
            d = d + 2*dy;
        }
        else {
            y1 = y1 + 1;
            d = d + 2*dy - 2*dx;
        }
    }
}

void render(int x, int y) {
    putpixel(x, y, WHITE);
}