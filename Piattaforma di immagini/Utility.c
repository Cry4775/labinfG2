#define _CRT_SECURE_NO_WARNINGS
#include "Utility.h"


void SvuotaInput()
{
    while (getchar() != '\n');
}

void AssegnaStringa(char** destinazione, char buffer[])
{
    buffer[0] = toupper(buffer[0]);
    *destinazione = (char*)malloc(strlen(buffer) + 1);
    strcpy(*destinazione, buffer);
}

unsigned short int DataCorretta(unsigned short int giorno, unsigned short int mese, unsigned short int anno)
{
    if (anno >= 1900 && anno <= 2021)
    {
        if (mese >= 1 && mese <= 12)
        {
            if (mese == (1 || 3 || 5 || 7 || 8 || 10 || 12))
            {
                // Se è corretto ritorna true
                if (giorno >= 1 && giorno <= 31)
                    return true;
                // Altrimenti ritorna false
                else
                    return false;
            }
            else if (mese == 2)
            {
                if (giorno >= 1 && giorno <= 28)
                    return true;
                else
                    return false;
            }
            else if (mese == 2 && (anno % 4 == 0))
            {
                if (giorno >= 1 && giorno <= 29)
                    return true;
                else
                    return false;
            }
            else
            {
                if (giorno >= 1 && giorno <= 30)
                    return true;
                else
                    return false;
            }
        }
        else
            return false;
    }
    else
        return false;
}

void ConversioneMinuscolo(char buffer[])
{
    for (size_t i = 0; i < strlen(buffer); i++)
    {
        buffer[i] = tolower(buffer[i]);
    }
}

unsigned short int ContieneSimboli(char buffer[])
{
    size_t i = 0;
    while (i < strlen(buffer))
    {
        if (buffer[i] >= 'a' && buffer[i] <= 'z')
        {
            i++;
        }
        else
        {
            printf("Errore! I simboli e i numeri non sono ammessi!\n");
            return true;
        }
    }
    return false;
}

