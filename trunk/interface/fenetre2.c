#include "../structure.h"
#include "interface.h"
//INSCRIPTION///////////********************************************
void inscription(Window_ident *p,Window_ident *pf1)
{
InscrireWindow *pf;

pf = g_malloc(sizeof(InscrireWindow));

llist ** ptr;
ptr=(pf1->tabDH);
pf->tabDH = ptr;
pf->arbrevol = pf1->arbrevol;
//(pf->tabDH) =(pf1->tabDH);
printf("DBG inscription \n");
/*

t_client a;

const gchar* nom;
const gchar* prenom;
long num;
const gchar* adresse;
const gchar* pays;
const gchar*mot_de_passe1;
const gchar*mot_de_passe2;

*/
gtk_init(0,0);



pf->pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_position(GTK_WINDOW(pf->pWindow), GTK_WIN_POS_CENTER);
gtk_window_set_default_size(GTK_WINDOW(pf->pWindow), 450, 600);
gtk_window_set_title(GTK_WINDOW(pf->pWindow), "AIR-EFREI : INSCRIPTION");

 /*Creation : gtkEntry*/
 pf->pnom=     gtk_entry_new ();
 pf->pprenom=  gtk_entry_new ();
 pf->ptel=     gtk_entry_new ();
 pf->padresse= gtk_entry_new ();
 pf->pville=   gtk_entry_new ();
 pf->ppays=    gtk_entry_new ();
 pf->pmot_de_passe=     gtk_entry_new ();
 pf->pmot_de_passe2=    gtk_entry_new ();

 gtk_entry_set_visibility((GtkEntry*)(pf->pmot_de_passe),FALSE);
 gtk_entry_set_visibility((GtkEntry*)(pf->pmot_de_passe2),FALSE);

 //creation bouton :
 pf->pvalider = gtk_button_new_with_label("Valider");

 /* Creation et insertion de la table 15 lignes 4 colonnes */
 pf->pTable=gtk_table_new(17,2,TRUE);
 gtk_container_add(GTK_CONTAINER(pf->pWindow), GTK_WIDGET(pf->pTable));

 /*label: Bienvenue*/ pf->pLabel_info = gtk_label_new("Merci de remplir les champs suivants pour vous inscrire.");
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pLabel_info,
 0, 2, 0, 1,
 GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,
       0, 0);

 /*label:Nom*/ pf->pLabel = gtk_label_new("Nom");
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pLabel,
 0, 1, 1, 2,
 0, 0,
       0, 0);

 /*Entry:Nom*/
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pnom,
 0, 2, 2, 3,
 GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,
       0, 0);

 /*label: Prénom*/ pf->pLabel = gtk_label_new("Prenom");
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pLabel,
 0, 1, 3, 4,
 GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,
       0, 0);

 /*Entry:Prenom*/
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pprenom,
 0, 2, 4, 5,
 GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,
       0, 0);

 /*label: tel*/ pf->pLabel = gtk_label_new("Num. de tel");
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pLabel,
 0, 1, 5, 6,
 GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,
       0, 0);

 /*Entry:tel*/
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->ptel,
 0, 2, 6, 7,
 GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,
       0, 0);

 /*label: Adresse*/ pf->pLabel = gtk_label_new("Adresse");
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pLabel,
 0, 1, 7, 8,
 GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,
       0, 0);

 /*Entry:Adresse*/
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->padresse,
 0, 2, 8, 9,
 GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,
       0, 0);

 /*label: Ville*/ pf->pLabel = gtk_label_new("Ville");
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pLabel,
 0, 1, 9, 10,
 GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,
       0, 0);

 /*Entry:Ville*/
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pville,
 0, 2, 10, 11,
 GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,
       0, 0);

 /*label: Pays*/ pf->pLabel = gtk_label_new("Pays");
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pLabel,
 0, 1, 11, 12,
 GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,
       0, 0);

 /*Entry:Pays*/
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->ppays,
 0, 2, 12, 13,
 GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,
       0, 0);

 /*label: Mdp*/ pf->pLabel = gtk_label_new("Mot de passe");
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pLabel,
 0, 1, 13, 14,
 GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,
       0, 0);
 /*label: Mdp2*/ pf->pLabel = gtk_label_new("Reecrire le mot de passe");
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pLabel,
 1, 2, 13, 14,
 GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,
       0, 0);

 /*Entry:mot_de_passe*/
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pmot_de_passe,
 0, 1, 14, 15,
 0,GTK_EXPAND | GTK_FILL,
       0, 0);
 /*Entry:mot_de_passe2*/
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pmot_de_passe2,
 1, 2, 14, 15,
 0,GTK_EXPAND | GTK_FILL,
       0, 0);

 /*Bouton: valider*/
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pvalider,
 1, 2, 15, 17,
 GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,
       30, 10);




 /*Callbacks: */
 g_signal_connect(G_OBJECT(pf->pWindow), "destroy", G_CALLBACK(OnDestroy),0);
 g_signal_connect(G_OBJECT(pf->pvalider), "clicked", G_CALLBACK(inscrire),(gpointer*) pf);

 /* Affichage de la fenetre */
 gtk_widget_show_all(pf->pWindow);

 /* Demarrage de la boucle evenementielle */
 gtk_main();
 g_free(pf);
}

