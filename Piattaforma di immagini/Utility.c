#define _CRT_SECURE_NO_WARNINGS
#include "Utility.h"


void SvuotaInput()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        continue;
}

void AssegnaStringa(char destinazione[], char buffer[], bool primaMaiuscola)
{
    if (primaMaiuscola)
        buffer[0] = toupper(buffer[0]);

    strcpy(destinazione, buffer);
}

bool DataCorretta(unsigned short int giorno, unsigned short int mese, unsigned short int anno)
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

bool ContieneSimboli(char buffer[], bool numeriAmmessi)
{
    if (!numeriAmmessi)
    {
        size_t i = 0;
        while (i < strlen(buffer))
        {
            if ((buffer[i] >= 'a' && buffer[i] <= 'z') || (buffer[i] >= 'A' && buffer[i] <= 'Z') || buffer[i] == ' ')
            {
                i++;
            }
            else if (buffer[i] == '\n')
                buffer[i] = '\0';
            else
            {
                StampaErrore("Errore! I simboli e i numeri non sono ammessi!");
                return true;
            }
        }
        return false;
    }
    else
    {
        size_t i = 0;
        while (i < strlen(buffer))
        {
            if ((buffer[i] >= 'a' && buffer[i] <= 'z') || (buffer[i] >= 'A' && buffer[i] <= 'Z') || (buffer[i] >= '0' && buffer[i] <= '9') || buffer[i] == ' ')
            {
                i++;
            }
            else if (buffer[i] == '\n')
                buffer[i] = '\0';
            else
            {
                StampaErrore("Errore! I simboli non sono ammessi!");
                return true;
            }
        }
        return false;
    }
}

int RNG(int MIN, int MAX)
{
    return MIN + (rand() / (RAND_MAX / (MAX - MIN)));
}

FILE* ApriFile(const char* percorsoFile)
{
    FILE* file = fopen(percorsoFile, "rb+");
    if (file == NULL)
    {
        file = fopen(percorsoFile, "wb+");
        fclose(file);
        file = fopen(percorsoFile, "rb+");
    }

    return file;
}

const char* CreaIstogramma(unsigned int percentualeOccorrenza)
{
    // Dichiaro il buffer static altrimenti a fine esecuzione, perdo la variabile e viene restituita corrotta
    static char buffer[10] = { 0 };

    // Lo svuoto ogni volta
    for (size_t i = 0; i < 10; i++)
    {
        buffer[i] = '\0';
    }

    // Gli assegno le barrette
    for (size_t i = 0; i < percentualeOccorrenza; i++)
    {
        buffer[i] = '|';
    }
    return buffer;
}

void red()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
}

void green()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
}

void blue()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
}

void reset()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void StampaErrore(const char* testo)
{
    red();
    printf("\n%s\n\n", testo);
    reset();
    system("pause");
}