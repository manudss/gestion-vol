#ifndef LISTE_H
# define LISTE_H

//protos
llist ajouterEnTete(llist liste, void * valeur);

llist effacerListe(llist liste, void * (fctfree) (void *));

void * freet_client ( void * liste);

llist effacerListe(llist liste, void * (fctfree) (void *));

llist effacerelmt(llist liste, char * aeffacer);
 
llist effacervol(llist liste, int i);

void * affiche_client(void * tmp);

void afficherListe(llist liste, void *(afficher) (void *));

void * affiche_avion (void * tmp);

void * affiche_dest (void * tmp);

void * freet_avions ( void * liste);

void afficherListe(llist liste, void *(afficher) (void *));

#endif
