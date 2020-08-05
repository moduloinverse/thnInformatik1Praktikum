/**********************************************************************\
* XOR swap: Uebung: 5.2.6; Punkte: n
*
* Datum:       Autor:        Grund der Aenderung:
* 14.03.2016   moduloinverse          Neuerstellung
*
\**********************************************************************/

/*--- #includes ------------------------------------------------------*/
#include <stdio.h>

/*--- #defines -------------------------------------------------------*/

/*--- typedef-Datentypen ---------------------------------------------*/

/*--- Funktionsdefinitionen ------------------------------------------*/

int main( void )
{

short int a = 10;
short int b = 6;

printf("a = %d, b = %d \n", a, b);
a = a ^ b;
b = b ^ a;
a = a ^ b;
printf("a = %d, b = %d \n", a, b);

   return 0;
}

/*
a = a ^ b ^ c // a==a^b^c
b = a ^ b ^ c // b==(a^b^c)^b^c==a
c = a ^ b ^ c // c==(a^b^c)^a^c==b
a = a ^ b ^ c // a==(a^b^c)^a^b==c
*/
