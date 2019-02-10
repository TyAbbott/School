#include <stdio.h>
#include "scanner.h"
#include "parsercodgen.h"
#include "pmachine.h"

/*   
	-l : print the list of lexemes/tokens (scanner output) to the screen
    ​-a : print the generated assembly code (parser/codegen output) to the screen
    ​-v : print virtual machine execution trace (virtual machine output) to the screen 
*/

int main(int argc, char *argv[])
{
    int lFlag=0;
    int pFlag=0;
    int tFlag=0;

    int i;
    for (i=0; i< argc; i++)
    {
        if (strcmp(argv[i], "-l") ==0)
            lFlag=1;

        if (strcmp(argv[i], "-a") ==0)
            pFlag=1;

        if (strcmp(argv[i], "-v") ==0)
            tFlag=1;
    }
    scanner(lFlag);
    parsercodgen(pFlag);
    pmachine(tFlag);
}