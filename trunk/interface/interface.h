#ifndef Interface_H
#define Interface_H

#include <gtk/gtk.h>
 //pour strcmp..

//Struct
/////////////////////////////
typedef struct _ident_Window
{
    
    //pEntry:
    GtkWidget *pcle; //clé
    GtkWidget *pmot_de_passe; // mdp
    
    GtkWidget *pvalider; //bouton
    GtkWidget *pinscrire; //bouton
    
    //GtkWidget *pButton;
    GtkWidget *pTable;//table
    GtkWidget *pWindow;//FENETRE
    
    GtkWidget *pLabel_info; //label etat inscription.
    
     llist** tabDH;
}Window_ident;
/////////////////////////////
typedef struct _MainWindow
{
    //Widget
    GtkWidget *pTable;//table
    GtkWidget *pWindow;//FENETRE
    GtkWidget *pImage; //image
    GtkWidget *pScrollbar;
    GtkWidget *pBox;
    //MENU :
    GtkWidget *pMenuBar; //menu-bar
    GtkWidget *pMenu;//sous menu
    GtkWidget *pMenuItem;//item du sous menu
    
    //boutons :
    GtkWidget *pres; //reservation
    GtkWidget *pvol;//vols en cours
    GtkWidget *pff; // ff ?
    
    //label:
    GtkWidget *pLabel_bienvenue; //bienvenue GENERIQUE
    GtkWidget *pLabel_msg;
    
//    struct t_client *liste;
    
}MainWindow;
///////////////////////////////////
typedef struct _inscrire
{
GtkWidget *pTable;//table
GtkWidget *pWindow;//FENETRE
GtkWidget *pLabel; //labels
GtkWidget *pLabel_info;

// Gtk_Entry :
GtkWidget *pnom;
GtkWidget *pprenom;
GtkWidget *ptel;
GtkWidget *padresse;
GtkWidget *pville;
GtkWidget *ppays;
GtkWidget *pmot_de_passe;
GtkWidget *pmot_de_passe2;

//Gtk_button :

GtkWidget *pvalider;
 
llist** tabDH;

}InscrireWindow;
//////////////////VOLS/////////////////////
typedef struct _vols
{
GtkWidget *pWindow;//FENETRE
GtkWidget *pLabel; //labels
GtkWidget *pTable; //table

GtkWidget *pChoix[];//tableau de pointeur de boutons

//GtkWidget *pScrollbar;//scrollbar

}VolsWindow;

///////////////////protos : ///////////////////////////////////////
int hachage1(char*);
int hachage2(char*);
///
void OnQuitter(GtkWidget* , gpointer);
void OnDestroy(GtkWidget* , gpointer);
 
void verif_champs(Window_ident *, Window_ident* );
 /** @function verif_champs
* @brief Recupere les deux champs et verifie qu'ils correspondent a un t_client (LC)
* @version 1.0
* @bug 0 -> probleme dans le cas de caractère accentué/non standarts ..
* @warning 0
* @param 1er param : je ne le comprend pas !! mais il est necessaire ! le deuxieme , donne pf .
* @return exit_success...
*
* On pourrait externaliser la partie de parcours de la liste chainée pour comparer la clé et le mdp au t_client...
*/

int identification(llist** );
/** @function identification
* @brief fonction affichant la fenetre de connexion et callbacks
* @version 1.0
* @bug 0
* @warning 0 
* @param 1er param : recoit la liste des t_client de la fontion principale
* @return 0
*
* 
*/
void inscrire(InscrireWindow *,InscrireWindow *);

int f_principale(ptr_t_client);
/** @function f_principale
* @brief fonction affichant la fenetre principale + callbacks
* @version 1.0
* @bug 0
* @warning 0 
* @param 1er param : t_client* pour le message (pour l'instant!)/!\
* @return 0
*
* 
*/
void vols(Window_ident *p,Window_ident *pf1);

char* recup_chp(GtkWidget*);
void inscription(Window_ident *,Window_ident *);
//EXTERNES :

char* gen_cle2(char* , char* , long , long );
void * ajout_client(char* table_champ[], int , void * );
llist ajouterEnTete(llist , void * );

#endif
