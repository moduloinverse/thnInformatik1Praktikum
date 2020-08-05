/* LCGI - Linux C Graphics Interface         */
/*                                           */
/* Version: 4.0 (Qt4.6) (28.07.2010)         */
/* Autor  : Guenther R. Wenninger            */
/* based on work done by: Dr. Helmut Herold  */

#include "graphics.h"

#include <stdarg.h>
#include <stdlib.h>

#include <QtCore/QtCore>
#include <QtGui/QtGui>

#undef DEBUG

#define MAX_PIXMAPS     10000

typedef enum {
    None = -1,
    Arc = 0,          Bar,           Bar3d,      Circle,
    Cleardevice,  Clearviewport, Drawpoly,   Ellipse,
    Fillellipse,  Fillpoly,      Line,       Linerel,
    Lineto,       Moverel,       Moveto,     Outtextxy,
    Pieslice,     Putimage,      Putpixel,   Rectangle,
    Setwritemode, Sector,        Setviewport
} typ_t;

const char *typ_t_s[] = {
    "Arc",
    "Bar",
    "Bar3d",
    "Circle",
    "Cleardevice",
    "Clearviewport",
    "Drawpoly",
    "Ellipse",
    "Fillellipse",
    "Fillpoly",
    "Line",
    "Linerel",
    "Lineto",
    "Moverel",
    "Moveto",
    "Outtextxy",
    "Pieslice",
    "Putimage",
    "Putpixel",
    "Rectangle",
    "Setwritemode",
    "Sector",
    "Setviewport",
};

//********************************************************************* Tabellen

QColor colorMap[] = {   //................................... colorMap
    QColor(   0,   0,   0 ),
    QColor(   0,   0, 255 ),
    QColor(   0, 255,   0 ),
    QColor(   0, 255, 255 ),
    QColor( 255,   0,   0 ),
    QColor( 255,   0, 255 ),
    QColor( 120,  58,  58 ),
    QColor( 211, 211, 211 ),
    QColor( 150, 150, 150 ),
    QColor( 155, 200, 255 ),
    QColor( 150, 255, 150 ),
    QColor( 200, 255, 255 ),
    QColor( 255,  80,  80 ),
    QColor( 255, 190, 255 ),
    QColor( 255, 255,   0 ),
    QColor( 255, 255, 255 ) };

Qt::BrushStyle brushMap[] = {   //........................... brushMap
    Qt::NoBrush,
    Qt::SolidPattern,
    Qt::Dense1Pattern,
    Qt::Dense2Pattern,
    Qt::Dense3Pattern,
    Qt::Dense4Pattern,
    Qt::Dense5Pattern,
    Qt::Dense6Pattern,
    Qt::Dense7Pattern,
    Qt::HorPattern,
    Qt::VerPattern,
    Qt::CrossPattern,
    Qt::BDiagPattern,
    Qt::FDiagPattern,
    Qt::DiagCrossPattern
};

Qt::PenStyle lineMap[] = {   //............................... lineMap
    Qt::NoPen,
    Qt::SolidLine,
    Qt::DashLine,
    Qt::DotLine,
    Qt::DashDotLine,
    Qt::DashDotDotLine
};

Qt::AlignmentFlag hAlignMap[] = { //....................... hAlignMap
    Qt::AlignLeft,
    Qt::AlignHCenter,
    Qt::AlignRight
};

Qt::AlignmentFlag vAlignMap[] = { //....................... vAlignMap
    Qt::AlignBottom,
    Qt::AlignVCenter,
    Qt::AlignTop
};

#if 0
Qt::RasterOp rasterMap[] = {  //............................ rasterMap
    Qt::CopyROP,
    Qt::XorROP,
    Qt::OrROP,
    Qt::AndROP,
    Qt::NotROP
};
#endif

QPainter::CompositionMode rasterMap[] = {
    QPainter::CompositionMode_SourceOver,
    QPainter::CompositionMode_Xor
};

int cursorMap[] = {  //..................................... cursorMap
    Qt::ArrowCursor,      // standard arrow cursor
    Qt::UpArrowCursor,    // upwards arrow
    Qt::CrossCursor,      // crosshair
    Qt::WaitCursor,       // hourglass/watch
    Qt::IBeamCursor,      // ibeam/text entry
    Qt::SizeVerCursor,    // vertical resize
    Qt::SizeHorCursor,    // horizontal resize
    Qt::SizeBDiagCursor,  // diagonal resize (/)
    Qt::SizeFDiagCursor,  // diagonal resize (\)
    Qt::SizeAllCursor,    // all directions resize
    Qt::BlankCursor,      // blank/invisible cursor
    Qt::SplitVCursor,     // vertical bar with left-right
    Qt::SplitHCursor,     // horizontal bar with up-down
    Qt::PointingHandCursor  // pointing hand
};

