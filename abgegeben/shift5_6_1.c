/**********************************************************************\
* Kurzbeschreibung: Uebung: 5_6_1; Punkte: n
*
* Datum:       Autor:        Grund der Aenderung:
* 31.03.2016   moduloinverse       Neuerstellung
*
\**********************************************************************/

/*--- #includes ------------------------------------------------------*/
#include <stdio.h>

/*--- #defines -------------------------------------------------------*/

/*--- typedef-Datentypen ---------------------------------------------*/

/*--- Funktionsdefinitionen ------------------------------------------*/

int main( void )
{

   unsigned short x = 0x12AB;

   printf("Wert: %X\n",x);

   x = x >> 8 | x << 8;

   printf("Wert: %X\n",x);


   return 0;
}
