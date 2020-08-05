/**********************************************************************\
* Kurzbeschreibung: Uebung: 16.2; Punkte: n
*
* Datum:       Autor:        Grund der Aenderung:
* 18.05.2016   moduloinverse          Neuerstellung
*
\**********************************************************************/

/*--- #includes ------------------------------------------------------*/
#include <stdio.h>

/*--- #defines -------------------------------------------------------*/
#define EINGABE "Geben Sie eine gerade Zahl zwische 1 und 100 ein\n"\
                "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"

/*--- typedef-Datentypen ---------------------------------------------*/

/*--- Funktionsdefinitionen ------------------------------------------*/

int main( void )
{
   unsigned int zahl;
   int errCode;
   printf("%s\n", EINGABE);
   errCode = scanf("%u", &zahl);
   printf("Error Code: %d\n", errCode);

   while (errCode != 1 || !( (zahl > 1 && zahl <= 100) && ( zahl % 2 == 0) ) )
   {
      //fflush(stdin);
      //fflush(stdout);
      printf("Die eingabe: %d entspricht nicht den Voragaben\n", zahl);
      printf("%s\n", EINGABE);
      errCode = scanf("%u", &zahl);
      printf("Error Code: %d\n", errCode);
      getchar();
   }
   printf("\nDie eingegebene Zahl lautet: %u\n", zahl);




   return 0;
}
