#include <stdio.h>
#include <stdlib.h>





llist ajouterEnTete(llist liste, void * valeur)
{
    element* nouvelElement = malloc(sizeof(element));
    nouvelElement->data = valeur;
    nouvelElement->suiv = liste;

    return nouvelElement;
}


llist effacerListe(llist liste, void * (fctfree) (void *))
{
    element* tmp = liste;
    element* tmpnxt;

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
    printf("Fonction efface client");
    free(liste->mot_de_passe);
    free(liste->nom);
    free(liste->prenom);
    free(liste->adresse->rue);
    free(liste->adresse->ville);
    free(liste->adresse->pays);
    free(liste->ff);
    free(liste->message);
    free(liste->vols);

    return NULL;

}

/*
int main(int argc, char *argv[])
{
	int i;
	int n;
	char* fichier[100];
	llist liste = NULL;
	donnee a, b, c;

	a.data = 1;
	b.data = 2;
	c.data = 3;

	liste = ajouterEnTete(liste, &a);
	liste = ajouterEnTete(liste, &b);
	liste = ajouterEnTete(liste, &c);

	liste = effacerListe(liste, &freet_client);

    system("pause");
     return 0;
}
*/