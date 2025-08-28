#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "SolveSquare.h"
#include "TrollMode.h"
#include "Colors.h"

const int MIN_CAPTCHA_SIZE = 3;
const int MAX_CAPTCHA_SIZE = 10;

void RunTrollMode(void)
{
    struct ParametersOfSquare parameters = {}; // Объявление структуры параметров
    enum Roots nroots = SS_NO_ROOTS; // Кол-во корней

    TrollGetParameters(&parameters);
    nroots = SolveSquare(&parameters);
    TrollShowResult(nroots, &parameters);

    return;
}

void TrollGetParameters(struct ParametersOfSquare * parameters_ptr)
{
    assert(parameters_ptr != NULL);
    
    parameters_ptr->x1 = NAN;
    parameters_ptr->x2 = NAN;
    
    printf(COLOR_YELLOW "Troll Mode enabled\n");
    Captcha();
    printf(COLOR_WHITE "This program outputs the roots of a quadratic equation\n");
    Captcha();
    printf(COLOR_YELLOW "Enter the parameters of the quadratic equation: ");

    do {
        char ch = 0;
        int amount_of_parameters = scanf("%lf %lf %lf", &(parameters_ptr->a), &(parameters_ptr->b), &(parameters_ptr->c));

        ClearInput();

        if (amount_of_parameters == 3) // Когда ввод произведен корректно, выполнение функции прекращается
            return;

        printf(COLOR_RED_BOLD "The parameters were entered incorrectly! They must be written as 3 real numbers.\nEnter it again!\n" COLOR_WHITE);

    } while (true);
}

void TrollShowResult(Roots nroots, struct ParametersOfSquare * const parameters)
{
    bool x1_success = false, x2_success = false;
    int check_calc = system("calc.exe"); // Запускает калькулятор
    MYASSERT(!check_calc);

    printf(COLOR_MAGENTA "Count for yourself!\n");
    Captcha();

    while (true) // Ввод кол-ва корней пользователем
    {
        char roots_input[4] = "";
        enum Roots amount_roots = SS_NO_INFO;

        printf(COLOR_YELLOW "Enter the number of roots :\n"); 
        GetString(roots_input, 4);

        amount_roots = ConvertRoots(roots_input);

        if (amount_roots == nroots) // Прекращает, если пользователь ввел правильное кол-во корней
            break;

        printf(COLOR_RED_BOLD "Incorrect!!! " COLOR_WHITE);
    }

    while (nroots >= SS_ONE_ROOT) // Ввод первого корня
    {
        double user_input = 0;
        int scanf_correct = 0;

        printf(COLOR_YELLOW "Enter the first root :\n"); 
        scanf_correct = scanf("%lf", &user_input);

        if (scanf_correct) // Правильный scanf
        {
            x1_success = IsZero(parameters->x1 - user_input);
            x2_success = IsZero(parameters->x2 - user_input);

            if (x1_success || x2_success)
                break;
        }

        printf(COLOR_RED_BOLD "Incorrect!!! " COLOR_WHITE);
        ClearInput();
    }

    while (nroots == SS_TWO_ROOTS) // Ввод первого корня
    {
        double user_input = 0;
        int scanf_correct = 0;

        printf(COLOR_YELLOW "Enter the second root :\n"); 
        scanf_correct = scanf("%lf", &user_input);

        if (scanf_correct) // Правильный scanf
        {
            x1_success = IsZero(parameters->x1 - user_input) || x1_success;
            x2_success = IsZero(parameters->x2 - user_input) || x2_success;

            if (x1_success && x2_success)
                break;
        }

        printf(COLOR_RED_BOLD "Incorrect!!! " COLOR_WHITE);
        ClearInput();
    }

    printf(COLOR_GREEN_BOLD "\nMy congratulations, you solved the quadratic equation!\n\n");
    ClearInput();
    
    return;
}

int RandInt(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

char RandChar(void)
{
    char rand_char = RandInt(1, 52);

    rand_char += rand_char > 26 ? 70 : 64;

    return rand_char;
}

void Captcha(void)
{
    bool captcha_failed = true;
    char captcha[MAX_CAPTCHA_SIZE + 1] = "";
    char user_input[MAX_CAPTCHA_SIZE + 1] = "";

    srand(time(NULL));

    while (captcha_failed)
    {
        printf(COLOR_YELLOW "Enter captcha %s :\n", CaptchaGenerate(captcha));
        GetString(user_input, MAX_CAPTCHA_SIZE + 1);

        captcha_failed = strcmp(captcha, user_input);
    }

    return;
}

char * CaptchaGenerate(char * captcha)
{
    int captcha_len = RandInt(MIN_CAPTCHA_SIZE, MAX_CAPTCHA_SIZE);

    for (int i = 0; i < captcha_len; i++) // Генерируем капчу
    {
        captcha[i] = RandChar();
    }

    captcha[captcha_len] = '\0';
    
    return captcha;
}