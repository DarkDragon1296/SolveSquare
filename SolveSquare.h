#ifndef SOLVE_SQUARE_H
#define SOLVE_SQUARE_H

enum Roots // Кол-во корней
{
    SS_NO_INFO = -2,
    SS_INF_ROOTS,
    SS_NO_ROOTS,
    SS_ONE_ROOT,
    SS_TWO_ROOTS
};

enum Errors
{
    EXIT_FILE_NULL = 2,
    EXIT_INCORRECT_TEST
};

struct ParametersOfSquare // Структура с параметрами для решения квадратного уравнения
{
    double a;
    double b;
    double c;
    double x1;
    double x2;
};

#define MYASSERT(X) if(!(X)) {printf("Assertion failed: " #X ", file %s, line %d\n", __FILE__, __LINE__); abort(); }

bool IsZero(double check); // Проверяет, находится ли значение переменной в пределах погрешности от нуля

Roots SolveSquare(struct ParametersOfSquare * parameters_ptr); /* Возвращает кол-во корней
квадратного уравнения. Передает в указатели &x1 и &x2 значения корней квадратного уравнения */

void GetParameters(struct ParametersOfSquare * parameters_ptr); // Принимает параметры от пользователя

void ShowResult(Roots nroots, struct ParametersOfSquare * const parameters); // Выводит информацию о решении уравнения

void RunSolveSquare(void); // Решает квадртаное уравнение

char * GetString(char * str, int n);

void ClearInput(void); // Очищает ввод

Roots ConvertRoots(char * str);

void ToLowerString(char * str);

#endif