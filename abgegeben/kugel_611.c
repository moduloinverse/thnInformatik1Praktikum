/**********************************************************************\
* Kugel: Uebung: 6.1.1; Punkte: n
*
* Datum:       Autor:        Grund der Aenderung:
* 31.03.2016   moduloinverse          Neuerstellung
*
\**********************************************************************/

/*--- #includes ------------------------------------------------------*/
#include <stdio.h>
#include <math.h>

/*--- #defines -------------------------------------------------------*/
#define PI 3.14159265359
#define PI4 12.5663706144

/*--- typedef-Datentypen ---------------------------------------------*/

/*--- Funktionsdefinitionen ------------------------------------------*/

float umfang(float radius)
{
   return radius * 2.0 * PI;
}

float volumen(float radius)
{
   return (4 / 3.0 * pow(radius, 3.0) * PI);
}

float oberflaeche(float radius)
{
   return (PI4 * pow(radius, 2.0));
}


int main( void )
{


   float radius;
   printf("Radius: ");
   scanf("%f", &radius);
   printf("\n%f\n",radius);

   printf("Umfang = %f\n", umfang(radius));
   printf("Volumen = %f\n", volumen(radius));
   printf("Oberflaeche = %f\n", oberflaeche(radius));

   return 0;
}
