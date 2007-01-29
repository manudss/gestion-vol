#include "../structure.h"
#include "chargement.h"
#include "../recherche/recherche.h"



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
    int j;
    char tmp[TAILLE_MOT + 1];
    char *tmp2;

	for (j = debut; j <= fin; j++)       // On recopie caractère par caractère
    {
        tmp[ j - debut ] = buffer[j];
    }
    tmp[ j - debut] = '\0';
    tmp2 = (char *) strdup( (char *) &tmp);				// Copie et reservation mémoire
    return tmp2;
}


/**
* @brief Chargement d'un fichier
* Charge une ligne ou TAILLE_BUFFER caractère puis l'enregistre dans une structure
* @bug affcihe deux fois la dernière ligne : probleme du qu'il a pris en compte la dernière ligne mais pas la fin du fichier, puis au prochain gets il prend la fin de fichier mais traite quand même ce qui est resté das le buffer.
*
*
*/
void * chargement(char * fichiercsv ,void * (ajout) (void *, int , void *), void * liste, void * liste2)
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
        fgets((char *) &buffer, TAILLE_BUFFER, fichier);    // récupération d'une ligne ou de TAILLE_BUFFER caractères
		numero_champ = 0;
        while (!feof(fichier))  // Continu tant qu'on est pas arrivé à la fin du fichier
        {
            buffer[0] = CVS;
            fgets( (char *) &buffer, TAILLE_BUFFER, fichier);    // récupération d'une ligne ou de TAILLE_BUFFER caractères
            if (buffer[0] != CVS)   // Cas si le premier arument est nul
            {
				debut = 0;
            	puts(buffer);
            	i = 0;
				while (i < TAILLE_BUFFER && buffer[i] != '\0')	// boucle pour sélection des mots
            	{
                	if (buffer[ i] == GUILLEMET && buffer[ i - 1] == CVS)     // si on est à la fin
                	    debut = debut + 1;
                	else if ((buffer[ i ] == CVS || buffer[ i ] == FINCVS  ) && buffer[ i - 1 ] != CVS )  // On a trouver un mot
                	{
                	    if (buffer[ i - 1 ] == GUILLEMET)     // si on est à la fin
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
					else if (buffer[ i ] == '\n') // fin de la ligne.
                	        debut = fin;
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

void * ajout_client(char* table_champ[], int nbr_champ, void * liste, void * liste2)
{
    ptr_t_client nouveau;
	llist *TDH = NULL;
	int indice;

	indice = hachage(table_champ[0]);

	TDH = (llist *) liste;

    if (table_champ[0] == NULL)   // Si le premier champ est vide on annule l'enregistrement de la ligne
		return liste;

    nouveau = (ptr_t_client) malloc(sizeof(t_client));
	strcpy(nouveau->cle, table_champ[0]);
	nouveau->mot_de_passe = table_champ[1];
    nouveau->nom = table_champ[2];
    nouveau->prenom = table_champ[3];
    nouveau->tel = atoi( table_champ[4]);
    nouveau->adresse.adresse = table_champ[5];
    nouveau->adresse.ville = table_champ[6];
    nouveau->adresse.pays = table_champ[7];


    TDH[indice] = ajouterEnTete(TDH[indice], nouveau);
    return liste;
}


void * ajout_avion(char* table_champ[], int nbr_champ, void * liste, void * liste2)
{
    ptr_t_avions nouveau;
    llist *listeavion;

	if (table_champ[0] == NULL)   // Si le premier champ est vide on annule l'enregistrement de la ligne
		return liste;

    listeavion = (llist *) liste;
    nouveau = (ptr_t_avions) malloc(sizeof(t_client));


    nouveau->capacite = (long) table_champ[1];

	strcpy(nouveau->modele, table_champ[0]);

	liste = ajouterEnTete(listeavion, nouveau);

    return liste;
}


void * ajout_destination (char* table_champ[], int nbr_champ, void * liste, void * liste2)
{
    ptr_t_destination nouveau;
    llist *listedestination;

	if (table_champ[0] == NULL)   // Si le premier champ est vide on annule l'enregistrement de la ligne
		return liste;

    listedestination = (llist) liste;
    nouveau = (ptr_t_destination) malloc(sizeof(t_destination));
	strcpy(nouveau->code, table_champ[0]);
	printf("nouveau->code : %s", nouveau->code);

    nouveau->destination = table_champ[1];
    printf("nouveau->destination : %s", nouveau->destination);
    nouveau->origine = table_champ[2];
    printf("nouveau->origine : %s", nouveau->origine);
    nouveau->distance = atoi( table_champ[2] );
    printf("nouveau->distance : %ld\n", nouveau->distance);

    DBG

	listedestination = ajouterEnTete(listedestination, nouveau);

    return listedestination;
}

void * ajout_FF (char* table_champ[], int nbr_champ, void * liste, void * liste2)
{
    llist *listeff;
    llist *TDH;
    ptr_t_client elmt;
    ptr_t_ff nouveau;
    int indice, i;
    DBG
    if (table_champ[0] == NULL)   // Si le premier champ est vide on annule l'enregistrement de la ligne
		return liste;
		DBG
    indice = hachage(table_champ[0]);
	TDH = (llist *) liste;
    DBG
    printf("ajout_FF : %ld", TDH[ indice ]);
	elmt = recherche(table_champ[0] , TDH[ indice ] , &recherch_client_par_cle);           // Recherche d'un client
    if (elmt == NULL)   // Si on a pas trouvé cette élément on arrete
		return liste;
    DBG
    nouveau = (ptr_t_ff) malloc(sizeof(t_ff));
    DBG
	strcpy(nouveau->cle, table_champ[0]);
    DBG
    nouveau->points = atoi ( table_champ[1] );
    DBG
    nouveau->km = atoi ( table_champ[2] );

    for ( i = 3; i < nbr_champ; i ++ )
    {
        DBG
        listeff = ajouterEnTete(listeff, table_champ[ i ]);
    }
    DBG
    nouveau->vols = &listeff;

    DBG

	elmt->ff = nouveau;
    DBG
    return liste;
}

void * ajout_vols_en_cours (char* table_champ[], int nbr_champ, void * liste, void * liste2)
{
    llist *listeff;
    llist *TDH;
    ptr_t_client elmt;
    ptr_t_ff nouveau;
    int indice, i;
    DBG
    if (table_champ[0] == NULL)   // Si le premier champ est vide on annule l'enregistrement de la ligne
		return liste;
		DBG
    indice = hachage(table_champ[0]);
	TDH = (llist *) liste;
    DBG
    //printf("ajout_vols : %ld\n", TDH[ indice ]);
    DBG
	elmt = recherche(table_champ[0] , TDH[ indice ] , &recherch_client_par_cle);           // Recherche d'un client
    if (elmt == NULL)   // Si on a pas trouvé cette élément on arrete
		return liste;
    DBG
    nouveau = (ptr_t_ff) malloc(sizeof(t_vols));
    DBG
	strcpy(nouveau->cle, table_champ[0]);
    DBG

    for ( i = 1; i < nbr_champ - 1; i ++ )
    {
        DBG
        listeff = ajouterEnTete(listeff, table_champ[ i ]);
    }
    DBG
    nouveau->vols = &listeff;

    DBG

	elmt->ff = nouveau;
    DBG
    return liste;
}

void * ajout_vols (char* table_champ[], int nbr_champ, void * liste, void * liste2)
{
    ptr_t_vols nouveau;
    ptr_t_vols *arbre;
    llist listedest;
    int i;
    printf("liste 2 = %ld", liste2);
    //printf("liste 2 = %ld", *liste2);
    listedest = (llist) &liste2;


	if (table_champ[0] == NULL)   // Si le premier champ est vide on annule l'enregistrement de la ligne
		return liste;

    arbre = (ptr_t_vols *) liste;
    nouveau = init_listevols ( table_champ[0] );
    DBG
    puts(nouveau->code_vol);
    for (i = 0; i < 6; i ++)  // copie de la destination qui est les 6 premières lettres du code vols
    {
        nouveau->dest[i] = table_champ[0][i];
    }
    nouveau->dest[6] = '\0';
    DBG
    puts(nouveau->dest);
    strcpy(nouveau->avion, table_champ[1] );
    nouveau->nbr_client = atoi( table_champ[2] );
    nouveau->horaire = atoi( table_champ[3] );

    for (i = 0; i < 31; i ++)  // Mise à zéro des jours seront chargé plus tard
    {
        nouveau->jour[i] = 0;
    }
    // ajout des pointeurs vers destinations
    //printf("listedest : %ld", *listedest);

    //nouveau->ptr_dest = recherche(nouveau->dest , listedest , &recherche_dest); // Recherche d'une destination pour faire le liens entres les structures


    DBG
	printf("%ld\n", *arbre);
    ajoutavl( nouveau, arbre);

    return (arbre);
}



llist *init_listeclient (void)
{
	llist *ll = NULL;
    int i;

	if ((ll = malloc(sizeof(llist) * TAILLETDH * TAILLETDH)) == NULL)
        return (NULL);
    for (i = 0; i < TAILLETDH * TAILLETDH; i ++)
    {
        ll[i] = NULL;
    }
    return (ll);
}
