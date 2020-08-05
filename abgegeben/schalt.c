/**********************************************************************\
* Kurzbeschreibung: Uebung 11.1; Punkte: n
*
* Datum:       Autor:        Grund der Aenderung:
* 14.04.2016   moduloinverse          Neuerstellung
*
\**********************************************************************/

/*--- #includes ------------------------------------------------------*/
#include <stdio.h>

/*--- #defines -------------------------------------------------------*/

/*--- typedef-Datentypen ---------------------------------------------*/

/*--- Funktionsdefinitionen ------------------------------------------*/

int main( void )
{

   int jahr;
   printf("Jahr eingeben: ");
   scanf("%d", &jahr);

   printf("%d\n", jahr);

   if (jahr % 4 == 0)
   {
      if (jahr % 100 == 0)
      {
         if (jahr % 400 == 0)
         printf("Schaltjahr\n");
         else
            printf("Kein Schaltjahr\n");
      }
      else
         printf("Schaltjahr\n");
   }
   else
      printf("Kein Schaltjahr\n");



   return 0;
}
