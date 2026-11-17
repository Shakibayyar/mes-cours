/**
 *  Label class of a widget library that uses DirectFB for the rendering and the
 *  event managment.
 *
 *  @file    wgt_label.cc
 *  @author  Nicolas Wanner
 *  @history 2003-02-26 : created
 */
#include "iostream.h"
#include "string.h"
#include "wgt_label.hh"

/**
 *  Class constructor
 *  @param parent, The identifier of the parent window
 */
cWgtLabel::cWgtLabel( )
{
   cout << "cWgtLabel::cWgtLabel ( no text )\n";
   text[0] = 0;
};

/**
 *  Class constructor
 *  @param parent, The identifier of the parent window
 */
cWgtLabel::cWgtLabel( char *label )
{
   if ( label ) {
      cout << "cWgtLabel::cWgtLabel ( " << label << " )\n";
      strncpy( text, label, 31 );
      text[31] = 0;
   }
   else {
      cout << "cWgtLabel::cWgtLabel ( null string!!! )\n";
      text[0] = 0;
   }
};

/**
 *  Class destructor
 */
cWgtLabel::~cWgtLabel( )
{
   /* Nothing done yet */
   cout << "cWgtLabel::~cWgtLabel\n";
};

/**
 * Redraw the entire widget.
 */
void cWgtLabel::Draw( void )
{
   cWgtBase::Draw();
   cout << "cWgtLabel::Draw text is " << text << "\n";
};

/**
 *  Set the text label
 *  @param label, the string to be displayed
 */
void cWgtLabel::SetText( char *label )
{
   if ( label ) {
      cout << "cWgtLabel::SetLabel ( " << label << " )\n";
      strncpy( text, label, 31 );
      text[31] = 0;
   }
   else {
      cout << "cWgtLabel::SetLabel ( null string!!! )\n";
      text[0] = 0;
   }
};

/**
 *  Get the text label
 *  @return A pointer to the string
 */
char *cWgtLabel::GetText( void )
{
   if ( text[0] == 0 )
      return NULL;
   return text;
};

