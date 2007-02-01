#include "../structure.h"

/**
* @brief fonction generant la clé a partir d'un client
* 
* @version 1.0
* @bug 0->testé et vérifié sans problème
*
* @param 'a' la structure du client
* 
* @return cle	un poineteur vers la chaine contenant la clé
* @commentaires calculs lourds a cause du type "long" du tel.. ne presente cependant aucun bug !
*                  le tel , doit etre de la forme 123456789 si on met un zero , cela ne passe plus !
*/



/////VERSION 2 .. en effet c con de passer une structure a gen_cle puisque la structure ne peut etre deja crée vu kon a pas encore la clé !
// Voici donc la version , ou on récupere juste les chps necessaires :
char* gen_cle2(char* nom, char* prenom, long tel, long ff )// si le client est ff, ff !=0
{
char *cle;
long i;
long num;

cle=(char*)malloc(11*sizeof(char));
cle[0]=nom[0];
cle[1]=nom[1];
cle[2]=prenom[0];
cle[3]=prenom[1];
num=(tel-(tel/10000*10000)); // les 4 derniers chiffres!

cle[4]=(num/1000)+48;
cle[5]=(num/100-(cle[4]-48)*10)+48;
cle[6]=(num/10-((cle[4]-48)*100)-((cle[5]-48)*10)+48);
cle[7]=tel-(tel/10*10)+48;
/*
if (ff) 
    {
    cle[8]='F';
    cle[9]='F';
    }

else
    {
    cle[8]='N';
    cle[9]='N';
    }        
*/
////////// A NE PAS LAISSER !!, recherchez dans tabDH si existe !
cle[8]='0';
cle[9]='\0';

return cle;
}
