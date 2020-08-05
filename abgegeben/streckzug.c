/**********************************************************************\
* Kurzbeschreibung: Uebung: 22.2; Punkte: n
*
* Datum:       Autor:        Grund der Aenderung:
* 02.06.2016   moduloinverse          Neuerstellung
*
\**********************************************************************/

/*--- #includes ------------------------------------------------------*/
#include <stdio.h>
#include <math.h>

/*--- #defines -------------------------------------------------------*/
#define OUT1      "Strecken-Berechnungen\n"\
                  "~~~~~~~~~~~~~~~~~~~~~~~\n\n"
#define OUTSTART  "\nBitte Startpunkt eingeben (x,y): "
#define OUTOTRO   "Neuer Streckenpunkt x,y (Abbruch mit x=-1): "
#define OUTRESULT "=> Die Streckenlaenge betraegt: "   
/*--- typedef-Datentypen ---------------------------------------------*/

/*--- Funktionsdefinitionen ------------------------------------------*/
int *input2Int (char *txt)
{
   int errCode;
   static int inp[3];
   do
   {
      //getchar();
      printf("%s", txt);
      errCode = scanf("%d,%d", &inp[0], &inp[1]);
      while (getchar() != '\n')
         ;

      if (errCode == 1 && inp[0] == -1)
         break;
   }
   while(errCode != 2);
   inp[2] = errCode;
   return inp;
}

float lengthBetweenPoints(int x1, int x2, int y1, int y2)
{
   float length;
   length = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
   length = sqrt(length);
   return length;
}

int main( void )
{

   float length = .0;
   int xNew, yNew;
   printf("%s", OUT1);
   int *input = input2Int(OUTSTART);
   int xStart = *input;
   int yStart = *(input + 1);

//printf("%d,%d,%d\n", *(input+0),*(input+1),*(input+2));
   do
   {
      input = input2Int(OUTOTRO);
      xNew = *(input+0);
      yNew = *(input+1);
      if ( *input == -1 && *(input+2) == 1)
         break;
      length = length + lengthBetweenPoints(xStart, xNew, yStart, yNew);
      xStart = xNew;
      yStart = yNew;
//printf("%d,%d,%d\n", *input,*(input+1),*(input+2));
   }
   while(1);
   
   printf("%s%.2f Einheiten\n", OUTRESULT, length);

   return 0;
}