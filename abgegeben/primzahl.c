/**********************************************************************\
* Kurzbeschreibung: Uebung: 18.2; Punkte: n
*
* Datum:       Autor:        Grund der Aenderung:
* 18.05.2016   moduloinverse          Neuerstellung
*
\**********************************************************************/

/*--- #includes ------------------------------------------------------*/
#include <stdio.h>


/*--- #defines -------------------------------------------------------*/
#define OUT1 "Primzahlen\n"\
             "~~~~~~~~~~\n"\
             "Dieses Programm gibt Ihnen alle Primzahlen zwischen\n"\
             "m und n aus. m und n sind dabei einzugeben\n"

/*--- typedef-Datentypen ---------------------------------------------*/

/*--- Funktionsdefinitionen ------------------------------------------*/
int inputUInt (void)
{
   unsigned int inp;
   do
   {
      scanf("%u", &inp);
   }
   while(getchar() != '\n');
   return inp;
}

int isPrim(int zahl)
{
   int f = 2;
   int ans = 0;
   if (zahl == 2 || zahl == 3)
      ans = 1;
   else if (zahl == 1 || zahl % 2 == 0)
      ans = 0;
   else
   {
      f = 3;
      ans = 1;
      do
      {
         if(zahl % f == 0)
         {
            ans = 0;
            break;
         }
         else
         {
            f += 2;
         }
      }
      while (f*f <= zahl);
   }
   return ans;
   
}


int main( void )
{

   int m, n, count = 0;
   printf("%s", OUT1);
   printf("m: ");
   m = inputUInt();
   printf("n: ");
   n = inputUInt();

   if (m > n)
   {
      m = m ^ n;
      n = m ^ n;
      m = m ^ n;
   }

   while(1)
   {
      if (m == n)
         break;
      if (isPrim(m) == 1)
      {
         printf("%8u, ", m);
         count++;
      }
      m++;
      if (count == 8)
      {
         printf("\n");
         count = 0;
      }
   }
   printf("\n");

   return 0;
}