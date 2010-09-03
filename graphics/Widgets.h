/*
 * Widgets.h
 *
 *  Created on: 30.06.2010
 */

#ifndef WIDGETS_H_
#define WIDGETS_H_

#include <string>
using std::string;
#include <vector>

#include "Graphics.h"
#include "debug.h"

enum wType { NONE = 0, BLANK, TEXT, BAR};

class Widget
{
public:
	Widget();
	virtual ~Widget();

	virtual bool create( string name, string text, int x=0, int y=0 );

	void setType( wType t ){ type = t; }
	wType getType( ){ return type; }

	void setZ( float z ){ posz = z * 0.1; }
	float getZ( );

	virtual void setParent( Widget* p );

	void addChild( Widget* child );

	virtual void toggleVisibility( );

	virtual void setFont( string, int ) {};
	virtual void setFontColor( int r, int g, int b ) {};
	virtual void setText( string ) {};
	virtual void setTextPosition( float, float ) {};

	virtual void createBar( string name, int* ) {};
	virtual void setBarSize( int size ) {};
	virtual void setBarValue( int val ) {};

	//FIXME: как-то не хорошо так публично.
	string name;
	float width;
	float height;
	float posx;
	float posy;

protected:
	bool visible;
	Graphics* graph;
	Sprite* background;

private:
	wType type;
	float posz;

	Widget* parent;
	std::vector<Widget*> children;
};

class TextWidget: public Widget
{
public:
	TextWidget( );
	~TextWidget( );

	bool create( string name, string text, int x=0, int y=0 );

	void setParent( Widget* p );

	void setFont( string name, int size ){ FontName = name; FontSize = size; }
	void setFontColor( int r, int g, int b );
	void setText( string text );
	void setTextPosition( float x, float y );
	float getTextX( ){ return textx; }
	float getTextY( ){ return texty; }

	void toggleVisibility( );

protected:
	string AddText;

private:

	void textPosition( float x, float y );

	Sprite* StaticTextSprite;
	Sprite* TextSprite;
	float textx, texty;
	string Text;
	string FontName;
	int FontSize;
};

class BarWidget: public TextWidget
{
public:
	BarWidget( );
	~BarWidget( );

	/*bool create( string name, int x=0, int y=0 );*/

	void createBar( string name, int* position );
	void setBarValue( int size );
	void setBarSize( int val ){
		if( val > 0 )
			barmaxvalue = val;
		else
			barmaxvalue = 1;
	}

	void setParent( Widget* p );

	void toggleVisibility( );

protected:
	Sprite* bar;
	int barcolor[3];
	Sprite* top;

private:
	int barvalue;
	int barmaxvalue; // in units
	float barstartx;
	float barwidth; // in pixels
};


#endif /* WIDGETS_H_ */
