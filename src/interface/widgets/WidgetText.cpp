/*
 * TextWidget.cpp
 *
 *  Created on: 24.03.2012
 *
 */

#include "interface/widgets/WidgetText.h"
#include "graphics/Render.h"
#include "scripts/LuaConfig.h"

#include "safestring.h"


WidgetText::WidgetText( )
{
	FontName = "DejaVuSans";
	FontSize = 12;
	TextX = 0;
	TextY = 0;
	TextAlign = wtNone;
	TextContent = "";
	fBindedCache = 0.00123f;
	iBindedCache = 123000;
}


WidgetText::~WidgetText( )
{

}


bool WidgetText::load( std::string id )
{
	std::string font;
	std::string text;
	std::string talign;
	std::string tvalign;
	int fontsize = 12;
	float lineheight;
	std::vector<int> vcolor;
	LuaConfig* cfg = new LuaConfig;

	cfg->getValue( "text", id, BaseText );
	cfg->getValue( "textx", id, TextX );
	cfg->getValue( "texty", id, TextY );
	cfg->getValue( "textalign", id, talign );
	cfg->getValue( "textvalign", id, tvalign );
	cfg->getValue( "font", id, font );
	cfg->getValue( "fontsize", id, fontsize );
	cfg->getValue( "fontcolor", id, vcolor );
	cfg->getValue( "lineheight", id, lineheight );
	if( !lineheight )
		lineheight = 1.0;

	delete cfg;

	if( talign == "Center" )
		TextAlign = CENTER;
	else if( talign == "Right" )
		TextAlign = RIGHT;
	else
		TextAlign = LEFT;
	if( tvalign == "Middle" )
		TextVAlign = MIDDLE;
	else if( tvalign == "Bottom" )
		TextVAlign = BOTTOM;
	else
		TextVAlign = TOP;

	TextSprite.setPosition( TextX, TextX, getZ() );
	TextSprite.setFont( font, fontsize );
	TextSprite.setFixed( true );
	TextSprite.setLineHeight( lineheight );
	setText( "" );

	for( unsigned int i=0; i < 3; ++i ){
		if( i >= vcolor.size() )
			vcolor.push_back(0);
	}
	setFontColor( (unsigned)vcolor[0], (unsigned)vcolor[1], (unsigned)vcolor[2] );

	if( !Widget::load( id ) )
		return false;

	return true;
}

void WidgetText::updatePosition( )
{
	float posx, posy, height, width;
	width = (float)TextSprite.width();
	height = (float)TextSprite.height();
	if( width + TextX > Width )
		this->Width = width + TextX;
	if( height + TextY > Height )
		this->Height = height + TextY;
	Widget::updatePosition( );
	posx = posy = 0;
	switch(TextAlign){
		case CENTER:
			posx = PosX + this->Width * 0.5f - width * 0.5f + TextX;
			break;
		case RIGHT:
			posx = PosX + this->Width - width + TextX;
			break;
		case LEFT:
		default:
			posx = PosX + TextX;
			break;
	}
	switch(TextVAlign){
			case CENTER:
				posy = PosY - height * 0.5f + this->Height * 0.5f + TextY;
				break;
			case BOTTOM:
				posy = PosY + TextY;
				break;
			case TOP:
			default:
				posy = PosY + this->Height -
				TextSprite.getLineSize() + TextY;
				break;
		}
	TextSprite.setPosition( posx, posy, getZ( ) + 0.1f );
}

void WidgetText::setFontColor( unsigned int r, unsigned int g, unsigned int b )
{
	TextSprite.setColor( r, g, b );
}

void WidgetText::setText( std::string text )
{
	float w, h;
	if( TextContent == text )
		return;
	TextContent = text;
	TextSprite.setText( (BaseText + text).c_str() );
	w = (float)Width;
	h = (float)Height;
	if( !Width || Width < TextSprite.width() )
		w = (float)TextSprite.width();
	if( !Height || Height < TextSprite.height() )
		h = (float)TextSprite.height();
	resize( w, h );
	updatePosition();
}

void WidgetText::setTextPosition( float x, float y )
{
	TextX = x;
	TextY = y;
	updatePosition();
}

void WidgetText::Update( )
{
	if( fBinded && (*fBinded) != fBindedCache ){
		fBindedCache = (*fBinded);
		char d[6];
		snprintf(d, 6, "%.0f", fBindedCache);
		setText( d );
	}else if( iBinded && (*iBinded) != iBindedCache ){
		iBindedCache = (*iBinded);
		char d[6];
		snprintf(d, 6, "%.0i", iBindedCache);
		setText( d );
	}
}

void WidgetText::toggleVisibility( )
{
	Widget::toggleVisibility( );
	TextSprite.setVisible(visible);
	// You need to show cursor every time. No remembering of old state.
	if( isCursorVisible() )
		clearCursorVisible();
}

