/**********************************************************************\
* Kurzbeschreibung: Uebung: 16.6; Punkte: n
*
* Datum:       Autor:        Grund der Aenderung:
* 05.2016      moduloinverse        Neuerstellung
*
\**********************************************************************/

/*--- #includes ------------------------------------------------------*/
#include <stdio.h>

/*--- #defines -------------------------------------------------------*/

/*--- typedef-Datentypen ---------------------------------------------*/

/*--- Funktionsdefinitionen ------------------------------------------*/

int main( void )
{

   unsigned int zahl;
   unsigned count = 0;

   printf("Quersumme zu einer Zahl\n");
   printf("++++++++++++++++++++++\n\n");
   printf("Gib eine Zahl ein: \n");
   scanf("%u", &zahl);

   while (zahl > 0)
   {
      count += zahl % 10;
      zahl -= zahl % 10;
      zahl = zahl / 10;
   }
   printf("Summe : %u\n", count);


   return 0;
}
