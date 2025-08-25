#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <float.h>
#include "Tests.h"

int TestOne(struct Tests * CheckTest)
{
    int nroots = SolveSquare(&(CheckTest->Parameters));
    bool nroots_success = (nroots == CheckTest->ans_roots); // Проверяет кол-во корней
    bool x1_success = IsZero(CheckTest->Parameters.x1 - CheckTest->ans_x1) || IsZero(CheckTest->Parameters.x1 - CheckTest->ans_x2);
    // Проверяет корень x1
    bool x2_success = IsZero(CheckTest->Parameters.x2 - CheckTest->ans_x1) || IsZero(CheckTest->Parameters.x2 - CheckTest->ans_x2);
    // Проверяет корень x2
    bool roots_success = x1_success + x2_success >= nroots; // Проверяет правильность корней (корни, которые не тиею значения равны NAN)

    if (nroots_success && roots_success) // Все в порядке
        return 0;
    
    printf("TestError (%.1lf %.1lf %.1lf): ", CheckTest->Parameters.a, CheckTest->Parameters.a, CheckTest->Parameters.a);
    printf("nRoots = %d x1 = %.3lf x2 = %.3lf, ", nroots, CheckTest->Parameters.x1, CheckTest->Parameters.x2);
    printf("expected: nRoots = %d x1 = %.3lf x2 = %.3lf\n", CheckTest->ans_roots, CheckTest->ans_x1, CheckTest->ans_x2);
    return 1;
}

void RunTest(void)
{
    int errors = 0;

    FILE * fp = fopen("Tests.txt", "r"); // Открываем файл с тестами
 
    if (fp == NULL)
    {
        printf("File opening error \"Test.txt\"");
        exit(EXIT_FILE_NULL);
    }

    while (true)
    {
        struct Tests StructTest = {};
        int correct_input = 0;

        correct_input = fscanf(fp, "%lf %lf %lf %d %lf %lf", &StructTest.Parameters.a, &StructTest.Parameters.b, &StructTest.Parameters.c, &StructTest.ans_roots, &StructTest.ans_x1, &StructTest.ans_x2);
        
        if (correct_input != 6 && correct_input != EOF)
        {
            printf("Incorrect test entry!!!\n");
            exit(EXIT_INCORRECT_TEST);
        }
        else if (correct_input == EOF)
        {
            break;
        }

        errors += TestOne(&StructTest);
    }

    fclose(fp);

    if (errors)
        printf("\nAs a result of the check, %d errors were detected.\n\n", errors);
    else
        printf("\nNo errors detected\n\n");

    return;
}

bool IsZero(double check)
{
    return fabs(check) < FRACCURACY;
}

Roots SolveSquare(struct ParametersOfSquare * parameters_ptr)
{
    assert(!(parameters_ptr == NULL)); // Проверка на наличие указателя
    assert(fabs(parameters_ptr->a) < DBL_MAX);
    assert(fabs(parameters_ptr->b) < DBL_MAX);
    assert(fabs(parameters_ptr->c) < DBL_MAX);
    assert(fabs(parameters_ptr->b * parameters_ptr->b - 4 * parameters_ptr->a * parameters_ptr->c) < DBL_MAX);

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
        parameters_ptr->x1 = (-parameters_ptr->b - sqrt(D)) / (2 * parameters_ptr->a);
        parameters_ptr->x2 = (-parameters_ptr->b + sqrt(D)) / (2 * parameters_ptr->a);
        return SS_TWO_ROOTS;
    }
}