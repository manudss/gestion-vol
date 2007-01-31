#include "../structure.h"
#include "interface.h"
///////////////////////////////////////
int identification(llist* TDH[])
{
    /*Declaration et initialisation fenetre */
    
    Window_ident *pf;
    
    GtkWidget *pLabel_cle;
    GtkWidget *pLabel_mot_de_passe;
    
    gtk_init(0,0);
    pf = g_malloc(sizeof(Window_ident));
    
    pf->pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(pf->pWindow), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(pf->pWindow), 320, 200);
    gtk_window_set_title(GTK_WINDOW(pf->pWindow), "Identification");
    
    /* CREATION */
    
    //creation zone de saisie: pour cl� et mot_de_passe
    pf->pcle = gtk_entry_new_with_max_length(11); //cle limit�e a 11 caracteres.
    pf->pmot_de_passe = gtk_entry_new ();
    gtk_entry_set_visibility((GtkEntry*)(pf->pmot_de_passe),FALSE);
    
    /* Creation des boutons */
    pf->pvalider= gtk_button_new_with_label("Valider");
    pf->pinscrire= gtk_button_new_with_label("S'inscrire");
    //Cr�ation Label
    pLabel_cle= gtk_label_new("Saisir cle :");
    pLabel_mot_de_passe= gtk_label_new("Saisir mot de passe");
    pf->pLabel_info= gtk_label_new("Veuillez saisir vos identifiants ");   
    /* Creation et insertion de la table 7 lignes 2 colonne */
    pf->pTable=gtk_table_new(6,2,TRUE);
    gtk_container_add(GTK_CONTAINER(pf->pWindow), GTK_WIDGET(pf->pTable));

    
    /*TABLE: Insertion des champs .. */
    //label explication:
    gtk_table_attach(GTK_TABLE(pf->pTable), pf->pLabel_info,
        0, 2, 0, 1,
        GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0);
    
    //label cl�
    gtk_table_attach(GTK_TABLE(pf->pTable), pLabel_cle,
        0, 1, 1, 2,
        GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0);
    //champ cl�    
    gtk_table_attach(GTK_TABLE(pf->pTable), pf->pcle,
        0, 2, 2, 3,
        GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0);
    //label mdp
    gtk_table_attach(GTK_TABLE(pf->pTable), pLabel_mot_de_passe,
        0, 1, 3, 4,
        GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0);
    //champ mdp
    gtk_table_attach(GTK_TABLE(pf->pTable), pf->pmot_de_passe,
        0, 2, 4, 5,
        GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0);
    
    //bouton valider..
    gtk_table_attach(GTK_TABLE(pf->pTable), pf->pvalider,
        1, 2, 5, 6,
        0, GTK_EXPAND,
        0, 0);
        
    //bouton inscription
    gtk_table_attach(GTK_TABLE(pf->pTable), pf->pinscrire,
        0, 1, 5, 6,
        0, GTK_EXPAND,
        0, 0);
        
    
    //printf("%s",(TDH[0][0]).cle);
    //recopie de l'adresse de la TDH dans struct pf
    
    
    pf->tabDH = TDH;

        
    //On lance les CALLBACKS :
    //g_signal_connect(G_OBJECT(pf->pcle), "activate", G_CALLBACK(get_pEntry),(gpointer) pf); => je ne sais pas a quoi sa sert ! :)
    
    g_signal_connect(G_OBJECT(pf->pvalider), "clicked", G_CALLBACK(verif_champs),(gpointer*) pf);
    g_signal_connect(G_OBJECT(pf->pinscrire), "clicked", G_CALLBACK(inscription),(gpointer*) pf);
    g_signal_connect(G_OBJECT(pf->pWindow), "destroy", G_CALLBACK(OnDestroy),0);
    

    ///
    /* Affichage de la fenetre */
    gtk_widget_show_all(pf->pWindow);

    /* Demarrage de la boucle evenementielle */
    gtk_main();
    
    g_free(pf);

    return EXIT_SUCCESS;
}
/////////////////////////////////////////////
int f_principale(ptr_t_client client)
{
 /*Declaration et init de la fenetre .. */
 MainWindow* pf;

 gtk_init(0,0);
 
 pf = g_malloc(sizeof(MainWindow));   
 pf->pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
 
 
 
 gtk_window_set_position(GTK_WINDOW(pf->pWindow), GTK_WIN_POS_CENTER);
 gtk_window_set_default_size(GTK_WINDOW(pf->pWindow), 1100, 850);
 gtk_window_maximize((GtkWindow*)pf->pWindow);
 gtk_window_set_title(GTK_WINDOW(pf->pWindow), "AIR-EFREI : INTERFACE t_client");
 
 
 
 
 //menu:
 pf->pMenuBar= gtk_menu_bar_new();
 pf->pMenu= gtk_menu_new();
 pf->pMenuItem= gtk_menu_item_new_with_label("Quitter");
 g_signal_connect(G_OBJECT(pf->pMenuItem), "activate", G_CALLBACK(OnQuitter), (GtkWidget*) pf->pWindow);
 gtk_menu_shell_append(GTK_MENU_SHELL(pf->pMenu), pf->pMenuItem);
 
 pf->pMenuItem = gtk_menu_item_new_with_label("Fichier");
 gtk_menu_item_set_submenu(GTK_MENU_ITEM(pf->pMenuItem),pf->pMenu);
 gtk_menu_shell_append(GTK_MENU_SHELL(pf->pMenuBar), pf->pMenuItem);
 
 //init image:
 pf->pImage = gtk_image_new_from_file("logo2.png");
 
 pf->pBox=gtk_vbox_new(FALSE,5);
 
 //creation boutons
 pf->pres= gtk_button_new_with_label("Reserver vol");
 pf->pvol= gtk_button_new_with_label("Mes vols");
 pf->pff= gtk_button_new_with_label("FF ?");
 
 // cr�a pLabel
 pf->pLabel_bienvenue = gtk_label_new("Bienvenue sur votre interface client");
 pf->pLabel_msg = gtk_label_new(client->message);
 
 /* Creation et insertion de la table 14 lignes 4 colonnes */
 pf->pTable=gtk_table_new(14,4,TRUE);
 gtk_container_add(GTK_CONTAINER(pf->pWindow), GTK_WIDGET(pf->pTable));
 
 /*TABLE: Insertion des champs .. */
 
 //menu
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pMenuBar,
 0, 4, 0, 1,
 GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,
       0, 0);
 
 //message de Bienvenue GENERIQUE:
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pLabel_bienvenue,
 1, 3, 1, 2,
 0,0,
       0, 0);
 //message personnalis� du t_client ("t_client.message")
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pLabel_msg,
 1, 3, 2, 5,
 GTK_EXPAND | GTK_FILL , GTK_EXPAND | GTK_FILL,
        0, 0);
 
 //image air-efrei
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pImage,
 0, 1, 1, 6,
GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0);
 // bouton reserve vol
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pres,
 0, 1, 6, 9,
 GTK_EXPAND | GTK_FILL , GTK_EXPAND | GTK_FILL,
        15, 25);
 
 //bouton mes vols:
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pvol,
 0, 1, 9, 12,
 GTK_EXPAND | GTK_FILL , GTK_EXPAND | GTK_FILL,
        15, 25);
 //bouton FF: Facultatif ..
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pff,
 0, 1, 12, 15,
 GTK_EXPAND | GTK_FILL , GTK_EXPAND | GTK_FILL,
        15, 25);
 
    

 /*Callbacks: */
 
 g_signal_connect(G_OBJECT(pf->pres), "clicked", G_CALLBACK(vols),(gpointer*) pf);
 g_signal_connect(G_OBJECT(pf->pWindow), "destroy", G_CALLBACK(OnDestroy),0); 
 
 
 /* Affichage de la fenetre */
 gtk_widget_show_all(pf->pWindow);

 /* Demarrage de la boucle evenementielle */
 gtk_main();
 g_free(pf);
 
return EXIT_SUCCESS;
}
//INSCRIPTION///////////********************************************
void inscription(Window_ident *p,Window_ident *pf1)
{
InscrireWindow *pf;

pf = g_malloc(sizeof(InscrireWindow));

llist ** ptr;
ptr=(pf1->tabDH);
pf->tabDH = ptr;

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
       
 /*label: Pr�nom*/ pf->pLabel = gtk_label_new("Prenom");
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

///////////////////VOL ///////////////////////
void vols(MainWindow *p,MainWindow *pf1)
{
VolsWindow *pf;
int n=34,i;
char * nom=".!.";


pf = (VolsWindow*)g_malloc(sizeof(VolsWindow));
(pf->pChoix) = (GtkWidget**)g_malloc(sizeof(GtkWidget)* n);
//pf->pLabel = (GtkWidget**)g_malloc(sizeof(GtkWidget)* n);

gtk_init(0,0);

pf->pWindow= gtk_window_new(GTK_WINDOW_TOPLEVEL);
//pf->pWindow =gtk_scrolled_window_new(NULL,NULL);
//gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)pf->pWindow,pf->pTable);

gtk_window_set_position(GTK_WINDOW(pf->pWindow), GTK_WIN_POS_CENTER);
gtk_window_set_default_size(GTK_WINDOW(pf->pWindow), 800, 200);
gtk_window_set_resizable((GtkWindow*)pf->pWindow,FALSE);
gtk_window_set_title(GTK_WINDOW(pf->pWindow), "AIR-EFREI : Reservation Vols");
pf->pScrollbar = gtk_scrolled_window_new(NULL, NULL);

//gtk_container_add(GTK_CONTAINER(pf->pWindow),pf->pScrollbar);


 /* Creation et insertion de la table */
 pf->pTable2 = gtk_table_new(n,5,TRUE);
 gtk_container_add(GTK_CONTAINER(pf->pWindow), GTK_WIDGET(pf->pTable2));
 gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(pf->pScrollbar), pf->pTable2);
 
/*
     gtk_table_attach(GTK_TABLE(pf->pTable2),pf->pLabel,
     0, 4, i, i+1,
     GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,
           0, 0);
 
*/ 
 
 // Boucle cr�ation table ...
 for (i=0;i<n;i++)
     {
     pf->pChoix[i] = gtk_button_new_with_label("Choisir");
     
     /*label: vol*/ pf->pLabel = gtk_label_new(nom);
     gtk_table_attach(GTK_TABLE(pf->pTable2),pf->pLabel,
     0, 4, i, i+1,
     GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,
           0, 0);
     
     // bouton reservation vol
     gtk_table_attach(GTK_TABLE(pf->pTable2),pf->pChoix[i],
     4, 5, i, i+1,
     GTK_EXPAND | GTK_FILL , GTK_EXPAND | GTK_FILL,
            15, 25);
     
     }
 
 
 
 /*Callbacks: */
 g_signal_connect(G_OBJECT(pf->pWindow), "destroy", G_CALLBACK(OnDestroy),0); 
 
 /* Affichage de la fenetre */
 gtk_widget_show_all(pf->pWindow);

 /* Demarrage de la boucle evenementielle */
 gtk_main();
 g_free(pf);
printf("5\n");
}
