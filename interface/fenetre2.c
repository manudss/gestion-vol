#include "../structure.h"
#include "interface.h"


//////////affiche_vol /////////////
void affiche_vols(MainWindow* a, MainWindow* pf1)
{
    
    Affiche_vol_Window *pf;
     DBG  
    
    int i=0;
    int cpt;
    int n=0;
    cpt=0;
    char label[400];

    llist ptr;
    

    
    printf("\nENTREE DANS AFFICHE VOL\n");
    pf = (Affiche_vol_Window*)g_malloc(sizeof(Affiche_vol_Window));
    
    //=>passage d'�l�ments ..
    
    //pf->arbrevol = pf1->arbrevol;
    pf->tabDH = pf1->tabDH;
    
    pf->client =pf1->client;
    
    printf("[affiche vol ]nom client:");
    puts(pf->client->nom);
    pf->temps = pf1->temps;
    pf->destination = pf1->destination;
    
    
    ptr = pf->client->vols;
    DBG
    
    while(ptr!=NULL)
    {
        //printf("i :%ld; ptr->suiv : %ld\n",i, ptr);
        ptr=ptr->suiv;
        DBG
        i++;
        printf("boucle compte_elt: affiche :%ld",i);
        DBG
    }
    DBG
        
    
    
    pf->pSuppr = (GtkWidget**)g_malloc(sizeof(GtkWidget)* i);
    pf->pLabel2 = (GtkWidget**)g_malloc(sizeof(GtkWidget)* i);
    DBG
    gtk_init(0,0);
    pf->pWindow= gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //pf->pWindow =gtk_scrolled_window_new(NULL,NULL);
    //gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)pf->pWindow,pf->pTable);
    
    gtk_window_set_position(GTK_WINDOW(pf->pWindow), GTK_WIN_POS_CENTER);
    gtk_window_move(GTK_WINDOW(pf->pWindow), 300, 300);
    gtk_window_set_default_size(GTK_WINDOW(pf->pWindow), 660, 530);
    //gtk_window_set_resizable((GtkWindow*)pf->pWindow,FALSE);
    gtk_window_set_title(GTK_WINDOW(pf->pWindow), "AIR-EFREI : Vos vols reserv�s");
    //pf->pScrollbar = gtk_scrolled_window_new(NULL, NULL);
    
    //gtk_container_add(GTK_CONTAINER(pf->pWindow),pf->pScrollbar);
    
     /* Creation et insertion de la table */
     pf->pTable = gtk_table_new(i,5,FALSE);
     gtk_container_add(GTK_CONTAINER(pf->pWindow), GTK_WIDGET(pf->pTable));
     //gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(pf->pScrollbar), pf->pTable);
    
    ptr = pf->client->vols;
     // Boucle cr�ation table ...
     DBG
     for (cpt=0;cpt<i;cpt++)
         {
         //Boutons
         pf->pSuppr[i] = gtk_toggle_button_new_with_label("Supprimer");
         
         
         //labels ..
         strcpy(label,g_locale_to_utf8((const gchar *) affichevols(pf->destination, ptr->data),-1,NULL,NULL,NULL));
              DBG
         strcat(label,ptr->data);
         
         pf->pLabel2[i]=gtk_label_new(g_locale_to_utf8((const gchar *) label,-1,NULL,NULL,NULL)) ;
          
            //pf->pLabel2[i]=gtk_label_new("test") ;               
         ptr=ptr->suiv;
    
         /*label: vol*/
         gtk_table_attach(GTK_TABLE(pf->pTable),pf->pLabel2[i],
         0, 4, cpt, cpt+1,
         GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,
               0, 0);
    
         // bouton reservation vol
         gtk_table_attach(GTK_TABLE(pf->pTable),pf->pSuppr[i],
         4, 5, cpt, cpt+1,
         GTK_EXPAND | GTK_FILL , GTK_EXPAND | GTK_FILL,
                15, 25);
    
    
         }
    
    
    DBG
     /*Callbacks: */
    //printf("\n[AFFICHE]pf->pLabel2[0]:%s|",(pf->pLabel2[0]));
    for(cpt=0; cpt< i; cpt++)
     {
      g_signal_connect(G_OBJECT(pf->pSuppr[i]), "clicked", G_CALLBACK(clic_suppr),(gpointer*) pf);
     }
     
     g_signal_connect(G_OBJECT(pf->pWindow), "destroy", G_CALLBACK(OnDestroy),0);
     
    DBG
    
     /* Affichage de la fenetre */
     gtk_widget_show_all(pf->pWindow);
    
     /* Demarrage de la boucle evenementielle */
     gtk_main();
    
     
     g_free(pf);
    
  
}//Fin affiche_vol


