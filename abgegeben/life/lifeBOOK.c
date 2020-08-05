#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <graphics.h>
#include <time.h>

#define MAXX  800
#define MAXY  600

int  pers, zeil, spal, faktz, fakts, maxx, maxy;
int  altGen [MAXX+2][MAXY+2],
     neuGen [MAXX+2][MAXY+2];
     
void  initialisiere(void);
void  spiele(void);

/*----------------- main ------------------------------------------*/
int  main( int argc, char *argv[] )
{
   initgraph( MAXX, MAXY );
   initialisiere();
   spiele();
   closegraph();
   return(0);
}

/*----------------- initialisiere ---------------------------------*/
void  initialisiere(void)
{
   int  i, j, x, y, xk, yk;
   char string[100], zeich;

   srand(time(NULL));
   for (j=0; j<=MAXX+1; j++)
      for (i=0; i<=MAXY+1; i++)
         altGen[i][j] = 2 ;
         neuGen[i][j] = 0;
   do {
      sprintf( string, "Spielfeldgroesse; Zeilen (1,%d): ", MAXY/6);
      zeil = getint( string );
   } while (zeil<1 || zeil>MAXY/6);
   do {
      sprintf( string, "Spalten(1,%d): ", MAXX/8);
      spal = getint( string );
   } while (spal<1 || spal>MAXX/8);

   faktz = MAXY/zeil;
   fakts = MAXX/spal;

   setcolor( WHITE );
   setfillstyle( SOLID_FILL, LIGHTGRAY );
   setlinestyle( SOLID_LINE, 2 );
   bar3d( 0, 0, fakts*spal, faktz*zeil, 0 );

   zeich = getcharacter("Möchten Sie Anfangsverteilung eingeben (j/n): ");
   if ( tolower(zeich) != 'j') {
      do {
         sprintf(string, "Anzahl der Personen (1,%d): ", zeil*spal);
         pers = getint( string );
      } while (pers<1 || zeil*spal<pers);
      do {                 /* Zufaellige Verteilung */
         while (neuGen[x=rand()%spal][y=rand()%zeil] == 1)
            ;
         neuGen[x][y] = 1;
      } while (--pers>=1);
   } else {
      outtextxy( 10, 10, getmaxx(), getmaxy(),
                 "Mit der Maus kannst Du nun die Leben setzen/loeschen\n"
                 "Abbruch des Setzens mit einer beliebigen Taste.......");
      getch();

      for (j=0; j<spal; j++)
         for (i=0; i<zeil; i++)
            bar3d( j*fakts, i*faktz, (j+1)*fakts, (i+1)*faktz, 0 );
      do {
         if (mouse_left() || mouse_right()) {
            mouse_getpos(&x, &y);
            xk = x/fakts;
            yk = y/faktz;
            if (xk>=0 && xk<spal && yk>=0 && yk<zeil) {
               mouse_hide();
               if (neuGen[xk][yk] == 0 && getpixel(x,y) == LIGHTGRAY) {
                  setfillstyle(SOLID_FILL, BLUE);
                  neuGen[xk][yk] = 1;
               } else if (neuGen[xk][yk] == 1 && getpixel(x,y) == BLUE) {
                  setfillstyle(SOLID_FILL, LIGHTGRAY);
                  neuGen[xk][yk] = 0;
               }
               bar3d( xk*fakts, yk*faktz, (xk+1)*fakts, (yk+1)*faktz, 0 );
               while (mouse_left() || mouse_right())
                  ;
               mouse_show();
            }
         }
      } while (!kbhit());
      getch();
      mouse_hide();
   }
}

/*----------------- spiele ----------------------------------------*/
void  spiele(void)
{
   int  x, y;

   do {
      for ( x=0; x<spal; x++ )
         for ( y=0; y<zeil; y++ )
             if ( altGen[x][y] != neuGen[x][y] ) {
                 setfillstyle(SOLID_FILL, (neuGen[x][y] == 1) ? BLUE : LIGHTGRAY );
                 bar3d( x*fakts, y*faktz, (x+1)*fakts, (y+1)*faktz, 0 );
                 altGen[x][y] = neuGen[x][y];
             }
      for ( x=0; x<spal; x++)
         for ( y=0; y<zeil; y++ ) {
            int l = (x-1) < 0     ? spal-1 : x-1;      
            int r = (x+1) >= spal ? 0      : x+1;      
            int o = (y-1) < 0     ? zeil-1 : y-1;      
            int u = (y+1) >= zeil ? 0      : y+1;      
            int sum = altGen[l][o] + altGen[l][y] + altGen[l][u] +
                      altGen[x][u] + altGen[r][u] + altGen[r][y] +
                      altGen[r][o] + altGen[x][o];
           
            if ( sum < 2 || sum > 3 )
               neuGen[x][y] = 0;
            else if ( sum == 3 )
               neuGen[x][y] = 1;
            else
               neuGen[x][y] = altGen[x][y];
         }
   } while (!kbhit());
   getch();
}
