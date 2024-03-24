#include <iostream>
#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <NTL/ZZX.h>

using namespace std;
using namespace NTL;

bool MillerRabinTest(const ZZ &n, long k = 20)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;

    ZZ d = n - 1;
    long s = 0;

    while (d % 2 == 0)
    {
        d /= 2;
        s++;
    }

    for (long i = 0; i < k; ++i)
    {
        ZZ a = RandomBnd(n - 3) + 2;
        ZZ x = PowerMod(a, d, n);

        if (x == 1 || x == n - 1)
            continue;

        for (long j = 0; j < s - 1; ++j)
        {
            x = MulMod(x, x, n);
            if (x == n - 1)
                break;
        }

        if (x != n - 1)
            return false;
    }

    return true;
}

// Функція для факторизації числа методом пробних поділів
ZZ trialDivision(const ZZ &n)
{
    for (ZZ i = conv<ZZ>("2"); i <= SqrRoot(n); i++)
    {
        if (n % i == 0)
        {
            return i;
        }
    }
    return conv<ZZ>("0");
}

// Функція для факторизації числа методом Ферма
ZZ fermaFactorization(const ZZ &n)
{
    ZZ x, y, square;
    x = SqrRoot(n) + 1;

    square = x * x - n;
    y = SqrRoot(square);

    while (y * y != square)
    {
        square += 2 * x + 1;
        x++;
        y = SqrRoot(square);
    }

    return x + y;
}

void factorize()
{
    ZZ n = conv<ZZ>("915706771359694969219");

    cout << "Факторизація числа (метод пробних поділів) " << n << ":\n";

    // Перевірка чи є число n простим
    if (MillerRabinTest(n))
    {
        cout << n << " - просте число, немає необхідності факторизувати.\n";
        return;
    }

    // Факторизація числа методом пробних поділів
    ZZ factor1 = trialDivision(n);
    if (factor1 == 0)
    {
        cout << "Факторизація методом пробних поділів не була успішною.\n";
    }
    else
    {
        ZZ otherFactor1 = n / factor1;
        cout << "Результат факторизації: " << n << " = " << factor1 << " * " << otherFactor1 << "\n\n";
    }

    n = conv<ZZ>("663453879574938389141");
    cout << "Факторизація числа (метод ферма) " << n << ":\n";
    ZZ factor2 = fermaFactorization(n);

    if (factor2 == 0)
    {
        cout << "Факторизація методом пробних поділів не була успішною.\n";
    }
    else
    {
        ZZ otherFactor2 = n / factor2;
        cout << "Результат факторизації: " << n << " = " << factor2 << " * " << otherFactor2 << "\n";
    }
}

int main()
{
    factorize();
    getchatr();
    return 0;
}
