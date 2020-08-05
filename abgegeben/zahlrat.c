/**********************************************************************\
* Kurzbeschreibung: Uebung: 17.1; Punkte: n
*
* Datum:       Autor:        Grund der Aenderung:
* 18.05.2016   moduloinverse          Neuerstellung
*
\**********************************************************************/

/*--- #includes ------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*--- #defines -------------------------------------------------------*/
#define EINGABE1 "Ich denke mir eine Zahl aus dem Intervall [1,x].\n"\
                 "Du musst dann versuchen, diese Zahl zu erraten\n\n"
#define EINGABE2 "Zunaechst musst du einmal festlegen, wie gross die zu\n"\
                 "ratende Zahl maximal sein darf: "
#define VERSUCH  "Dein %u.Versuch: "
#define ERGEBNIS "\nDu hast %u Versuche gebraucht\n"
#define LOW      "                                                       ......zu niedrig\n"
#define HIGH     "                                                       .........zu hoch\n"
#define EXACT    "                                                       .........Richtig\n"
/*--- typedef-Datentypen ---------------------------------------------*/

/*--- Funktionsdefinitionen ------------------------------------------*/

int main( void )
{
   unsigned int input;
   unsigned int count = 0;
   unsigned int random;
   int errCode;

   printf("%s", EINGABE1);

   do
   {
      printf("%s", EINGABE2);
      errCode = scanf("%u", &input);
      getchar();
   }
   while(errCode != 1 || input < 1);

   srand(time(NULL));  //initailize random seed
   // rand() % (o-u+1) + 1
   random = rand() % (input - 1 + 1) + 1;
   printf("\nHm..... OK, ich habe eine Zahl\n\n");

   do
   {
      ++count;
      do
      {
         printf(VERSUCH, count);
         errCode = scanf("%u", &input);
         getchar();
      }
      while (errCode != 1 || input < 1);
   
      if (input == random)
         printf(EXACT);
      else if (input < random)
         printf(LOW);
      else
         printf(HIGH);
   }
   while( input != random);

   printf(ERGEBNIS, count);


   return 0;
}
