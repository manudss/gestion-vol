#include "../structure.h"
#include "liste.h"

#define DGB printf("DEBUG File: %s Line:%d \n",__FILE__,__LINE__);



llist ajouterEnTete(llist liste, void * valeur)
{
    llist nouvelElement = malloc(sizeof(element));
    nouvelElement->data = valeur;
    nouvelElement->suiv = liste;

    return nouvelElement;
}

// ----------------------------- Fonction de suppression des listes ----------------------------- //

llist effacerListe(llist liste, void * (fctfree) (void *))
{
    element* tmp = liste;
    element* tmpnxt;

    printf("effacer liste\n");

    while(tmp != NULL)
    {
        tmpnxt = tmp->suiv;
        // effacement de la structure.
        tmp->data = fctfree(tmp->data);
        free(tmp);
        tmp = tmpnxt;
    }
    return NULL;
}

void * freet_client ( void * liste)
{

    t_client *listeclient;
    listeclient = (t_client *)liste;
    free(listeclient->mot_de_passe);
    free(listeclient->nom);
    free(listeclient->prenom);
    free(listeclient->adresse.adresse);
    free(listeclient->adresse.ville);
    free(listeclient->adresse.pays);
    //free(listeclient->ff);
    //free(listeclient->message);
    //free(listeclient->vols);

    free(listeclient);

    return NULL;
}

void * freet_avions ( void * liste)
{
    t_avions *avion;
    avion = (t_avions *)liste;
    free(avion);

    return NULL;
}



//------------------------- Fonction d'affichage ----------------------------------------//

void * affiche_client(void * tmp)
{
    ptr_t_client client;
    client  = (ptr_t_client) tmp;
    puts( client->cle);
    puts(client->mot_de_passe);
    puts(client->nom);
    puts(client->prenom);
    printf("%ld\n",client->tel);
    puts(client->adresse.adresse);
    puts(client->adresse.ville);
    puts(client->adresse.pays);
}

void * affiche_avion (void * tmp)
{
    ptr_t_avions avion;
    avion  = (ptr_t_avions) tmp;
    //puts(avion->modele);
    printf("%ls\n",avion->modele);
    printf("%ld\n",avion->capacite);
    printf("%ld\n",avion->autonomie);

}





void afficherListe(llist liste, void *(afficher) (void *))
{
    element *tmp;
	tmp = (element *) liste;
    printf("afficher liste");
    DBG
    while(tmp != NULL)
    {
        afficher (tmp->data);
        tmp = tmp->suiv;
    }
 }

