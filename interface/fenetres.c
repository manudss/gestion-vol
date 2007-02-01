#include "../structure.h"
#include "interface.h"
///////////////////////////////////////
int identification(llist* TDH[],ptr_t_vols *arbrevol)
{
    /*Declaration et initialisation fenetre */

    Window_ident *pf;

    GtkWidget *pLabel_cle;
    GtkWidget *pLabel_mot_de_passe;


    pf = g_malloc(sizeof(Window_ident));
    pf->arbrevol = arbrevol ; //aquisition de l'arbre .
    gtk_init(0,0);


    pf->pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(pf->pWindow), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(pf->pWindow), 320, 200);
    gtk_window_set_title(GTK_WINDOW(pf->pWindow), "Identification");

    /* CREATION */

    //creation zone de saisie: pour clé et mot_de_passe
    pf->pcle = gtk_entry_new_with_max_length(11); //cle limitée a 11 caracteres.
    pf->pmot_de_passe = gtk_entry_new ();
    gtk_entry_set_visibility((GtkEntry*)(pf->pmot_de_passe),FALSE);

    /* Creation des boutons */
    pf->pvalider= gtk_button_new_with_label("Valider");
    pf->pinscrire= gtk_button_new_with_label("S'inscrire");
    //Création Label
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
int f_principale(ptr_t_client client,ptr_t_vols *arbrevol,llist** tabDH)
{
 /*Declaration et init de la fenetre .. */
 MainWindow* pf;

 pf = g_malloc(sizeof(MainWindow));
 //RECOPIE CHP UTILES :
 pf->arbrevol = arbrevol;
 pf->tabDH = tabDH;
 pf->client =client;
 
 gtk_init(0,0);


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
 //pf->pImage = gtk_image_new_from_file("logo2.png");

 pf->pBox=gtk_vbox_new(FALSE,5);

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
 //message personnalisé du t_client ("t_client.message")
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pLabel_msg,
 1, 3, 2, 5,
 GTK_EXPAND | GTK_FILL , GTK_EXPAND | GTK_FILL,
        0, 0);

 //image air-efrei
/*
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pImage,
 0, 1, 1, 6,
GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0);
*/ 
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

///////////////////VOLS ///////////////////////
void vols(MainWindow *p,MainWindow *pf1)
{
VolsWindow *pf;
int i;
int cpt;
int n=0;

cpt=0;

printf("\nENTREE DANS VOLS");
pf = (VolsWindow*)g_malloc(sizeof(VolsWindow));
//passage d'éléments ..
pf->arbrevol = pf1->arbrevol;
pf->tabDH = pf1->tabDH;
pf->client =pf1->client;


pf->nbr = nbr_elmt(pf->arbrevol);
printf("pf->nbr de champ %ld\n",pf->nbr);
pf->tab = (ptr_t_vols) malloc(sizeof( ptr_t_vols ) * pf->nbr);
parcourttotab( pf->arbrevol, pf->tab, &n);


pf->pChoix = (GtkWidget**)g_malloc(sizeof(GtkWidget)* (pf->nbr)+1);
pf->pLabel2 = (GtkWidget**)g_malloc(sizeof(GtkWidget)* (pf->nbr));

gtk_init(0,0);
pf->pWindow= gtk_window_new(GTK_WINDOW_TOPLEVEL);
//pf->pWindow =gtk_scrolled_window_new(NULL,NULL);
//gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)pf->pWindow,pf->pTable);

gtk_window_set_position(GTK_WINDOW(pf->pWindow), GTK_WIN_POS_CENTER);
gtk_window_move(GTK_WINDOW(pf->pWindow), 500, 400);
gtk_window_set_default_size(GTK_WINDOW(pf->pWindow), 900, 600);
//gtk_window_set_resizable((GtkWindow*)pf->pWindow,FALSE);
gtk_window_set_title(GTK_WINDOW(pf->pWindow), "AIR-EFREI : Reservation Vols");
pf->pScrollbar = gtk_scrolled_window_new(NULL, NULL);

gtk_container_add(GTK_CONTAINER(pf->pWindow),pf->pScrollbar);

 /* Creation et insertion de la table */
 pf->pTable = gtk_table_new(pf->nbr,5,TRUE);
 gtk_container_add(GTK_CONTAINER(pf->pWindow), GTK_WIDGET(pf->pTable));
 gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(pf->pScrollbar), pf->pTable);


 // Boucle création table ...
 for (i=0;i<pf->nbr;i++)
     {
     //Boutons
     pf->pChoix[i] = gtk_toggle_button_new_with_label("Choisir");

     //labels ..
     *(pf->pLabel2+i)=gtk_label_new(pf->tab[i]->code_vol) ;

     /*label: vol*/
     gtk_table_attach(GTK_TABLE(pf->pTable),pf->pLabel2[i],
     0, 4, i, i+1,
     GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,
           0, 0);

     // bouton reservation vol
     gtk_table_attach(GTK_TABLE(pf->pTable),pf->pChoix[i],
     4, 5, i, i+1,
     GTK_EXPAND | GTK_FILL , GTK_EXPAND | GTK_FILL,
            15, 25);


     }



 /*Callbacks: */

