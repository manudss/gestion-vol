#include "../structure.h"
#include "liste.h"

#define DGB printf("DEBUG File: %s Line:%d \n",__FILE__,__LINE__);




llist ajouterEnTete(llist liste, void * valeur)
{
    llist nouvelElement = malloc(sizeof(element));
    DBG
    nouvelElement->data = valeur;
    DBG
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

void * generic ( void * liste) // 8-)
{

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
    puts(avion->modele);
    printf("modele : %s\n",avion->modele);
    printf("strlen modele : %ld", strlen(avion->modele));
    printf("capacite : %ld\n",avion->capacite);
    printf("autonomie : %ld\n",avion->autonomie);

}

void * affiche_dest (void * tmp)
{
    ptr_t_destination dest;
    dest  = (ptr_t_destination) tmp;
    //puts(avion->modele);
    printf("dest->code = %s\n",dest->code);
    printf("destination = %s\n",dest->destination);
    printf("origine = %s\n",dest->origine);

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


 llist effacerelmt(llist liste, char * aeffacer)
{
    element* tmp = liste;
    element* tmpprec = liste;
    int fin = 0;

    printf("effacer liste\n");

    if (strstr((char *) tmp->data, aeffacer ) != 0 && tmp != NULL)  // cas en tête
    {
        liste = liste->suiv;
        // effacement de la structure.
        tmp->data = NULL;
        free(tmp);
        fin = 1;
    }
    while(tmp != NULL || fin != 0)
    {

        tmpprec = tmp->suiv;
        if (strstr((char *) tmp->data, aeffacer ) != 0 )
        {
            tmpprec->suiv = tmp->suiv;
            // effacement de la structure.
            tmp->data = NULL;
            free(tmp);
            fin = 1;
        }
        else
        {
            tmpprec = tmp;
            tmp = tmp->suiv;
        }
    }
    return liste;
}

llist effacervol(llist liste, int i)
{
int k;
llist ptr, ptrprec;
ptr=liste;
ptrprec = liste;

if (i == 1 && liste != NULL)  // cas en tête
{
    DBG
    liste = liste->suiv;
    // effacement de la structure.
    ptr->data = NULL;
    free(ptr);
}
else if (liste != NULL)
{    
    DBG
    for (k=1;k<i;k++)
    {
        printf("effacevol : k :%ld",k);
        ptrprec = ptr;
        ptr=ptr->suiv;
        printf("ptr->suiv %ld",ptr->suiv);
    }
    ptrprec->suiv = ptr->suiv;
    // effacement de la structure.
    ptr->data = NULL;
    free(ptr);
}    
return liste;
}
