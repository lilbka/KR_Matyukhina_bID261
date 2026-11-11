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

        if (scanf("%d", &choice) != 1) 
        {
            printf("Ошибка ввода. Введите число.\n");

            while (getchar() != '\n');
            continue;
        }

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

        if (scanf("%lf", &start) != 1)
        {
            printf("ошибка ввода.\n");
            while (getchar() != '\n');
            continue;
        }

        printf("введите конец интервала: ");

        if (scanf("%lf", &end) != 1)
        {
            printf("ошибка ввода.\n");
            while (getchar() != '\n');
            continue;
        }

        printf("введите шаг (через запятую): ");
        if (scanf("%lf", &step) != 1) 
        {
            printf("ошибка ввода.\n");
            while (getchar() != '\n');
            continue;
        }

        if (step <= 0 || start > end)
        {
            printf("проверьте шаг и интервал.\n");
            continue;
        }

        double x, y;

        printf("\n-------------------------------------------------\n");
        if (choice == 1)
        {
            printf("|       x       |            Y(x)             |\n");
        }

        else
        {
            printf("|       x       |            V(x)             |\n");
        }

        printf("-------------------------------------------------\n");

        for (x = start; x <= end; x += step)
        {

            if (choice == 1)
            {
                if (x <= 0) 
                {
                    printf("| %13.4lf |    ОШИБКА                |\n", x);
                    continue;
                }

                double arg = exp(cos(sqrt(x)));

                if (fabs(cos(arg)) < 0.000001) // необходимая погрешность
                {
                    printf("| %13.4lf |    ОШИБКА                 |\n", x);
                    continue;
                }

                y = Y(x);
                printf("| %13.4lf | %23.9lf |\n", x, y);
            }

            else
            {

                if (x >= 1 && 0.2 * x > 700.0) // проверка переполнения
                {
                    printf("| %13.4lf |    ОШИБКА                 |\n", x);
                    continue;
                }

                y = V(x);
                printf("| %13.4lf | %23.9lf |\n", x, y);
            }
        }
        printf("-------------------------------------------------\n\n");

        double max_val = 0.0;

        for (x = start; x <= end; x += step)
        {
            if (choice == 1) 
            {
                if (x <= 0 || fabs(cos(exp(cos(sqrt(x))))) < 0.000001)
                {
                    continue;
                }

                y = Y(x);
            }

            else 
            {
                if (x >= 1 && 0.2 * x > 700.0)
                {
                    continue;
                }

                y = V(x);
            }

            if (fabs(y) > max_val)
            {
                max_val = fabs(y);
            }

        }

        if (max_val == 0.0)
        {
            max_val = 1.0;
        }

        int half_width = 25;

        for (x = start; x <= end; x += step)
        {
            printf("%6.2lf | ", x);

            if (choice == 1) 
            {
                if (x <= 0 || fabs(cos(exp(cos(sqrt(x))))) < 0.000001) 
                {
                    printf("ошибка\n");
                    continue;
                }

                y = Y(x);
            }
            else 
            {
                if (x >= 1 && 0.2 * x > 700.0)
                {
                    printf("ошибка\n");
                    continue;
                }

                y = V(x);
            }

            int stars = (int)(fabs(y) / max_val * half_width);
            if (stars > half_width) stars = half_width;

            if (y > 0)
            {
                for (int k = 0; k < half_width; k++) printf(" ");
                printf("|");
                for (int k = 0; k < stars; k++) printf("*");
            }

            else if (y < 0)
            {
                for (int k = 0; k < half_width - stars; k++) printf(" ");
                for (int k = 0; k < stars; k++) printf("*");
                printf("|");
            }

            else
            {
                for (int k = 0; k < half_width; k++) printf(" ");
                printf("|");
            }

            printf("\n");
        }
    } 
    
    while (choice != 0);

    return 0;
}

double Y(double x)
{
    double den = tan(exp(cos(sqrt(x))));
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