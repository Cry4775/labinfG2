#define _CRT_SECURE_NO_WARNINGS

#include "Menu.h"

int main(void)
{
    unsigned short int accessoEseguito = MenuIniziale();

    if (accessoEseguito == true)
    {

    }

    system("pause"); // Da rimuovere a programma finito
    return 0;
}






/* per formattare l'allineamento delle colonne
printf("%15s%15s\n", "ciao", "ciao");
printf("%15s%15s\n", "ciaoooo", "ciao");
*/