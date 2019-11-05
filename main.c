#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



#include "Lib/Eden.h"


int main(int argc, char const *argv[]) {
    //Code here...
    
    char *basedir = ".\\/Prova";
    EDEN eden;    
    LoadEden(basedir, &eden);
    
    EDENIZE(&eden, 1000);
    //End of the program.
    system("pause");
    //getchar();
    return 0;
}