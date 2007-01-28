#ifndef PILE_H
# define PILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DBG printf("DEBUG File: %s Line:%d \n",__FILE__,__LINE__);
#define TAILLETDH 27

/** @struct  t_adresse
* @brief Structure d'une adresse
* @version 1.0
* @bug Y a pas
* @warning Y a pas
* @param
*
*/

typedef struct t_adresse
{

	char *adresse;  // le nom de la rue
	char *ville; // la ville
	char *pays; //le pays

}t_adresse;


 /** @struct  t_client
* @brief Structure d'un client
* @version 1.0
* @bug Y a pas
* @warning Y a pas
* @param
*
*/

typedef struct t_client
{
    char cle[11];   // Les Deux premières lettres du prénom + les deux premières du nom + 4 derniers chiffres du numéro de tél +  FF si frequent flyer NN si non fréquent Flyer + 1 chiffre pour éviter les doublons
	char *mot_de_passe;  // le mot de passe pour la gestion (pointeur)

	//Etats civil
	char *nom; 								// le nom du client
	char *prenom; 							// le prénom du client
	long tel; 								//numéro de téléphone
	struct t_adresse adresse;				// L'adresse du client
	char *message; 							// les messages éventuels pour le client
	// Compagnie
	struct t_ff *ff;						// Liens vers Fréquent Flyer, NULL si pas fréquent flyer
	struct t_historique_vols *vols;						// Liens vers l'historique des vols en cours , NULL si aucun vols

}t_client;

typedef t_client* ptr_t_client;

typedef struct t_ff* ptr_t_ff;

 /** @struct  t_ff
* @brief Structure pour les fréquent flyer
* @version 1.0
* @bug Y a pas
* @warning Y a pas
* @param
*
*/

typedef struct t_ff
{
    char cle[11];   // Les Deux premières lettres du prénom + les deux premières du nom + 4 derniers chiffres du numéro de tél +  FF si frequent flyer NN si non fréquent Flyer + 1 chiffre pour éviter les doublons
	long points;  // Les points Fréquent Flyer acumulé
	long km;  // Les kilomètres éffectués
	struct t_historique_vols *vols;  // Pointeur vers une liste chainée des vols éffectués

}t_ff;

/** @struct  t_vols_cours
* @brief Structure pour les vols_en_cours
* @version 1.0
* @bug Y a pas
* @warning Y a pas
* @param
*
*/

typedef struct t_vols_cours
{
    char cle[11];   // Les Deux premières lettres du prénom + les deux premières du nom + 4 derniers chiffres du numéro de tél +  FF si frequent flyer NN si non fréquent Flyer + 1 chiffre pour éviter les doublons
	struct t_historique_vols *vols;  // Pointeur vers une liste chainée des vols éffectués
}t_vols_cours;

 /** @struct  t_historique_vols
* @brief liste chainée de vols
* @version 1.0
* @bug Y a pas
* @warning Y a pas
* @param
*
*/

typedef struct t_historique_vols
{
    char num_vol[12];   // le numéro de vol (desorihhmm) + jour

}t_historique_vols;

 /** @struct  t_avions
* @brief liste chainée des avions
* @version 1.0
* @bug Y a pas
* @warning Y a pas
* @param
*
*/

typedef struct t_avions
{
    char modele[4];   	// le modèle de l'avion A380; B747; .....
	long capacite;		// Le nombre de siege dans l'avion
	long autonomie;		// L'autonomie de l'avion ( le nombre de kilomètre maximale)
}t_avions;

typedef t_avions* ptr_t_avions;  // pointeur vers un avion

/** @struct  t_destination
* @brief liste chainée des destinations
* @version 1.0
* @bug Y a pas
* @warning Y a pas
* @param
*
*/

typedef struct t_destination
{
    char code[6];   	// le code de destination : 3 premières lettres de la destination + 3 premières lettres de l'origine
	char *destination;	// Le nom de la destination
	char *origine;		// Le nom de l'origine
	long distance;		// La distance entre les deux

}t_destination;


typedef t_destination* ptr_t_destination;  // pointeur vers une destination


 /** @struct  t_liste_client
* @brief liste chainée des clients pour un vol rangé par jour.
* @version 1.0
* @bug Y a pas
* @warning Y a pas
* @param
*
*/

typedef struct t_liste_client
{
    char cle_clent[9];   	// le numéro de clé du client
	// suiv
    struct t_liste_client *suiv; 					//cellule suivante

}t_liste_client;

typedef t_liste_client* ptr_t_liste_client;  // pointeur vers un avion

/** @struct  t_vols
* @brief arbres ordonée lexicographiquement des vols
* @version 1.0
* @bug Y a pas
* @warning Y a pas
* @param
*
*/

typedef struct t_vols
{
    char code_vol[10]; // Le code correespondant au vol c'est à partir ce code qu'est rangé l'arbre AVL
	char dest[6]; // Le code correspondant à la destination
	ptr_t_destination ptr_dest;  // pointeur vers la destination
	char avion[4]; // Le code correspondant à l'avion
	ptr_t_avions* ptr_avion;  // pointeur vers l'avion
	// donnée complémentaire
	int horaire; // l'horaire du vol
	int prix; // le prix du vol

	ptr_t_liste_client jour[31];  // un tableau de pointeur chaque case corresepond à un jour du mois et pointe vers la liste des passager
	int nbr_client;  // le nombre de client ayant déjà réserver ce vol
	// arbres AVL
    struct t_vols *fd; 	//fils droit
    struct t_vols *fg; 	//fils gauche
	int balance;

}t_vols;

typedef t_vols* ptr_t_vols;  // pointeur vers un vols

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
    struct element *suiv;
};

typedef struct donnee
{
    long data;
}donnee;

typedef element* llist;

/** @struct  strucutre
* @brief Une union permettant de stocké n'importe quel pointeur de structure
*
* @param
*
*/
union listeuniversel {
llist  listechaine;

} listeuniversel;
#endif
