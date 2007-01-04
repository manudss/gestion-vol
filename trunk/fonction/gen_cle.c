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
*/

char* gen_cle(t_client a)
{
char *cle;
long i;
long num;

cle=(char*)malloc(11*sizeof(char));
cle[0]=a.nom[0];
cle[1]=a.nom[1];
cle[2]=a.prenom[0];
cle[3]=a.prenom[1];


/* NE rien changer dans cette partie, mm si c'est tentant : tt les calculs sont necessaires*/
num=(a.tel-(a.tel/10000*10000)); // les 4 derniers chiffres!
cle[4]=(num/1000)+48; /**/
cle[5]=(num/100-(cle[4]-48)*10)+48;/**/
cle [6]=(num/10-((cle[4]-48)*100)-((cle[5]-48)*10)+48);/**/
cle[7]=a.tel-(a.tel/10*10)+48;/**/

if (a.ff) 
    {
    cle[8]='F';
    cle[9]='F';
    }

else
    {
    cle[8]='N';
    cle[9]='N';
    }        

////////// A NE PAS LAISSER !!, recherchez dans tabDH si existe !
cle[10]='0';

return cle;
}
