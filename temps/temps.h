#ifndef TEMPS_H
# define TEMPS_H


/*


*/

char * quelheure(ptr_t_temps temps);

char * ajoutertemps(ptr_t_temps temps, long t_plus);

void sauvgardetemps (ptr_t_temps temps);

void lecturetemps (ptr_t_temps temps);

char * date (ptr_t_temps temps, int i);


#endif
