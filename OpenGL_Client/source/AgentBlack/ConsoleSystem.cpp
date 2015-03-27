#include "ConsoleSystem.h"
#include <gl/glut.h>

ConsoleSystem::ConsoleSystem()
{
	mStringList.push_back( "Console Start" );
	mStringList.push_back( "" );
	mCurrentString = mStringList.begin();
	mCurrentString ++;

	mClientWidth = 0;
	mClientHeight = 0;
}

ConsoleSystem::~ConsoleSystem()
{
}

ConsoleSystem& ConsoleSystem::GetInstance()
{
	static ConsoleSystem instance;
	return instance;
}

void ConsoleSystem::operator<<( std::string str )
{
	std::string lSaveCurrentStr( "" );
	if( mCurrentString != mStringList.end() )
		lSaveCurrentStr = *mCurrentString;
	StringInput( str );

	if( lSaveCurrentStr != "" )
		SetCurrentString( lSaveCurrentStr );
}

void ConsoleSystem::Draw()
{
	// Console Coordinate
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	glOrtho( 0, mClientWidth, -mClientHeight, 0, -1, 1 );

	// Depth Test Off
	glDisable( GL_DEPTH_TEST );

	// Light Off
	glDisable( GL_LIGHTING );

	// Console BackGround Draw
	// Blend On
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE );
	glColor4f( 0.7, 0.7, 0.7, 0.8 );
	glRectf( 0, -425, mClientWidth, 0 );

	// Blend Off
	glDisable( GL_BLEND );

	// Draw Strings
	int lStrNum = 1;
	for( std::string it : mStringList )
	{
		glLineWidth( 2 );
		glColor4f( 0, 0, 0, 1 );
		DrawStrokeText( it.c_str(), 1, -25 * lStrNum, 0, 0.150 );
		lStrNum++;
	}
	// Restore LineWidth 
	glLineWidth( 1 );
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );

	// Restore Depth Test
	glEnable( GL_DEPTH_TEST );
}

void ConsoleSystem::Reshape( int w, int h )
{
	mClientWidth = w;
	mClientHeight = h;
}

void ConsoleSystem::AddCharToCurrentStr( const unsigned char c )
{
	if( mCurrentString != mStringList.end() )
		*mCurrentString += c;
}

void ConsoleSystem::DeleteCharToCurrentStr()
{
	if( mCurrentString != mStringList.end() )
	{
		if( (*mCurrentString).size() > 0 )
			(*mCurrentString).pop_back();
	}
		
}

void ConsoleSystem::StringInput( std::string str )
{
	*mCurrentString = str;
	NextLine();
}

void ConsoleSystem::SetCurrentString( std::string str )
{
	if( mCurrentString != mStringList.end() )
	{
		*mCurrentString = str;
	}
}

std::string ConsoleSystem::NextLine()
{
	std::string lStrReturn;

	if( *mCurrentString == "" )
	{
		return lStrReturn;
	}

	mStringList.push_back( "" );
	if( mCurrentString != mStringList.end() )
	{
		lStrReturn = *mCurrentString;
		mCurrentString++;
	}

	if ( mStringList.size() > 16 )
	{
		mStringList.pop_front();
	}

	return lStrReturn;
}