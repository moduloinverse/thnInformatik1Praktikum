/**********************************************************************\
* Kurzbeschreibung: Uebung: 15.2; Punkte: n
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

   printf("Summe Ungerader Zahlen\n");
   printf("++++++++++++++++++++++\n\n");
   printf("Gib eine Zahl ein: \n");
   scanf("%u", &zahl);

   for(i = 1; i <= zahl; i++)
   {
      if(i % 2 == 1)
         count += i;
   }
   printf("Summe der Zahlen bis %u: %u\n", zahl, count);


   return 0;
}
