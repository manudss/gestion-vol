#ifndef Interface_H
#define Interface_H

#include <gtk/gtk.h>
#include "../structure.h"
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
    ptr_t_vols *arbrevol;
    
    ptr_t_client client;
    llist** tabDH;
    ptr_t_temps temps;
    llist destination;
    llist listeavion;
}Window_ident;
/////////////////////////////
typedef struct _MainWindow
{
    int sec;
    
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
        //pr l'h:
    GtkWidget *pafficheh;
    GtkWidget *p1h;
    GtkWidget *p1j;
    GtkWidget *pvalidh;
    GtkWidget *pchph;
    
    //label:
    GtkWidget *pLabel_bienvenue; //bienvenue GENERIQUE
    GtkWidget *pLabel_msg;
    
    ptr_t_vols *arbrevol;
    ptr_t_client client;
    llist** tabDH;
    ptr_t_temps temps;
    llist destination;
    llist listeavion;
    
}MainWindow;

/////////////INSCRIRE//////////////////////
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

ptr_t_temps temps;
t_client* client;
ptr_t_vols *arbrevol;
llist** tabDH;
llist destination;
llist listeavion;

}InscrireWindow;
//////////////////VOLS/////////////////////
typedef struct _vols
{
int i;
int nbr;
GtkWidget *pWindow;//FENETRE
//GtkScrolledWindow *pSWindow;

GtkWidget *pLabel; //labels
GtkWidget **pLabel2; //tableau de labels

GtkWidget *pTable; //table


GtkWidget** pChoix;//tableau de pointeur de boutons

GtkWidget *pScrollbar;//scrollbar

ptr_t_vols *arbrevol;
llist** tabDH;
t_client* client;
ptr_t_temps temps;
ptr_t_vols *tab;
llist destination;

}VolsWindow;

/////////////Temps ///////
typedef struct choix_jour
{
int jour;

GtkWidget *pWindow;

GtkWidget *pLabel;
GtkWidget *pTable;
GtkWidget *pJour; 
GtkWidget *pCombo;


t_client* client;
ptr_t_vols *arbrevol;
llist** tabDH;
ptr_t_temps temps;

ptr_t_vols vol;

}JourWindow;

////////////////AFFICHE_VOLS //////////////////
typedef struct affiche_vol
{


GtkWidget *pWindow;
int nbr;

GtkWidget **pLabel2;
GtkWidget *pTable;
GtkWidget **pSuppr; 
GtkWidget *pScrollbar;

//ptr_t_vols *arbrevol;
llist** tabDH;
ptr_t_client client;
ptr_t_temps temps;
llist destination;

}Affiche_vol_Window;
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

int identification(llist** ,ptr_t_vols *arbrevol,ptr_t_temps temps,llist destination,llist listeavion);
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

int f_principale(ptr_t_client,ptr_t_vols *arbrevol,llist** tabDH,ptr_t_temps temps,llist destination,llist listeavion);
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
void vols(MainWindow *p,MainWindow *pf1);

char* recup_chp(GtkWidget*);
void inscription(Window_ident *,Window_ident *);
//EXTERNES :

char* gen_cle2(char* , char* , long , long );
void * ajout_client(char* table_champ[], int , void * );
llist ajouterEnTete(llist , void * );
void clic (GtkWidget* ,VolsWindow* n);//fct
int choix_jour(VolsWindow* pf1,ptr_t_vols vol);//fenetre
void clic_choix_jour (GtkWidget* a,JourWindow* pf);//fct
void affiche_vols(MainWindow* a, MainWindow* pf1); //fenetre
void clic_suppr(GtkWidget* a, Affiche_vol_Window* pf); //fct
//heures
void afficheh(MainWindow *a, MainWindow *pf); //fct
void p1h (MainWindow *a, MainWindow *pf);//fct
void p1j (MainWindow *a, MainWindow *pf); //fct
void validh (MainWindow *a, MainWindow *pf); //fct

//GtkWidget* affiche_vol(GtkWidget*);

#endif
