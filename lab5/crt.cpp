#include "NTL/ZZ.h"
#include <iostream>

using namespace NTL;
using namespace std;

void calculateCRT(ZZ &a, ZZ &p, const ZZ &b, const ZZ &m)
{
    ZZ A = b;
    ZZ P = m;
    CRT(a, p, A, P);
}

void printInfo(const ZZ &a, const ZZ &p)
{
    cout << "a: " << a << "\tp: " << p << "\t(a+p)=" << (a + p) << endl;
}

void task1_1()
{
    ZZ b1, b2, b3, b4;
    ZZ m1, m2, m3, m4;

    b1 = 11;
    b2 = 22;
    b3 = 33;
    b4 = 44;
    m1 = 170;
    m2 = 151;
    m3 = 117;
    m4 = 149;

    ZZ a, p;
    // 1 ітерація
    a = b1;
    p = m1;

    calculateCRT(a, p, b2, m2);
    cout << "1-ша ітерація ";
    printInfo(a, p);

    // 2 ітерація
    calculateCRT(a, p, b3, m3);
    cout << "2-га ітерація ";
    printInfo(a, p);

    // 3 ітерація
    calculateCRT(a, p, b4, m4);
    cout << "3-тя ітерація ";
    printInfo(a, p);

    ZZ x = a % (m1 * m2 * m3 * m4);
    cout << "Значення x: " << x << endl;
}

void task1_2()
{
    ZZ b1, b2, b3, b4;
    ZZ m1, m2, m3, m4;

    b1 = 111;
    b2 = 222;
    b3 = 333;
    b4 = 444;
    m1 = 170000;
    m2 = 151001;
    m3 = 117003;
    m4 = 1427;

    ZZ a, p;
    // 1 ітерація
    a = b1;
    p = m1;

    calculateCRT(a, p, b2, m2);
    cout << "1-ша ітерація ";
    printInfo(a, p);

    // 2 ітерація
    calculateCRT(a, p, b3, m3);
    cout << "2-га ітерація ";
    printInfo(a, p);

    // 3 ітерація
    calculateCRT(a, p, b4, m4);
    cout << "3-тя ітерація ";
    printInfo(a, p);

    ZZ x = a % (m1 * m2 * m3 * m4);
    cout << "Значення x: " << x << endl;
}

void task1_3()
{
    ZZ b1, b2, b3, b4;
    ZZ m1, m2, m3, m4;

    b1 = 111;
    b2 = 222;
    b3 = 333;
    b4 = 444;
    m1 = conv<ZZ>("1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
    m2 = conv<ZZ>("1510010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000111");
    m3 = conv<ZZ>("1270000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000003");
    m4 = conv<ZZ>("1490000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000027");

    ZZ a, p;
    // 1 ітерація
    a = b1;
    p = m1;
    calculateCRT(a, p, b2, m2);
    cout << "1-ша ітерація ";
    printInfo(a, p);

    // 2 ітерація
    calculateCRT(a, p, b3, m3);
    cout << "2-га ітерація ";
    printInfo(a, p);

    // 3 ітерація
    calculateCRT(a, p, b4, m4);
    cout << "3-тя ітерація ";
    printInfo(a, p);

    ZZ x = a % (m1 * m2 * m3 * m4);
    cout << "Значення x: " << x << endl;
}

int main()
{
    cout << "1.1" << endl;
    task1_1();
    cout << "1.2" << endl;
    task1_2();
    cout << "1.3" << endl;
    task1_3();

    return 0;
}
