#define _CRT_SECURE_NO_WARNINGS

#include "Menu.h"

int main(void)
{
    srand(time(NULL));

    bool isCreatore = false;
    char nomeUtente[MAX_BUFFER] = { 0 };
    bool accessoEseguito = MenuIniziale(&isCreatore, nomeUtente);

    if (accessoEseguito == true)
    {
        MenuPrincipale(&isCreatore, nomeUtente);
    }

    system("pause"); // Da rimuovere a programma finito
    return 0;
}