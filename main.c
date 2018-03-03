/* 
    Mogući rezultati:
    0 - OK
    -1 - Poziv na broj sadrži manje od 2 znaka
    -2 - Sadrži više od 22 znaka
    -3 - Sadrži nedopuštene znakove
    -4 - Sadrži previše "-"
    -5 - Podatak P1 je predugačak
    -6 - Podatak P2 je predugačak
    -7 - Podatak P3 je predugačak
    -8 - Podatak P1 je prekratak
    -9 - Kontrolni broj nije točan
*/

#include <stdio.h>

// Prototip funkcije
int model05(const char *);

int main(void)
{
    const char *model[20] = 
    {
        "789632190-ba-09jd03j000", "92916161065464879561651", "1", "",
        "/()?", "*123", "452--", "1234567a",
        "452", "482--", "-81-32-", "77-----",
        "1457985327895", "12-8951235478991", "99-2-4592631478962", "1-562-789",
        "334445556669-23-3", "22-98-", "284216", "77777777777-98-898"
    };
    for(int i = 0; i < 20; i++)
    {
        printf("%d\n", model05(model[i]));   
    }
    return 0;
}

// Tijelo funkcije
int model05(const char *model)
{
    int size = 0, i = 0, count_dash = 0, P1size = 0, P2size = 0, P3size = 0, sum = 0, control_num = 0;
    char P1[22] = {0}; 
    
    while(model[i] != '\0')
    {
        size++;
        i++;
    }
    // Provjerava dužinu unesenog poziva na broj.
    if(size < 2)        return -1;
    else if(size > 22)  return -2;
    else
    {
        // Provjerava sadrži li poziv dopuštene znakove.
        for(i = 0; i < size; i++)
        {
            if((model[i] > 0 && model[i] < 45) || (model[i] > 45 && model[i] < 48) || (model[i] > 57 && model[i] < 127)) return -3;
            // Koliko "-" ima u pozivu
            else if (model[i] == 45) count_dash++;
        }
        if (count_dash > 2) return -4;
        // Ukoliko ne postoji "-" provjerava duljinu broja P1.
        else if (count_dash == 0)
        {
            P1size = size;
            for(i = 0; i < size; i++) P1[i] = model[i];
            if (P1size > 12) return -5;
        }
        // Ukoliko je samo jedna "-" provjerava duljinu broja P1 i P2.
        else if (count_dash == 1)
        {
            i = 0;
            while(model[i] != 45)
            {
                P1[i] = model[i];
                P1size++;
                i++;
            }
            P2size = size - P1size - 1;
            if(P1size > 12) return -5;
            if(P2size > 12) return -6;
        }
        // Ukoliko su dvije "-" provjerava duljinu broja P1, P2 i P3.
        else if (count_dash == 2)
        {
            i = 0;
            while(model[i] != 45)
            {
                P1[i] = model[i];
                P1size++;
                i++;
            }
            i++;
            while(model[i] != 45)
            {
                P2size++;
                i++;
            }
            P3size = size - (P1size + P2size +2);
            if(P1size > 12) return -5;
            if(P2size > 12) return -6;
            if(P3size > 12) return -7;
        }
        // Ukoliko je P1 prekratak. Mora biti min 2 broja.
        if(P1size < 2) return -8;
        // Provjerava kontrolni broj P1 podatka.
        for(i = 0; i < P1size-1; i++)
        {
            sum += ((P1[i]-48) * (P1size - i));
        }
        control_num = 11 - sum % 11;
        if(control_num == 11) control_num = 1;
        if(control_num == 10) control_num = 0;
        if(control_num != P1[(P1size-1)]-48) return -9;
        return 0;
    }
    
}
