#include "interface.h"

int identification(client* tete)
{
    
    /*Declaration et initialisation fenetre */
    
    Window_ident *pf;
    GtkWidget *pLabel_cle;
    GtkWidget *pLabel_mdp;
    
    gtk_init(0,0);
    pf = g_malloc(sizeof(Window_ident));
    
    pf->pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(pf->pWindow), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(pf->pWindow), 320, 200);
    gtk_window_set_title(GTK_WINDOW(pf->pWindow), "Identification");
    
    /* CREATION */
    
    //creation zone de saisie: pour clé et mdp
    pf->pcle = gtk_entry_new_with_max_length(11); //cle limitée a 11 caracteres.
    pf->pmdp = gtk_entry_new ();
    gtk_entry_set_visibility((GtkEntry*)(pf->pmdp),FALSE);
    
    /* Creation des boutons */
    pf->pvalider= gtk_button_new_with_label("Valider");
    pf->pinscrire= gtk_button_new_with_label("S'inscrire");
    //Création Label
    pLabel_cle= gtk_label_new("Saisir cle :");
    pLabel_mdp= gtk_label_new("Saisir mot de passe");
    pf->pLabel_info= gtk_label_new("Veuillez saisir vos identifiants \n(pour tester:cle= 'a', mdp= 'a'");   
    /* Creation et insertion de la table 7 lignes 2 colonne */
    pf->pTable=gtk_table_new(6,2,TRUE);
    gtk_container_add(GTK_CONTAINER(pf->pWindow), GTK_WIDGET(pf->pTable));

    
    /*TABLE: Insertion des champs .. */
    //label explication:
    gtk_table_attach(GTK_TABLE(pf->pTable), pf->pLabel_info,
        0, 2, 0, 1,
        GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0);
    
    //label clé
    gtk_table_attach(GTK_TABLE(pf->pTable), pLabel_cle,
        0, 1, 1, 2,
        GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0);
    //champ clé    
    gtk_table_attach(GTK_TABLE(pf->pTable), pf->pcle,
        0, 2, 2, 3,
        GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0);
    //label mdp
    gtk_table_attach(GTK_TABLE(pf->pTable), pLabel_mdp,
        0, 1, 3, 4,
        GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0);
    //champ mdp
    gtk_table_attach(GTK_TABLE(pf->pTable), pf->pmdp,
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
        
    
    
    //recopie de l'adresse de la liste clients ..
    pf->liste=tete;
    
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
////////////////////////////////
int f_principale(client* client)
{
 /*Declaration et init de la fenetre .. */
 MainWindow* pf;

 gtk_init(0,0);
 
 pf = g_malloc(sizeof(MainWindow));
    
 pf->pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
 gtk_window_set_position(GTK_WINDOW(pf->pWindow), GTK_WIN_POS_CENTER);
 gtk_window_set_default_size(GTK_WINDOW(pf->pWindow), 1100, 850);
 gtk_window_maximize((GtkWindow*)pf->pWindow);
 gtk_window_set_title(GTK_WINDOW(pf->pWindow), "AIR-EFREI : INTERFACE CLIENT");
 
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
 
 //creation boutons
 pf->pres= gtk_button_new_with_label("Reserver vol");
 pf->pvol= gtk_button_new_with_label("Mes vols");
 pf->pff= gtk_button_new_with_label("FF ?");
 
 // créa pLabel
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
 //message personnalisé du client ("client.message")
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
 
 g_signal_connect(G_OBJECT(pf->pWindow), "destroy", G_CALLBACK(OnDestroy),0); 
 
 /* Affichage de la fenetre */
 gtk_widget_show_all(pf->pWindow);

 /* Demarrage de la boucle evenementielle */
 gtk_main();
 g_free(pf);
 
return EXIT_SUCCESS;
}

void inscription(Window_ident *p,Window_ident *pf1)
{
InscrireWindow *pf;

gtk_init(0,0);
 
pf = g_malloc(sizeof(InscrireWindow));
    
pf->pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_position(GTK_WINDOW(pf->pWindow), GTK_WIN_POS_CENTER);
gtk_window_set_default_size(GTK_WINDOW(pf->pWindow), 450, 600);
gtk_window_set_title(GTK_WINDOW(pf->pWindow), "AIR-EFREI : INSCRIPTION");

 /*Creation : gtkEntry*/
 pf->pnom=     gtk_entry_new ();
 pf->pprenom=  gtk_entry_new ();
 pf->ptel=     gtk_entry_new ();
 pf->padresse= gtk_entry_new ();
 pf->ppays=    gtk_entry_new ();
 pf->pmdp=     gtk_entry_new ();
 pf->pmdp2=    gtk_entry_new ();
 
 gtk_entry_set_visibility((GtkEntry*)(pf->pmdp),FALSE);
 gtk_entry_set_visibility((GtkEntry*)(pf->pmdp2),FALSE);
 
 //creation bouton :
 pf->pvalider = gtk_button_new_with_label("Valider");
 
 /* Creation et insertion de la table 15 lignes 4 colonnes */
 pf->pTable=gtk_table_new(15,2,TRUE);
 gtk_container_add(GTK_CONTAINER(pf->pWindow), GTK_WIDGET(pf->pTable));
 
 /*label: Bienvenue*/ pf->pLabel = gtk_label_new("Merci de remplir les champs suivant pour vous inscrire.");
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pLabel,
 0, 1, 0, 1,
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
 
 /*label: Pays*/ pf->pLabel = gtk_label_new("Pays");
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pLabel,
 0, 1, 9, 10,
 GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,
       0, 0);
 
 /*Entry:Pays*/ 
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->ppays,
 0, 2, 10, 11,
 GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,
       0, 0);
 
 /*label: Mdp*/ pf->pLabel = gtk_label_new("Mot de passe");
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pLabel,
 0, 1, 11, 12,
 GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,
       0, 0);
 /*label: Mdp2*/ pf->pLabel = gtk_label_new("Reecrire le mot de passe");
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pLabel,
 1, 2, 11, 12,
 GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,
       0, 0);
 
 /*Entry:Mdp*/ 
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pmdp,
 0, 1, 12, 13,
 0,GTK_EXPAND | GTK_FILL,
       0, 0);
 /*Entry:Mdp2*/ 
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pmdp2,
 1, 2, 12, 13,
 0,GTK_EXPAND | GTK_FILL,
       0, 0);
 
 /*Bouton: valider*/ 
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pvalider,
 1, 2, 13, 15,
 GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,
       30, 10);
       
 
 
 
 
 
 
 /*Callbacks: */
 g_signal_connect(G_OBJECT(pf->pWindow), "destroy", G_CALLBACK(OnDestroy),0); 
 
 /* Affichage de la fenetre */
 gtk_widget_show_all(pf->pWindow);

 /* Demarrage de la boucle evenementielle */
 gtk_main();
 g_free(pf);
}
