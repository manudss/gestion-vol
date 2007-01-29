#ifndef CHARGEMENT_H
#define CHARGEMENT_H


#include "../liste/liste.h"
#include "../avl/avl.h"


#define TAILLE_MOT 50	// Taille d'un mot pour la copie chaine au dela de cette limite le mot entier ne sera pas pris en compte, prendre un nombre suffisament grand
#define TAILLE_BUFFER 1000	// Taille du buffer, qui récupérera une ligne sur le fichier texte, prendre un nombre suffisament grand
#define TAILLE_TABLEAU_CHAMP 500	// Taille du tableau du champ, contenant les champs d'un ligne du fichier texte avant d'êtres ajouter dans la structure correspondante
#define CVS ';'	// Séparations des champs
#define FINCVS '\n'	// Fin d'une ligne
#define GUILLEMET '"'	// Fin d'une ligne

//protos :
char* copie_chaine(int debut, int fin,char buffer[]);
void *chargement(char * fichiercsv ,void * (ajout) (void *, int , void *), void * liste, void * liste2);
void * ajout_client(char* table_champ[], int nbr_champ, void * liste, void * liste2);
void * ajout_avion(char* table_champ[], int nbr_champ, void * liste, void * liste2);
void * ajout_destination (char* table_champ[], int nbr_champ, void * liste, void * liste2);
void * ajout_FF (char* table_champ[], int nbr_champ, void * liste, void * liste2);
void * ajout_vols_en_cours (char* table_champ[], int nbr_champ, void * liste, void * liste2);
void * ajout_vols (char* table_champ[], int nbr_champ, void * liste, void * liste2);
llist *init_listeclient (void);


#endif

