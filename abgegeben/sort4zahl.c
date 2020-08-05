/**********************************************************************\
* Kurzbeschreibung: Uebung: 22.3; Punkte: n
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
#define OUTSTART  "Sortieren von 4 Integer Zahlen\n"\
                  "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
#define OUTAKT ". Durchlauf - Aktueller Stand:\n"
#define OUTRET "Weiter mit Return...\n"

/*--- typedef-Datentypen ---------------------------------------------*/

/*--- Funktionsdefinitionen ------------------------------------------*/
int input(char *txt);
int sort(int aray[]);

int input(char *txt)
{
   int output, errCode;
   do
   {
      printf("%s", txt);
      errCode = scanf("%d", &output);
      while (getchar() != '\n')
         ;
   }
   while(errCode != 1);
   return output;
}

int sort( int array[] )
{
   int inner;
   int sorted = 0;

   for (inner = 0; inner < 3; inner++)
   {
      if( array[inner] > array[inner+1] )
      {
         array[inner]   =  array[inner] ^ array[inner+1];
         array[inner+1] =  array[inner] ^ array[inner+1];
         array[inner]   =  array[inner] ^ array[inner+1];
         sorted = 1;
      }
   }

   return sorted;
}



int main( void )
{

   int zahlen[4];
   int *ptr = zahlen;
   int sorted, counter;
   counter = 0;

   printf("%s", OUTSTART);

   zahlen[0] = input("Zahl1?: ");
   zahlen[1] = input("Zahl2?: ");
   zahlen[2] = input("Zahl3?: ");
   zahlen[3] = input("Zahl4?: ");

   while(1)
   {
      sorted = sort(zahlen);
      if (sorted == 1)
      {
         counter++;
         printf("%u%s", counter, OUTAKT);
         printf("%d; %d; %d; %d\n",*ptr,*(ptr+1),*(ptr+2),*(ptr+3));
         printf("%s", OUTRET);
         while( getchar() != '\n' )
            ;
      }
      if (sorted == 0  && counter == 0)
      {
         printf("Die Zahlen sind bereits sortiert!\n");
         break;
      }
      if(sorted == 0)
      {
         printf("!!!Fertig nach %u Durchlaeufen !!!!!\n",counter);
         break;
      }
   }

   return 0;
}
