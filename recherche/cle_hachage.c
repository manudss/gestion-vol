#include "../structure.h"
#include "recherche.h"



int hachage1(char* sText_cle)
{
int i;
//1er caractère !
if (sText_cle[0]>=97 && sText_cle[0]<=122) //si 1er carac. minuscule
          {
          i=sText_cle[0]-97;
          }
else if (sText_cle[0]>=65 && sText_cle[0]<=90) //MAJ
    {
    i=sText_cle[0]-65;
    }
else i=TAILLETDH-1;

return i;
}



int hachage2(char* sText_cle)
{
int j;
//2ème caractère
if (sText_cle[1]>=97 && sText_cle[1]<=122) //si 1er carac. minuscule
          {
          j=sText_cle[1]-97;
          }
else if (sText_cle[1]>=65 && sText_cle[1]<=90) //MAJ
    {
    j=sText_cle[1]-65;
    }
else j=TAILLETDH-1;
return j;
}

int hachage(char* sText_cle)
{
    int h1 = 0;
    int h2 = 0;

    h1 = hachage1(sText_cle);
    h2 = hachage2(sText_cle);
    return (h1 * TAILLETDH + h2);
}
