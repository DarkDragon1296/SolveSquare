/* SolveSquare.c - Программа по решению квадратного уравнения */
#include <stdio.h>
#include "AllSolveSquare.h" // TODO: build folder for .o and .exe files

const int STR_MAX_LEN = 10;
 
int main(int argc, char * argv[])
{
    MenuMode mode = NO_MODE;

    if (argc > 1)
    {
        mode = StrToMode(argv[1]);
        ChooseMode(mode);
    }

    while (true)
    {
        char str[STR_MAX_LEN] = "";

        Menu(str);

        if (str[0] == '\0')
            break;

        mode = StrToMode(str);
        ChooseMode(mode);   
    }

    return 0;
}