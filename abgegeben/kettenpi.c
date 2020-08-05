/**********************************************************************\
* Kurzbeschreibung: Uebung: 5.2.5; Punkte: n
*
* Datum:       Autor:        Grund der Aenderung:
* 17.03.2016   moduloinverse       Neuerstellung
*
\**********************************************************************/

/*--- #includes ------------------------------------------------------*/
#include <stdio.h>

/*--- #defines -------------------------------------------------------*/

/*--- typedef-Datentypen ---------------------------------------------*/

/*--- Funktionsdefinitionen ------------------------------------------*/

int main( void )
{
   float pi;

   pi = 1.0f+1.0f/(292.0f+0.5f);
   pi = 15.0f + 1.0f/pi;
   pi = 7.0f + 1.0f/pi;
   pi = 3.0f + 1.0f/pi;

   printf("Pi = %f\n",pi);
   return 0;
}
