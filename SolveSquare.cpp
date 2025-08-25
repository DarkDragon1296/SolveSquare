/* SolveSquare.c - Программа по решению квадратного уравнения */
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <float.h>
#include "Tests.h"

void GetParameters(struct ParametersOfSquare * parameters_ptr);
void ShowResult(Roots nroots, struct ParametersOfSquare * const parameters); // Выводит информацию о решении уравнения

int main(void)
{
    struct ParametersOfSquare parameters = {}; // Объявление структуры параметров
    enum Roots nroots = SS_NO_ROOTS; // Кол-во корней

    RunTest(); // Тестировка программы

    printf("This program outputs the roots of a quadratic equation\n");
    printf("Enter the parameters of the quadratic equation: ");

    GetParameters(&parameters);
    nroots = SolveSquare(&parameters);
    ShowResult(nroots, &parameters);

    return 0;
}

void GetParameters(struct ParametersOfSquare * parameters_ptr)
{
    assert(isfinite(parameters_ptr));

    parameters_ptr->x1 = NAN;
    parameters_ptr->x2 = NAN;

    do {
        char ch = 0;
        int amount_of_parameters = scanf("%lf %lf %lf", &(parameters_ptr->a), &(parameters_ptr->b), &(parameters_ptr->c));

        if (amount_of_parameters == 3) // Когда ввод произведен корректно, выполнение функции прекращается
            return;

        printf("The parameters were entered incorrectly! They must be written as 3 real numbers.\nEnter it again!\n");

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF); // Очистка ввода 
    } while (true);
}

void ShowResult(Roots nroots, struct ParametersOfSquare * const parameters)
{
    switch (nroots) // Вывод результатов
    {
    case SS_INF_ROOTS:
        printf("There are infinitely many roots\n");
        break;
    case SS_NO_ROOTS:
        printf("There are no roots\n");
        break;
    case SS_ONE_ROOT:
        printf("The only root x1 = %.2lf\n", parameters->x1);
        break;
    case SS_TWO_ROOTS:
        printf("The roots are: x1 = %.2lf, x2 = %.2lf\n", parameters->x1, parameters->x2);
        break;
    }

    return;
}