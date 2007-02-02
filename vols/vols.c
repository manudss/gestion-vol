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
    char *codevol[100];
    char chartabjour[10];
    char *jour= NULL;
    int tabjour;


    tmp.courant = temps->courant;
    tabjour = (lejour + temps->jour) %31;
    vol->jour[tabjour].liste_client = ajouterEnTete(vol->jour[tabjour].liste_client, client->cle);
    vol->jour[tabjour].nbr_client ++;
    strcpy(codevol, vol->code_vol);
    printf("\nJour [enregistrement_vol] :%ld\n",lejour+1);
    jour = date (temps, lejour+1);
    itoa(tabjour, chartabjour, 10);
    strcat(codevol,chartabjour);
    strcat(codevol, "  ->  le ");
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
    char * chaine1=NULL,chaine2=NULL;
    char chaine[300]="Vol à destination : ";
    ptr_t_destination tmp;

    // recherche destination
    if ( tmp = recherche(levol->dest , listedestination , &recherche_dest) != NULL );   // codedestination variable contenant le code de la destination : (par ex :"lonpar").
    {                                                                            //listedestination la liste chainée des destinations
      strcat(chaine, tmp->destination );
      strcat(chaine, "au départ de " );
      strcat(chaine, tmp->origine );
    }
    strcat(chaine, "\nHoraire :");
    strcat(chaine, levol->horaire );
    strcat(chaine, "Numéro du vol : " );
}
