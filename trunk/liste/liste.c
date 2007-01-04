#include <stdio.h>
#include <stdlib.h>
#include "structure.h"

#define DGB printf("DEBUG File: %s Line:%d \n",__FILE__,__LINE__);



llist ajouterEnTete(llist liste, void * valeur)
{
    element* nouvelElement = malloc(sizeof(element));
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
    free(listeclient->adresse.rue);
    free(listeclient->adresse.ville);
    free(listeclient->adresse.pays);
    free(listeclient->ff);
    free(listeclient->message);
    free(listeclient->vols);

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
    printf("%ld",client->tel);
    printf("%ld",client->adresse.num);
    puts(client->adresse.rue);
    printf("%ld",client->adresse.code_postal);
    puts(client->adresse.ville);
    puts(client->adresse.pays);
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

