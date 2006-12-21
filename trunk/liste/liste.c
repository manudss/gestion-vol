/** @struct  element
* @brief structure d'une liste chain�e g�n�rale
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
    /* On cr�e un nouvel �l�ment */
    element* nouvelElement = malloc(sizeof(element));

    /* On assigne la valeur au nouvel �l�ment */
    nouvelElement->val = valeur;

    /* On assigne l'adresse de l'�l�ment suivant au nouvel �l�ment */
    nouvelElement->nxt = liste;

    /* On retourne la nouvelle liste, ie. le pointeur sur le premier �l�ment */
    return nouvelElement;
}