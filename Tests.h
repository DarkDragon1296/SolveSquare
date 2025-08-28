#ifndef TEST_H
#define TEST_H

struct Tests
{
    struct ParametersOfSquare Parameters;
    enum Roots ans_roots;
    double ans_x1;
    double ans_x2;
};

void RunTest(void); //Производит тест программы с выводом справки о выполнении

int TestOne(struct Tests * CheckTest); // Производит тест одного уравнения по его параметрам

#endif