#include "../structure.h"
#include "avl.h"


void rotationgauche ( ptr_t_vols *A )
{
    ptr_t_vols aux;

    aux = (*A)->fd;
    (*A)->fd = aux->fg;
    aux->fg = *A;
    *A = aux;

    (*A)->fg->balance = -1 - (*A)->balance;
    (*A)->balance = 1 + (*A)->balance;

}

void rotationdroite ( ptr_t_vols *A )
{
    ptr_t_vols aux;

    aux = (*A)->fg;
    (*A)->fg = aux->fd;
    aux->fd = (*A);
    (*A) = aux;

    (*A)->fd->balance = -1 - (*A)->balance;
    (*A)->balance = 1 + (*A)->balance;
}

void rotationgauchedroite ( ptr_t_vols *A )
{
    ptr_t_vols aux;

    // Rotation gauche sur fils gauche
    aux = (*A)->fg->fd;
    (*A)->fg->fd = aux->fg;
    aux->fg = (*A)->fg;
    // Rotation droite
    (*A)->fg = aux->fd;
    aux->fd = *A;
    *A = aux;
    // rétablissement de l'équilibre
    (*A)->fg->balance = 0;
    (*A)->fd->balance = 0;
    if ((*A)->balance == -1)
      (*A)->fg->balance = 1;
    else if ((*A)->balance == 1)
      (*A)->fd->balance = - 1;

    (*A)->balance = 0;
}

void rotationdroitegauche ( ptr_t_vols *A )
{
    ptr_t_vols aux;

    // Rotation droite sur fils droit
    aux = (*A)->fd->fg;
    (*A)->fd->fg = aux->fd;
    aux->fd = (*A)->fd;
    // Rotation gauche
    (*A)->fd = aux->fg;
    aux->fg = *A;
    *A = aux;
    // rétablissement de l'équilibre
    (*A)->fg->balance = 0;
    (*A)->fd->balance = 0;
    if ((*A)->balance == -1)
      (*A)->fd->balance = 1;
    else if ((*A)->balance == 1)
      (*A)->fg->balance = - 1;

    (*A)->balance = 0;
}

/**
* ajout dans un arbre avl
*
*
* @param ptr_t_vols x		L'élément à ajouter (doit déjà être créer)
* @param  ptr_t_vols  *B
* @return int			retourne le changment le changment de hauteur;    0 si il existe déjà de l'arbre
*/


