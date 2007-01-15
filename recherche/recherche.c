#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"




//--------------------------- Fonction Recherche --------------------------------------------------------------//

void * recherche(void *  achercher,llist liste, void * (fct_rech) (void* achercher,void * chercherdans))
{


    element* tmp = liste;
    char * val;

    int ok =0;
	void * cherche = NULL;
    DBG
    val = (char *) achercher;
    printf("recherche ... ");
    puts(val);

    while(liste != NULL && ok != 1 )
    {
        DBG
		cherche = fct_rech(achercher, liste->data);

    	if(cherche != NULL)
    	{
    	    DBG
    	    tmp = (llist) cherche;
    	    //puts(tmp->cle);
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
    char * cle;
    ptr_t_client client;

    cle = (char*) achercher;
    puts(cle);
    client = (ptr_t_client) chercherdans;
    DBG
    puts(client->cle);
    DBG
    if (strcmp(cle , client->cle) == 0 )
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
