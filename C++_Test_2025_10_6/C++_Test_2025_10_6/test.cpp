#define _CRT_SECURE_NO_WARNINGS 1
#include "Data.h"

int main()
{
    char a[9];
    char b[9];
    int y1, m1, d1, y2, m2, d2;
    cin >> a >> b;
    sscanf(a, "%4d%2d%2d", &y1, &m1, &d1);
    sscanf(b, "%4d%2d%2d", &y2, &m2, &d2);
    Date a1{ y1,m1,d1 };
    Date a2{ y2,m2,d2 };
    cout << a1.operator-(a2);
}