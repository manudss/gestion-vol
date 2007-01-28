#ifndef LISTE_H
# define LISTE_H

//protos
llist ajouterEnTete(llist liste, void * valeur);

llist effacerListe(llist liste, void * (fctfree) (void *));

void * freet_client ( void * liste);

llist effacerListe(llist liste, void * (fctfree) (void *));

void * affiche_client(void * tmp);

void afficherListe(llist liste, void *(afficher) (void *));

void * affiche_avion (void * tmp);

void * freet_avions ( void * liste);

int hachage(char* sText_cle);

void * recherch_client_par_cle(void* achercher,void * chercherdans);

void * recherche(void *  achercher,llist liste, void * (fct_rech) (void* achercher,void * chercherdans));

#endif
