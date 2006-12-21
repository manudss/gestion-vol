#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

int main()
{
	pile energiser;
	int i;
	double val;
	int debut=0;
	int fin=15;


	//initialisation
	init(&energiser);



	// empiler
	for (i = debut; i< fin; i++)
	{
	    printf("\nempiler %ld",i);
	    empiler(&energiser, i);
	}

    // affichage
   for (i = 0; i< fin - debut; i++)
	{
	    printf("\n affichage %ld  : %lf",i, affiche_valeur(energiser, i));
	}


	vider(&energiser);

	// affichage
	    printf("\nvider pile + test affiche_valeur : %lf",affiche_valeur(energiser, i));


    return 0;
}
