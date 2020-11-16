#include <graphics.h>

int main() {

    int gd = DETECT, gm;

    initgraph(&gd, &gm, NULL);

//    int arr[8] = {100, 50, 50, 150, 150, 150, 100, 50};
//    drawpoly(8, arr);

// L

    int arr[14] = {50, 50, 75, 50, 75, 100, 150, 100, 150, 150, 50, 150, 50, 50};
    drawpoly(7, arr);

    getch();
    closegraph();
    return 0;
}