Qt::Key keyMap[] = {
    Qt::Key_Escape,      // misc keys
    Qt::Key_Tab,
    Qt::Key_Backtab,
    Qt::Key_Backspace,
    Qt::Key_Return,
    Qt::Key_Enter,
    Qt::Key_Insert,
    Qt::Key_Delete,
    Qt::Key_Pause,
    Qt::Key_Print,
    Qt::Key_SysReq,
    Qt::Key_Home,        // cursor movement
    Qt::Key_End,
    Qt::Key_Left,
    Qt::Key_Up,
    Qt::Key_Right,
    Qt::Key_Down,
    Qt::Key_PageUp,
    Qt::Key_PageDown,
    Qt::Key_Shift,        // modifiers
    Qt::Key_Control,
    Qt::Key_Meta,
    Qt::Key_Alt,
    Qt::Key_CapsLock,
    Qt::Key_NumLock,
    Qt::Key_ScrollLock,
    Qt::Key_F1,   // function keys
    Qt::Key_F2,
    Qt::Key_F3,
    Qt::Key_F4,
    Qt::Key_F5,
    Qt::Key_F6,
    Qt::Key_F7,
    Qt::Key_F8,
    Qt::Key_F9,
    Qt::Key_F10,
    Qt::Key_F11,
    Qt::Key_F12,
    Qt::Key_F13,
    Qt::Key_F14,
    Qt::Key_F15,
    Qt::Key_F16,
    Qt::Key_F17,
    Qt::Key_F18,
    Qt::Key_F19,
    Qt::Key_F20,
    Qt::Key_F21,
    Qt::Key_F22,
    Qt::Key_F23,
    Qt::Key_F24,
    Qt::Key_F25,   // F25 .. F35 only on X11
    Qt::Key_F26,
    Qt::Key_F27,
    Qt::Key_F28,
    Qt::Key_F29,
    Qt::Key_F30,
    Qt::Key_F31,
    Qt::Key_F32,
    Qt::Key_F33,
    Qt::Key_F34,
    Qt::Key_F35,
    Qt::Key_Super_L,    // extra keys
    Qt::Key_Super_R,
    Qt::Key_Menu,
    Qt::Key_Hyper_L,
    Qt::Key_Hyper_R,
    Qt::Key_Space,     // 7 bit printable ASCII
    Qt::Key_Exclam,
    Qt::Key_QuoteDbl,
    Qt::Key_NumberSign,
    Qt::Key_Dollar,
    Qt::Key_Percent,
    Qt::Key_Ampersand,
    Qt::Key_Apostrophe,
    Qt::Key_ParenLeft,
    Qt::Key_ParenRight,
    Qt::Key_Asterisk,
    Qt::Key_Plus,
    Qt::Key_Comma,
    Qt::Key_Minus,
    Qt::Key_Period,
    Qt::Key_Slash,
    Qt::Key_0,
    Qt::Key_1,
    Qt::Key_2,
    Qt::Key_3,
    Qt::Key_4,
    Qt::Key_5,
    Qt::Key_6,
    Qt::Key_7,
    Qt::Key_8,
    Qt::Key_9,
    Qt::Key_Colon,
    Qt::Key_Semicolon,
    Qt::Key_Less,
    Qt::Key_Equal,
    Qt::Key_Greater,
    Qt::Key_Question,
    Qt::Key_At,
    Qt::Key_A,
    Qt::Key_B,
    Qt::Key_C,
    Qt::Key_D,
    Qt::Key_E,
    Qt::Key_F,
    Qt::Key_G,
    Qt::Key_H,
    Qt::Key_I,
    Qt::Key_J,
    Qt::Key_K,
    Qt::Key_L,
    Qt::Key_M,
    Qt::Key_N,
    Qt::Key_O,
    Qt::Key_P,
    Qt::Key_Q,
    Qt::Key_R,
    Qt::Key_S,
    Qt::Key_T,
    Qt::Key_U,
    Qt::Key_V,
    Qt::Key_W,
    Qt::Key_X,
    Qt::Key_Y,
    Qt::Key_Z,
    Qt::Key_BracketLeft,
    Qt::Key_Backslash,
    Qt::Key_BracketRight,
    Qt::Key_AsciiCircum,
    Qt::Key_Underscore,
    Qt::Key_QuoteLeft,
    Qt::Key_BraceLeft,
    Qt::Key_Bar,
    Qt::Key_BraceRight,
    Qt::Key_AsciiTilde
};
const int keyMapSize = sizeof(keyMap) / sizeof(keyMap[0]);


//************************************************************ Klasse MalFenster
class MalFenster : public QWidget
{
    Q_OBJECT
    public:
        MalFenster( int w=640, int h=480 );

        //............................................... Tastatur-Funktionen
        int    kbhit( void );
        int    getch( void );
        char   getcharacter( char *text );
        double getdouble( char *text );
        int    getint( char *text );
        char  *getstring( char *text );
        //......................... Bildschirm-, Farben- und Pixel-Funktionen
        void cleardevice( int color );
        int  getmaxcolor( void );
        int  getmaxx( void );
        int  getmaxy( void );
        int  getpixel( int x, int y );
        int  getx( void );
        int  gety( void );
        void putpixel( int x, int y, int color );
        //............... Positionieren, Linien zeichnen und Farbe einstellen
        int  getcolor(void);
        void moverel( int x1, int y1 );
        void moveto( int x1, int y1 );
        void line( int x1, int y1, int x2, int y2 );
        void linerel( int x1, int y1 );
        void lineto( int x1, int y1 );
        void setcolor( int color );
        void setlinestyle( int lstyle, int thickness );
        //................................................. Figuren-Funktionen
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
        //................................................... Text-Funktionen
        void outtextxy( int x1, int y1, int x2, int y2, const char *text );
        int  textheight( void );
        int  textwidth( char *text );
        void settextjustify( int hJust, int vJust );
        void settextstyle( const char *name, int groesse );
        //................................................. Bilder-Funktionen
        void getimage( int left, int top, int right, int bottom, void **imagebuffer );
        void loadimage(const char *filename, void **imagebuffer );
        void putimage( int x, int y, void *imagebuffer, int op );
        void freeimage( void **imagebuffer ); 
        //........................................... Einstellungs-Funktionen
        void setpalette( int farbe, int neufarbe );
        void setrgbpalette( int farbe, int r, int g, int b );
        void setwritemode( int op );
        void setantialiasing(int bo);
        //......................................... Zeichenfenster-Funktionen
        void clearviewport( int color );
        void setviewport(int x1, int y1, int x2, int y2 );
        //................................................... Maus-Funktionen
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


        public slots:
            void readySlot( void );

    protected:
        //virtual void timerEvent( QTimerEvent *e );
        virtual void paintEvent( QPaintEvent *e );
        virtual void keyPressEvent( QKeyEvent *e );
        virtual void mousePressEvent( QMouseEvent *e );
        virtual void mouseReleaseEvent( QMouseEvent *e );
        virtual void mouseMoveEvent( QMouseEvent *e );
        virtual void showEvent( QShowEvent *e );
        virtual void moveEvent( QMoveEvent *e );
        virtual void resizeEvent( QResizeEvent *e );

