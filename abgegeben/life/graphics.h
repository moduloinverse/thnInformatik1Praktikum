/* LCGI - Linux C Graphics Interface         */
/*                                           */
/* Version: 4.0 (Qt4.6) (28.07.2010)         */
/* Autor  : Guenther R. Wenninger            */
/* based on work done by: Dr. Helmut Herold  */

#ifndef HAVE__GRAPHICS_H
#define HAVE__GRAPHICS_H

#include <stdio.h>
#include <math.h>

#ifndef WIN32
  #include <unistd.h>
#endif

enum { BLACK,    BLUE,         GREEN,    CYAN,      RED,        MAGENTA,
       BROWN,    LIGHTGRAY,    DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN,
       LIGHTRED, LIGHTMAGENTA, YELLOW,   WHITE, MAXCOLORS = WHITE };

enum { EMPTY_FILL,   SOLID_FILL,   DENSE1_FILL,  DENSE2_FILL, DENSE3_FILL,
       DENSE4_FILL,  DENSE5_FILL,  DENSE6_FILL,  DENSE7_FILL,
       HORLINE_FILL, VERLINE_FILL, CROSS_FILL,
       LDIAG_FILL,   RDIAG_FILL,   CROSSDIAG_FILL,
       MAXFILLSTYLE = CROSSDIAG_FILL };

enum { NO_LINE,     SOLID_LINE,    DASHED_LINE,
       DOTTED_LINE, DASH_DOT_LINE, DASH_DOT_DOT_LINE,
       MAXLINESTYLE = DASH_DOT_DOT_LINE                 };

enum { LEFT_TEXT,   HCENTER_TEXT, RIGHT_TEXT  };
enum { BOTTOM_TEXT, VCENTER_TEXT, TOP_TEXT    };

enum { COPY_PUT, XOR_PUT, OR_PUT, AND_PUT, NOT_PUT };

enum { arrowCursor,     upArrowCursor, crossCursor,   waitCursor,
       ibeamCursor,     sizeVerCursor, sizeHorCursor, sizeBDiagCursor,
       sizeFDiagCursor, sizeAllCursor, blankCursor,   splitVCursor,
       splitHCursor,    pointingHandCursor
};

enum {
 //...... verschiedene Tasten
    Key_Escape, Key_Tab,   Key_Backtab, Key_Backspace,
    Key_Return, Key_Enter, Key_Insert,  Key_Delete,
    Key_Pause,  Key_Print, Key_Sysreq,
 //...... Tasten zur Cursor-Steuerung
    Key_Home,   Key_End,
    Key_Left,   Key_Up,       Key_Right, Key_Down,
    Key_Pageup, Key_Pagedown,
 //...... Umschalt-Tasten
    Key_Shift,    Key_Control, Key_Meta,       Key_Alt,
    Key_Capslock, Key_Numlock, Key_Scrolllock,
 //...... Funktions-Tasten
    Key_F1,  Key_F2,  Key_F3,  Key_F4,  Key_F5,  Key_F6,  Key_F7,  Key_F8,  Key_F9,
    Key_F10, Key_F11, Key_F12, Key_F13, Key_F14, Key_F15, Key_F16, Key_F17, Key_F18,
    Key_F19, Key_F20, Key_F21, Key_F22, Key_F23, Key_F24,
    Key_F25, Key_F26, Key_F27, Key_F28, Key_F29,
    Key_F30, Key_F31, Key_F32, Key_F33, Key_F34, Key_F35,
 //...... Sonder-Tasten
    Key_Super_L, Key_Super_R, Key_Menu, Key_Hyper_L, Key_Hyper_R,
 //...... 7-Bit druckbare ASCII-Tasten
    Key_Space,     Key_Exclam,     Key_Quotedbl,  Key_Numbersign,
    Key_Dollar,    Key_Percent,    Key_Ampersand, Key_Apostrophe,
    Key_Parenleft, Key_Parenright, Key_Asterisk,  Key_Plus,
    Key_Comma,     Key_Minus,      Key_Period,    Key_Slash,
    Key_0, Key_1, Key_2, Key_3, Key_4, Key_5, Key_6, Key_7, Key_8, Key_9,
    Key_Colon, Key_Semicolon,
    Key_Less,  Key_Equal,     Key_Greater, Key_Question, Key_At,
    Key_A, Key_B, Key_C, Key_D, Key_E, Key_F, Key_G, Key_H, Key_I, Key_J,
    Key_K, Key_L, Key_M, Key_N, Key_O, Key_P, Key_Q, Key_R, Key_S, Key_T,
    Key_U, Key_V, Key_W, Key_X, Key_Y, Key_Z,
    Key_Bracketleft, Key_Backslash, Key_Bracketright, Key_Asciicircum,
    Key_Underscore,  Key_Quoteleft, Key_Braceleft,    Key_Bar,
    Key_Braceright,  Key_Asciitilde
};

