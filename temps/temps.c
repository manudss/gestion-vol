#include "../structure.h"
#include <math.h>

char * quelheure(ptr_t_temps temps)
{
    t_temps tmp;
    int difjour;
    double delta;
    int depass=0;
    char s[64];
    char *retour;
    struct tm tm_now;





    temps->deb = *localtime (&temps->debut);

    /*
    strftime (s, sizeof s, "%A %d %B %Hh%M", &(temps->deb));
    printf ("Le temps du d�but : %s\n", s);

    strftime (s, sizeof s, "%A %d %B %Hh%M", &(temps->cour));
    printf ("Temps courant  : %s\n", s);
    */

    // avoir l'heure du jour suivant � minuit
    tmp.courant = temps->courant + 60*60*24;
    tmp.cour = *localtime (&tmp.courant);
    tmp.cour.tm_hour = 0;
    tmp.cour.tm_min = 0;
    tmp.cour.tm_sec = 0;
    tmp.courant = mktime(&tmp.cour);

    delta = difftime(time(NULL),temps->debut);
    temps->courant += abs(delta);
    temps->cour = *localtime (&temps->courant);
    temps->cour.tm_mday += 31;
    strftime (s, sizeof s, "%A %d %B %Hh%M", &(temps->cour));
    //printf ("Il est : %s\n", s);
    retour = strdup(&s);







    if (difftime(temps->courant,tmp.courant) >= 0 )          // Si on a changer de jour
    {
        printf("Changement de jour : sauvegarde, vieullez patienter ......\n");
       /* do
        {

            effacementjour ( );    // effacement des jours dans l'arbre avl
            effacementcolsclient( ); // effacement dans la liste des vols en cours du client
            difjour --;
        while ( difjour != 0)
        enregistrement ( );    // enregistrement dans les fichiers
        sauvgardetemps (temps)
        */
    }
    return retour;
}

char * ajoutertemps(ptr_t_temps temps, long t_plus)
{
    char * retour;
    temps->courant += t_plus;
    retour = quelheure(temps);
    return retour;
}



//int tm_sec;   /* Secondes */
//
//  int tm_min;   /* Minutes */
//
//  int tm_hour;  /* Heures (0 - 23) */
//
//  int tm_mday;  /* Quanti�me du mois (1 - 31) */
//
//  int tm_mon;   /* Mois (0 - 11) */
//
//  int tm_year;  /* An (ann�e calendaire - 1900) */
//
//  int tm_wday;  /* Jour de semaine (0 - 6  Dimanche = 0) */
//
//  int tm_yday;  /* Jour dans l'ann�e (0 - 365) */
//
//  int tm_isdst; /* 1 si "daylight saving time" */


void sauvgardetemps (ptr_t_temps temps)
{
    FILE* fichtemps;
    char *date;

    fichtemps = fopen("temps.txt", "w+");

    if (fichtemps != NULL)
    {
        fprintf(fichtemps,"%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", temps->cour.tm_sec, temps->cour.tm_min ,
        temps->cour.tm_hour ,temps->cour.tm_mday , temps->cour.tm_mon , temps->cour.tm_year , temps->cour.tm_wday ,
        temps->cour.tm_yday , temps->cour.tm_isdst);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier temps.txt\n");
    }

}

void lecturetemps (ptr_t_temps temps)
{
    FILE* fichtemps;

    fichtemps = fopen("temps.txt", "r");
    if (fichtemps != NULL)
    {

        fscanf(fichtemps,"%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", &(temps->cour.tm_sec), &(temps->cour.tm_min) ,
        &(temps->cour.tm_hour) ,&(temps->cour.tm_mday) , &(temps->cour.tm_mon) , &(temps->cour.tm_year) , &(temps->cour.tm_wday) ,
        &(temps->cour.tm_yday) , &(temps->cour.tm_isdst));

        temps->courant = mktime(&temps->cour);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier temps.txt\n");
    }

}



