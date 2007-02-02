#include "../structure.h"
#include "recherche.h"



//--------------------------- Fonction Recherche --------------------------------------------------------------//

void * recherche(void *  achercher,llist liste, void * (fct_rech) (void* achercher,void * chercherdans))
{


    llist tmp = liste;
    char * val;
    ptr_t_client client;

    int ok =0;
	void * cherche = NULL;

    val = (char *) achercher;
    printf("recherche ... ");
    puts(val);
    printf("liste : %ld", liste);






    while(liste != NULL && ok != 1 )
    {
        //puts(&liste->data);
        printf("liste->data : %ld\n", liste->data);
		cherche = fct_rech(achercher, liste->data);
    	if(cherche != NULL)
    	{
            tmp = (llist) cherche;
    	    printf("trouver");
    	    ok=1;
    	    return liste->data;
    	}
		else
		{

		    liste = liste->suiv;

		}

    }

    return liste;
}

/* Utilisation

if ( tmp = recherche(cleclient , TDH[ hachage(cleclient) ] , &recherche_dest) != NULL );   // cleclient variable contenant le cle du cleint : (par ex :"DEEM8603NN0").
                                                                                //TDH la table de hachage des clients, et transmettre juste la liste (llist) correpondant a la plce dans la TDH
  {
      // traitement réussite
      // On a la variable tmp a gerer normalement comme une variable normal du ty pe de la structure
      puts(tmp->cle);
    }
    else
    {
        //traitement erreur
    }

*/


void * recherch_client_par_cle(void* achercher,void * chercherdans)
{

    char * cle;
    ptr_t_client client;

    cle = (char*) achercher;
    puts(cle);
    client = (ptr_t_client) chercherdans;
    printf("chercherdans : %ld\n", chercherdans);
    printf("client : %ld\n", client);


    puts(client->cle);

    if (strcmp(cle , &client->cle) == 0 )
    {

        return chercherdans;
    }
    else
    {

        return NULL;
    }


}


/* Utilisation

if ( tmp = recherche(codedestination , listedestination , &recherche_dest) != NULL );   // codedestination variable contenant le code de la destination : (par ex :"lonpar").
                                                                                //listedestination la liste chainée des destinations
  {
      // traitement réussite
      // On a la variable tmp a gerer normalement comme une variable normal du ty pe de la structure
      puts(tmp->code);
    }
    else
    {
        //traitement erreur
    }

*/

void * recherche_dest(void* achercher,void * chercherdans)
{

    char * codedest;
    ptr_t_destination dest;

    codedest = (char*) achercher;
    puts(codedest);
    dest = (ptr_t_destination) chercherdans;
    printf("chercherdans : %ld\n", chercherdans);
    //printf("dest : %ld\n", *dest);
    //printf("client : %ld\n", dest);


    puts(dest->code);

    if (strcmp(codedest , &dest->code) == 0 )
    {

        return chercherdans;
    }
    else
    {

        return NULL;
    }

}


/* Utilisation

if ( tmp = recherche(modele  , listeavion , &recherche_avion) != NULL );   // modele variable contenant le nom du modele : (par ex :"a380"). listeavion la liste chainée des avions
  {
      // traitement réussite
      // On a la variable tmp a gerer normalement comme une variable normal du ty pe de la structure
      puts(dest->model);
    }
    else
    {
        //traitement erreur
    }

*/

void * recherche_avion(void* achercher,void * chercherdans)
{

    char * modele;
    ptr_t_avions avion;

    modele = (char*) achercher;
    puts(modele);
    avion = (ptr_t_avions) chercherdans;
    printf("chercherdans$ : %ld\n", chercherdans);
    //printf("dest : %ld\n", *dest);
    //printf("client : %ld\n", dest);


    puts(avion->modele);

    if (strcmp(modele , &avion->modele) == 0 )
    {

        return chercherdans;
    }
    else
    {

        return NULL;
    }

}