#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "temps.h"

void obtenirTemps(TEMPS *temps)
{
    time_t now;
    char all[30], *h, *m, *s;

    time(&now);
    strcpy(all,ctime(&now));

    m = strchr(all,':');
    if(m == NULL)
        return;
    h = m++ - 2;
    s = m + 3;

    temps->heure = atoi(h);
    temps->minute = atoi(m);
    temps->seconde = atoi(s);
}

long tempsTOsec(TEMPS temps)
{
    return (temps.heure * 3600)+(temps.minute * 60)+temps.seconde;
}

void secTOtemps(long sec, TEMPS *temps)
{
    temps->heure = sec/3600;
    temps->minute = (sec%3600)/60;
    temps->seconde = sec%60;
}
