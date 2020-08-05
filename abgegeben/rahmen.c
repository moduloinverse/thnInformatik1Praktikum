/**********************************************************************\
* Rahmen: Uebung: 7_3_1; Punkte: n
*
* Datum:       Autor:        Grund der Aenderung:
* 31.03.2016   moduloinverse          Neuerstellung
*
\**********************************************************************/

/*--- #includes ------------------------------------------------------*/
#include <stdio.h>
#include <string.h>

/*--- #defines -------------------------------------------------------*/

/*--- typedef-Datentypen ---------------------------------------------*/

/*--- Funktionsdefinitionen ------------------------------------------*/

int main( void )
{

   int breite = 5;

   puts("Breite eingaben: ");
   scanf("%d", &breite);
   printf("Breite: %d\n", breite);

   breite += 3;
   char topline[breite];
   memset(topline, '-', breite);
   topline[0] = '+';
   topline[breite-2] = '+';
   topline[breite-1] = '\0';
   breite -= 3;

   printf("%s\n", topline);


   printf("|%*s|\n", breite, "");
   printf("|%*s|\n", breite, "");
   printf("|%*s|\n", breite, "");


   printf("+%.*s+\n", breite, "---------------------------------------------------------------"
   "------------------------------------------------------------------------------------------");


   return 0;
}
