#include "DrawSystem.h"
#include <ctime>

DrawSystem::DrawSystem()
{
}

DrawSystem::~DrawSystem()
{
}

bool DrawSystem::Init()
{
	// Initialize OpenGL ( GLUT )
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( 1280, 800 );
	glutCreateWindow( "OpenGL Frame" );
	glutDisplayFunc( DrawSystem::DrawScene );
	glutReshapeFunc( DrawSystem::Reshape );
	glutKeyboardFunc( DrawSystem::KeyBoard );
	glutKeyboardUpFunc( DrawSystem::KeyBoardUp );
	glutSpecialFunc( DrawSystem::KeyBoardSpecial );
	glutSpecialUpFunc( DrawSystem::KeyBoardSpecialUp );
	glutMouseFunc( DrawSystem::Mouse );
	glutMotionFunc( DrawSystem::MouseMotion );

	// Set Timer
	glutTimerFunc( 10, DrawSystem::Timer, 0 );

	// Set Random Seed
	srand( (unsigned int)time( NULL ) );

	// GameSystem Initialize;
	GAMESYSTEM_INST->Init();

	return true;
}

bool DrawSystem::Run()
{
	glutMainLoop();
	return true;
} 

GLvoid DrawSystem::DrawScene( GLvoid )
{
	// Screen Clear
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	if( GAMESYSTEM_INST->GetDepthTest() )
		glEnable( GL_DEPTH_TEST );
	else
		glDisable( GL_DEPTH_TEST );

	// Game Scene Draw
	glMatrixMode( GL_MODELVIEW );
	GAMESYSTEM_INST->Draw();

	// Color Initializing
	glColor4f( 1, 1, 1, 1 );

	// Swap Double Buffer
	glutSwapBuffers();
}

GLvoid DrawSystem::Reshape( int w, int h )
{

	if( GAMESYSTEM_INST->GetPerspectiveMode() )
	{
		// DrawSystem Perspective Reshape
		glViewport( 0, 0, w, h );
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluPerspective( 60, (float)w / (float)h, 1.0, 100000.0 );
		glMatrixMode( GL_MODELVIEW );
	}
	else
	{
		// DrawSystem Ortho Reshape
		glViewport( 0, 0, w, h );
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		glOrtho( 0.0, w, 0.0, h, -1000.0, 1000.0 );
		glMatrixMode( GL_MODELVIEW );
	}

	GAMESYSTEM_INST->Reshape( w, h );
}

GLvoid DrawSystem::KeyBoard( unsigned char key, int x, int y )
{
	GAMESYSTEM_INST->KeyBoard( key, x, y );
}

GLvoid DrawSystem::KeyBoardUp( unsigned char key, int x, int y )
{
	GAMESYSTEM_INST->KeyBoardUp( key, x, y );
}

GLvoid DrawSystem::KeyBoardSpecial( int key, int x, int y )
{
	GAMESYSTEM_INST->KeyBoardSpecial( key, x, y );
}

GLvoid DrawSystem::KeyBoardSpecialUp( int key, int x, int y )
{
	GAMESYSTEM_INST->KeyBoardSpecialUp( key, x, y );
}

GLvoid DrawSystem::Mouse( int button, int state, int x, int y )
{
	GAMESYSTEM_INST->Mouse( button, state, x, y );
}

GLvoid DrawSystem::MouseMotion( int x, int y )
{
	GAMESYSTEM_INST->MouseMotion( x, y );
}

GLvoid DrawSystem::Timer( int Value )
{
	GAMESYSTEM_INST->Update( 0 );

	// if GameSystem Call ReshapeFunc
	if( GAMESYSTEM_INST->GetReshape() )
	{
		Vector2 lClientSize = GAMESYSTEM_INST->GetClientSize();
		DrawSystem::Reshape( lClientSize.x, lClientSize.y );
	}

	// Call Timer Function
	glutTimerFunc( 33, DrawSystem::Timer, 0 );

	// Call DisplayFunction
	glutPostRedisplay();
}