///////////////////////////////

//////////////////CHOIX JOUR ///////////////////////////
int choix_jour(VolsWindow* pf1,ptr_t_vols vol)
{
    /*Declaration et initialisation fenetre */
    int k;
    JourWindow *pf;
    
    pf = g_malloc(sizeof(JourWindow));
    
    pf->temps=pf1->temps;
    //tmp.courant = time(NULL);
    
    pf->arbrevol = pf1->arbrevol;
    pf->client = pf1->client;
    pf->tabDH = pf1->tabDH;
    pf->vol = vol;
    DBG
    
    gtk_init(0,0);


    pf->pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(pf->pWindow), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(pf->pWindow), 100 , 170);
    gtk_window_set_title(GTK_WINDOW(pf->pWindow), "Choix Jour");

    /* CREATION */

    //crea combobox
    pf->pCombo = gtk_combo_box_new_text();
    //pf->pJour = gtk_combo_box_new_text();
    DBG
    for (k=1;k<=31;k++)
    {
        
        gtk_combo_box_insert_text((GtkComboBox*) pf->pCombo,k, g_locale_to_utf8((const gchar*) date(pf->temps,k), -1, NULL, NULL, NULL ));
    }    
    
    

    /* Creation des boutons */
    
    
    //Cr�ation Label
    pf->pLabel= gtk_label_new("Selectionez le jour de votre vol");
    
    /* Creation et insertion de la table 7 lignes 2 colonne */
    pf->pTable=gtk_table_new(3,2,TRUE);
    gtk_container_add(GTK_CONTAINER(pf->pWindow), GTK_WIDGET(pf->pTable));

    DBG
    /*TABLE: Insertion des champs .. */
    //label explication:
    gtk_table_attach(GTK_TABLE(pf->pTable), pf->pLabel,
        0, 2, 0, 1,
        GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0);
    
        
    gtk_table_attach(GTK_TABLE(pf->pTable), pf->pCombo,
        0, 2, 1, 2,
        GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0);

    /*
    gtk_table_attach(GTK_TABLE(pf->pTable), pf->pValider,
        1, 2, 2, 3,
        GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0);

    */
    
    //On lance les CALLBACKS :
    
   DBG
    
    g_signal_connect(G_OBJECT(pf->pWindow), "destroy", G_CALLBACK(OnDestroy),0);
    g_signal_connect(G_OBJECT(pf->pCombo), "changed", G_CALLBACK(clic_choix_jour),(gpointer*) pf);

    ///
    /* Affichage de la fenetre */
    DBG
    gtk_widget_destroy(pf1->pWindow);
    gtk_widget_show_all(pf->pWindow);

    /* Demarrage de la boucle evenementielle */
    gtk_main();

    g_free(pf);

    return EXIT_SUCCESS;
}//Fin tps






//INSCRIPTION///////////********************************************
void inscription(Window_ident *p,Window_ident *pf1)
{
InscrireWindow *pf;

pf = g_malloc(sizeof(InscrireWindow));

llist ** ptr;
ptr=(pf1->tabDH);
pf->tabDH = ptr;
pf->arbrevol = pf1->arbrevol;
pf->temps =pf1->temps;
pf->client = pf1->client;
pf->destination =pf1->destination;
pf->listeavion = pf1-> listeavion;

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
 gtk_widget_destroy(pf1->pWindow); //destruction fenetre parent
 gtk_widget_show_all(pf->pWindow);

 /* Demarrage de la boucle evenementielle */
 gtk_main();
 g_free(pf);
}