int ajoutavl(ptr_t_vols x, ptr_t_vols *B)
{
    int		cmp = 0;
//    DBG
	if (B == NULL)
		printf("B == NULL\n");
    else printf("listevol : %ld\n", (*B));
	if ((*B) == NULL)
	{
//		DBG
		*B = x;   // On  ajoute le lien
		(*B)->balance = 0;
		return 1;
	}
	else
	{
//	    DBG
	    printf("b->code_vol : %s\n", (*B)->code_vol);
	    printf("x->code_vol : %s\n", x->code_vol);
	    cmp = strcmp( x->code_vol, (*B)->code_vol);
	    printf("cmp = %i", cmp);

		if (cmp == 0 )  // Si il  existe déjà
			return 0;						// on renvoie 0 pour dire qu'il existe déjà
		else
		{
//		DBG
			if ( cmp <  0 )
			{
//			    DBG
				if ( ajoutavl(x, &((*B)->fg) ) == 0 )
					return 0;
				else
				{
//				    DBG
				    (*B)->balance = (*B)->balance + 1;
					if ( (*B)->balance == 2 )
					{
						if ( (*B)->fg->balance == 1 )
							rotationdroite(B);
						else
							rotationgauchedroite(B);
					}
					return ((*B)->balance);
				}
			}
			else
			{
			//	printf("b->fd : %ld", (*B)->fd );
//				DBG
				if ( ajoutavl(x, &((*B)->fd) ) == 0 )
					return 0;
				else
				{
//				    DBG
					(*B)->balance = (*B)->balance - 1;
					if ( (*B)->balance == -2 )
					{
						if ( (*B)->fd->balance == -1 )
							rotationgauche(B);
						else
							rotationdroitegauche(B);
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
* @donnee : ptr_t_vols a
* @DM :
* @param ptr_t_vols *aa
* @return de type ptr_t_vols renvoie la cellule contenant la plus petite valeur du sad
*
*
*/


ptr_t_vols plus_petit(ptr_t_vols a)
{
   printf("plus_petit\n");
   //a = a->sad;
   while (a->fg != NULL)
   {
   		 a = a->fg;
   }
printf("plus_petit2\n");
   return a;
}

/**
* Copie les valeurs de la premiere cellule dans la deuxième
*
* @donnee : ptr_t_vols source
* @DM :  ptr_t_vols *destination
* @param ptr_t_vols source, ptr_t_vols *destination
* @return rien
*/


void copie_arbre(ptr_t_vols source, ptr_t_vols *destination)
{

   strcpy((*destination)->code_vol, source->code_vol );
   strcpy((*destination)->dest, source->dest );
   strcpy((*destination)->avion, source->avion );

   return;
}

/**
* suppression dans un arbre aboh
*
* @donnee : type x
* @DM :  ptr_t_vols *aa
* @param type x, ptr_t_vols *aa
* @return de type booléen
*/
/*

int suppression(type x, ptr_t_vols *aa)
{
	ptr_t_vols q;
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
			else     // on a trouver
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

*/
ptr_t_vols   init_listevols (char *codevol)
{
	ptr_t_vols nouvvols = NULL;

    DBG
	if ( ( nouvvols = (ptr_t_vols) malloc(sizeof(t_vols)) ) == NULL)
	  exit(2);

        nouvvols->fg = NULL;
        nouvvols->fd = NULL;
        nouvvols->balance = 0;
		strcpy( nouvvols->code_vol, codevol );
        printf("nouvvols = Filsdroit : %ld\n", nouvvols->fd);

    return nouvvols;
}

/*

int main()
{
	ptr_t_vols listevol = NULL;
    DBG
	//listevol = init_listeclient ("A");
	//printf("listevol : %ld\n", listevol);
	//printf("Filsdroit : %ld\n", listevol->fd);

	DBG
	ajout( init_listeclient ("A"), &listevol);
	printf("listevol : %ld\n", listevol);
    ajout( init_listeclient ("B"), &listevol);
    printf("listevol : %ld\n", listevol);
    ajout( init_listeclient ("D"), &listevol);
    ajout( init_listeclient ("F"), &listevol);
    ajout( init_listeclient ("Z"), &listevol);
	ajout( init_listeclient ("Y"), &listevol);
	ajout( init_listeclient ("M"), &listevol);
	ajout( init_listeclient ("G"), &listevol);
	ajout( init_listeclient ("L"), &listevol);
	ajout( init_listeclient ("E"), &listevol);
	ajout( init_listeclient ("G"), &listevol);
	ajout( init_listeclient ("H"), &listevol);
	ajout( init_listeclient ("I"), &listevol);
	ajout( init_listeclient ("K"), &listevol);
	ajout( init_listeclient ("O"), &listevol);
	ajout( init_listeclient ("X"), &listevol);
	ajout( init_listeclient ("W"), &listevol);
	ajout( init_listeclient ("N"), &listevol);
	ajout( init_listeclient ("Q"), &listevol);
	ajout( init_listeclient ("R"), &listevol);


    system("pause");
	return 0;
}
*/

//Recherche par ordre
int parcourttotab(ptr_t_vols a, ptr_t_vols tab[], int *n )
{

	 printf("n = %ld", *n);
	 if( a != NULL)
	 {
		 printf("parcourttotab");
		 parcourttotab(a->fg, tab, n);

		 tab[*n] = a;

		 printf("tab[%ld]->code_vol : %s\n",  *n , tab[ *n ]->code_vol);
		 *n = *n + 1;
		 parcourttotab(a->fd, tab, n);

	 }


}

// Comptage du nombre d'élément
int nbr_elmt(ptr_t_vols a)
{
	int nbr = 0;

	if( a != NULL)
    {
	  	 nbr = nbr + nbr_elmt(a->fg);
		 printf("nbr_elmt : %ld\n", nbr);
	 	 nbr = nbr + nbr_elmt(a->fd);
		 printf("nbr_elmt : %ld\n", nbr);
		 return nbr + 1;
	}
	return 0;
}