    private:
        void paint( const QRect &r  );

        QPainter      *imagePainter;
        QPainter      *widgetPainter;
        QImage         im;
        QPainterPath   *paintpath;
        QPixmap        puffer;
        QPoint         currentPos;
        QTimer         *timer;
        int            width, height;
        int            x1, x2, y1, y2;
        int            radius;
        int            start;
        int            end;
        int            xradius;
        int            yradius;
        int            depth;
        QPolygon       points;
        int            noPoints;
        typ_t          type;
        int            keyPressed;
        int            key;
        QColor         color;
        int            colorId;
        QColor         bgColor;
        int            bgColorId;
        QColor         pixelColor;
        int            pixelColorId;
        QPolygon       pointArray;
        Qt::BrushStyle fillStyle;
        QColor         fillColor;
        int            fillColorId;
        int            hJustId;
        int            vJustId;
        int            textAlign;
        QString        fontName;
        int            textGroesse;
        QString        currentText;
        Qt::PenStyle   lineStyle;
        int            lineThick;
        QPixmap        image;
        int            rasterOpId;
        QPainter::CompositionMode   rasterOp;
        int            opTemp;
        double         PI;
        int            clipx1, clipy1, clipx2, clipy2;
        int            mouseCursor;
        int            mouseLeft, mouseMid, mouseRight, mouseButton;
        int            mx1, my1, mx2, my2;
        int            cursorIsVisible;
        bool           mwindow;
        QPixmap        pixmap[MAX_PIXMAPS];
        void          *pixmapAdresse[MAX_PIXMAPS];
        int            pixmapNumber;
        char           statischText[1000];
        QMessageBox    *mbox;
};

#include "graphics.moc"

//*************************************** Funktionen initgraph_ und closegraph

MalFenster *__myM;
QApplication *app;

void initgraph_( int argc, char *argv[], int w, int h ) {
    app = new QApplication( argc, argv );
    __myM = new MalFenster( w, h );
    QObject::connect( qApp, SIGNAL( lastWindowClosed() ),
            __myM, SLOT( readySlot() ) );
}

void closegraph( void ) {
    delete app;
}


//....................................................... MalFenster-Konstruktor
MalFenster::MalFenster( int w, int h ) : QWidget( 0 ) {
    colorId      = BLACK;
    color        = colorMap[BLACK];
    bgColorId    = LIGHTGRAY;
    bgColor      = colorMap[BLUE];
    fillStyle    = brushMap[SOLID_FILL];
    fillColorId  = WHITE;
    fillColor    = colorMap[fillColorId];
    pixelColorId = BLACK;
    pixelColor   = colorMap[BLACK];
    lineStyle    = (Qt::PenStyle)SOLID_LINE;
    lineThick    = 2;
    hJustId      = LEFT_TEXT;
    vJustId      = TOP_TEXT;
    textAlign    = (hAlignMap[hJustId] | vAlignMap[vJustId]);
    fontName     = "Helvetica";
    textGroesse  = 12;
    rasterOpId   = COPY_PUT;
    rasterOp     = rasterMap[rasterOpId];
    keyPressed   = 0;
    currentPos   = QPoint( 0, 0 );
    clipx1 = clipy1 = 0;
    clipx2 = w-1;
    clipy2 = h-1;
    mouseCursor = cursorMap[Qt::ArrowCursor];
    mouseLeft = mouseMid = mouseRight = mouseButton = 0;
    mwindow = false;
    pixmapNumber = 0;
    cursorIsVisible = 1;

    setAttribute(Qt::WA_OpaquePaintEvent);

    imagePainter  = new QPainter;
    widgetPainter = new QPainter;

    mbox = new QMessageBox(0);

    PI = 4*atan(1.0);
    resize( w, h );
    setFixedSize( w, h );
    width  = w;
    height = h;

    type = None;

    im = QImage(size(), QImage::Format_ARGB32);
    imagePainter->begin(&im);
    imagePainter->initFrom(this);
    imagePainter->eraseRect(rect());
    imagePainter->end();

    repaint(); // avoid ugly garbage if window is shown
    show();
}


//********************************************************* Tastatur-Funktionen

//....................................................................... kbhit
int MalFenster::kbhit( void ) {
    qApp->processEvents();
    return keyPressed;
}


//....................................................................... getch
int MalFenster::getch( void ) {
    qApp->processEvents();
    while ( !keyPressed )
        qApp->processEvents();
    keyPressed = 0;
    return key;
}


//................................................................ getcharacter
char MalFenster::getcharacter( char *info ) {
    bool ok;

    QString z = QInputDialog::getText(this, tr("Eingabe eines Zeichens"),
            tr(info), QLineEdit::Normal, "", &ok);

    while ( kbhit() )
        getch();

    qApp->processEvents();
    if ( !ok || z.isEmpty() )
        return ' ';
    return (char )*(z.left(1).toLatin1());
}


//................................................................... getdouble
double MalFenster::getdouble( char *info ) {
    bool ok;

    double z = QInputDialog::getDouble (this, tr("Eingabe einer Double-Zahl"),
            tr(info), 0, -2147483647, 2147483647, 10, &ok);

    while (kbhit())
        getch();
    qApp->processEvents();
    return z;
}

//...................................................................... getint
int MalFenster::getint( char *info ) {
    bool ok;

    int z = QInputDialog::getInteger(this, tr("Eingabe einer Integer-Zahl"),
            tr(info), 0, -2147483647, 2147483647, 1, &ok);
    while (kbhit())
        getch();
    qApp->processEvents();
    return z;
}

//................................................................... getstring
char *MalFenster::getstring( char *info ) {
    bool ok;

    QString z = QInputDialog::getText(this, tr("Eingabe von Text"),
            tr(info), QLineEdit::Normal, "", &ok );
    while (kbhit())
        getch();
    qApp->processEvents();
    for (int i=0; i<z.length(); i++)
        statischText[i] = (char) *(z.mid(i,1).toLatin1());
    statischText[z.length()] = '\0';
    return (char *)statischText;
}


