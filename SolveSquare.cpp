#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>
#include "SolveSquare.h"
#include "Colors.h"

const double FRACCURACY = 0.01;

bool IsZero(double check)
{
    return fabs(check) < FRACCURACY;
}

Roots SolveSquare(struct ParametersOfSquare * parameters_ptr)
{
     MYASSERT(parameters_ptr != NULL); // Проверка на наличие указателя

    parameters_ptr->x1 = NAN; // По умолчанию неопределено
    parameters_ptr->x2 = NAN;

    if (parameters_ptr->a == 0 && parameters_ptr->b == 0 && parameters_ptr->c == 0) // Проверка на бесконечное кол-во корней
        return SS_INF_ROOTS;
    
    if (parameters_ptr->a == 0 && parameters_ptr->b == 0)
        return SS_NO_ROOTS;
        
    if (parameters_ptr->a == 0) // Проверка на линейное уравнение
    {
        parameters_ptr->x1 = -parameters_ptr->c / parameters_ptr->b;
        return SS_ONE_ROOT;
    }

    double D = parameters_ptr->b * parameters_ptr->b - 4 * parameters_ptr->a * parameters_ptr->c;

    if (IsZero(D)) // Проверка на 0 корней
    {
        parameters_ptr->x1 = -parameters_ptr->b / (2 * parameters_ptr->a);
        return SS_ONE_ROOT;
    }
    else if (D < 0)
    {
        return SS_NO_ROOTS;
    }
    else // Проверка на квадратное уравнение с 2 корнями
    {
        double sqrt_D = sqrt(D);
        parameters_ptr->x1 = (-parameters_ptr->b - sqrt_D) / (2 * parameters_ptr->a);
        parameters_ptr->x2 = (-parameters_ptr->b + sqrt_D) / (2 * parameters_ptr->a);
        return SS_TWO_ROOTS;
    }
}

void GetParameters(struct ParametersOfSquare * parameters_ptr)
{
    MYASSERT(parameters_ptr != NULL);

    parameters_ptr->x1 = NAN;
    parameters_ptr->x2 = NAN;
    
    printf(COLOR_YELLOW "Solve Square Mode enabled\n");
    printf(COLOR_WHITE "This program outputs the roots of a quadratic equation\n");
    printf(COLOR_YELLOW "Enter the parameters of the quadratic equation: ");

    do {
        int amount_of_parameters = scanf("%lf %lf %lf", &(parameters_ptr->a), &(parameters_ptr->b), &(parameters_ptr->c));
  
        ClearInput();

        if (amount_of_parameters == 3) // Когда ввод произведен корректно, выполнение функции прекращается
            return;

        printf(COLOR_RED_BOLD "The parameters were entered incorrectly! They must be written as 3 real numbers.\nEnter it again!\n" COLOR_WHITE);

    } while (true);
}

void ShowResult(Roots nroots, struct ParametersOfSquare * const parameters)
{
    switch (nroots) // Вывод результатов
    {
    case SS_INF_ROOTS:
        printf(COLOR_GREEN_BOLD "\nThere are infinitely many roots\n\n");
        break;
    case SS_NO_ROOTS:
        printf(COLOR_GREEN_BOLD "\nThere are no roots\n\n");
        break;
    case SS_ONE_ROOT:
        printf(COLOR_GREEN_BOLD "\nThe only root x1 = %.2lf\n\n", parameters->x1);
        break;
    case SS_TWO_ROOTS:
        printf(COLOR_GREEN_BOLD "\nThe roots are: x1 = %.2lf, x2 = %.2lf\n\n", parameters->x1, parameters->x2);
        break;
    }

    return;
}

void RunSolveSquare(void)
{
    struct ParametersOfSquare parameters = {}; // Объявление структуры параметров
    enum Roots nroots = SS_NO_ROOTS; // Кол-во корней

    GetParameters(&parameters);
    nroots = SolveSquare(&parameters);
    ShowResult(nroots, &parameters);

    return;
}

char * GetString(char * str, int n)
{
    char * ret_val = fgets(str, n, stdin);
    char * find = NULL;

    if (ret_val)
    {
        find = strchr(str, '\n');

        if (find)
            *find = '\0';
        else
            while (getchar() != '\n')
                continue;
    }

    return ret_val;
}

void ClearInput(void)
{
    char ch = 0;

    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF); // Очистка ввода 
}

Roots ConvertRoots(char * str)
{
    MYASSERT(str != NULL);

    ToLowerString(str);

    if (!strcmp(str, "inf"))
        return SS_INF_ROOTS;
    else if (!strcmp(str, "0"))
        return SS_NO_ROOTS;
    else if (!strcmp(str, "1"))
        return SS_ONE_ROOT;
    else if (!strcmp(str, "2"))
        return SS_TWO_ROOTS;

    return SS_NO_INFO;
}

void ToLowerString(char * str)
{
    MYASSERT(str != NULL);

    for (int i = 0; str[i] != '\0' && str[i] != EOF; i++)
    {   
        str[i] = tolower(str[i]);
    }
}