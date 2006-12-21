#include <stdio.h>
#include <stdlib.h>
#include "aboh.h"


/**
* ajout dans un arbre avl
*
* 
* @param t_vols x		L'élément à ajouter (doit déjà être créer)
* @param  ptr_t_vols  *B
* @return int			retourne le changment le changment de hauteur;    0 si il existe déjà de l'arbre 
*/


void ajout(ptr_t_vols x, ptr_t_vols *B)
{
	if (*B == NULL)
	{
		*B = x;   // On  ajoute le lien
		(*B)->balance = 0;   
		return 1;
	}
	else
	{
		if ((*B)->code_vols == x->code_vols)   // Si il  existe déjà 
			return 0;						// on renvoie 0 pour dire qu'il existe déjà
		else
		{
			if (x->code_vols < (*B)->code_vols)
			{
				if ( ajout(x, (*B)->fg) == 0 ) 
					return 0;
				else
				{
					(*B)->balance = *B->balance + 1;
					if (*B)->balance == 2
					{
						if (*B)->fg->balance == 1
							rotationgauche(*B);
						else
							rotationdroitegauche(*B);
					}
					return ((*B)->balance);
				}
			}
			else
			{
				if ( ajout(x, (*B)->fd) == 0 )
					return 0;
				else
				{
					(*B)->balance = (*B)->balance - 1;
					if (*B)->balance == -2
					{
						if (*B)->fg->balance == -1 
							rotationgauche(*B);
						else
							rotationdroitegauche(*B);
					}
					return ((*B)->balance);
				}
			}			
		}
	}
} 

/**
* @brief Rotation à gauche 
*
* @donnee : ptr_arbre a
* @DM :  
* @param ptr_arbre *aa
* @return de type ptr_arbre renvoie la cellule contenant la plus petite valeur du sad
* 
*
*/


ptr_arbre plus_petit(ptr_arbre a)
{
   printf("plus_petit\n");
   //a = a->sad;
   while (a->sag != NULL)
   {
   		 a = a->sag;
   }
printf("plus_petit2\n");
   return a;
}

/**
* Copie les valeurs de la premiere cellule dans la deuxième
*
* @donnee : ptr_arbre source
* @DM :  ptr_arbre *destination
* @param ptr_arbre source, ptr_arbre *destination
* @return rien
*/


void copie_arbre(ptr_arbre source, ptr_arbre *destination)
{
   printf("copie_arbre: %ld\n",(*destination)->info);
   (*destination)->info = source->info;
   printf("copie_arbre2 %ld\n",(*destination)->info);
   return;
}

/**
* ajout dans un arbre aboh
*
* @donnee : type x
* @DM :  ptr_arbre *aa
* @param type x, ptr_arbre *aa
* @return de type booléen
*/


int suppression(type x, ptr_arbre *aa)
{
	ptr_arbre q;	
	int ok;
	printf("suppression x : %ld\n", x);	
	printf("suppression *aa->info : %ld\n", (*aa)->info);	
	if (*aa == NULL)
	   ok = 0;
    else
    {
	 	if ((*aa)->info < x)
	 	   suppression(x, &((*aa)->sad));
        else          
		{
		 	if ((*aa)->info > x)
	 	   	   suppression(x, &((*aa)->sag));
			else     /* on a trouver */
			{		
				ok = 1;
				printf("suppression\n");
			 	if ((*aa)->sag == NULL)   // cas 1 et 2 
			 	{
				   printf("suppression1\n");
				   q = (*aa);
				   (*aa) = (*aa)->sad;
				   free(q);
		 		}
		 		else
		 		{
				 	if ((*aa)->sad == NULL) // cas 2
				 	{
					   	printf("suppression2\n");
						q = (*aa);
				   		(*aa) = (*aa)->sag;
				   		free(q);				   			 
					}
					else   // cas 3
					{
					 	printf("suppression3\n");
						q = plus_petit((*aa)->sad);  // on récupère l'adresse de la cellule du plus petit du sad
						printf("suppression 4: %ld\n",(*aa)->info);
					 	copie_arbre(q, *aa);   // on copie la valeur de la plus petite valeur dans le noeud
						ok = suppression(q->info, &q);  // on supprime la cellule
						printf("suppression5\n");
					} 	   
				}
			}
		} 		
	}
	
	return ok;
} 