//*********************************** Bildschirm-, Farben- und Pixel-Funktionen


//................................................................. cleardevice
void MalFenster::cleardevice( int color ) {
    bgColorId = color;
    bgColor   = colorMap[color];
    type = Cleardevice;
    repaint();
}


//................................................................. getmaxcolor
int MalFenster::getmaxcolor( void ) {
    return MAXCOLORS;
}

//..................................................................... getmaxx
int MalFenster::getmaxx( void ) {
    return width-1;
}

//..................................................................... getmaxy
int MalFenster::getmaxy( void ) {
    return height-1;
}

//.................................................................... getpixel
int MalFenster::getpixel( int x, int y ) {
    QImage tmp = im.copy(x, y, 1, 1);
    QColor c(tmp.pixel(0, 0));

    for ( int i=0; i<=getmaxcolor(); i++)
        if ( c == colorMap[i] )
            return  i;
    return WHITE;
}

//........................................................................ getx
int MalFenster::getx( void ) {
    return currentPos.x();
}

//........................................................................ gety
int MalFenster::gety( void ) {
    return currentPos.y();
}



//.................................................................... putpixel
void MalFenster::putpixel( int x, int y, int color ) {
    this->x1 = x;
    this->y1 = y;
    this->pixelColorId = color;
    this->pixelColor = colorMap[color];
    type = Putpixel;
    repaint(x, y, 1, 1);
}


//************************* Positionieren, Linien zeichnen und Farbe einstellen

//.................................................................... getcolor
int MalFenster::getcolor(void) {
    return colorId;
}


//........................................................................ line
void MalFenster::line( int x1, int y1, int x2, int y2 ) {
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
    type = Line;
    //repaint(x1-lineThick-5, y1-lineThick-5, x2-x1+lineThick+5, y2-y1+lineThick+5);
    repaint();
}


//..................................................................... linerel
void MalFenster::linerel( int x1, int y1 ) {
    this->x1 = x1;
    this->y1 = y1;
    type = Linerel;
    repaint();
}

//...................................................................... lineto
void MalFenster::lineto( int x1, int y1 ) {
    this->x1 = x1;
    this->y1 = y1;
    type = Lineto;
    repaint();
}

//..................................................................... moverel
void MalFenster::moverel( int x1, int y1 ) {
    this->x1 = x1;
    this->y1 = y1;
    type = Moverel;
    repaint();
}

//...................................................................... moveto
void MalFenster::moveto( int x1, int y1 ) {
    this->x1 = x1;
    this->y1 = y1;
    type = Moveto;
    repaint();
}

//.................................................................... setcolor
void MalFenster::setcolor( int color ) {
    this->colorId = color;
    this->color   = colorMap[color];
}


//................................................................ setlinestyle
void MalFenster::setlinestyle( int lstyle, int thickness ) {
    lineStyle = lineMap[lstyle];
    lineThick = thickness;
}



//********************************************************** Figuren-Funktionen

//......................................................................... arc
void MalFenster::arc( int x, int y, int start, int end, int radius ) {
    this->x1      = x;
    this->y1      = y;
    this->start   = start;
    this->end     = end;
    this->radius  = radius;
    type    =  Arc;
    repaint();
}

//......................................................................... bar
void MalFenster::bar( int x1, int y1, int x2, int y2 ) {
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
    this->type = Bar;
    repaint(x1, y1, x2, y2);
}

//....................................................................... bar3d
void MalFenster::bar3d( int x1, int y1, int x2, int y2, int depth ) {
    if ( x1 <= x2 )  {
        this->x1 = x1;
        this->x2 = x2;
    } else {
        this->x1 = x2;
        this->x2 = x1;
    }
    if ( y1 <= y2 )  {
        this->y1 = y1;
        this->y2 = y2;
    } else {
        this->y1 = y2;
        this->y2 = y1;
    }
    this->depth = depth;
    type = Bar3d;
    repaint();
}
//...................................................................... circle
void MalFenster::circle( int x, int y, int radius ) {
    this->x1     = x;
    this->y1     = y;
    this->radius = radius;
    type =  Circle;
    repaint();
}
//.................................................................... drawpoly
void MalFenster::drawpoly( int numpoints, int *polypoints ) {
    pointArray.resize( numpoints );
    for ( int i=0; i<numpoints*2; i+=2 ) {
        pointArray[ i/2] = QPoint( polypoints[i], polypoints[i+1] );
    }
    type = Drawpoly;
    repaint();
}

//..................................................................... ellipse
void MalFenster::ellipse( int x, int y, int start, int end,
        int xradius, int yradius ) {
    this->x1      = x;
    this->y1      = y;
    this->start   = start;
    this->end     = end;
    this->xradius = xradius;
    this->yradius = yradius;
    type =  Ellipse;
    repaint();
}

//................................................................. fillellipse
void MalFenster::fillellipse( int x, int y, int xradius, int yradius ) {
    this->x1      = x;
    this->y1      = y;
    this->xradius = xradius;
    this->yradius = yradius;
    type =  Fillellipse;
    repaint();
}

//.................................................................... fillpoly
void MalFenster::fillpoly( int numpoints, int *polypoints ) {
    pointArray.resize( numpoints );
    for ( int i=0; i<numpoints*2; i+=2 ) {
        pointArray[ i/2] = QPoint( polypoints[i], polypoints[i+1] );
    }
    type = Fillpoly;
    repaint();
}

//.................................................................... pieslice
void MalFenster::pieslice( int x, int y, int start, int end, int radius ) {
    this->x1      = x;
    this->y1      = y;
    this->start   = start;
    this->end     = end;
    this->radius  = radius;
    type =  Pieslice;
    repaint();
}


//................................................................... rectangle
void MalFenster::rectangle(int x1, int y1, int x2, int y2 ) {
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
    type = Rectangle;
    repaint();
}


