#include "../structure.h"
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


char* recup_chp(GtkWidget* chp)
{
//const gchar *txt;
char* txt;
(const gchar*)txt = gtk_entry_get_text(GTK_ENTRY(chp));

return txt;
}
//
void verif_champs(Window_ident *p, Window_ident* pf)
{
  const gchar *sText_cle,*sText_mot_de_passe;
  int i=0,j=0,k;
  t_client* ptr;
  int OK=0;
  
  //Recuperation de la cle et du mdp dans les sText_ correspondants.
  sText_cle =recup_chp(pf->pcle);
  
  sText_mot_de_passe =recup_chp(pf->pmot_de_passe);
    
  printf("cle : %s\n",sText_cle);//[CONSOLE]
  printf("mdp : %s\n",sText_mot_de_passe);//[CONSOLE]
  
//calcul de l'indice ds la TDH
i=hachage1((char*)sText_cle);
j=hachage2((char*)sText_cle);
printf("\ni=%ld; j=%ld\n",i,j);//ok

//pointeur sur listes des t_clients :

ptr= (pf->tabDH+i+j*(TAILLETDH-1));

printf("%ld",ptr);
while (ptr != 0 && OK!= 1 && (ptr->cle)!= NULL)
 {
    if(strcmp(ptr->cle,sText_cle)==0 && strcmp(ptr->mot_de_passe,sText_mot_de_passe)==0)
     {
     
     OK=1;
     printf("LE client EXISTE !!\n"); //[CONSOLE]
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
    gtk_entry_set_text((GtkEntry*)pf->pmot_de_passe,"");
    }


  
// Si oui : appel de la fonction pour la fenetre principale
if (OK==1) 
 {
  gtk_main_quit();
  f_principale(ptr);  
 }
  
}
////////////////////*******************************////////////////////////////
void inscrire(InscrireWindow *pvalider ,InscrireWindow *pf)
{
//recup champ dans tablo
 
 char* tab[9];
 
 
 ptr_t_client ptr;
 long i,j;
 
 printf("%s\n",recup_chp (pf->pprenom));
 // 0 : clé
 tab[0]=strdup(gen_cle2(recup_chp (pf->pnom), recup_chp(pf->pprenom) , (long)atoi((char*)recup_chp(pf->ptel)) , 0));
 //1 : nom
 tab[1]=strdup((const char*)recup_chp(pf->pnom));
 //printf("\nINSCRIREtab : %s\n",tab[1]);

 //2: prenom
 tab[2]=strdup((const char*)recup_chp(pf->pprenom));
 
 //3: tel
 tab[3]=strdup((const char*)recup_chp(pf->ptel));

 //4: adresse
 tab[4]=strdup((const char*)recup_chp(pf->padresse));
 //5: Ville
 
 tab[5]=strdup((const char*)recup_chp(pf->pville));
 //6: Pays 
 tab[6]=strdup((const char*)recup_chp(pf->ppays));
 //7 : mdp
 tab[7]=strdup((const char*)recup_chp(pf->pmot_de_passe));
 tab[8]=strdup((const char*)recup_chp(pf->pmot_de_passe2));

 
// BLINDAGE DE LA SAISIE ! 
 if (strcmp(tab[7],tab[8])!=0)
 {
 printf("[inscription : mot de passe different ![ERREUR]]\n");//[CONSOLE]
 //on signale le pb
    gtk_label_set_text((GtkLabel*)pf->pLabel_info,"mots de passes non-identiques!");
    //on vide les champs :
    gtk_entry_set_text((GtkEntry*)pf->pmot_de_passe,"");
    gtk_entry_set_text((GtkEntry*)pf->pmot_de_passe2,"");
 } 
 
for (i=0;i<8;i++) 
{printf("tab[%ld] : %s\n",i,tab[i]);}

 

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


/////////////////**********************************///////////////////////
int hachage1(char* sText_cle)
{
int i;
//1er caractère !
if (sText_cle[0]>=97 && sText_cle[0]<=122) //si 1er carac. minuscule
          {
          i=sText_cle[0]-97;
          }     
else if (sText_cle[0]>=65 && sText_cle[0]<=90) //MAJ
    {
    i=sText_cle[0]-65;
    }    
else i=TAILLETDH-1;

return i;
}
///////////////////
int hachage2(char* sText_cle)
{
int j;
//2ème caractère
if (sText_cle[1]>=97 && sText_cle[1]<=122) //si 1er carac. minuscule
          {
          j=sText_cle[1]-97;
          }     
else if (sText_cle[1]>=65 && sText_cle[1]<=90) //MAJ
    {
    j=sText_cle[1]-65;
    }    
else j=TAILLETDH-1;
return j;
}
