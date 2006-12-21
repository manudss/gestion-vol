#include "pile.h"

/**
  * Tester si un arbre est vide
  *
  * @param t_vols 		arbre passage d'un arbre
  * 
  * @return int   			test booleen : 0 si vide et 1 si non vide
  */

int arbre_vide(t_vols arbre)
{
    return if(arbre == NULL);
}

/**
  * ajouter un �l�ment dans un arbre
  *
  * @param pile* pp (passage du pointeur d'une pile) et double valeur (de la valeur � ajouter)
  * @return rien
  */

void empiler(pile *pp, double valeur)
{
    ptr_poste cour;


    cour = (ptr_poste) malloc(sizeof(poste));

    cour->val = valeur;

    cour->suiv = pp->sommet;
    pp->sommet = cour;
    pp->nb_elt = pp->nb_elt + 1;
    printf("sommet->val : %lf",pp->sommet->val);
    return;
}


/**
* D�piler une pile
*
* @param pile* pp (passage du pointeur d'une pile) et double val (de la valeur � r�cup�r�)
* @return renvoie valeur boull�enne : 1 si ca a march� et 0 si il y a eu un probl�me
*/

int depiler(pile *pp, double *val)
{
    int ok;
    ptr_poste cour;
    if (pile_vide(*pp)==1)
    {
        *val = pp->sommet->val;
        pp->nb_elt = pp->nb_elt - 1;
        cour = pp->sommet;
        pp->sommet = pp->sommet->suiv;
        free(cour);
        ok = 1;
    }
    else
    {
        ok = 0;
    }

    return ok;
}


/**
* Renvoie la Iieme valeur de la pile (sans d�piler)
*
* @param pile pp (passage d'une pile) et int  i (de la valeur � r�cup�rer)
* @return renvoie valeur bool�enne : 1 si ca a march� et 0 si il y a eu un probl�me
*/

double affiche_valeur(pile pp, int i)
{
    double result=-1;
    int j;
    ptr_poste parcourt;
    parcourt = pp.sommet;
    if (i > pp.nb_elt || pp.nb_elt == 0)
    {
        result = 0;
    }
    else
    {
        for (j = 0; j < i; j++)
        {
            parcourt = parcourt->suiv;
        }
        result = parcourt->val;
    }

    return result;
}

/**
  * Vider une pile, ou l'initialiser
  *
  * @param pile* pp (passage du pointeur d'une pile)
  * @return rien
  */

void vider(pile *pp)
{
    double val;
    int i;
    int tmp;

    if (pp->nb_elt > 0)
    {
        tmp = pp->nb_elt;
        // d�piler
        for (i=0; i<tmp; i++)
        {
            depiler(pp, &val);
        }
    }


    pp->sommet = 0;
    pp->nb_elt = 0;

    return;
}

/**
  * Initier une pile
  *
  * @param pile* pp (passage du pointeur d'une pile)
  * @return rien
  */

void init(pile *pp)
{

    pp->sommet = 0;
    pp->nb_elt = 0;

    return;
}



