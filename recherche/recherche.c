#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"




void * recherche(void *  achercher,llist liste, void * (fct_rech) (void* achercher,void * chercherdans))
{


    element* tmp = liste;

    int ok =0;
	void * cherche = NULL;

    while(tmp != NULL && ok != 1 )
    {
		cherche = fct_rech(achercher, liste.data);

    	if(cherche != NULL) ok=1;
		else liste = liste.suiv;

    }
    return cherche;
}