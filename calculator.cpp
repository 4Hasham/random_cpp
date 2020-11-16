#include <iostream>

using namespace std;

void add(int, int);
void sub(int, int);
void divide(int, int);
void mul(int, int);
void ave(int, int);

int main() {

    int a;
    int b;

    cout << "Enter first number: ";
    cin >> a;
    cout << "Enter second number: ";
    cin >> b;

    add(a, b);
    cout << endl;
    sub(a, b);
    cout << endl;
    divide(a, b);
    cout << endl;
    mul(a, b);
    cout << endl;
    ave(a, b);
    cout << endl;

    return 0;
}

void add(int a, int b) {
    cout << "Addition: " << a + b;
}

void sub(int a, int b) {
    cout << "Subtraction: " << a - b;
}

void divide(int a, int b) {
    cout << "Division: " << a / b;
}

void mul(int a, int b) {
    cout << "Multiplication: " << a * b;
}

void ave(int a, int b) {
    cout << "Average: " << ((a + b) / 2);
}

void square(int a) {
    cout << "Sqaure: " << a * a;
}