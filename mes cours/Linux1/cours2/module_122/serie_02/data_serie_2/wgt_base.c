/**
 *  Base class of a widget library that uses DirectFB for the rendering and the
 *  event managment.
 *
 *  @file    wgt_base.cc
 *  @author  Nicolas Wanner
 *  @history 2003-02-26 : created
 */
#include "iostream.h"
#include "wgt_base.hh"

/** ----------------------------------------------------------------------------
 *  Class constructor
 *  @param parent, The identifier of the parent window
 */
cWgtBase::cWgtBase( ) {
   wnd = NULL;
};

/** ----------------------------------------------------------------------------
 *  Class destructor
 */
cWgtBase::~cWgtBase( ) {
};

/** ----------------------------------------------------------------------------
 * Initialise the widget. MUST be called after the creation
 * @param  parent, The window where the widget is drawn
 * @param posx  &nbsp; posy,   position
 * @param width &nbsp; height, dimension
 * @return true on success, false on failure
 */
bool cWgtBase::Initialise( cWindow *parent,
                           unsigned int posx=0,  unsigned int posy=0,
                           unsigned int width=0, unsigned int height=0 )
{
   bool retval = false;
   cout << "cWgtBase::Initialise\n";
   if ( parent ) {
      wnd = parent;
      SetPosition( posx, posy );
      SetSize( widht, height  );
      flags = border = round = 0;
      backCol   = 0xffa0a0a0;  // aa rr gg bb
      darkCol   = 0xff404040;  // aa rr gg bb
      brightCol = 0xfff0f0f0;  // aa rr gg bb
      retval = true;
   }
   return retval;
};

/** ----------------------------------------------------------------------------
 * Set the current size of the widget
 * @param width &space; height, new size 
 */
void cWgtBase::SetSize( unsigned int width, unsigned int height )
{
   cout << "cWgtBase::SetSize ( " << width << ", " << height << " )\n";
   w = width;
   h = height;
};

/**
 * Reads the current size of the widget
 * @param width &space; height, returns the size of the widgets
 */
void cWgtBase::GetSize( unsigned int &width, unsigned int &height )
{
   cout << "cWgtBase::GetSize ( " << w << ", " << h << " )\n";
   width = w;
   height = h;
};

/**
 * Set the current position of the widget
 * @param posx &space; posy, new position
 */
void cWgtBase::SetPosition( unsigned int posx,  unsigned int posy  )
{
   cout << "cWgtBase::SetPosition ( " << posx << ", " << posy << " )\n";
   x = posx;
   y = posy;
};

/**
 * Reads the current size of the widget
 * @param posx &space; y, returns position of the widgets
 */
void cWgtBase::GetPosition( unsigned int &posx, unsigned int &posy )
{
   cout << "cWgtBase::GetPosition ( " << x << ", " << y << " )\n";
   posx = x;
   posy = y;
};

/**
 * Redraw the entire widget.
 */
void cWgtBase::Draw( void )
{
   cout << "cWgtBase::Draw, border size is " << border << "\n";
};

/**
 * Manages the events
 */
void cWgtBase::Event( cEvent event )
{
   cout << "cWgtBase::Event " << event << "\n";
};


bool cWgtBase::AddCallback( int type, int (*fct)( cEvent event ) )
{
   cout << "cWgtBase::AddCallback " << "\n";
};

bool cWgtBase::DelCallback( int type, int (*fct)( cEvent event ) )
{
   cout << "cWgtBase::DelCallback " << "\n";
};

