#include "../structure.h"
#include "recherche.h"


//--------------------------- Fonction Recherche --------------------------------------------------------------//

void * recherche(void *  achercher,llist liste, void * (fct_rech) (void* achercher,void * chercherdans))
{


    element* tmp = liste;
    char * val;
    ptr_t_client client;

    int ok =0;
	void * cherche = NULL;
    DBG
    val = (char *) achercher;
    printf("recherche ... ");
    puts(val);
    client = (ptr_t_client) liste->data;

    puts(client->cle);



    while(liste != NULL && ok != 1 )
    {
        DBG
        //puts(&liste->data);
        DBG
        printf("liste->data : %ld\n", liste->data);
        DBG
		cherche = fct_rech(achercher, liste->data);

    	if(cherche != NULL)
    	{
    	    DBG
    	    tmp = (llist) cherche;
    	    //puts(tmp.cle);
    	    //puts(tmp.nom);
    	    printf("trouver");

    	    ok=1;
    	    return liste->data;
    	}
		else
		{
		    DBG
		    liste = liste->suiv;
		    DBG
		}

    }
    DBG
    return liste;
}

void * recherch_client_par_cle(void* achercher,void * chercherdans)
{
    DBG
    char * cle;
    ptr_t_client client;
    DBG
    cle = (char*) achercher;
    puts(cle);
    client = (ptr_t_client) chercherdans;
    printf("chercherdans : %ld\n", chercherdans);
    printf("client : %ld\n", client);

    DBG
    puts(client->cle);
    DBG
    if (strcmp(cle , &client->cle) == 0 )
    {
        DBG
        return chercherdans;
    }
    else
    {
        DBG
        return NULL;
    }

}
