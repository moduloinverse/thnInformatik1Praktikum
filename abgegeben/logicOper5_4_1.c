/**********************************************************************\
* Kurzbeschreibung: Uebung: 5.4.1; Punkte: n
*
* Datum:       Autor:        Grund der Aenderung:
* 01.10.2013   moduloinverse       Neuerstellung
*
\**********************************************************************/

/*--- #includes ------------------------------------------------------*/
#include <stdio.h>
#include <limits.h>

/*--- #defines -------------------------------------------------------*/

/*--- typedef-Datentypen ---------------------------------------------*/

/*--- Funktionsdefinitionen ------------------------------------------*/

int main( void )
{

   short int wert;

   short int a = -15, b = 10;
   short int x = 1, y = 7;
   short int z = 15;
   short int jahr = 2100;
   char antwort = 'A';
   short int zaehler = 30;


   if(a >= -20 && a <= 100)
   {
      wert = 1;
      printf("n.Wert: %d\n", wert);
   }
   if (x < 0 && (y >= 5 && y <= 30) )
   {
      wert = 2;
      printf("n.Wert: %d\n", wert);
   }
   if ((z % 2 != 0) && (z % 3 == 0) && (z % 5 == 0) )
   {
      wert = 3;
      printf("n.Wert: %d\n", wert);
   }
   if (jahr % 400 == 0 || (jahr % 4 == 0 && jahr % 100 != 0))
   {
      wert = 4;
      printf("n.Wert: %d\n", wert);
   }

   a = 25;
   if (a * b <= UCHAR_MAX)
   {
      wert = 5;
      printf("n.Wert: %d\n", wert);
   }
   if (antwort != 'j' && antwort != 'J')
   {
      wert = 6;
      printf("n.Wert: %d\n", wert);
   }
   if ( !(zaehler >= 5 && zaehler <= 25) )
   {
      wert = 7;
      printf("n.Wert: %d\n", wert);
   }
   return 0;
}
