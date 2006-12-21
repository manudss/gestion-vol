#ifndef PILE_H
#define PILE_H

/**
  * Structure poste donn�e de la liste
  * @val : valeur r�el (double) et pointeur vers la structure suivante
  */

typedef struct poste
{
    double val;
    struct poste *suiv;

}poste;

/**
  * pointeur vers une structure poste donn�e de la liste
  */

typedef poste* ptr_poste;

/**
  * pointeur vers une structure poste donn�e de la liste
  * @val : pointeur vers sommet et nombre d'�l�ment dans la pile
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
  * @param pile* pp (passage du pointeur d'une pile) et double val (de la valeur � ajouter)
  * @return rien
  */

void empiler(pile *pp, double val);

/**
* D�piler une pile
*
* @param pile* pp (passage du pointeur d'une pile) et double val (de la valeur � r�cup�r�)
* @return renvoie valeur boull�enne : 1 si ca a march� et 0 si il y a eu un probl�me
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
* Renvoie la Iieme valeur de la pile (sans d�piler)
*
* @param pile pp (passage d'une pile) et int  i (de la valeur � r�cup�rer)
* @return renvoie valeur bool�enne : 1 si ca a march� et 0 si il y a eu un probl�me
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
