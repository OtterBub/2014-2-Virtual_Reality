#ifndef __DRAWSYSTEM_H__
#define __DRAWSYSTEM_H__

#include "GameSystem.h"
// Define Only One GameSystem Singleton
#define GAMESYSTEM_INST GameSystem::GetInstance()

class DrawSystem
{
public:
	DrawSystem();
	~DrawSystem();
	bool Init();
	bool Run();

	static GLvoid DrawScene( GLvoid );
	static GLvoid Reshape( int w, int h );
	static GLvoid KeyBoard( unsigned char key, int x, int y );
	static GLvoid KeyBoardUp( unsigned char key, int x, int y );
	static GLvoid KeyBoardSpecial( int key, int x, int y );
	static GLvoid KeyBoardSpecialUp( int key, int x, int y );
	static GLvoid Mouse( int button, int state, int x, int y );
	static GLvoid MouseMotion( int x, int y );
	static GLvoid Timer( int milsec );

private:

};

#endif