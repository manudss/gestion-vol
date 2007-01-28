#include "structure.h"
#include "liste/liste.h"
#include "avl/avl.h"

int main()
{
	llist *listeclient = NULL;
	llist listeavion = NULL;
	llist listedestination = NULL;
	ptr_t_vols *arbrevol = NULL;

	if ((listeclient = init_listeclient()) == NULL)
        exit (2);
	chargement("listeclient.csv", (void *) &ajout_client, (void *) listeclient, NULL);
	listeavion = chargement("listeavion.csv", (void *) &ajout_avion, (void *) listeavion, NULL);
	listedestination = chargement("listedestination.csv", (void *) &ajout_destination, (void *) listedestination, NULL);
	chargement("listeFF.csv", (void *) &ajout_FF, (void *) listeclient, NULL);
	chargement("listevolsencours.csv", (void *) &ajout_vols_en_cours, (void *) listeclient, NULL);
	chargement("listevols.csv", (void *) &ajout_vols, (void *) &arbrevol, NULL);


    afficherListe(listeclient[hachage("DE")], &affiche_client);
    afficherListe(listeavion, &affiche_avion);

    //listeclient = effacerListe(listeclient, &freet_client);
    listeavion = effacerListe(listeavion, &freet_avions);


    system("pause");
	return 0;
}