//...................................................................... sector
void MalFenster::sector( int x, int y, int start, int end,
        int xradius, int yradius ) {
    this->x1      = x;
    this->y1      = y;
    this->start   = start;
    this->end     = end;
    this->xradius = xradius;
    this->yradius = yradius;
    type =  Sector;
    repaint();
}

//................................................................ setfillstyle
void MalFenster::setfillstyle( int pattern, int color ) {
    fillStyle   = brushMap[pattern];
    fillColorId = color;
    fillColor   = colorMap[fillColorId];
}



//************************************************************* Text-Funktionen


//................................................................... outtextxy
void MalFenster::outtextxy( int x1, int y1, int x2, int y2, const char *text ) {
    currentText = text;
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
    type = Outtextxy;
    repaint(x1, y1, x2-x1+1, y2-y1+1);
    type = Outtextxy;
    repaint(x1, y1, x2-x1+1, y2-y1+1);
}


//.................................................................. textheight
int MalFenster::textheight( void ) {
    int g;
    imagePainter->begin( this );
    imagePainter->setFont( QFont( fontName, textGroesse ) );
    g = imagePainter->fontMetrics().height();
    imagePainter->end();
    return g;
}

//................................................................... textwidth
int MalFenster::textwidth( char *text ) {
    int g;
    imagePainter->begin( this );
    imagePainter->setFont( QFont( fontName, textGroesse ) );
    g = imagePainter->fontMetrics().width( text );
    imagePainter->end();
    return g;
}

//.............................................................. settextJUSTIFy
void MalFenster::settextjustify( int hJust, int vJust ) {
    this->hJustId   = hJust;
    this->vJustId   = vJust;
    this->textAlign = (hAlignMap[hJustId] | vAlignMap[vJustId]);
}

//................................................................ settextstyle
void MalFenster::settextstyle( const char *name, int groesse ) {
    this->fontName = name;
    this->textGroesse = groesse;
}


//********************************************************** Bilder-Funktionen

//.................................................................... getimage
void MalFenster::getimage( int left, int top, int right, int bottom,
        void **imagebuffer ) {
    QImage  tmp_img;

    if (pixmapNumber >= 0 && pixmapNumber < MAX_PIXMAPS) {
        int w = right-left+1;
        int h = bottom-top+1;

        pixmap[pixmapNumber] = QPixmap( w, h );
        tmp_img = im.copy(left, top, w, h);
        pixmap[pixmapNumber].fromImage(tmp_img, Qt::AutoColor);

        pixmapAdresse[pixmapNumber] = *imagebuffer =  &pixmap[pixmapNumber];
        pixmapNumber++;
    }
}

//................................................................... loadimage
void MalFenster::loadimage(const char *filename, void **imagebuffer ) {
    if (pixmapNumber >= 0 && pixmapNumber < MAX_PIXMAPS) {
        if ( ! pixmap[pixmapNumber].load( filename ) ) {
            QString fehlerMeld;
            fehlerMeld.sprintf("cannot open file `%s'", filename );
            QMessageBox::warning(this, tr("Loadimage error"), fehlerMeld);
        }
        pixmapAdresse[pixmapNumber] = *imagebuffer =  &pixmap[pixmapNumber];
        pixmapNumber++;
    }
}

//.................................................................... putimage
void MalFenster::putimage( int x, int y, void *imagebuffer, int op ) {
    for (int i=0; i<pixmapNumber; i++)
        if (pixmapAdresse[i] != NULL && pixmapAdresse[i] == imagebuffer &&
                !pixmap[i].isNull()) {
            this->x1     = x;
            this->y1     = y;
            this->image  = QPixmap(pixmap[i]);
            this->opTemp = op;
            type         = Putimage;
            repaint(x, y, pixmap[i].width(), pixmap[i].height());
            break;
        }
}

//................................................................... freeimage
void MalFenster::freeimage( void **imagebuffer ) {
    for (int i=0; i<pixmapNumber; i++)
        if (pixmapAdresse[i] != NULL && pixmapAdresse[i] == imagebuffer &&
                !pixmap[i].isNull()) {
            pixmap[pixmapNumber] = QPixmap(0, 0);         
            pixmapAdresse[pixmapNumber] = *imagebuffer = NULL;
            break;
        }
}



//***************************************************** Einstellungs-Funktionen

//.................................................................. setpalette
void MalFenster::setpalette( int farbe, int neufarbe ) {
    colorMap[farbe] = colorMap[neufarbe]; 
}

//............................................................... setrgbpalette
void MalFenster::setrgbpalette( int farbe, int r, int g, int b ) {
    colorMap[farbe] = QColor( r, g, b );
}

//................................................................ setwritemode
void MalFenster::setwritemode( int op ) {
    rasterOpId = op;
    rasterOp   = rasterMap[op];
}

void MalFenster::setantialiasing(int bo) {
    widgetPainter->begin(this);

    if(bo > 0)
        widgetPainter->setRenderHint(QPainter::Antialiasing, true);
    else
        widgetPainter->setRenderHint(QPainter::Antialiasing, false);

    widgetPainter->end();
}

//*************************************************** Zeichenfenster-Funktionen

//............................................................... clearviewport
void MalFenster::clearviewport( int color ) {
    bgColorId = color;
    bgColor   = colorMap[color];
    type = Clearviewport;
    repaint();
}

//................................................................. setviewport
void MalFenster::setviewport(int x1, int y1, int x2, int y2 ) {
    this->clipx1 = x1;
    this->clipy1 = y1;
    this->clipx2 = x2;
    this->clipy2 = y2;
    type = Setviewport;
    repaint();
}



//************************************************************* Maus-Funktionen

//................................................................ mouse_setpos
void MalFenster::mouse_setpos( int x, int y ) {
    QCursor::setPos( mapToGlobal( QPoint( x, y ) ) );
}

//................................................................ mouse_getpos
void MalFenster::mouse_getpos( int *x, int *y ) {
    QPoint p = mapFromGlobal( QCursor::pos() );
    *x = p.x();
    *y = p.y();
}

