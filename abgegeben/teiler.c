/**********************************************************************\
* Kurzbeschreibung: Uebung: 15.6; Punkte: n
*
* Datum:       Autor:        Grund der Aenderung:
* 28.04.2016   moduloinverse        Neuerstellung
*
\**********************************************************************/

/*--- #includes ------------------------------------------------------*/
#include <stdio.h>

/*--- #defines -------------------------------------------------------*/

/*--- typedef-Datentypen ---------------------------------------------*/

/*--- Funktionsdefinitionen ------------------------------------------*/

int main( void )
{

   unsigned int zahl, i;
   unsigned count = 0;

   printf("Alle Teiler zu einer Zahl bestimmen\n");
   printf("+++++++++++++++++++++++++++++++++++\n\n");
   printf("Gib eine Zahl ein: \n");
   scanf("%u", &zahl);

   for(i = 2; i < zahl; i++)
   {
      if (zahl % i == 0)
      {
         count++;
      }
   }

   if (count == 0)
   {
      printf("   %u ist eine Primzahl\n", zahl);
   }
   else
   {
      printf("    %u ist teilbar durch: ", zahl);
      for(i = 2; i < zahl; i++)
      {
         if (zahl % i == 0)
            printf(" %u,", i);
      }
      fflush(stdout);
      printf("\b     ");
      fflush(stdout);
      printf("\n");
   }


   return 0;
}
