#include "SceneCollisionTest.h"

SceneCollisionTest::SceneCollisionTest()
{
	mSceneName = "CollisionTest";
	for( unsigned int i = 0; i < UCHAR_MAX; ++i )
		mKey[i] = false;

	mObjCollisionCube.SetSize( 40 );
	mObjCollisionCube.SetPosition( Vector3( 100, 25, 50 ) );
	mObjCollisionCube.SetColor( Vector4( 0.1f, 0.5f, 0.1f, 1.f ) );
	mObjControlCube.SetSize( 30 );
}

SceneCollisionTest::~SceneCollisionTest()
{

}

void SceneCollisionTest::Enter()
{	
	SCENEMGR_INST->SetPerspectiveMode( true );
	
	SKCONSOLE << "HELP";
	SKCONSOLE << "a/d - Cube X Move ";
	SKCONSOLE << "w/s - Cube Z Move ";
	SKCONSOLE << "r/f - Cube Y Move ";

	mButton.SetButtonSize( 170 );
	mButton.AddButton( "MainMenu", Vector2( 0, 10 ), 1 );
	mButton.AddButton( ">>", Vector2( SCENEMGR_INST->GetClientSize().x - 150, 10 ), 2 );
}

void SceneCollisionTest::Exit()
{

}

void SceneCollisionTest::Draw()
{
	glPushMatrix();
	{
		Vector3 lCubePos = mObjControlCube.GetPosition();

		gluLookAt( -50, 100, 300, lCubePos.x, lCubePos.y, lCubePos.z, 0, 1, 0 );

		// Draw Ground
		glPushMatrix();
		{
			float lGroundSize = 300;
			float lGroundHeight = -80;
			glBegin( GL_QUADS );
			glColor4f( 0.5, 0, 0.5, 1 );
			glVertex3fv( reinterpret_cast< GLfloat* >( &Vector3( lGroundSize, lGroundHeight, lGroundSize ) ) );
			glColor4f( 0.5, 0, 1, 1 );
			glVertex3fv( reinterpret_cast< GLfloat* >( &Vector3( -lGroundSize, lGroundHeight, lGroundSize ) ) );
			glColor4f( 1, 0, 0.5, 1 );
			glVertex3fv( reinterpret_cast< GLfloat* >( &Vector3( -lGroundSize, lGroundHeight, -lGroundSize ) ) );
			glColor4f( 0.5, 1, 0.5, 1 );
			glVertex3fv( reinterpret_cast< GLfloat* >( &Vector3( lGroundSize, lGroundHeight, -lGroundSize ) ) );
			glEnd();
		}
		glPopMatrix();

		mObjControlCube.Draw();
		if( mCollision )
		{
			Vector3 lPos = mObjControlCube.GetPosition();
			glColor4f( 1, 1, 1, 1 );
			DrawStrokeText( "Collision!", lPos.x, lPos.y, lPos.z, 0.5 );
			
		}
		mObjCollisionCube.Draw();
		mButton.Draw();
	}
	glPopMatrix();

}

void SceneCollisionTest::Update( double dt )
{
	if( mKey['a'] )
	{
		mControlPos.x--;
		mObjControlCube.SetPosition( mControlPos );
	}
	if( mKey['d'] )
	{
		mControlPos.x++;
		mObjControlCube.SetPosition( mControlPos );
	}
	if( mKey['w'] )
	{
		mControlPos.z--;
		mObjControlCube.SetPosition( mControlPos );
	}
	if( mKey['s'] )
	{
		mControlPos.z++;
		mObjControlCube.SetPosition( mControlPos );
	}
	if( mKey['r'] )
	{
		mControlPos.y++;
		mObjControlCube.SetPosition( mControlPos );
	}
	if( mKey['f'] )
	{
		mControlPos.y--;
		mObjControlCube.SetPosition( mControlPos );
	}

	static int sCount = 0;

	mCollision = CollisionCheck3DBox( 
		mObjControlCube.GetPosition(), mObjControlCube.GetSize(), 
		mObjCollisionCube.GetPosition(), mObjCollisionCube.GetSize() ) ;
}

void SceneCollisionTest::Reshape( int w, int h )
{
	mButton.Reshape( w, h );
}
	 
void SceneCollisionTest::KeyBoard( unsigned char key, int x, int y )
{
	mKey[key] = true;
}

void SceneCollisionTest::KeyBoardUp( unsigned char key, int x, int y)
{
	mKey[key] = false;
}

void SceneCollisionTest::Mouse( int button, int state, int x, int y )
{
	switch( button )
	{
		case GLUT_LEFT_BUTTON:
			switch( state )
			{
				case GLUT_DOWN:
				{
					int lButtonId = mButton.CheckButtonId( x, y );
					if( lButtonId )
					{
						switch( lButtonId )
						{
							case 1:
								SCENEMGR_INST->SceneChangeByName( "Main" );
								break;
							case 2:
								SCENEMGR_INST->SceneChangeByName( "Skiing1" );
								break;
						}
						break;
					}
				}
			}
	}
}