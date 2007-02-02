#include "../structure.h"
#include "../recherche/recherche.h"


// adresse de la case d'un client
// adresse de la case d'un vols
// et le jour.(en int )
//


int enregistrement_vols ( ptr_t_client client, ptr_t_vols vol, int lejour, ptr_t_temps temps)
{

    t_temps tmp;
    char *codevol[50];
    char *jour= NULL;

    tmp.courant = temps->courant;
    lejour = (lejour + temps->jour) %31;

    vol->jour[lejour].liste_client = ajouterEnTete(vol->jour[lejour].liste_client, client->cle);
    vol->jour[lejour].nbr_client ++;
    strcpy(codevol, vol->code_vol);
    jour = date (temps, lejour);
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