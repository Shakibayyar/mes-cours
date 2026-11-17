/**
 *  Window manager included in a library.
 *
 *  @file    window.cc
 *  @author  Nicolas Wanner
 *  @history 2003-02-26 : created
 */
#include <libio.h>
#include <iostream.h>
#include <directfb.h>
#include <stdio.h>

/* macro for a safe call to DirectFB functions */
#define DFBCHECK(x...)                       \
{ err = x;                                   \
   if ( err != DFB_OK) {                     \
      cout << __FILE__ <<  __LINE__ << "\n"; \
      DirectFBErrorFatal( #x, err );         \
   }                                         \
}

IDirectFBDisplayLayer  *layer  = NULL;
IDirectFBFont          *font   = NULL;
FILE        *debugFile = NULL;

enum  eWindowState {
   WM_IDLE,          // Window is not "used"
   WM_FOCUS,         // Window is "used" 
   WM_MOVE,          // Window is moved
   WM_RESIZE_L,      // Window is resized by the left   side
   WM_RESIZE_R,      // Window is resized by the right  side
   WM_RESIZE_H,      // Window is resized by the bottom side
   WM_RESIZE_RH,     // Window is resized by the right-bottom side
   WM_RESIZE_LH      // Window is resized by the left-bottom  side
};

class cWindow {
   //===========================================================================
   // public methods and attributes
   //===========================================================================
   public    :
      cWindow( );
     ~cWindow( );
      bool Initialise( int posx, int posy, int width, int height );
      void DrawBorder( void );
      void EventLoop(  void );
      inline IDirectFBSurface *GetSurface( void );

   //===========================================================================
   // Private methods
   //===========================================================================
   private   :
      eWindowState cWindow::EventIdle(  DFBWindowEvent *e );
      eWindowState cWindow::EventMove(  DFBWindowEvent *e );
      eWindowState cWindow::EventFocus( DFBWindowEvent *e );
      eWindowState cWindow::EventResize( DFBWindowEvent *e );

   //===========================================================================
   // Private attributes
   //===========================================================================
   private   :
      // Direct Frame Buffer ressources
      IDirectFBWindow *dfbWindow;
      IDirectFBSurface *dfbSurface;
      IDirectFBEventBuffer *dfbBuffer;

      // Window dorder dimensions (Right, Left, Top, Bottom)
      int   bdrR, bdrL, bdrT, bdrB;

      // What is done on the window now
      eWindowState state;

      // Do we need to redraw the window
      bool redraw;

      // Needed by the resize, move functions
      int deltaX, deltaY;
};

// ----------------------------------------------------------------------------
//% @descr : Class constructor
// ----------------------------------------------------------------------------
cWindow::cWindow( )
{
   dfbWindow  = NULL;
   dfbSurface = NULL;
   dfbBuffer  = NULL;
   state = WM_FOCUS;
   bdrR = 5;
   bdrL = 5;
   bdrT = 15;
   bdrB = 5;
};

// ----------------------------------------------------------------------------
//% @descr : Class destructor
// ----------------------------------------------------------------------------
cWindow::~cWindow( )
{
   if ( dfbWindow )
   {
      dfbSurface->Release( dfbSurface );
      dfbWindow->Release(  dfbWindow  );
      dfbBuffer->Release(  dfbBuffer  );
   }
};

// ----------------------------------------------------------------------------
//% @descr : Get the drawing surface handler
//% @return The pointer to the drawing surface
// ----------------------------------------------------------------------------
inline IDirectFBSurface *cWindow::GetSurface( void )
{
   return dfbSurface;
}

// ----------------------------------------------------------------------------
//% @descr : Allocation of the ressources
//% @param  x,y,    The position of the window
//% @param  w,h,    The size of the window
//% @return true on success, false on failure
// ----------------------------------------------------------------------------
bool cWindow::Initialise( int posx, int posy, int width, int height )
{
   DFBWindowDescription  desc;   // Description of the created window
   int                   err;    // error managment

   // Create the DFB window
   desc.flags  = (DFBWindowDescriptionFlags )( DWDESC_POSX | DWDESC_POSY |
                                              DWDESC_WIDTH | DWDESC_HEIGHT );
   desc.posx   = posx;
   desc.posy   = posy;
   desc.width  = width;
   desc.height = height;
   err = layer->CreateWindow( layer, &desc, &dfbWindow );
   if ( err != DFB_OK)
      return false;

   // Allocations
   dfbWindow->GetSurface( dfbWindow, &dfbSurface );
   dfbWindow->SetOpacity( dfbWindow, 0xFF );
   dfbWindow->CreateEventBuffer( dfbWindow, &dfbBuffer );

   // Initialisations
   redraw = true;
   dfbWindow->GrabPointer(  dfbWindow );
   dfbWindow->GrabKeyboard( dfbWindow );

   return true;
};

// ----------------------------------------------------------------------------
//% @descr : Draw the window borders
// ----------------------------------------------------------------------------
void cWindow::DrawBorder( void )
{
   if ( !dfbWindow || !dfbSurface )
      return;

   unsigned int w, h;
   dfbSurface->GetSize( dfbSurface, &w, &h );
   w--; h--;

   dfbSurface->SetColor(      dfbSurface, 0x00, 0x00, 0x00, 0xff );
   dfbSurface->FillRectangle( dfbSurface, 0,    0,    w,    h    );

   // Borders
   dfbSurface->SetColor(      dfbSurface, 0x33, 0xa0, 0xff, 0xff );
   dfbSurface->FillRectangle( dfbSurface, 0, 0, w, bdrT );
   dfbSurface->FillRectangle( dfbSurface, 0, 0, bdrL, h );
   dfbSurface->FillRectangle( dfbSurface, w-bdrR, 0, bdrR, h );
   dfbSurface->FillRectangle( dfbSurface, 0, h-bdrB, w, bdrB );

   /* bright 3D effects */
   dfbSurface->SetColor( dfbSurface, 0xa0, 0xff, 0xff, 0xff );
   dfbSurface->DrawLine( dfbSurface, 0, 0, w, 0   );
   dfbSurface->DrawLine( dfbSurface, 0, 0, 0, h   );
   dfbSurface->DrawLine( dfbSurface, w-bdrR, bdrT, w-bdrR, h-bdrB );
   dfbSurface->DrawLine( dfbSurface, bdrL, h-bdrB, w-bdrR, h-bdrB );

   /* dark 3D effects */
   dfbSurface->SetColor( dfbSurface, 0x10, 0x55, 0x55, 0xff );
   dfbSurface->DrawLine( dfbSurface, 0, h, w, h );
   dfbSurface->DrawLine( dfbSurface, w, 0, w, h );
   dfbSurface->DrawLine( dfbSurface, bdrL, bdrT, bdrL, h-bdrB );
   dfbSurface->DrawLine( dfbSurface, bdrL, bdrT, w-bdrR, bdrT );

   /* commit changes */
   dfbSurface->Flip( dfbSurface, NULL, (DFBSurfaceFlipFlags )0 );
}

// ----------------------------------------------------------------------------
//% @descr : Treat the events when the window is not focused
// ----------------------------------------------------------------------------
eWindowState cWindow::EventIdle( DFBWindowEvent *e )
{
   if ( e->type == DWET_BUTTONUP && e->button==DIBI_LEFT )
   {
      redraw = true;
      return WM_FOCUS;
   }
   return WM_IDLE;
}

// ----------------------------------------------------------------------------
//% @descr : Treat the events when the window is focused
// ----------------------------------------------------------------------------
eWindowState cWindow::EventFocus( DFBWindowEvent *e )
{
   unsigned int w, h;
   int          x, y;

   dfbWindow->GetSize(     dfbWindow, &w, &h );
   dfbWindow->GetPosition( dfbWindow, &x, &y );

   if( e->type == DWET_BUTTONDOWN && e->button == DIBI_LEFT )
   {
      // Click in the top bar => move the window
      if ( e->y < bdrT ) {
         deltaX = x - e->cx;
         deltaY = y - e->cy;
         return WM_MOVE;
      }
      // Click in the left, right or bottom border => resize the window
      if ( e->y > h-bdrB ) {
         deltaY = y+h - e->cy;

         if ( e->x < bdrL ) {
            deltaX = e->cx - x;
            return WM_RESIZE_LH;
         }

         if ( e->x > w-bdrR ) {
            deltaX = x + w - e->cx;
            return WM_RESIZE_RH;
         }
         return WM_RESIZE_H;
      }
      if ( e->x < bdrL ) {
         deltaX = e->cx - x;
         return WM_RESIZE_L;
      }
      if ( e->x > w-bdrR ) {
         deltaX = x + w - e->cx;
         return WM_RESIZE_R;
      }
   }

   return WM_FOCUS;
}

// ----------------------------------------------------------------------------
//% @descr : Treat the events when the window is moved
// ----------------------------------------------------------------------------
eWindowState cWindow::EventMove( DFBWindowEvent *e )
{
   if ( e->type == DWET_BUTTONUP && e->button == DIBI_LEFT )
   {
      deltaX = deltaY = 0;
      return WM_FOCUS;
   }
   else if ( e->type == DWET_MOTION   )
   {
      dfbWindow->MoveTo( dfbWindow, deltaX + e->cx, deltaY + e->cy );
   }

   return WM_MOVE;
}

// ----------------------------------------------------------------------------
//% @descr : Treat the events when the window is resized
// ----------------------------------------------------------------------------
eWindowState cWindow::EventResize( DFBWindowEvent *e )
{
   unsigned int w,  h;
   int          x,  y, t ;

   dfbWindow->GetSize(     dfbWindow, &w, &h );
   dfbWindow->GetPosition( dfbWindow, &x, &y );

   if ( e->type == DWET_BUTTONUP && e->button == DIBI_LEFT )
   {
      deltaX = deltaY = 0;
      return WM_FOCUS;
   }
   else if ( e->type == DWET_MOTION   )
   {
      switch( state )
      {
         case WM_RESIZE_L  :
            t = x + w - bdrL - bdrR;
            w = w - (e->cx - deltaX) + x; 
            x = e->cx - deltaX;
            if ( w < bdrL + bdrR || x > t )  {
               x = t;
               w = bdrL + bdrR;
            }
            break;

         case WM_RESIZE_R  :
            w = deltaX - x + e->cx;
            if ( w < bdrL + bdrR )
               w = bdrL + bdrR;
            break;

         case WM_RESIZE_H  :
            h = deltaY - y + e->cy;
            if ( h < bdrT + bdrB )
               h = bdrT + bdrB;
            break;

         case WM_RESIZE_RH :
            w = deltaX - x + e->cx;
            if ( w < bdrL + bdrR )
               w = bdrL + bdrR;

            h = deltaY - y + e->cy;
            if ( h < bdrT + bdrB )
               h = bdrT + bdrB;
            break;

         case WM_RESIZE_LH :
            t = x + w - bdrL - bdrR;
            w = w - (e->cx - deltaX) + x; 
            x = e->cx - deltaX;
            if ( w < bdrL + bdrR || x > t )  {
               x = t;
               w = bdrL + bdrR;
            }

            h = deltaY - y + e->cy;
            if ( h < bdrT + bdrB )
               h = bdrT + bdrB;
            break;
      }
      dfbWindow->Resize( dfbWindow, w, h );
      dfbWindow->MoveTo( dfbWindow, x, y );
      redraw = true;
   }

   return state;
}

// ----------------------------------------------------------------------------
//% @descr : Treat the events from the window. The methods ends only when the
//%          application terminates
// ----------------------------------------------------------------------------
void cWindow::EventLoop( void )
{
   bool           leave = false;
   DFBWindowEvent event;

   while( !leave )
   {
      // Set a timeout of 15[s] to force the application to quit if we 
      // got problems with the focus
      dfbBuffer->WaitForEventWithTimeout( dfbBuffer, 15, 0 );
      leave = true;


      while( dfbBuffer->GetEvent( dfbBuffer, DFB_EVENT(&event) ) == DFB_OK )
      {
         // WaitForEventWithTimeout was terminated by an event -> stay!
         if ( event.type!=DWET_KEYDOWN || event.key_symbol!=DIKS_ESCAPE )
            leave = false;

         // Finite state machine to make the event processing easyer
         switch( state )
         {
            case WM_IDLE      : state = EventIdle(   &event ); break;
            case WM_FOCUS     : state = EventFocus(  &event ); break;
            case WM_MOVE      : state = EventMove(   &event ); break;
            case WM_RESIZE_L  : state = EventResize( &event ); break;
            case WM_RESIZE_R  : state = EventResize( &event ); break;
            case WM_RESIZE_H  : state = EventResize( &event ); break;
            case WM_RESIZE_RH : state = EventResize( &event ); break;
            case WM_RESIZE_LH : state = EventResize( &event ); break;
            default           : state = EventFocus(  &event ); break;
         }

      }

      // Redraw the border if needed
      if ( redraw ) {
         DrawBorder( );
         redraw = false;
      }

   }
}







int main( int argc, char *argv[] )
{
   IDirectFB                 *dfb;        // Main handler
   DFBDisplayLayerConfig      layerCfg;   // layer configuration
   DFBCardCapabilities        caps;
   cWindow                    window1;    // a managed window
   DFBResult                  err;

   debugFile = fopen( "debug.log", "w+" );
   fprintf( debugFile, "bonjour----------------------------------------\n" );

   
   // Initialise DirectFB environment
   DFBCHECK( DirectFBInit(&argc, &argv) );
   DFBCHECK( DirectFBCreate(&dfb) );
   dfb->GetCardCapabilities( dfb, &caps );
   dfb->GetDisplayLayer( dfb, DLID_PRIMARY, &layer );
   if (!((caps.blitting_flags & DSBLIT_BLEND_ALPHACHANNEL) &&
         (caps.blitting_flags & DSBLIT_BLEND_COLORALPHA  ) ))
   {
      layerCfg.flags      = DLCONF_BUFFERMODE;
      layerCfg.buffermode = DLBM_BACKSYSTEM;
      layer->SetConfiguration( layer, &layerCfg );
   }

   // Open first window
   window1.Initialise( 10, 10, 320, 200 );

   window1.EventLoop( );

   layer->Release( layer );
   dfb->Release( dfb );

   return 42;
}
