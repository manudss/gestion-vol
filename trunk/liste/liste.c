/** @struct  element
* @brief structure d'une liste chainée générale
*
* @param
*
*/

typedef struct element element;
struct element
{
    void *data;
    struct element *nxt;
};

typedef element* llist;


llist ajouterEnTete(llist liste, int valeur)
{
    /* On crée un nouvel élément */
    element* nouvelElement = malloc(sizeof(element));

    /* On assigne la valeur au nouvel élément */
    nouvelElement->val = valeur;

    /* On assigne l'adresse de l'élément suivant au nouvel élément */
    nouvelElement->nxt = liste;

    /* On retourne la nouvelle liste, ie. le pointeur sur le premier élément */
    return nouvelElement;
}