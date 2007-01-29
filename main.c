#include "structure.h"
#include "liste/liste.h"
#include "avl/avl.h"
#include "chargement/chargement.h"

int main()
{
	llist *listeclient = NULL;
	llist listeavion = NULL;
	llist listedestination = NULL;
	ptr_t_vols *arbrevol = NULL;
	int nbr;
	ptr_t_vols *tab;
    int i, n=0;

	if ((listeclient = init_listeclient()) == NULL)
        exit (2);
	chargement("listeclient.csv", (void *) &ajout_client, (void *) listeclient, NULL);
	listeavion = chargement("listeavion.csv", (void *) &ajout_avion, (void *) listeavion, NULL);
	listedestination = chargement("listedestination.csv", (void *) &ajout_destination, (void *) listedestination, NULL);
	chargement("listeFF.csv", (void *) &ajout_FF, (void *) listeclient, NULL);
	chargement("listevolsencours.csv", (void *) &ajout_vols_en_cours, (void *) listeclient, NULL);
	chargement("listevols.csv", (void *) &ajout_vols, (void *) &arbrevol, NULL);

    printf("fin chargement");

    nbr = nbr_elmt(arbrevol);
	 printf("nbr de champ %ld\n",nbr);
    DBG
    tab = (ptr_t_vols) malloc(sizeof( ptr_t_vols ) * nbr);
    DBG
    parcourttotab( arbrevol, tab, &n );

    printf("nbr de champ \n");

    for (i = 0; i < nbr; i ++)
    {
        printf("tab[%ld ]->code_vol : %s",i, tab [ i ]->code_vol);
    }

    //afficherListe(listeclient[hachage("DE")], &affiche_client);
    //afficherListe(listeavion, &affiche_avion);

    //listeclient = effacerListe(listeclient, &freet_client);
    //listeavion = effacerListe(listeavion, &freet_avions);
    //vols(0,0);
    //identification ((llist**)listeclient);

	return 0;
}