//.................................................................. mouse_left
int MalFenster::mouse_left( void ) {
    qApp->processEvents();
    return mouseLeft;
}

//................................................................... mouse_mid
int MalFenster::mouse_mid( void ) {
    qApp->processEvents();
    return mouseMid;
}

//................................................................. mouse_right
int MalFenster::mouse_right( void ) {
    qApp->processEvents();
    return mouseRight;
}


//................................................................ mouse_button
int MalFenster::mouse_button( void ) {
    qApp->processEvents();
    return mouseButton;
}


//.................................................................. mouse_show
void MalFenster::mouse_show( void ) {
    qApp->setOverrideCursor( QCursor((Qt::CursorShape)cursorMap[mouseCursor]));
    cursorIsVisible = 1;
}

//.................................................................. mouse_hide
void MalFenster::mouse_hide( void ) {
    qApp->setOverrideCursor(QCursor((Qt::CursorShape)cursorMap[blankCursor]));
    cursorIsVisible = 0;
}

//............................................................... mouse_visible
int MalFenster::mouse_visible( void ) {
    return !cursorIsVisible;
}

//............................................................. mouse_setcursor
void MalFenster::mouse_setcursor( int mouseCursor ) {
    this->mouseCursor = mouseCursor;

    setCursor(QCursor((Qt::CursorShape)cursorMap[mouseCursor]));
}

//............................................................. mouse_setwindow
void MalFenster::mouse_setwindow( int x1, int y1, int x2, int y2 ) {
    mwindow = true;
    this->mx1 = x1;
    this->my1 = y1;
    this->mx2 = x2;
    this->my2 = y2;
}

//.............................................................. mouse_inwindow
int MalFenster::mouse_inwindow( int x1, int y1, int x2, int y2 ) {
    QPoint p = mapFromGlobal( QCursor::pos() );
    if ( p.x() >= x1 && p.y() >= y1 &&
            p.x() <= x2 && p.y() <= y2 )
        return 1;
    else
        return 0;
}



//******************************************************** protected-Funktionen
//


//................................................................... readySlot
void MalFenster::readySlot( void ) {
    exit( 1 );
}

//.................................................................. timerEvent
/*
void MalFenster::timerEvent( QTimerEvent * ) {
    printf("timer event");
    repaint();
    qApp->processEvents();
}
*/


//.................................................................. paintEvent
void MalFenster::paintEvent( QPaintEvent *e  ) {
    paint(e->rect());
}


//............................................................... keyPressEvent
void MalFenster::keyPressEvent( QKeyEvent *e ) {
    keyPressed = 1;
    for ( int i=0; i<keyMapSize; i++)
        if ( keyMap[i] == e->key() ) {
            key = i;
            break;
        }
}


//............................................................. mousePressEvent
    void MalFenster::mousePressEvent( QMouseEvent *e ) {
        if ( e->button() == Qt::LeftButton )
            mouseLeft = mouseButton = 1;
        else if ( e->button() == Qt::MidButton ) 
            mouseMid = mouseButton = 1;
        else if ( e->button() == Qt::RightButton ) 
            mouseRight = mouseButton = 1;
    }


//........................................................... mouseReleaseEvent
void MalFenster::mouseReleaseEvent( QMouseEvent * ) {
    mouseLeft = mouseMid = mouseRight = mouseButton = 0;
}


//.............................................................. mouseMoveEvent
void MalFenster::mouseMoveEvent( QMouseEvent * ) {
    if ( mwindow ) {
        QPoint p = mapFromGlobal( QCursor::pos() );
        if ( p.x() < mx1 ) QCursor::setPos( mapToGlobal( QPoint( mx1, p.y() ) ) );
        if ( p.y() < my1 ) QCursor::setPos( mapToGlobal( QPoint( p.x(), my1 ) ) );
        if ( p.x() > mx2 ) QCursor::setPos( mapToGlobal( QPoint( mx2, p.y() ) ) );
        if ( p.y() > my2 ) QCursor::setPos( mapToGlobal( QPoint( p.x(), my2 ) ) );
    }
}


//................................................................... showEvent
void MalFenster::showEvent( QShowEvent * ) {
    qApp->processEvents();
}

//................................................................... moveEvent
void MalFenster::moveEvent( QMoveEvent * ) {
    qApp->processEvents();
}

//................................................................. resizeEvent
void MalFenster::resizeEvent( QResizeEvent * ) {
    //QPixmap save( puffer );
    //puffer = puffer.copy(QRect(QPoint(0, 0), e->size()));
    //puffer.fill( colorMap[bgColorId] );
    //bitBlt( &puffer, 0, 0, &save );
    qApp->processEvents();
}


