#include "interface.h"
void OnDestroy(GtkWidget* widget, gpointer data)
{
//arret boucle evenementielle :
gtk_main_quit();
}
void OnQuitter(GtkWidget* widget, gpointer data)
{
    GtkWidget *pQuestion;

    pQuestion = gtk_message_dialog_new(GTK_WINDOW(data),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "Voulez vous vraiment\n"
        "quitter le programme?");

    switch(gtk_dialog_run(GTK_DIALOG(pQuestion)))
    {
        case GTK_RESPONSE_YES:
            gtk_main_quit();
            break;
        case GTK_RESPONSE_NONE:
        case GTK_RESPONSE_NO:
            gtk_widget_destroy(pQuestion);
            break;
    }
}


const gchar* recup_chp(GtkWidget* chp)
{
const gchar *txt;

txt = gtk_entry_get_text(GTK_ENTRY(chp));

return txt;
}

void verif_champs(Window_ident *p, Window_ident* pf)
{
  const gchar *sText_cle,*sText_mdp;
  client *ptr;
  int OK=0; 
  
  //Recuperation de la cle et du mdp dans les sText_ correspondants.
  sText_cle =recup_chp(pf->pcle);
  
  sText_mdp =recup_chp(pf->pmdp);
    
  printf("cle : %s\n",sText_cle);//[CONSOLE]
  printf("mdp : %s\n",sText_mdp);//[CONSOLE]
  
// Verifier si les 2 champs correspondent
ptr=(pf->liste);
  
if(ptr != NULL)
{
 while (ptr != NULL && OK!= 1)
 {
    if(strcmp(ptr->cle,sText_cle)==0 && strcmp(ptr->mdp,sText_mdp)==0)
     {
     OK=1;
     printf("LE CLIENT EXISTE !!\n"); //[CONSOLE]
     gtk_label_set_text((GtkLabel*)pf->pLabel_info,"LOGIN OK");
     }
    else ptr=ptr->suiv;
 }
if (OK==0)
    {
    printf("Le client n'existe pas ..\n");//[CONSOLE]
    //on signale le pb
    gtk_label_set_text((GtkLabel*)pf->pLabel_info,"Erreur d'authentification!\n Veuillez vous inscrire!");
    //on vide les champs :
    gtk_entry_set_text((GtkEntry*)pf->pcle,"");
    gtk_entry_set_text((GtkEntry*)pf->pmdp,"");
    }

}
  
// Si oui : appel de la fonction pour la fenetre principale
if (OK==1) 
 {
  gtk_main_quit();
  f_principale(ptr);  
 }
  
}




