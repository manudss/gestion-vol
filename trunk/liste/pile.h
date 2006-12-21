#ifndef PILE_H
#define PILE_H

/**
  * Structure poste donnée de la liste
  * @val : valeur réel (double) et pointeur vers la structure suivante
  */

typedef struct poste
{
    double val;
    struct poste *suiv;

}poste;

/**
  * pointeur vers une structure poste donnée de la liste
  */

typedef poste* ptr_poste;

/**
  * pointeur vers une structure poste donnée de la liste
  * @val : pointeur vers sommet et nombre d'élément dans la pile
  */
typedef struct pile
{
    ptr_poste sommet;
    int nb_elt;

}pile;

/**
  * Tester si une pile est vide
  *
  * @param pile pp (passage d'une pile)
  * @return test booleen : 0 si vide et 1 si non vide
  */

int pile_vide(pile p);

/**
  * Empiler une pile
  *
  * @param pile* pp (passage du pointeur d'une pile) et double val (de la valeur à ajouter)
  * @return rien
  */

void empiler(pile *pp, double val);

/**
* Dépiler une pile
*
* @param pile* pp (passage du pointeur d'une pile) et double val (de la valeur à récupéré)
* @return renvoie valeur boulléenne : 1 si ca a marché et 0 si il y a eu un problème
*/

int depiler(pile *pp, double *val);

/**
  * Vider une pile, ou l'initialiser
  *
  * @param pile* pp (passage du pointeur d'une pile)
  * @return rien
  */

void vider(pile *pp);

/**
* Renvoie la Iieme valeur de la pile (sans dépiler)
*
* @param pile pp (passage d'une pile) et int  i (de la valeur à récupérer)
* @return renvoie valeur booléenne : 1 si ca a marché et 0 si il y a eu un problème
*/

double affiche_valeur(pile pp, int i);

/**
  * Initier une pile
  *
  * @param pile* pp (passage du pointeur d'une pile)
  * @return rien
  */

void init(pile *pp);
#endif