//....................................................................... paint
void MalFenster::paint( const QRect &r  ) {
    int          x, y, len,
                 top, left, right, bottom;

    int rx = r.x();
    int ry = r.y();
    int rw = r.width();
    int rh = r.height();


    QPainter::CompositionMode opOld;

    widgetPainter->begin(this);

    imagePainter->begin(&im);
    imagePainter->initFrom(this);
    imagePainter->setPen( QPen( colorMap[colorId], lineThick,
                (Qt::PenStyle)lineStyle));
    imagePainter->setBrush(QBrush(colorMap[fillColorId],
                fillStyle));
    //imagePainter->setBrush(fillStyle);
    imagePainter->setCompositionMode(rasterOp);
    imagePainter->setClipRect( clipx1, clipy1, clipx2-clipx1+1,
            clipy2-clipy1+1);

    if(type != None) {

#ifdef DEBUG
        printf("PAINT (%s): REGION: x: %d, y: %d, w: %d, h: %d\n",
                typ_t_s[type], rx, ry, rw, rh);
#endif


        switch (type) {

            case Arc:
                if ( (len = end-start) < 0 )
                    len = 360 - (start - end);
                imagePainter->drawArc( x1-radius, y1-radius, radius*2+1, radius*2+1,
                        start*16, len*16 );
                break;

            case Bar:
                // XXX
                imagePainter->fillRect( x1, y1, x2-x1+1, y2-y1+1,
                        QBrush( colorMap[fillColorId], fillStyle));
                /*
                   imagePainter->fillRect( x1, y1, x2-x1+1, y2-y1+1,
                   QBrush( colorMap[fillColorId]), fillStyle );
                   */
                break;

            case Bar3d:
                imagePainter->fillRect( x1, y1, x2-x1+1, y2-y1+1,
                        QBrush( colorMap[fillColorId], fillStyle ) );
                imagePainter->drawRect( x1, y1, x2-x1+1, y2-y1+1 );
                if ( depth > 0 ) {
                    left = x1;
                    top  = y1;
                    right  = x2;
                    bottom = y2;
                    int dx = (int)(cos( PI/8 ) * depth);
                    int dy = (int)(sin( PI/8 ) * depth);
                    imagePainter->drawLine( left,  top, left+dx,  top-dy );
                    imagePainter->drawLine( right, top, right+dx, top-dy );
                    imagePainter->drawLine( left+dx, top-dy, right+dx, top-dy );
                    imagePainter->drawLine( right, bottom, right+dx, bottom-dy );
                    imagePainter->drawLine( right+dx, top-dy, right+dx, bottom-dy );
                }
                break;

            case Circle:
                imagePainter->drawArc( x1-radius, y1-radius,
                        radius*2+1, radius*2+1, 0, 16*360 );
                break;

            case Cleardevice:
                imagePainter->fillRect( 0, 0, width, height, colorMap[bgColorId] );
                break;

            case Clearviewport:
                imagePainter->fillRect( clipx1, clipy1, clipx2-clipx1+1, clipy2-clipy1+1,
                        colorMap[bgColorId] );
                break;

            case Drawpoly:
                imagePainter->drawPolyline( pointArray );
                break;

            case Ellipse:
                if ( (len = end-start) < 0 )
                    len = 360 - (start - end);
                imagePainter->drawArc( x1-xradius, y1-yradius,
                        xradius*2+1, yradius*2+1, start*16, len*16 );
                break;

            case Fillellipse:
                imagePainter->drawEllipse( x1-xradius, y1-yradius,
                        xradius*2+1, yradius*2+1 );
                break;

            case Fillpoly:
                imagePainter->drawPolygon( pointArray );
                break;

            case Line:
                imagePainter->drawLine( x1, y1, x2, y2 );
                break;

            case Linerel:
                x = currentPos.x();
                y = currentPos.y();
                imagePainter->drawLine( x, y, x+x1, y+y1 );
                break;

            case Lineto:
                x = currentPos.x();
                y = currentPos.y();
                imagePainter->drawLine( x, y, x1, y1 );
                break;

            case Moverel:
                x = currentPos.x();
                y = currentPos.y();
                imagePainter->setBrushOrigin( x+x1, y+y1 );
                break;

            case Moveto:
                imagePainter->setBrushOrigin( x1, y1 );
                break;

            case Outtextxy:
                imagePainter->setPen( colorMap[colorId] );
                imagePainter->setFont( QFont( fontName, textGroesse ) );
                imagePainter->drawText( x1, y1, x2-x1+1, y2-y1+1,
                        textAlign | Qt::TextWordWrap, currentText, 0 );
                break;

            case Pieslice:
                if ( (len = end-start) < 0 )
                    len = 360 - (start - end);
                imagePainter->drawPie( x1-radius, y1-radius, radius*2+1, radius*2+1,
                        start*16, len*16 );
                break;

            case Putimage:
                opOld = imagePainter->compositionMode();
                imagePainter->setCompositionMode( rasterMap[opTemp] );
                imagePainter->drawPixmap ( x1, y1, image );
                imagePainter->setCompositionMode( opOld );
                break;

            case Putpixel:
                imagePainter->setPen( colorMap[pixelColorId] );
                imagePainter->drawPoint( x1, y1 );
                break;

            case Rectangle:
                imagePainter->drawRect(QRect(x1, y1, x2-x1, y2-y1));
                break;

            case Sector:
                if ( (len = end-start) < 0 )
                    len = 360 - (start - end);
                imagePainter->drawPie( x1-xradius, y1-yradius,
                        xradius*2+1, yradius*2+1, start*16, len*16 );
                break;

            case Setviewport:
                imagePainter->setClipRect( clipx1, clipy1,
                        clipx2-clipx1, clipy2-clipy1 );
                break;

            case Setwritemode:
                imagePainter->setCompositionMode( rasterOp );
                break;

            case None:
                break;
        }
        type = None;
    } else {
#ifdef DEBUG
        printf("TYPE  : None\n");
#endif
    }

    currentPos = imagePainter->brushOrigin();

    widgetPainter->drawImage ( rx, ry, im, rx, ry, rw, rh, Qt::AutoColor);
    widgetPainter->end();
    imagePainter->end();

    qApp->processEvents();
}



//********************************************************* Tastatur-Funktionen

int  kbhit( void )  { return __myM->kbhit();     }
int  getch( void )  { return __myM->getch();     }


char getcharacter( char *text, ... ) {
    va_list     az;
    char puffer[5000];
    va_start(az, text);
    vsprintf(puffer, text, az);
    va_end(az);
    return __myM->getcharacter( puffer );
}


double getdouble( char *text, ... ) {
    va_list     az;
    char puffer[5000];
    va_start(az, text);
    vsprintf(puffer, text, az);
    va_end(az);
    return __myM->getdouble( puffer );
}

int getint( char *text, ... ) {
    va_list     az;
    char puffer[5000];
    va_start(az, text);
    vsprintf(puffer, text, az);
    va_end(az);
    return __myM->getint( puffer );
}

char *getstring( char *text, ... ) {
    va_list     az;
    char puffer[5000];
    va_start(az, text);
    vsprintf(puffer, text, az);
    va_end(az);
    return __myM->getstring( puffer );
}


//*********************************** Bildschirm-, Farben- und Pixel-Funktionen

void cleardevice( int color )   { __myM->cleardevice( color );    }

