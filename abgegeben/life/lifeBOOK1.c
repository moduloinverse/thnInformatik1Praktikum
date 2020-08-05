#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <graphics.h>
#include <time.h>

#define MAXX  800 //spalten
#define MAXY  600 //zeilen

int  pers, zeil, spal, faktz, fakts, maxx, maxy;
int  altGen [0][0],
     neuGen [0][0];

int **feld,**feldnew;
int livecells, changedcells, maxlivecells;
     
void  initialisiere(void);
void  spiele(void);

void setmanual(void);
void setalive(int x, int y);
void setdead(int x, int y);
int validindex(int x, int y);
int getsum(int x, int y);
void gametime(void);

/*----------------- main ------------------------------------------*/
int  main( int argc, char *argv[] )
{
   livecells = 0;
   changedcells = 0;
   initgraph( MAXX, MAXY );
   initialisiere();
   gametime();
   //spiele();
   closegraph();
   return(0);
}

/*----------------- initialisiere ---------------------------------*/
void initialisiere(void)
{
   int  i, j;
   char string[100], zeich;
/*
   //srand(time(NULL));
   for (j=0; j<MAXX; j++)
      for (i=0; i<MAXY; i++)
         //feld[i][j] = 0;
         //altGen[i][j] = 2;
         //neuGen[i][j] = 0;
*/
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

   maxlivecells = zeil * spal;

   setcolor( WHITE );
   setfillstyle( SOLID_FILL, LIGHTGRAY );
   setlinestyle( SOLID_LINE, 2 );
   bar3d( 0, 0, fakts*spal, faktz*zeil, 0 );

   feld = (int **)malloc(sizeof(int *) * zeil);
   feldnew = (int **)malloc(sizeof(int *) * zeil);
   feld[0] = (int *)malloc(sizeof(int) * spal *zeil);
   feldnew[0] = (int *)malloc(sizeof(int) * spal *zeil);
   for (i = 0; i < zeil; i++)
   {
      feldnew[i] = (*feldnew + spal * i);
      feld[i] = (*feld + spal * i);
   }

   for (j=0; j<spal; j++)
   {
      for (i=0; i<zeil; i++)
      {
         bar3d( j*fakts, i*faktz, (j+1)*fakts, (i+1)*faktz, 0 );
         feld[j][i] = 0;
         feldnew[i][j] =0;
         //printf("%d i zeil x %d j spal y\n",i,j);
      }
   }
   //getch();
   zeich = getcharacter("Möchten Sie Anfangsverteilung eingeben (j/n): ");
   if ( tolower(zeich) == 'j')
   {
      setmanual();
   }
   else
   {
      //setmanual();
   }
}

/*   
    {
      do {
         sprintf(string, "Anzahl der Personen (1,%d): ", zeil*spal);
         pers = getint( string );
      } while (pers<1 || zeil*spal<pers);
      do {                 // Zufaellige Verteilung
         while (neuGen[x=rand()%spal][y=rand()%zeil] == 1)
            ;
         neuGen[x][y] = 1;
      } while (--pers>=1);
   } else {
      outtextxy( 10, 10, getmaxx(), getmaxy(),
                 "Mit der Maus kannst Du nun die Leben setzen/loeschen\n"
                 "Abbruch des Setzens mit einer beliebigen Taste.......");
      getch();

*/


void setmanual(void)
{
   int x,y, xk,yk;
   do
   {
      if(mouse_left() || mouse_right())
      {
         mouse_getpos(&x, &y);
         xk = x/fakts;
         yk = y/faktz;
         if (xk>=0 && xk<spal && yk>=0 && yk<zeil)
         {
            mouse_hide();
            if(feld[xk][yk]==0 && getpixel(x,y) == LIGHTGRAY)
            {
               setalive(xk,yk);
               feld[xk][yk]=1;
               livecells++;
            }
            else if(feld[xk][yk]==1 && getpixel(x,y) == BLUE)
            {
               setdead(xk,yk);
               feld[xk][yk]=0;
               livecells--;
            }

            while(mouse_left() || mouse_right())
               ;
            mouse_show();
         }
      }
   }
   while(!kbhit());
   getch();
   mouse_hide();
}

void setdead(int x, int y)
{
   setfillstyle(SOLID_FILL, LIGHTGRAY);
   bar3d( x*fakts, y*faktz, (x+1)*fakts, (y+1)*faktz, 0 );
}
void setalive(int x, int y)
{
   setfillstyle(SOLID_FILL, BLUE);
   bar3d( x*fakts, y*faktz, (x+1)*fakts, (y+1)*faktz, 0 );
}

int validindex(int x, int y)
{ 
   int valid=1;
   if(x < 0 || x >= spal || y < 0 || y >= zeil)
      valid = 0;
   return valid;
}

int getsum(int x, int y)
{
   int sum = 0;
   if (validindex(x-1,y)==1) 
      sum += feld[x-1][y];
   if(validindex(x-1,y-1)==1)
      sum += feld[x-1][y-1];
   if(validindex(x-1,y+1)==1)
      sum += feld[x-1][y+1];
   if(validindex(x,y-1)==1)
      sum += feld[x][y-1];
   if(validindex(x,y+1)==1)
      sum += feld[x][y+1];
   if(validindex(x+1,y-1)==1)
      sum += feld[x+1][y-1];
   if(validindex(x+1,y+1)==1)
      sum += feld[x+1][y+1];
   if(validindex(x+1,y)==1)
      sum += feld[x+1][y];
   return sum;
}

void gametime(void)
{

   int sum=0,x,y;
   do
   {
      
      for(x=0; x<spal; x++)
      {
         for(y=0; y<zeil; y++)
         {
            sum += getsum(x,y);
            if(sum < 2 || sum > 3)
               feldnew[x][y] = 0;
            else if (sum == 3)
               feldnew[x][y] = 1;
            else 
               feldnew[x][y] = feld[x][y];
            sum=0;
         }
      }

      for(x=0; x<spal; x++)
      {
         for(y=0;y<zeil;y++)
         {
            feld[x][y] = feldnew[x][y];
            if (feldnew[x][y] == 0)
               setdead(x,y);
            else if (feldnew[x][y] == 1)
               setalive(x,y);
            //feldnew[x][y] = 0;
         }
      }
      if (getch() == Key_F3)
         break;
   }
   while(1);
}


/*----------------- spiele ----------------------------------------*/
/*
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
}*/
