#ifndef TROLL_MODE_H
#define TROLL_MODE_H

void RunTrollMode(void);

void TrollGetParameters(struct ParametersOfSquare * parameters_ptr); // Принимает параметры от пользователя

void TrollShowResult(Roots nroots, struct ParametersOfSquare * const parameters); // Выводит информацию о решении уравнения

char * CaptchaGenerate(char * captcha); // Генерирует рандомную капчу

void Captcha(void); // Заставляет пользователя вводить капчу

int RandInt(int min, int max); // Возвращает целое число в диапазоне [min, max]

char RandChar(void); // Возвращает рандомную букву латинского алфавита

#endif