for(i=0; i< pf->nbr; i++)
 {
  g_signal_connect(G_OBJECT(pf->pChoix[i]), "clicked", G_CALLBACK(clic),(gpointer*) pf);
 }

 //g_signal_connect(G_OBJECT(pf->pChoix[1]), "clicked", G_CALLBACK(clic),&cpt);
 
 g_signal_connect(G_OBJECT(pf->pWindow), "destroy", G_CALLBACK(OnDestroy),0);
 


 /* Affichage de la fenetre */
 gtk_widget_show_all(pf->pWindow);

 /* Demarrage de la boucle evenementielle */
 gtk_main();

 printf("\ni : %ld\t cpt : %ld\n",i,cpt);


 g_free(pf);

}//FIN VOLS /////////////

//////////////Temps /////////////:
int choix_jour(VolsWindow* pf1,int i)
{
    /*Declaration et initialisation fenetre */
    
    JourWindow *pf;
    pf = g_malloc(sizeof(JourWindow));
    
    pf->arbrevol = pf1->arbrevol;
    pf->client = pf1->client;
    pf->tabDH = pf1->tabDH;

    
    
    
    
    gtk_init(0,0);


    pf->pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(pf->pWindow), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(pf->pWindow), 100 , 170);
    gtk_window_set_title(GTK_WINDOW(pf->pWindow), "Choix Jour");

    /* CREATION */

    //creation zone de saisie: pour clé et mot_de_passe
    pf->pJour = gtk_entry_new_with_max_length(2); 
    

    /* Creation des boutons */
    pf->pValider= gtk_button_new_with_label("Valider");
    
    //Création Label
    pf->pLabel= gtk_label_new("Dans combien de jour souhaitez vous prendre le vol?");
    
    /* Creation et insertion de la table 7 lignes 2 colonne */
    pf->pTable=gtk_table_new(3,2,TRUE);
    gtk_container_add(GTK_CONTAINER(pf->pWindow), GTK_WIDGET(pf->pTable));


    /*TABLE: Insertion des champs .. */
    //label explication:
    gtk_table_attach(GTK_TABLE(pf->pTable), pf->pLabel,
        0, 2, 0, 1,
        GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0);
    
        
    gtk_table_attach(GTK_TABLE(pf->pTable), pf->pJour,
        0, 1, 1, 2,
        GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0);

    gtk_table_attach(GTK_TABLE(pf->pTable), pf->pValider,
        1, 2, 2, 3,
        GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0);


    //On lance les CALLBACKS :
    
    //g_signal_connect(G_OBJECT(pf->pvalider), "clicked", G_CALLBACK(verif_champs),(gpointer*) pf);
    //g_signal_connect(G_OBJECT(pf->pinscrire), "clicked", G_CALLBACK(inscription),(gpointer*) pf);
    g_signal_connect(G_OBJECT(pf->pWindow), "destroy", G_CALLBACK(OnDestroy),0);


    ///
    /* Affichage de la fenetre */
    gtk_widget_show_all(pf->pWindow);

    /* Demarrage de la boucle evenementielle */
    gtk_main();

    g_free(pf);

    return EXIT_SUCCESS;
}//Fin tps

