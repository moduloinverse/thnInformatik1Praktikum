/**********************************************************************\
* Kurzbeschreibung: Uebung: 11.3; Punkte: n
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

   printf("Dieses Programm sagt Ihnen, ob eine Zahl x durch eine Zahl y \n"
      "teilbar ist. Dazu muessen nur die beiden ganzen Zahlen x und y "
      "eingeben.\n");

   int x, y;
   scanf("%d", &x);
   scanf("%d", &y);
   if (x % y == 0)
      printf("%d ist durch %d teilbar\n", x, y);
   else
      printf("%d ist durch %d nicht teilbar, Rest %d\n", x, y, x%y);

   return 0;
}
