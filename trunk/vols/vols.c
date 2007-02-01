#include "../structure.h"



// adresse de la case d'un client
// adresse de la case d'un vols
// et le jour.(en int )
//


int enregistrement_vols ( ptr_t_client client, ptr_t_vols vol, int lejour, ptr_t_temps temps)
{
    vol->jour[lejour].liste_client = ajouterEnTete(vol->jour[lejour].liste_client, client->cle);
    vol->jour[lejour].nbr_client ++;
    client->vols = ajouterEnTete(client->vols, vol->code_vol);
    return 1;
}


