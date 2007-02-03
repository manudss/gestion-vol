#include <math.h>
#include "../structure.h"
#include "../recherche/recherche.h"


// adresse de la case d'un client
// adresse de la case d'un vols
// et le jour.(en int )
//


int enregistrement_vols ( ptr_t_client client, ptr_t_vols vol, int lejour, ptr_t_temps temps, ptr_t_destination listedest)
{

        DBG
    t_temps tmp;


    char codevol[100];
    char chartabjour[10];
    char *jour= NULL;
    int tabjour;

    
    tmp.courant = temps->courant;
    tabjour = (lejour + temps->jour) %31;
    printf("tabjour : %ld", tabjour);
    DBG
    vol->jour[tabjour].liste_client = ajouterEnTete(vol->jour[tabjour].liste_client, client->cle);
    DBG
    vol->jour[tabjour].nbr_client ++;
    DBG
    strcpy(codevol, vol->code_vol);
    printf("\nJour [enregistrement_vol] :%ld\n",lejour+1);
    jour = date (temps, lejour+1);


    DBG
    itoa(tabjour, chartabjour, 10);
    DBG
    strcat(codevol,chartabjour);

    DBG

    DBG

    itoa(tabjour, chartabjour, 10);
    strcat(codevol,chartabjour);

    strcat(codevol, "  ->  le ");
    DBG
    strcat(codevol, jour);
    jour = strdup(codevol);

    client->vols = ajouterEnTete(client->vols, jour);

    printf("\nENREGISTREMENT VOL [OK] %s", jour);
    return 1;
}


void effacementjour (ptr_t_vols vol, ptr_t_temps temps , ptr_t_client TDH[])
{
    char *cle;
    ptr_t_vols ptrvol;

    //ptrvol
    if( vol != NULL)
	 {
		effacementjour(vol->fg, temps, TDH);
        //effacementvolsclient(TDH,  ); // effacement dans la liste des vols en cours du client
        //effacement de la liste entière
        //vol->jour[temps->jour] = effacerListe(lvol->jour[temps->jour], &generic)
		effacementjour(vol->fd, temps, TDH);

	 }
    //while (ptrvol->jour

}


void effacementvolsclient(ptr_t_client client, char * code)
{

    effacerelmt(client->vols, code);

    if (client->ff != NULL) // si il le client est fréquent Flyer
    {
        client->ff->vols = ajouterEnTete(client->ff->vols, code);
        // mise à jour du client

    }

}

void effacementclientvols(ptr_t_vols arbre)
{
    return NULL;
}

char * affichevols (llist listedestination, ptr_t_vols levol)
{
    char * chaine1=NULL;
    char chaine[300]="Vol à destination : ";
    char dest[7];
    char horaire[6];
    ptr_t_destination tmp=NULL;
    printf("--------------------- code destintation -----------------");
    dest[0] = levol->code_vol[0];
    dest[1] = levol->code_vol[1];
    dest[2] = levol->code_vol[2];
    dest[3] = levol->code_vol[3];
    dest[4] = levol->code_vol[4];
    dest[5] = levol->code_vol[5];
    dest[6] = '\0';
    horaire[0] = levol->code_vol[6];
    horaire[1] = levol->code_vol[7];
    horaire[2] = ':';
    horaire[3] = levol->code_vol[8];
    horaire[4] = levol->code_vol[9];
    horaire[5] = '\0';
    puts(dest);
    // recherche destination
    tmp = recherche(dest , listedestination , &recherche_dest);
    if (tmp  != NULL )   // codedestination variable contenant le code de la destination : (par ex :"lonpar").
    {  
        DBG
        puts(tmp->destination);  
        DBG                                                                        //listedestination la liste chainée des destinations
      strcat(chaine, tmp->destination );
      DBG
      strcat(chaine, "\t\t Au départ de " );
      DBG
      strcat(chaine, tmp->origine );
      DBG
    }
    strcat(chaine, "\nHoraire :\t");
    DBG
    strcat(chaine, horaire );
    DBG
    strcat(chaine, "\n\t\t\t\tNuméro du vol : " );
    DBG
    chaine1 = strdup(chaine);
    return chaine1;
}
