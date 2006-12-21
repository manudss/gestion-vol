#include "interface.h"

int main()
{
//Creation liste chainée bidon pour tester autentification ( a creer plus tard avec le fichier  client;))

//Creation & initialisation de 3 clients(bidon):
client a,b,c;
client *tete;
//client a :
a.cle="a";
a.mdp="a";
a.message="MESSAGE : Vous etes le client 'a'";
//client b :
b.cle="b";
b.mdp="b";
b.message="MESSAGE : Vous etes le client 'b'";
//client c :
c.cle="c";
c.mdp="c";
c.message="MESSAGE : Vous etes le client 'c'";
//chainage :
tete=&a;
a.suiv = &(b);
b.suiv= &(c);
c.suiv=NULL;


//lancement interface graphique (fenetre connexion)
identification(tete);


return 0;
}