#ifdef __cplusplus
extern "C" {
#endif


//....................................... initgraph_ und closegraph-Funktionen
   void initgraph_( int argc, char *argv[], int w, int h );
   void closegraph( void );
//........................................................ Tastatur-Funktionen
   int    kbhit( void );
   int    getch( void );
   char   getcharacter( char *text, ... );
   double getdouble( char *text, ... );
   int    getint( char *text, ... );
   char  *getstring( char *text, ... );
//.................................. Bildschirm-, Farben- und Pixel-Funktionen
   void cleardevice( int color );
   int  getmaxcolor( void );
   int  getmaxx( void );
   int  getmaxy( void );
   int  getpixel( int x, int y );
   int  getx( void );
   int  gety( void );
   void putpixel( int x, int y, int color );
//........................ Positionieren, Linien zeichnen und Farbe einstellen
   int  getcolor(void);
   void line( int x1, int y1, int x2, int y2 );
   void linerel( int x1, int y1 );
   void lineto( int x1, int y1 );
   void moverel( int x1, int y1 );
   void moveto( int x1, int y1 );
   void setcolor( int color );
   void setlinestyle( int lstyle, int thickness );
//......................................................... Figuren-Funktionen
   void arc( int x, int y, int start, int end, int radius );
   void bar( int x1, int y1, int x2, int y2 );
   void bar3d( int x1, int y1, int x2, int y2, int depth );
   void circle( int x, int y, int radius );
   void drawpoly( int numpoints, int *polypoints );
   void ellipse( int x, int y, int start, int end, int xradius, int yradius );
   void fillellipse( int x, int y, int xradius, int yradius );
   void fillpoly( int numpoints, int *polypoints );
   void pieslice( int x, int y, int start, int end, int radius );
   void rectangle(int x1, int y1, int x2, int y2 );
   void sector( int x, int y, int start, int end, int xradius, int yradius );
   void setfillstyle( int pattern, int color );
//............................................................ Text-Funktionen
   void outtextxy( int x1, int y1, int x2, int y2, const char *text, ... );
   int  textheight( void );
   int  textwidth( char *text );
   void settextjustify( int hJust, int vJust );
   void settextstyle( const char *name, int groesse );
//.......................................................... Bilder-Funktionen
   void getimage( int left, int top, int right, int bottom, void **imagebuffer );
   void loadimage(const char *filename, void **imagebuffer );
   void putimage( int x, int y, void *imagebuffer, int op );
   void freeimage( void **imagebuffer );
//.................................................... Einstellungs-Funktionen
   void setpalette( int farbe, int neufarbe );
   void setrgbpalette( int farbe, int r, int g, int b );
   void setwritemode( int op );
   void setantialiasing( int bo );
//.................................................. Zeichenfenster-Funktionen
   void clearviewport( int color );
   void setviewport(int x1, int y1, int x2, int y2 );
//............................................................ Maus-Funktionen
   void mouse_setpos( int x, int y );
   void mouse_getpos( int *x, int *y );
   int  mouse_left( void );
   int  mouse_mid( void );
   int  mouse_right( void );
   int  mouse_button( void );
   void mouse_show( void );
   void mouse_hide( void );
   int  mouse_visible( void );
   void mouse_setcursor( int mouseCursor );
   void mouse_setwindow( int x1, int y1, int x2, int y2 );
   int  mouse_inwindow( int x1, int y1, int x2, int y2 );
//..............................................................................

#ifdef __cplusplus
}
#endif

#define initgraph(w,h)  initgraph_( argc, argv, w, h )
#define delay(ms)       usleep(ms*1000)
#endif /* HAVE__GRAPHICS_H */
