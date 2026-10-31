#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES 
#include <locale.h>
#include <stdio.h>
#include <math.h>

double Y(double x);
double V(double x);
void print(int choice, double start, double end, double step);

int main()
{
    setlocale(LC_ALL, "RUS");

    // подзадача 1, вариант 18

    int choice;
    double start, end, step;

    do
    {
        printf("\n\n\n1. вычислить функцию Y(x)\n");
        printf("2. вычислить функцию V(x)\n");
        printf("0. выход\n");
        printf("выберите действие: ");
        scanf("%d", &choice);

        if (choice == 0)
        {
            break;
        }

        if (choice != 1 && choice != 2) 
        {
            printf("неверный выбор.\n");
            continue;
        }

        printf("введите начало интервала: ");
        scanf("%lf", &start);
        printf("введите конец интервала: ");
        scanf("%lf", &end);
        printf("введите шаг (через запятую): ");
        scanf("%lf", &step);

        if (step <= 0)
        {
            printf("шаг должен быть больше нуля.\n");
            continue;
        }

        if (start > end) 
        {
            printf("начало интервала не может быть больше конца.\n");
            continue;
        }

        print(choice, start, end, step);

    } 
    
    while (choice != 0);

    return 0;
}

double Y(double x)
{
    double den = tan(exp(cos(sqrt(x))));

    if (den == 0.0) 
    {
        return 0.0;
    }

    double numer = sin(x * x + 1.0 / x + cbrt(x));

    return (numer / den) * 0.000001;
}

double V(double x)
{
    if (x < 0)
    {
        return (1.0 + 2.0 * x) / (1.0 + x * x);
    }

    else if (x >= 0 && x < 1)
    {
        double sin_sq = sin(x) * sin(x);
        return sin_sq * sqrt(1.0 + x);
    }

    else
    {
        double sin_sq = sin(x) * sin(x);
        return sin_sq * exp(0.2 * x);
    }
}

void print(int choice, double start, double end, double step)
{
    double x, y;


    printf("\n-------------------------------------------------\n");
    if (choice == 1)
    {
        printf("|       x       |            Y(x)          |\n");
    }

    else
    {
        printf("|       x       |            V(x)          |\n");
    }

    printf("-------------------------------------------------\n");

    for (x = start; x <= end + 0.000001; x += step)
    {
        if (choice == 1 && x <= 0)
        {
            printf("| %13.4lf |    X                         |\n", x);
            continue;
        }

        if (choice == 1)
        {
            y = Y(x);
        }

        else
        {
            y = V(x);
        }

        printf("| %13.4lf | %23.9lf |\n", x, y);
    }


    for (x = start; x <= end + 0.000001; x += step)
    {
        if (choice == 1 && x <= 0)
        {
            continue;
        }

        if (choice == 1)
        {
            y = Y(x);
        }

        else
        {
            y = V(x);
        }

        printf("%6.2lf | ", x);

        if (choice == 1)
        {
            int stars = fabs(y) * 10000000;

            if (stars > 60)
            {
                stars = 60;
            }

            for (int k = 0; k < stars; k++)
            {
                printf("*");
            }
        }

        else
        {
            int stars = fabs(y) * 20;

            if (stars > 60)
            {
                stars = 60;
            }

            for (int k = 0; k < stars; k++)
            {
                printf("*");
            }
        }

        printf("\n");
    }
}