int  getmaxcolor( void )        { return __myM->getmaxcolor();    }
int  getmaxx( void )            { return __myM->getmaxx();        }
int  getmaxy( void )            { return __myM->getmaxy();        }
int  getpixel( int x, int y )   { return __myM->getpixel( x, y ); }
int  getx( void )               { return __myM->getx();           }
int  gety( void )               { return __myM->gety();           }

void putpixel( int x, int y, int color ) {
    __myM->putpixel( x, y, color );
}



//************************* Positionieren, Linien zeichnen und Farbe einstellen

int  getcolor(void)                         { return __myM->getcolor();      }
void line( int x1, int y1, int x2, int y2 ) { __myM->line( x1, y1, x2, y2 ); }
void setcolor( int color )                  { __myM->setcolor( color );      }
void linerel( int x1, int y1 )              { __myM->linerel( x1, y1 );      }
void lineto( int x1, int y1 )               { __myM->lineto( x1, y1 );       }
void moverel( int x1, int y1 )              { __myM-> moverel( x1, y1 );     }
void moveto( int x1, int y1 )               { __myM->moveto( x1, y1 );       }
void setlinestyle( int lstyle, int thick )  { __myM->setlinestyle( lstyle, thick ); }


//********************************************************** Figuren-Funktionen

void arc( int x, int y, int start, int end, int radius ) {
    __myM->arc( x, y, start, end, radius );
}

void bar( int x1, int y1, int x2, int y2 ) {
    __myM->bar( x1, y1, x2, y2 );
}

void bar3d( int x1, int y1, int x2, int y2, int depth ) {
    __myM->bar3d( x1, y1, x2, y2, depth );
}
void circle( int x, int y, int radius ) {
    __myM->circle( x, y, radius );
}
void drawpoly( int numpoints, int *polypoints ) {
    __myM->drawpoly( numpoints, polypoints );
}

void ellipse( int x, int y, int start, int end, int xradius, int yradius ) {
    __myM->ellipse( x, y, start, end, xradius, yradius );
}

void fillellipse( int x, int y, int xradius, int yradius ) {
    __myM->fillellipse( x, y, xradius, yradius );
}

void fillpoly( int numpoints, int *polypoints ) {
    __myM->fillpoly( numpoints, polypoints );
}

void pieslice( int x, int y, int start, int end, int radius ) {
    __myM->pieslice( x, y, start, end, radius );
}


void rectangle(int x1, int y1, int x2, int y2 ) {
    __myM->rectangle( x1, y1, x2, y2 );
}

void sector( int x, int y, int start, int end, int xradius, int yradius ) {
    __myM->sector( x, y, start, end, xradius, yradius );
}

void setfillstyle( int pattern, int color ) {
    __myM->setfillstyle( pattern, color );
}


//************************************************************* Text-Funktionen


void outtextxy( int x1, int y1, int x2, int y2, const char *text, ... ) {
    va_list     az;
    char puffer[5000];
    va_start(az, text);
    vsprintf(puffer, text, az);
    __myM->outtextxy( x1, y1, x2, y2, puffer );
    va_end(az);
}


int  textheight( void )      { return __myM->textheight();      }
int  textwidth( char *text ) { return __myM->textwidth( text ); }

void settextjustify( int hJust, int vJust ) {
    __myM->settextjustify( hJust, vJust );
}

void settextstyle( const char *name, int groesse ) {
    __myM->settextstyle( name, groesse );
}


//*********************************************************** Bilder-Funktionen

void getimage( int left, int top, int right, int bottom, void **imagebuffer ) {
    __myM->getimage( left, top, right, bottom, imagebuffer );
}

void loadimage(const char *filename, void **imagebuffer ) {
    static char buf[5000];
    //char *fn_buf = (char *)malloc(strlen(filename) + 1);
    //strcpy(fn_buf, filename);
    sprintf(buf, "%s", filename);
    __myM->loadimage( buf, imagebuffer );
    //free(fn_buf);
}

void putimage( int x, int y, void *imagebuffer, int op ) {
    __myM->putimage( x, y, imagebuffer, op );
}

void freeimage( void **imagebuffer ) {
    __myM->freeimage( imagebuffer );
}



//***************************************************** Einstellungs-Funktionen

void setpalette( int farbe, int neufarbe ) {
    __myM->setpalette( farbe, neufarbe );
}

void setrgbpalette( int farbe, int r, int g, int b ) {
    __myM->setrgbpalette( farbe, r, g, b );
}

void setwritemode( int op ) { __myM->setwritemode( op ); }

void setantialiasing( int bo ) { __myM->setwritemode( bo ); }



//*************************************************** Zeichenfenster-Funktionen

void clearviewport( int color ) { __myM->clearviewport( color ); }

void setviewport(int x1, int y1, int x2, int y2 ) {
    __myM->setviewport( x1, y1, x2, y2 );
}


//************************************************************* Maus-Funktionen
void mouse_setpos( int x, int y )   { __myM->mouse_setpos( x, y ); }
void mouse_getpos( int *x, int *y ) { __myM->mouse_getpos( x, y ); }

int  mouse_left( void )   { return __myM->mouse_left();   }
int  mouse_mid( void )    { return __myM->mouse_mid();    }
int  mouse_right( void )  { return __myM->mouse_right();  }
int  mouse_button( void ) { return __myM->mouse_button(); }

void mouse_show( void )    { __myM->mouse_show();           }
void mouse_hide( void )    { __myM->mouse_hide();           }
int  mouse_visible( void ) { return __myM->mouse_visible(); }

void mouse_setcursor( int mouseCursor ) {
    __myM->mouse_setcursor( mouseCursor );
}

void mouse_setwindow( int x1, int y1, int x2, int y2 ) {
    __myM->mouse_setwindow( x1, y1, x2, y2 );
}

int  mouse_inwindow( int x1, int y1, int x2, int y2 ) {
    return __myM->mouse_inwindow( x1, y1, x2, y2 );
}
