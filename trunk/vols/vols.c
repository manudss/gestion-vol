#include <math.h>
#include "../structure.h"
#include "../recherche/recherche.h"


// adresse de la case d'un client
// adresse de la case d'un vols
// et le jour.(en int )
//


int enregistrement_vols ( ptr_t_client client, ptr_t_vols vol, int lejour, ptr_t_temps temps)
{

        DBG
    t_temps tmp;
    char *codevol[50];
    char *jour= NULL;
    int tabjour;
    

    tmp.courant = temps->courant;
    tabjour = (lejour + temps->jour) %31;
    vol->jour[tabjour].liste_client = ajouterEnTete(vol->jour[tabjour].liste_client, client->cle);
    vol->jour[tabjour].nbr_client ++;
    strcpy(codevol, vol->code_vol);
    printf("\nJour [enregistrement_vol] :%ld\n",lejour+1);
    DBG
    jour = date (temps, lejour+1);
    DBG
    strcat(codevol, "  ->  le ");
    strcat(codevol, jour);
    DBG
    jour = strdup(codevol);
    DBG
        
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


void effacementvolsclient(ptr_t_client client, char * cle )
{
    ptr_t_client elmt;

    elmt = recherche(cle , client , &recherch_client_par_cle);           // Recherche d'un client
    while(elmt != NULL)  // fausse condition
    {
        effacerelmt(elmt->vols, cle);
    }

    if (elmt->ff != NULL) // si il le client est fréquent Flyer
    {
        elmt->ff->vols = ajouterEnTete(elmt->ff->vols, cle);
    }

}

void effacementclientvols(ptr_t_vols arbre, char * code )
{
    return ;
}
