/**********************************************************************\
* Kurzbeschreibung: Uebung: 7.2.1; Punkte: n
*
* Datum:       Autor:        Grund der Aenderung:
* 07.04.2016   moduloinverse          Neuerstellung
*
\**********************************************************************/

/*--- #includes ------------------------------------------------------*/
#include <stdio.h>

/*--- #defines -------------------------------------------------------*/

/*--- typedef-Datentypen ---------------------------------------------*/

/*--- Funktionsdefinitionen ------------------------------------------*/

int main( void )
{

   char primero, segundo, tercero, cuarto, quinto;
   int sum;

   int i[5];

   printf("5-digit integer: \n");
   scanf("%c %c %c %c %c", &primero, &segundo, &tercero, &cuarto, &quinto);
   primero -= 48;
   segundo -= 48;
   tercero -= 48;
   cuarto  -= 48;
   quinto  -= 48;

   sum = primero + segundo + tercero + cuarto + quinto;
   printf("%d %d %d %d %d\n", primero,segundo,tercero,cuarto, quinto);
   printf("sum: %d\n", sum);

   scanf("%1u %1u %1u %1u %1u", &i[0], &i[1], &i[2], &i[3], &i[4]);
   printf("sum: %d\n", i[0] + i[1] + i[2] + i[3] + i[4]);
   printf("%d %d %d %d %d\n", i[0], i[1], i[2], i[3], i[4]);

   return 0;
}
