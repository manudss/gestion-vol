#ifndef Interface_H
#define Interface_H

#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h> //pour strcmp..

//Struct
/////////////////////////////
typedef struct _ident_Window
{
    //pEntry:
    GtkWidget *pcle; //clé
    GtkWidget *pmdp; // mdp
    
    GtkWidget *pvalider; //bouton
    GtkWidget *pinscrire; //bouton
    
    //GtkWidget *pButton;
    GtkWidget *pTable;//table
    GtkWidget *pWindow;//FENETRE
    
    GtkWidget *pLabel_info; //label etat inscription.
    
    struct client *liste;
}Window_ident;
/////////////////////////////
typedef struct _MainWindow
{
    //Widget
    GtkWidget *pTable;//table
    GtkWidget *pWindow;//FENETRE
    GtkWidget *pImage; //image
    
    //MENU :
    GtkWidget *pMenuBar; //menu-bar
    GtkWidget *pMenu;//sous menu
    GtkWidget *pMenuItem;//item du sous menu
    
    //boutons :
    GtkWidget *pres; //reservation
    GtkWidget *pvol;//vols en cours
    GtkWidget *pff; // ff ?
    
    //label:
    GtkWidget *pLabel_bienvenue; //bienvenu GENERIQUE
    GtkWidget *pLabel_msg;
    
    struct client *liste;
    
}MainWindow;
///////////////////////////////////
typedef struct _inscrire
{
GtkWidget *pTable;//table
GtkWidget *pWindow;//FENETRE
GtkWidget *pLabel; //labels

// Gtk_Entry :
GtkWidget *pnom;
GtkWidget *pprenom;
GtkWidget *ptel;
GtkWidget *padresse;
GtkWidget *ppays;
GtkWidget *pmdp;
GtkWidget *pmdp2;

//Gtk_button :

GtkWidget *pvalider;


}InscrireWindow;

////////////////////////////////
typedef struct client //struct bidon pour tester identification ..
{
 char* cle;
 char* message;
 /*
 ...
 */
 char* mdp;
 struct client *suiv;
}client;


//protos :
void OnQuitter(GtkWidget* , gpointer);
void OnDestroy(GtkWidget* , gpointer);
 
void verif_champs(Window_ident *, Window_ident* );
 /** @function verif_champs
* @brief Recupere les deux champs et verifie qu'ils correspondent a un client (LC)
* @version 1.0
* @bug 0 -> probleme dans le cas de caractère accentué/non standarts ..
* @warning 0
* @param 1er param : je ne le comprend pas !! mais il est necessaire ! le deuxieme , donne pf .
* @return exit_success...
*
* On pourrait externaliser la partie de parcours de la liste chainée pour comparer la clé et le mdp au client...
*/

int identification(client*);
/** @function identification
* @brief fonction affichant la fenetre de connexion et callbacks
* @version 1.0
* @bug 0
* @warning 0 
* @param 1er param : recoit la liste des client de la fontion principale
* @return 0
*
* 
*/
int f_principale(client*);
/** @function f_principale
* @brief fonction affichant la fenetre principale + callbacks
* @version 1.0
* @bug 0
* @warning 0 
* @param 1er param : client* pour le message (pour l'instant!)/!\
* @return 0
*
* 
*/

const gchar* recup_chp(GtkWidget*);

void inscription(Window_ident *,Window_ident *);
#endif
