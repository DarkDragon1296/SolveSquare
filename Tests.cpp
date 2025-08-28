#include <stdio.h>
#include <stdlib.h>
#include "SolveSquare.h"
#include "Tests.h"
#include "Colors.h"

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
    
    printf(COLOR_RED_BOLD "TestError (%.1lf %.1lf %.1lf): ", CheckTest->Parameters.a, CheckTest->Parameters.a, CheckTest->Parameters.a);
    printf(COLOR_RED_BOLD "nRoots = %d x1 = %.3lf x2 = %.3lf, ", nroots, CheckTest->Parameters.x1, CheckTest->Parameters.x2);
    printf(COLOR_RED_BOLD "expected: nRoots = %d x1 = %.3lf x2 = %.3lf\n", CheckTest->ans_roots, CheckTest->ans_x1, CheckTest->ans_x2);
    return 1;
}

void RunTest(void)
{
    int errors = 0;

    FILE * fp = fopen("Tests.txt", "r"); // Открываем файл с тестами
 
    if (fp == NULL)
    {
        printf(COLOR_RED_BOLD "File opening error \"Test.txt\"");
        exit(EXIT_FILE_NULL);
    }

    while (true)
    {
        struct Tests StructTest = {};
        int correct_input = 0;

        correct_input = fscanf(fp, "%lf %lf %lf %d %lf %lf", &StructTest.Parameters.a, &StructTest.Parameters.b, &StructTest.Parameters.c, &StructTest.ans_roots, &StructTest.ans_x1, &StructTest.ans_x2);
        // Ввод значений в структуру
        if (correct_input != 6 && correct_input != EOF)
        {
            printf(COLOR_RED_BOLD "Incorrect test entry!!!\n");
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
        printf(COLOR_RED_BOLD"\nAs a result of the check, %d errors were detected.\n\n", errors);
    else
        printf(COLOR_GREEN_BOLD"\nNo errors detected\n\n");

    return;
}