/**********************************************************************\
* Kurzbeschreibung: Uebung: 25.1; Punkte: n
*
* Datum:       Autor:        Grund der Aenderung:
* 09.06.2016   moduloinverse          Neuerstellung
*
\**********************************************************************/

/*--- #includes ------------------------------------------------------*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/*--- #defines -------------------------------------------------------*/
#define OUTSTART  "Lottozahlen - Simulation\n"\
                  "~~~~~~~~~~~~~~~~~~~~~~~~\n"
#define OUT1  "Wieviele Kugeln sollen zur Verfuegung stehen (mind. 1 und max. 100) :"
#define OUT2  "Wieviele werden davon gezogen (mind. 1 und max. 49) :"

/*--- typedef-Datentypen ---------------------------------------------*/

/*--- Funktionsdefinitionen ------------------------------------------*/

int input(char *txt, int max)
{
   int output, errCode;
   do
   {
      printf("%s", txt);
      errCode = scanf("%u", &output);
      while (getchar() != '\n')
         ;
   }
   while(errCode != 1 || output < 0 || output > max);
   return output;
}



int main( void )
{

   printf("%s", OUTSTART);
   int zufZahl,i,exist;
   int counter = 0;
   int kugeln = input(OUT1, 100);
   int zuege  = input(OUT2, 49);
   int topf[zuege];
   srand(time(NULL));

   do
   {
      zufZahl = rand() % kugeln + 1;//rand % (o-u +1) + u
      exist = 0;
      for (i = 0; i < zuege; i++)
      {
         if(topf[i] == zufZahl)
         {
            exist = 1;
            break;
         }
      }
      if (exist == 0)
      {
         topf[counter] = zufZahl;
         counter++;
      }
   }
   while (counter != zuege);


   printf("==== %u aus %u ====\n", zuege, kugeln);
   for (i = 0; i < zuege; i++)
      printf("%4d",topf[i]);

   printf("\n");

   return 0;
}
