#ifndef TEMPS_H
# define TEMPS_H


/*


*/



char * ajoutertemps(ptr_t_temps temps, long t_plus,llist listeclient[],ptr_t_vols arbrevol,llist listeavion,llist listedestination);

void sauvgardetemps (ptr_t_temps temps);

void lecturetemps (ptr_t_temps temps);

char * date (ptr_t_temps temps, int i);

char * quelheure(ptr_t_temps temps, llist TDH[], ptr_t_vols arbre, llist listeavion, llist listedest);


#endif
