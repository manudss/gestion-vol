#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "liste.h"

#define TAILLE_MOT 50	// Taille d'un mot pour la copie chaine au dela de cette limite le mot entier ne sera pas pris en compte, prendre un nombre suffisament grand
#define TAILLE_BUFFER 1000	// Taille du buffer, qui récupérera une ligne sur le fichier texte, prendre un nombre suffisament grand
#define TAILLE_TABLEAU_CHAMP 500	// Taille du tableau du champ, contenant les champs d'un ligne du fichier texte avant d'êtres ajouter dans la structure correspondante
#define CVS ','	// Séparations des champs
#define FINCVS '\n'	// Fin d'une ligne
#define GUILLEMET '"'	// Fin d'une ligne



/**
* @brief fonction permettant de copier un morceau de chaine, dans un tableau de char.
* Copie chaque case du premier indice de debut, jusqu'à l'indice de fin, puis fais une reservation mémoire.
* @version 1.0.5
* @bug testé sans problème
*
* @param debut	l'indice de début de la chaine
* @param fin	l'indice de la fin de la chaine
* @param buffer[]	Tableau contenant la chaine à copier
* @return tmp2	un poineteur vers la chaine de caractère copié
*/

char* copie_chaine(int debut, int fin,char buffer[])
{
    int taille;
    int j;
    char tmp[TAILLE_MOT + 1];
    char *tmp2;

	for (j = debut; j <= fin; j++)       // On recopie caractère par caractère
    {
        tmp[ j - debut ] = buffer[j];
    }
    tmp[ j - debut] = '\0';
    tmp2 = (char *) strdup(&tmp);				// Copie et reservation mémoire
    return tmp2;
}


/**
* @brief Chargement d'un fichier
* Charge une ligne ou TAILLE_BUFFER caractère puis l'enregistre dans une structure
* @bug affcihe deux fois la dernière ligne : probleme du qu'il a pris en compte la dernière ligne mais pas la fin du fichier, puis au prochain gets il prend la fin de fichier mais traite quand même ce qui est resté das le buffer.
*
*
*/
void * chargement(char * fichiercsv ,void * (ajout) (void *, int , void *), void * liste)
{
    FILE* fichier = NULL;
    char  buffer[TAILLE_BUFFER];					// Le buffer qui prend une ligne
    char *tableau_champ[TAILLE_TABLEAU_CHAMP];		// Tableau contenant les mots d'un champ
    int debut, fin, numero_champ;
    int i;


    fichier = fopen(fichiercsv, "r");
    if (fichier != NULL)
    {
        printf("Chargement du fichier, veuillez patienter ...\n");
        fgets(&buffer, TAILLE_BUFFER, fichier);    // récupération d'une ligne ou de TAILLE_BUFFER caractères
		numero_champ = 0;
        while (!feof(fichier))  // Continu tant qu'on est pas arrivé à la fin du fichier

        {
            //buffer[0] = '\0';
            fgets(&buffer, TAILLE_BUFFER, fichier);    // récupération d'une ligne ou de TAILLE_BUFFER caractères
            debut = 0;
            puts(buffer);
            i = 0;
            while (i < TAILLE_BUFFER && buffer[i] != '\0')	// boucle pour sélection des mots
            {
                if (buffer[ i] == GUILLEMET && numero_champ == 0)     // si on est à la fin
                    debut = debut + 1;
                else if (buffer[ i ] == CVS || buffer[ i ] == FINCVS )  // On a trouver un mot
                {
                    fin = i - 1;  // on enregistre la fin, moins la virgule
                    if (buffer[ i - 1 ] == GUILLEMET && numero_champ != 0)     // si on est à la fin
                        fin = i - 2;  // on enregistre la fin, moins la virgule et le guillemet de fin
                    else
                        fin = i - 1;  // on enregistre la fin, moins la virgule
					tableau_champ[numero_champ] = copie_chaine(debut, fin, buffer);  // on copie la chaine, dans le tableau
                    puts(tableau_champ[numero_champ]);
					numero_champ++;
					debut = i + 1;
					if (buffer[ i ] == '\n') // fin de la ligne.
                        debut = fin;
                }
                i++;
            }
            if ( debut != fin ) // Cela veut dire qu'il reste reste un morceau de texte, qui n'a pas été pris en compte
            {
                fseek(fichier, - (TAILLE_BUFFER - debut - 1) * sizeof(char), SEEK_CUR);     // On revient en arrière
            }
            else                // On a lu une ligne on peut donc l'ajouter
            {
                liste = ajout (tableau_champ, numero_champ, liste);
                numero_champ = 0; // on réinitialise le tableau champ
            }
        }
		fclose(fichier);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier %s\n", fichiercsv );
    }


    return liste;
}

// ---------------------- Fonctions d'ajout  ---------------------------------------------//

void * ajout_client(char* table_champ[], int nbr_champ, void * liste)
{
    ptr_t_client nouveau;
    llist listeclient;

    listeclient = (llist) liste;

    nouveau = (ptr_t_client) malloc(sizeof(t_client));
	strcpy(nouveau->cle, table_champ[0]);
	nouveau->mot_de_passe = table_champ[1];
    nouveau->nom = table_champ[2];
    nouveau->prenom = table_champ[3];
    nouveau->tel = atoi( table_champ[4]);
    nouveau->adresse.num = atoi( table_champ[5] );
    nouveau->adresse.rue = table_champ[6];
    nouveau->adresse.code_postal = atoi( table_champ[7] );
    nouveau->adresse.ville = table_champ[8];
    nouveau->adresse.pays = table_champ[9];

	liste = ajouterEnTete(listeclient, nouveau);

    return liste;
}

//TODO  finir cette fonction
void * ajout_avion(char* table_champ[], int nbr_champ, void * liste)
{
    ptr_t_avions nouveau;
    llist listeavion;
    DBG
    listeavion = (llist) liste;

    nouveau = (ptr_t_client) malloc(sizeof(t_client));
	strcpy(nouveau->modele, table_champ[0]);

    nouveau->capacite = atoi( table_champ[1]);
    nouveau->autonomie = atoi( table_champ[2] );

    DBG

	liste = ajouterEnTete(listeavion, nouveau);

    return liste;
}
