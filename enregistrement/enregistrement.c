#include "../structure.h"
#include "enregistrement.h"

void enregistrement(llist listeclient[])
{
    FILE *fichier;
    int i;
    fichier = fopen ("listeclient.csv", "w+");
    printf("fichier %ld",fichier);
    if (fichier != NULL)
    {
        // fichier en tête
        fprintf(fichier,"%s;%s;","cle","mot de passe");
        fputs("nom",fichier);fprintf(fichier,";");
        fputs("prenom",fichier);fprintf(fichier,";%s;","tel");

        fputs("adresse",fichier);fprintf(fichier,";");
        fputs("ville",fichier);fprintf(fichier,";");
        fputs("pays",fichier);fprintf(fichier,";\n");

        for (i = 0; i < TAILLETDH * TAILLETDH; i ++)
        {
            if (listeclient[i] != NULL)
            {
                enregistrement2 (listeclient[i], fichier);
            }
        }
        fclose(fichier);
    }

}

void enregistrement2 (llist listeclient, FILE *fichier)
{
    llist tmp;
	tmp = listeclient;

    while(tmp != NULL)
    {
        ecrireuneligne( (ptr_t_client) listeclient->data, fichier) ;
        tmp = tmp->suiv;
    }
}

void ecrireuneligne( ptr_t_client liste, FILE *fichier)
{

     fprintf(fichier,"%s;%s;",liste->cle,liste->mot_de_passe);
     fputs(liste->nom,fichier);fprintf(fichier,";");
     fputs(liste->prenom,fichier);fprintf(fichier,";%ld;",liste->tel);

     fputs(liste->adresse.adresse,fichier);fprintf(fichier,";");
     fputs(liste->adresse.ville,fichier);fprintf(fichier,";");
     fputs(liste->adresse.pays,fichier);fprintf(fichier,";\n");

}

