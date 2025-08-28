#ifndef UI_H
#define UI_H

enum MenuMode
{
    NO_MODE,
    NORMAL,
    TROLL,
    TEST
};

void ChooseMode(MenuMode mode); // Выбрать режим

void Menu(char * str); // Показывает меню и запрашивает ввод

MenuMode StrToMode(char * str); // Переводит текст в номер режима

#endif