#include <iostream>

using namespace std;

void bar(int a,int &b) {
int tmp;
tmp = 5 * a + 1;
a = b - 3;
b = tmp;
cout << a << " " << b << endl;
}
int main(void) {
int x=-3,y=4;
cout << x << " " << y << endl;
bar(x,y);
cout << x << " " << y << endl;
return 0;
}