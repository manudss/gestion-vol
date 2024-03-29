#include "../structure.h"
#include "interface.h"
#include "../recherche/recherche.h"
#include "../liste/liste.h"

/////////////////HEURE FCT PRINCIPALE //////////////////////
void afficheh(MainWindow *a, MainWindow *pf)
{
gtk_entry_set_text (pf->pchph, g_locale_to_utf8((const gchar*) quelheure(pf->temps,pf->tabDH,pf->arbrevol,pf->listeavion, pf->destination), -1, NULL, NULL, NULL ));
}

void p1h (MainWindow *a, MainWindow *pf)
{

gtk_entry_set_text (pf->pchph,g_locale_to_utf8((const gchar *) ajoutertemps(pf->temps,60*60,pf->tabDH,pf->arbrevol,pf->listeavion, pf->destination),-1,NULL,NULL,NULL));
}


void p1j (MainWindow *a, MainWindow *pf)
{
gtk_entry_set_text (pf->pchph,g_locale_to_utf8((const gchar *) ajoutertemps(pf->temps,60*60*24,pf->tabDH,pf->arbrevol,pf->listeavion, pf->destination),-1,NULL,NULL,NULL));
}

void validh (MainWindow *a, MainWindow *pf)
{
char * tps;
long itps;
tps = recup_chp(pf->pchph);
itps=atoi(tps);
ajoutertemps(pf->temps,itps,pf->tabDH,pf->arbrevol,pf->listeavion, pf->destination);

}

//////////////FIN HEURE FCT_PRINCIPALE

void inscription_info(GtkWidget *pBtn, gpointer pf)
{
    GtkWidget *pAbout;

    // Creation de la boite de message 
    //Type : Information -> GTK_MESSAGE_INFO 
    // Bouton : 1 OK -> GTK_BUTTONS_OK 
    pAbout = gtk_message_dialog_new (GTK_WINDOW(pf),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "Votre nouvelle clef est: %s\ Merci de la conserver",
        pf);

    // Affichage de la boite de message 
    gtk_dialog_run(GTK_DIALOG(pAbout));

    // Destruction de la boite de message 
    gtk_widget_destroy(pAbout);
}


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
  int OK=0;
  
  //Recuperation de la cle et du mdp dans les sText_ correspondants.
  sText_cle =recup_chp(pf->pcle);
  
  sText_mot_de_passe =recup_chp(pf->pmot_de_passe);
  printf("cle : %s\n",sText_cle);//[CONSOLE]
  printf("mdp : %s\n",sText_mot_de_passe);//[CONSOLE]
  
pf->client =(ptr_t_client) recherche((void*)sText_cle ,(llist) pf->tabDH[ hachage((char*)sText_cle) ] , &recherch_client_par_cle);

//printf("MOT DE PASSE ??\n%s\n%s",pf->pmot_de_passe,pf->client->mot_de_passe);
if(pf->client != 0 && strcmp(sText_mot_de_passe,pf->client->mot_de_passe)==0)
     {
     DBG
     OK=1;
     printf("LE client EXISTE !!\n"); //[CONSOLE]
     //gtk_label_set_text((GtkLabel*)pf->pLabel_info,"LOGIN OK");
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
 //
// gtk_main_quit();
 f_principale(pf->client,pf->arbrevol,pf->tabDH,pf->temps, pf->destination, pf->listeavion);
 gtk_widget_destroy(pf->pWindow);
   
 }
  
}

////////////////////*************INSCRIRE******************////////////////////////////
void inscrire(InscrireWindow *pvalider ,InscrireWindow *pf)
{
//recup champ dans tablo
 
 char* tab[9];
 
 
 ptr_t_client ptr;
 long i,j=0,ERR=0;
 
 //printf("%s\n",recup_chp (pf->pprenom));
 // 0 : cl�
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
     if((tab[i][j])==';'||(tab[i][j])== '"' )
         {
         printf("ERREUR! [inscription]: mauvais caractere insere !\n");
         ERR=1;
         }
     } 
 
 if(ERR==1)
     {
        //on signale le pb
        gtk_label_set_text((GtkLabel*)pf->pLabel_info,"Veuillez entrez des caracteres alphanumeriques !");
        if (pf->pnom == "" || pf->ptel ==0 || pf->pprenom == "")
        {
        printf("\n!erreur inscrire : chp non renseigne");
        gtk_label_set_text((GtkLabel*)pf->pLabel_info,"Veuillez saisir les chp nom prenom et tel!");
        }    
        
        
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
 
for (i=0;i<9;i++) //affiche le nveau client
{
printf("tab[%ld] : %s\n",i,tab[i]);
}

ajout_client(tab, 8 , pf->tabDH);

//inscription_info(0, tab[0] );
 
 gtk_widget_destroy(pf->pWindow);

identification(pf->tabDH,pf->arbrevol,pf->temps,pf->destination,pf->listeavion);
}

/////////////////CLIC VOLS////////////
void clic (GtkWidget* a,VolsWindow* pf)
{
    int i=0,btn=-1;
    
    //printf("\ni = %ld",pf->i);
    DBG
    while (btn == -1 && i < pf->nbr)
    {
        if(gtk_toggle_button_get_active (pf->pChoix[i])!=0) 
        {
        
            btn = i;
            
        }    
        if (btn != -1)
                {     
                   
                   choix_jour(pf, pf->tab[btn]);
                }      
        i++;
    }

}

////////CHOIX JOUR ////////////
void clic_choix_jour (GtkWidget* a,JourWindow* pf)
{
    int i=0,btn=-1;
    
    
    gtk_widget_destroy(pf->pWindow);
    btn =gtk_combo_box_get_active(pf->pCombo);
    printf("\nCHOIX JOUR : temps :%ld",&(pf->temps));
    enregistrement_vols ( pf->client,pf->vol, btn, &(pf->temps));
  DBG  
}
////////CHOIX suppr ////////////
void clic_suppr(GtkWidget* a, Affiche_vol_Window* pf)
{
    int btn=-1;
    int i=0;
    DBG
    //printf("\npf->pLabel2[%ld]:%s|",btn,pf->pLabel2[1]);
    gtk_widget_destroy(pf->pWindow);
    DBG
    char * codevol;
    DBG
    printf("\npf->nbr:%ld",pf->nbr);
    while (btn == -1 && i < pf->nbr)
    {
        if(gtk_toggle_button_get_active (pf->pSuppr[i])!=0)
        { 
                DBG
                printf("\nLE BOUTON %ld EST CLICKE",i);
                btn = i;
        }    
        if (btn != -1)
                {     

                   DBG
                   printf(" Suppr clic_suppr : %ld",btn);
                   btn = btn+1;
                   DBG
                   pf->client->vols = effacervol(pf->client->vols, btn);
                   DBG
                   
                   if (pf->client->ff != 0)
                   {
                       
                       if ( pf->client->ff->points != 0)
                       { 
                            DBG
                            pf->client->ff->points -= 100;                  
                       }
                   }        
                   
                }      
        DBG
        i++;
    }

}
