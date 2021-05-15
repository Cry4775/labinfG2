#include "Utenti.h"

unsigned short int ControllaNomeUtente(FILE* file, char buffer[])
{
    char buf[BUFSIZ];
    char* ptr = NULL;

    while (fgets(buf, sizeof(buf), file)) // Leggo la riga del file su buf
    {
        ptr = buf; // Assegno a ptr la stringa appena copiata dal file (buf)
        while ((ptr = strtok(ptr, ":")) != NULL) // Quando trova un : (quindi user:) dividi la stringa
        {
            if (strcmp(ptr, "user") == 0)
            {
                ptr = strtok(NULL, " \n\0"); // Quando trova uno spazio o un delimitatore \r o \n o \0 dividi la stringa ptr
                if (strcmp(ptr, buffer) == 0) // Compara la stringa contrassegnata da user con la stringa memorizzata nel buffer
                    return true;
            }
            ptr = NULL;
        }
    }
    return false;
}
