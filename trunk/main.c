#include "structure.h"
#include "liste/liste.h"
#include "avl/avl.h"
#include "chargement/chargement.h"
#include "temps/temps.h"


int main()
{
	llist *listeclient = NULL;
	llist listeavion = NULL;
	llist listedestination = NULL;
	ptr_t_vols *arbrevol = NULL;
	int nbr;
	ptr_t_vols *tab;
    int i, n=0;

    // gestion du temps
    t_temps temps;


    temps.debut = time (NULL);
    //temps.courant = time (NULL);
    temps.deb = *localtime (&temps.debut);

    // On charge le derniers temps courant lors de la précédentes fermetures
    lecturetemps (&temps);

    printf("bonjour, on est le : ");
    puts( quelheure(&temps, listeclient, arbrevol,listeavion, listedestination) );

    puts( ajoutertemps(&temps, 60*60*24,listeclient, arbrevol,listeavion, listedestination) );
/*
    for (i = 1; i <=31; i ++)
    {
        puts( date (&temps, i));
    }


*/
printf("\ntemps : %ld",temps.jour);
 system("pause");


    // fin temps


	if ((listeclient = init_listeclient()) == NULL)
        exit (2);
	chargement("listeclient.csv", (void *) &ajout_client, (void *) listeclient, NULL);
	listeavion = chargement("listeavion.csv", (void *) &ajout_avion, (void *) listeavion, NULL);
	listedestination = chargement("listedestination.csv", (void *) &ajout_destination, (void *) listedestination, NULL);
	chargement("listeFF.csv", (void *) &ajout_FF, (void *) listeclient, NULL);
	chargement("listevolsencours.csv", (void *) &ajout_vols_en_cours, (void *) listeclient, NULL);
	chargement("listevols.csv", (void *) &ajout_vols, (void *) &arbrevol, NULL);

    printf("fin chargement");
/*
     // simple test pas important
    nbr = nbr_elmt(arbrevol);
	 printf("nbr de champ %ld\n",nbr);

    tab = (ptr_t_vols) malloc(sizeof( ptr_t_vols ) * nbr);

    parcourttotab( arbrevol, tab, &n );

    printf("nbr de champ \n");

    for (i = 0; i < nbr; i ++)
    {
        printf("tab[%ld ]->code_vol : %s\n",i, tab [ i ]->code_vol);
    }


*/

    //afficherListe(listeclient[hachage("DE")], &affiche_client);
    //afficherListe(listeavion, &affiche_avion);

    //listeclient = effacerListe(listeclient, &freet_client);
    //listeavion = effacerListe(listeavion, &freet_avions);
    //vols(0,0);


     // fin test




    //identification ((llist**)listeclient);
    
    printf("MAIN :temps %ld",&temps);
    system("pause");
    identification ((llist**)listeclient, arbrevol,&temps,listedestination,listeavion);

    puts( quelheure(&temps, listeclient, arbrevol,listeavion, listedestination) );

	return 0;
}

