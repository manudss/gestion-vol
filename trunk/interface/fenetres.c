#include "../structure.h"
#include "interface.h"
#include "../temps/temps.h"
#include <time.h>

///////////////////////////////////////
int identification(llist* TDH[],ptr_t_vols *arbrevol,ptr_t_temps temps,llist destination,llist listeavion)
{
    /*Declaration et initialisation fenetre */

    Window_ident *pf;


    GtkWidget *pLabel_cle;
    GtkWidget *pLabel_mot_de_passe;


    pf = g_malloc(sizeof(Window_ident));
    pf->arbrevol = arbrevol ; //aquisition de l'arbre .
    pf->temps = temps;
    pf->destination=destination;
    pf->listeavion=listeavion;
    
    gtk_init(0,0);


    pf->pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(pf->pWindow), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(pf->pWindow), 320, 200);
    gtk_window_set_title(GTK_WINDOW(pf->pWindow), "Veuillez saisir vos identifiants");

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
    pf->pLabel_info= gtk_label_new("votre cle de client : 2 lettres nom puis prenom, 4 derniers numero du tel + 0\n exemple : NoPr12340  ");
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
///////////////// F_PRINCIPALE ////////////////////////////
int f_principale(ptr_t_client client,ptr_t_vols *arbrevol,llist** tabDH,ptr_t_temps temps,llist destination,llist listeavion)
{
 /*Declaration et init de la fenetre .. */
 MainWindow* pf;

 pf = g_malloc(sizeof(MainWindow));
 //RECOPIE CHP UTILES :
 pf->arbrevol = arbrevol;
 pf->tabDH = tabDH;
 pf->client =client;
 pf->destination = destination;
 pf->listeavion = listeavion;
 pf->temps =temps;
 DBG

 gtk_init(0,0);


 pf->pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);

 gtk_window_set_position(GTK_WINDOW(pf->pWindow),GTK_WIN_POS_NONE);
 gtk_window_set_default_size(GTK_WINDOW(pf->pWindow), 800, 800);
 gtk_window_move(GTK_WINDOW(pf->pWindow), 1, 1);
 //gtk_window_maximize((GtkWindow*)pf->pWindow);
 gtk_window_set_title(GTK_WINDOW(pf->pWindow), "AIR-EFREI : INTERFACE t_client");


 DBG
 //menu:
 pf->pMenuBar= gtk_menu_bar_new();
 pf->pMenu= gtk_menu_new();
 pf->pMenuItem= gtk_menu_item_new_with_label("Quitter");
 g_signal_connect(G_OBJECT(pf->pMenuItem), "activate", G_CALLBACK(OnQuitter), (GtkWidget*) pf->pWindow);
 gtk_menu_shell_append(GTK_MENU_SHELL(pf->pMenu), pf->pMenuItem);
 DBG
 pf->pMenuItem = gtk_menu_item_new_with_label("Fichier");
 gtk_menu_item_set_submenu(GTK_MENU_ITEM(pf->pMenuItem),pf->pMenu);
 gtk_menu_shell_append(GTK_MENU_SHELL(pf->pMenuBar), pf->pMenuItem);

 //init image:
 pf->pImage = gtk_image_new_from_file("logo2.png");

 //pf->pBox=gtk_vbox_new(FALSE,5);

 //creation boutons && heure ..
 pf->pres= gtk_button_new_with_label("Reserver vol");
 pf->pvol= gtk_button_new_with_label("Mes vols");
 pf->pff= gtk_button_new_with_label("Frequent flyer");
 pf->pafficheh=gtk_button_new_with_label("afficher\nheure");
 pf->p1h=gtk_button_new_with_label("+1h");
 pf->p1j=gtk_button_new_with_label("+1J");
 pf->pvalidh=gtk_button_new_with_label("changer\nheure");
 pf->pchph = gtk_entry_new ();
 
 DBG
 // créa pLabel
 pf->pLabel_bienvenue = gtk_label_new("Bienvenue sur votre interface client");

DBG
 /* Creation et insertion de la table 14 lignes 4 colonnes */
 pf->pTable=gtk_table_new(14,13,TRUE);
 gtk_container_add(GTK_CONTAINER(pf->pWindow), GTK_WIDGET(pf->pTable));

 /*TABLE: Insertion des champs .. */
 DBG
 //menu
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pMenuBar,
 0, 13, 0, 1,
 GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,
       0, 0);
 
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pafficheh,
 10, 11, 1, 2,
 GTK_EXPAND | GTK_FILL , GTK_EXPAND | GTK_FILL,
       0, 0);
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->p1h,
 11, 12, 1, 2,
 GTK_EXPAND | GTK_FILL , GTK_EXPAND | GTK_FILL,
       0, 0);
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->p1j,
 12, 13, 1, 2,
 GTK_EXPAND | GTK_FILL , GTK_EXPAND | GTK_FILL,
       0, 0);
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pchph,
 10, 12, 2, 3,
 GTK_EXPAND | GTK_FILL , GTK_EXPAND | GTK_FILL,
       0, 0);
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pvalidh,
 12, 13, 2, 3,
 GTK_EXPAND | GTK_FILL , GTK_EXPAND | GTK_FILL,
       0, 0);
 
 //message de Bienvenue GENERIQUE:
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pLabel_bienvenue,
 4, 9, 1, 2,
 0,0,
       0, 0);
 /*
 //message personnalisé du t_client ("t_client.message")
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pLabel_msg,
 1, 3, 2, 5,
 GTK_EXPAND | GTK_FILL , GTK_EXPAND | GTK_FILL,
        0, 0);

 */
 //image air-efrei

 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pImage,
 0, 4, 1, 6,
GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0);

 // bouton reserve vol
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pres,
 0, 3, 6, 9,
 GTK_EXPAND | GTK_FILL , GTK_EXPAND | GTK_FILL,
        15, 25);

 //bouton mes vols:
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pvol,
 0, 3, 9, 12,
 GTK_EXPAND | GTK_FILL , GTK_EXPAND | GTK_FILL,
        15, 25);
 //bouton FF: Facultatif ..
 gtk_table_attach(GTK_TABLE(pf->pTable),pf->pff,
 0, 3, 12, 15,
 GTK_EXPAND | GTK_FILL , GTK_EXPAND | GTK_FILL,
        15, 25);

 printf("[Vol ]nom client: ");
    puts(pf->client->nom);
DBG
 /*Callbacks: */

 g_signal_connect(G_OBJECT(pf->pafficheh), "clicked", G_CALLBACK(afficheh),(gpointer*) pf);
 g_signal_connect(G_OBJECT(pf->p1h), "clicked", G_CALLBACK(p1h),(gpointer*) pf);
 g_signal_connect(G_OBJECT(pf->p1j), "clicked", G_CALLBACK(p1j),(gpointer*) pf);
 g_signal_connect(G_OBJECT(pf->pvalidh), "clicked", G_CALLBACK(validh),(gpointer*) pf);
 
 g_signal_connect(G_OBJECT(pf->pff), "clicked", G_CALLBACK(WFF),(gpointer*) pf);
 g_signal_connect(G_OBJECT(pf->pres), "clicked", G_CALLBACK(vols),(gpointer*) pf);
 g_signal_connect(G_OBJECT(pf->pvol), "clicked", G_CALLBACK(affiche_vols),(gpointer*) pf);
 g_signal_connect(G_OBJECT(pf->pWindow), "destroy", G_CALLBACK(OnDestroy),0);
 
 
DBG

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
char label[300];

cpt=0;

printf("\nENTREE DANS VOLS");
pf = (VolsWindow*)g_malloc(sizeof(VolsWindow));

//=>passage d'éléments ..
pf->arbrevol = pf1->arbrevol;
pf->tabDH = pf1->tabDH;
pf->client =pf1->client;
pf->temps = pf1->temps;
pf->destination = pf1->destination;

pf->nbr = nbr_elmt(pf->arbrevol);
printf("pf->nbr de champ %ld\n",pf->nbr);
pf->tab = (ptr_t_vols*) malloc(sizeof( ptr_t_vols ) * pf->nbr);//
parcourttotab( pf->arbrevol, pf->tab, &n);


pf->pChoix = (GtkWidget**)g_malloc(sizeof(GtkWidget)* (pf->nbr)+1);
pf->pLabel2 = (GtkWidget**)g_malloc(sizeof(GtkWidget)* (pf->nbr));

gtk_init(0,0);
pf->pWindow= gtk_window_new(GTK_WINDOW_TOPLEVEL);
//pf->pWindow =gtk_scrolled_window_new(NULL,NULL);
//gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)pf->pWindow,pf->pTable);

gtk_window_set_position(GTK_WINDOW(pf->pWindow), GTK_WIN_POS_CENTER);
gtk_window_move(GTK_WINDOW(pf->pWindow), 300, 300);
gtk_window_set_default_size(GTK_WINDOW(pf->pWindow), 660, 530);
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
     printf("------------------    Fenetre : pf->tab[i]->code_vols  %s------------", pf->tab[i]->dest);
     DBG
     strcpy(label,g_locale_to_utf8((const gchar *) affichevols(pf->destination, pf->tab[i]),-1,NULL,NULL,NULL));
     DBG
     strcat(label,pf->tab[i]->code_vol);
     DBG
     *(pf->pLabel2+i)=gtk_label_new(label) ;
     //*(pf->pLabel2+i)=gtk_label_new(pf->tab[i]->code_vol) ;

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

 //printf("\ni : %ld\t cpt : %ld\n",i,cpt);


 g_free(pf);

}//FIN VOLS /////////////



