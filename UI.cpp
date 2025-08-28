#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "AllSolveSquare.h"

const int STR_MAX_LEN = 10;

void ChooseMode(MenuMode mode)
{
    switch (mode)
    {
        case TEST:
            RunTest();
            break;
        case NORMAL:
            RunSolveSquare();
            break;
        case TROLL:
            RunTrollMode();
            break;
    }

    return;
}

void Menu(char * str)
{
    printf(COLOR_YELLOW "Select mode ([enter] to break):\n");
    printf(COLOR_WHITE "1) Test\n");
    printf("2) Normal\n");
    printf("3) Troll\n");

    GetString(str, STR_MAX_LEN);

    return;
}

MenuMode StrToMode(char * str)
{
    ToLowerString(str);

    if (!(strcmp("test", str) && strcmp("1", str)))
        return TEST;
    else if (!(strcmp("normal", str) && strcmp("2", str)))
        return NORMAL;
    else if (!(strcmp("troll", str) && strcmp("3", str)))
        return TROLL;

    return NO_MODE;
}