#ifndef TEST_H
#define TEST_H

const double FRACCURACY = 0.001;

enum Roots 
{
    SS_INF_ROOTS = -1,
    SS_NO_ROOTS,
    SS_ONE_ROOT,
    SS_TWO_ROOTS
};
struct ParametersOfSquare // Структура с параметрами для решения квадратного уравнения
{
    double a;
    double b;
    double c;
    double x1;
    double x2;
};

struct Tests
{
    struct ParametersOfSquare Parameters;
    enum Roots ans_roots;
    double ans_x1;
    double ans_x2;
};

enum Errors
{
    EXIT_FILE_NULL = 2,
    EXIT_INCORRECT_TEST
};

void RunTest(void); //Производит тест программы с выводом справки о выполнении

int TestOne(struct Tests * CheckTest); // Производит тест одного уравнения по его параметрам

bool IsZero(double check); // Проверяет, находится ли значение переменной в пределах погрешности от нуля

Roots SolveSquare(struct ParametersOfSquare * parameters_ptr); /* Возвращает кол-во корней
квадратного уравнения. Передает в указатели &x1 и &x2 значения корней квадратного уравнения */

#endif