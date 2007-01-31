#include "../structure.h"
#include "interface.h"
#include "../recherche/recherche.h"

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


char* recup_chp(GtkWidget* chp)
{
//const gchar *txt;
char* txt;
(const gchar*)txt = gtk_entry_get_text(GTK_ENTRY(chp));

return txt;
}

////////////////////
void verif_champs(Window_ident *p, Window_ident* pf)
{
  const gchar *sText_cle,*sText_mot_de_passe;
  int i=0,j=0,k;
  ptr_t_client client;
  int OK=0;
  
  //Recuperation de la cle et du mdp dans les sText_ correspondants.
  sText_cle =recup_chp(pf->pcle);
  
  sText_mot_de_passe =recup_chp(pf->pmot_de_passe);
  printf("cle : %s\n",sText_cle);//[CONSOLE]
  printf("mdp : %s\n",sText_mot_de_passe);//[CONSOLE]
  
client =(ptr_t_client) recherche((void*)sText_cle ,(llist) pf->tabDH[ hachage((char*)sText_cle) ] , &recherch_client_par_cle);

printf("MOT DE PASSE ??\n%s\n%s",pf->pmot_de_passe,client->mot_de_passe);
if(client != 0 && strcmp(sText_mot_de_passe,client->mot_de_passe)==0 )
     {
     
     OK=1;
     printf("LE client EXISTE !!\n"); //[CONSOLE]
     gtk_label_set_text((GtkLabel*)pf->pLabel_info,"LOGIN OK");
     }


if (OK==0)
    {
    printf("Le client n'existe pas ..\n");//[CONSOLE]
    //on signale le pb
    gtk_label_set_text((GtkLabel*)pf->pLabel_info,"Erreur d'authentification!\n Veuillez vous inscrire!");
    //on vide les champs:
    gtk_entry_set_text((GtkEntry*)pf->pcle,"");
    gtk_entry_set_text((GtkEntry*)pf->pmot_de_passe,"");
    }


  
// Si oui : appel de la fonction pour la fenetre principale
if (OK==1) 
 {
  gtk_main_quit();
  f_principale(client,pf->arbrevol);  
 }
  
}

////////////////////*******************************////////////////////////////
void inscrire(InscrireWindow *pvalider ,InscrireWindow *pf)
{
//recup champ dans tablo
 
 char* tab[9];
 
 
 ptr_t_client ptr;
 long i,j=0,ERR=0;
 
 printf("%s\n",recup_chp (pf->pprenom));
 // 0 : clé
 tab[0]=strdup(gen_cle2(recup_chp (pf->pnom), recup_chp(pf->pprenom) , (long)atoi((char*)recup_chp(pf->ptel)) , 0));
 //1 : nom
 tab[2]=strdup((const char*)recup_chp(pf->pnom));
 //printf("\nINSCRIREtab : %s\n",tab[1]);

 //2: prenom
 tab[3]=strdup((const char*)recup_chp(pf->pprenom));
 
 //3: tel
 tab[4]=strdup((const char*)recup_chp(pf->ptel));

 //4: adresse
 tab[5]=strdup((const char*)recup_chp(pf->padresse));
 //5: Ville
 
 tab[6]=strdup((const char*)recup_chp(pf->pville));
 //6: Pays 
 tab[7]=strdup((const char*)recup_chp(pf->ppays));
 //7 : mdp
 tab[1]=strdup((const char*)recup_chp(pf->pmot_de_passe));
 tab[8]=strdup((const char*)recup_chp(pf->pmot_de_passe2));

 for(i=0;i<8;i++)
 {
 while (j<strlen(tab[i]))
     {
     j++;
     if((tab[i][j])==';'||(tab[i][j])== '"'  )
         {
         printf("ERREUR! [inscription]: mauvais caractere insere !\n");
         ERR=1;
         }
     } 
 
 if(ERR==1)
     {
        //on signale le pb
        gtk_label_set_text((GtkLabel*)pf->pLabel_info,"Veuillez entrez des caracteres alphanumeriques !");
        //on vide les champs :
        //gtk_entry_set_text((GtkEntry*)pf->pmot_de_passe,"");
        //gtk_entry_set_text((GtkEntry*)pf->pmot_de_passe2,"");
     } 
 } 
 
// BLINDAGE DE LA SAISIE ! 
 if (strcmp(tab[1],tab[8])!=0)
 {
 printf("[inscription : mot de passe different ![ERREUR]]\n");//[CONSOLE]
 //on signale le pb
    gtk_label_set_text((GtkLabel*)pf->pLabel_info,"mots de passes non-identiques!");
    //on vide les champs :
    gtk_entry_set_text((GtkEntry*)pf->pmot_de_passe,"");
    gtk_entry_set_text((GtkEntry*)pf->pmot_de_passe2,"");
 } 
 
for (i=0;i<9;i++) 
{printf("tab[%ld] : %s\n",i,tab[i]);}

ajout_client(tab, 8 , pf->tabDH);
/*
//calcul de l'indice ds la TDH
i=hachage1(tab[0]);
j=hachage2(tab[0]);
printf("\ni=%ld; j=%ld\n",i,j);//ok
ptr= (pf->pf1->tabDH+i+j*(TAILLETDH-1));

//appel ajout client
//ajout_client(tab[8], 8, ptr);

*/
}


void clic (GtkWidget* a,VolsWindow* pf)
{
int i=0,btn=-1;

//printf("\ni = %ld",pf->i);
for(i=0;i<pf->nbr;i++)
    {
    if(gtk_toggle_button_get_active (pf->pChoix[i])!=0)
    btn = i;
    }
}



