#include "ButtonUI.h"
#include "UtillFunc.h"
#include "ConsoleSystem.h"

ButtonUI::ButtonUI()
{
	mButtonSize = 100;
}

ButtonUI::~ButtonUI()
{

}
void ButtonUI::Draw()
{
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	glOrtho( 0, mClientSize.x, 0, mClientSize.y, -1, 1 );

	// Light Off
	glDisable( GL_LIGHTING );
	glDisable( GL_DEPTH_TEST );

	float lHalfSize = mButtonSize / 2.f;
	float lHeight = 30;
	// Draw Strings
	for( auto it : mButton )
	{
		glColor4f( 1, 1, 1, 1 );
		glBegin( GL_LINE_LOOP );
		{
			glVertex3f( it.pos.x - 10, it.pos.y - lHeight / 3.f, -0.1 );
			glVertex3f( it.pos.x - 10, it.pos.y + lHeight, -0.1 );
			glVertex3f( it.pos.x + mButtonSize, it.pos.y + lHeight, -0.1 );
			glVertex3f( it.pos.x + mButtonSize, it.pos.y - lHeight / 3.f, -0.1 );
		}
		glEnd();
		glColor4f( 1, 1, 1, 1 );
		DrawStrokeText( it.str.c_str(), it.pos.x, it.pos.y, 0.5, 0.25 );
	}

	glPopMatrix();

	glMatrixMode( GL_MODELVIEW );
}

void ButtonUI::Reshape( int w, int h )
{
	mClientSize.x = w;
	mClientSize.y = h;
}

void ButtonUI::ClearButton()
{
	mButton.clear();
}

void ButtonUI::AddButton( std::string str, Vector2 pos, int id )
{
	Button lButton;
	lButton.str = str;
	lButton.pos = pos;
	lButton.id = id;
	
	mButton.push_back( lButton );
}

void ButtonUI::SetButtonSize( float size )
{
	mButtonSize = size;
}

int ButtonUI::CheckButtonId( int x, int y )
{

	float lHalfSize = mButtonSize / 2.f;
	float lHeight = 30;

	for( auto it : mButton )
	{
		Vector2 l2DBoxStart;
		Vector2 l2DBoxEnd;
		l2DBoxStart.x = it.pos.x - 10;
		l2DBoxStart.y = it.pos.y - lHeight / 3.f;

		l2DBoxEnd.x = it.pos.x + mButtonSize;
		l2DBoxEnd.y = it.pos.y + lHeight;
		if( CollisionCheck2DBox( l2DBoxStart, l2DBoxEnd, Vector2( x, mClientSize.y - y ), Vector2( x, mClientSize.y - y ) ) )
			return it.id;
	}

	return 0;
}