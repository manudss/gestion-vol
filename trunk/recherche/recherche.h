#ifndef RECHERCHE_H
#define RECHERCHE_H

//protos
int hachage1(char* sText_cle);
int hachage2(char* sText_cle);
int hachage(char* sText_cle);

void * recherche(void *  achercher,llist liste, void * (fct_rech) (void* achercher,void * chercherdans));
void * recherch_client_par_cle(void* achercher,void * chercherdans);
void * recherche_dest(void* achercher,void * chercherdans);
void * recherche_avion(void* achercher,void * chercherdans);


#endif
