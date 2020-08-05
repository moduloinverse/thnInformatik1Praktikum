/**********************************************************************\
* Kurzbeschreibung: Uebung: 5.5.1; Punkte: n
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

   int wert = 0;

   short x;
   unsigned short u;

   x = 7;
   if (x & 1)
   {
      wert = 1;
      printf("n.Wert: %d\n", wert);
   }

   u = 256; // 256 > 0x1 0000 0000
   if (u >> 8 & 1)
   {
      wert = 2;
      printf("n.Wert: %d\n", wert);
   }

   u = 520; // 16 -7 > 0x0000 0010 0000 0000
   if ( (u >> (sizeof(u) * 8 - 7)) & 1 )
   {
      wert = 3;
      printf("n.Wert: %d\n", wert);
   }

   x = 120; 
   if ( ! ( (1 << (sizeof(x) * 8 - 1)) & 1)  & !( x >> 7 & 1)   )
   //        MSB 1 negative                        <128
   {
      wert = 4;
      printf("n.Wert: %d\n", wert);
   }

   u = 44; // 4 = 1<<2
   if ( (u & 3) == 0 )
   {
      wert = 5;
      printf("n.Wert: %d\n", wert);
   }


   //printf("%d\n",6&3);
   //printf("%d\n",359 >> 8);
   return 0;
}
