#ifndef TEMPS_H_INCLUDED
#define TEMPS_H_INCLUDED

typedef struct
{
    int heure,minute,seconde;
} TEMPS;

void obtenirTemps(TEMPS *temps);
long tempsTOsec(TEMPS temps);
void secTOtemps(long sec, TEMPS *temps);


#endif // TEMPS_H_INCLUDED
