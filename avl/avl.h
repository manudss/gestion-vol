#ifndef AJOUT_H
# define AJOUT_H

//protos
void rotationgauche ( ptr_t_vols *A );
void rotationdroite ( ptr_t_vols *A );
void rotationgauchedroite ( ptr_t_vols *A );
void rotationdroitegauche ( ptr_t_vols *A );

int ajoutavl(ptr_t_vols x, ptr_t_vols *B);
ptr_t_vols plus_petit(ptr_t_vols a);
void copie_arbre(ptr_t_vols source, ptr_t_vols *destination);


ptr_t_vols   init_listevols (char *codevol);

int nbr_elmt(ptr_t_vols a);

int parcourttotab(ptr_t_vols a, ptr_t_vols tab[], int *n );


#endif
