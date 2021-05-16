#include "Utenti.h"

unsigned short int ControllaNomeUtente(FILE* file, char buffer[])
{
    char buf[BUFSIZ];
    char* ptr = NULL;

    while (fgets(buf, sizeof(buf), file)) // Leggo ogni riga del file su buf
    {
        ptr = buf; // Assegno a ptr la stringa appena copiata dal file (buf)
        while ((ptr = strtok(ptr, ":")) != NULL) // Quando trova un : (delimitatore) dividi la stringa
        {
            if (strcmp(ptr, "nomeUtente") == 0)
            {
                ptr = strtok(NULL, " \n\0"); // Richiedi il token successivo (ciò che sta dopo user: )
                if (strcmp(ptr, buffer) == 0) // Compara la stringa contrassegnata da user con la stringa memorizzata nel buffer
                    return true;
            }
            ptr = NULL;
        }
    }
    return false;
}

unsigned short int ControllaPassword(FILE* file, char bufferNomeUtente[], char bufferPassword[])
{
    char buf[BUFSIZ];
    char* ptr = NULL;

    while (fgets(buf, sizeof(buf), file)) // Leggo ogni riga del file su buf
    {
        ptr = buf; // Assegno a ptr la stringa appena copiata dal file (buf)
        while ((ptr = strtok(ptr, ":")) != NULL) // Quando trova un : (delimitatore) dividi la stringa
        {
            ptr = strtok(NULL, " \n\0"); // Richiedi il token successivo (ciò che sta dopo password: )
            if (strcmp(ptr, bufferPassword) == 0)
                return true;
            else return false;
            ptr = NULL;
        }
    }
    return false;
}
