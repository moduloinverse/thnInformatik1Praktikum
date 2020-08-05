/**********************************************************************\
* Kurzbeschreibung: Uebung: 8.1.1; Punkte: n
*
* Datum:       Autor:        Grund der Aenderung:
* 14.04.2016   moduloinverse          Neuerstellung
*
\**********************************************************************/

/*--- #includes ------------------------------------------------------*/
#include <stdio.h>
#include <math.h>

/*--- #defines -------------------------------------------------------*/
#define G 9.80665

/*--- typedef-Datentypen ---------------------------------------------*/

/*--- Funktionsdefinitionen ------------------------------------------*/

int main( void )
{

   int hight;
   int time; //float
   printf("Absprung hoehe eingeben: ");
   scanf("%6d", &hight);
   //printf("%d\n",hight);
   time = sqrt( 2.0 * (hight - 650.0) / G );
   printf("nach %d sekunden leine ziehen\n", time); //(int)

   return 0;
}
