#include "../structure.h"
#include <math.h>
#include "../temps/temps.h"

char * quelheure(ptr_t_temps temps, llist TDH[], ptr_t_vols arbre, llist listeavion, llist listedest)
{
    t_temps tmp;
    int difjour;
    double delta;
    int depass=0;
    char s[64];
    char *retour;
    struct tm tm_now;

    printf("\nquelheure temps%ld\n",temps);

    temps->deb = *localtime (&temps->debut);
    // avoir l'heure du jour suivant à minuit
    tmp.courant = temps->courant + 60*60*24;
    tmp.cour = *localtime (&tmp.courant);
    tmp.cour.tm_hour = 0;
    tmp.cour.tm_min = 0;
    tmp.cour.tm_sec = 0;
    tmp.courant = mktime(&tmp.cour);
    DBG
    delta = difftime(time(NULL),temps->debut);
    temps->courant += abs(delta);
    temps->cour = *localtime (&temps->courant);

    strftime (s, sizeof s, "%A %d %B %G %Hh%M", &(temps->cour));
    //printf ("Il est : %s\n", s);
    retour = strdup(&s);
    difjour = difftime(tmp.courant,temps->courant);
    printf("\ndifjour %ld\n",difjour);

    DBG
    if ( difjour >= 0 )          // Si on a changer de jour
    {
        printf("Changement de jour : sauvegarde, veuillez patienter ......\n");

        DBG
        do
        {
            temps->jour = (temps->jour + 1) % 31;
            effacementjour (arbre, temps , TDH);
            //effacementvolsclient( ); // effacement dans la liste des vols en cours du client
            difjour = difjour - 60*60*24;
        }
        while ( difjour >= 60*60*24);
        //enregistrement ( );    // enregistrement dans les fichiers
        sauvgardetemps (temps);
    }
    return retour;
}

char * ajoutertemps(ptr_t_temps temps, long t_plus,llist listeclient[],ptr_t_vols arbrevol,llist listeavion,llist listedestination)
{
    char * retour;
    temps->courant += t_plus;
    retour = quelheure(temps,listeclient, arbrevol,listeavion, listedestination);
    return retour;
}

char * date (ptr_t_temps temps, int i)
{
    char * retour;
    char s[64];
    t_temps tmp;

    tmp.courant = temps->courant;
    tmp.courant += i*60*60*24;
    tmp.cour = *localtime (&tmp.courant);
    strftime (s, sizeof s, "%A %d %B", &(tmp.cour));
    retour = strdup(&s);
    return retour;
}



//int tm_sec;   /* Secondes */
//
//  int tm_min;   /* Minutes */
//
//  int tm_hour;  /* Heures (0 - 23) */
//
//  int tm_mday;  /* Quantième du mois (1 - 31) */
//
//  int tm_mon;   /* Mois (0 - 11) */
//
//  int tm_year;  /* An (année calendaire - 1900) */
//
//  int tm_wday;  /* Jour de semaine (0 - 6  Dimanche = 0) */
//
//  int tm_yday;  /* Jour dans l'année (0 - 365) */
//
//  int tm_isdst; /* 1 si "daylight saving time" */


void sauvgardetemps (ptr_t_temps temps)
{
    FILE* fichtemps;
    char *date;

    fichtemps = fopen("temps.txt", "w+");

    if (fichtemps != NULL)
    {
        fprintf(fichtemps,"%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d", temps->cour.tm_sec, temps->cour.tm_min ,
        temps->cour.tm_hour ,temps->cour.tm_mday , temps->cour.tm_mon , temps->cour.tm_year , temps->cour.tm_wday ,
        temps->cour.tm_yday , temps->cour.tm_isdst,temps->jour);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier temps.txt\n");
    }
    fclose(fichtemps);

}

void lecturetemps (ptr_t_temps temps)
{
    FILE* fichtemps;

    fichtemps = fopen("temps.txt", "r");
    if (fichtemps != NULL)
    {
        fscanf(fichtemps,"%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", &(temps->cour.tm_sec), &(temps->cour.tm_min) ,
        &(temps->cour.tm_hour) ,&(temps->cour.tm_mday) , &(temps->cour.tm_mon) , &(temps->cour.tm_year) , &(temps->cour.tm_wday) ,
        &(temps->cour.tm_yday) , &(temps->cour.tm_isdst),&(temps->jour));
        temps->courant = mktime(&temps->cour);
        printf("\ntemps->jours :%ld",temps->jour);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier temps.txt\n");
    }
    fclose(fichtemps);

}




