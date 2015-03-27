#include "SceneSkiingTestStage.h"
#include <iterator>

SceneSkiingTestStage::SceneSkiingTestStage()
{
	mSceneName = "Skiing1";
	for( unsigned int i = 0; i < UCHAR_MAX; ++i )
		mKey[i] = false;
	mLeftButtonDown = false;
	mCurveUpdate = false;
	mStartSkier = false;
	mAngleY = -30;
}

SceneSkiingTestStage::~SceneSkiingTestStage()
{

}

void SceneSkiingTestStage::Enter()
{	
	Vector2 lClientSize = SCENEMGR_INST->GetClientSize();

	SCENEMGR_INST->SetPerspectiveMode( false );

	SKCONSOLE << "HELP";
	SKCONSOLE << "a/d - Camera Y Angle ";
	SKCONSOLE << "w/s - Camera Z Move ";
	SKCONSOLE << "r/f - Camera Y Move ";
	SKCONSOLE << "Mouse Left - Set Points(infinite)";

	mSkier.SetPosition( Vector3( 0, 300, lClientSize.y / 2.f ) );
	mSkier.SetVelocityAndIncrement( 100, 0 );
	mCubePos.push_back( mSkier.GetPosition() );

	mEyePos = Vector3( 0, 400, 800 );
	mLookatPos = Vector3( lClientSize.x / 2.f, 0, lClientSize.y / 2.f );

	mButton.SetButtonSize( 200 );
	mButton.AddButton( "MainMenu", Vector2( 0, 10 ), 1 );
	mButton.AddButton( ">>", Vector2( SCENEMGR_INST->GetClientSize().x - 150, 10 ), 2 );
	mButton.AddButton( "Start/stop", Vector2( SCENEMGR_INST->GetClientSize().x - 190, 60 ), 3 );
	mButton.AddButton( "3D/2D", Vector2( SCENEMGR_INST->GetClientSize().x - 190, 110 ), 4 );
}

void SceneSkiingTestStage::Exit()
{

}

void SceneSkiingTestStage::Draw()
{
	glPushMatrix();
	{
		if( SCENEMGR_INST->GetPerspectiveMode() )
		{
			gluLookAt( mEyePos.x, mEyePos.y, mEyePos.z, 0, 0, 0, 0, 1, 0 );
			glRotatef( mAngleY, 0, 1, 0 );
			glTranslatef( -mLookatPos.x, 0, -mLookatPos.z );
		}
		else
		{
			glRotatef( 90, 1, 0, 0 );
			glTranslatef( 0, 0, -mClientHeight );
		}

		// Draw Ground
		glPushMatrix();
		{
			float lGroundSize = 300;
			glBegin( GL_QUADS );
			glColor4f( 0.5, 0, 0.5, 1 );
			glVertex3fv( reinterpret_cast< GLfloat* >( &Vector3( 0, 0, 0) ) );
			glColor4f( 0.5, 0, 1, 1 );
			glVertex3fv( reinterpret_cast< GLfloat* >( &Vector3( mClientWidth, 0, 0 ) ) );
			glColor4f( 1, 0, 0.5, 1 );
			glVertex3fv( reinterpret_cast< GLfloat* >( &Vector3( mClientWidth, 0, mClientHeight ) ) );
			glColor4f( 0.5, 1, 0.5, 1 );
			glVertex3fv( reinterpret_cast< GLfloat* >( &Vector3( 0, 0, mClientHeight ) ) );
			glEnd();
		}
		glPopMatrix();

		for( auto it : mCubeVec )
			it->Draw();

		mSkier.Draw();
		
		glBegin( GL_LINE_STRIP );
		for( auto it : mLineVec )
		{
			glVertex3fv( reinterpret_cast<GLfloat*>( &it ) );
		}
		glEnd();
		mButton.Draw();
	}
	glPopMatrix();

}

void SceneSkiingTestStage::Update( double dt )
{
	if( mCurveUpdate && ( mCubePos.size() >= 4 ) )
	{
		std::vector< Vector3 > lVecNewCurve;
		AddMultiCurve( mCubePos, 100, mLineVec );
		lVecNewCurve = CreateCurve( mCubePos, 50 );
		mSkier.AddDest( std::list< Vector3 >( lVecNewCurve.begin(), lVecNewCurve.end() ) );
		mCurveUpdate = false;
		Vector3 lLastPos = mCubePos[3];
		mCubePos.clear();
		mCubePos.push_back( lLastPos );
	}

	if( mStartSkier )
		mSkier.Update( dt );

	float lSpeed = 500;
	float lAngularSpeed = 50;

	if( mKey['a'] )
	{
		mAngleY -= ( lAngularSpeed * dt );
	}
	if( mKey['d'] )
	{
		mAngleY += ( lAngularSpeed * dt );
	}
	if( mKey['w'] )
	{
		mEyePos.z -= ( lSpeed * dt );
	}
	if( mKey['s'] )
	{
		mEyePos.z += ( lSpeed * dt );
	}
	if( mKey['r'] )
	{
		mEyePos.y += ( lSpeed * dt );
	}
	if( mKey['f'] )
	{
		mEyePos.y -= ( lSpeed * dt );
	}
}

void SceneSkiingTestStage::Reshape( int w, int h )
{
	mClientWidth = w;
	mClientHeight = h;
	mButton.Reshape( w, h );
}
	 
void SceneSkiingTestStage::KeyBoard( unsigned char key, int x, int y )
{
	mKey[key] = true;
}

void SceneSkiingTestStage::KeyBoardUp( unsigned char key, int x, int y)
{
	mKey[key] = false;
}

void SceneSkiingTestStage::Mouse( int button, int state, int x, int y )
{
	Vector3 MousePos( x, ( 1 - ( x / (float)mClientWidth ) ) * 300.f, y );

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
								SCENEMGR_INST->SceneChangeByName( "Skiing2" );
								break;
							case 3:
							{
								mStartSkier = !mStartSkier;
							}
								break;
							case 4:
							{
								bool lPerspectiveMode = SCENEMGR_INST->GetPerspectiveMode();
								SCENEMGR_INST->SetPerspectiveMode( !lPerspectiveMode );
							}
								break;
						}
						break;
					}
				}
					mLeftButtonDown = true;
					if( mCubePos.size() < 4 )
					{
						std::shared_ptr< ObjectOutLineCube > lObj = std::make_shared<ObjectOutLineCube>();
						lObj->SetPosition( MousePos );
						lObj->SetSize( 5 );
						mCubeVec.push_back( lObj );

						Vector3 lObjPos = lObj->GetPosition();
						mCubePos.push_back( lObjPos );

						SKCONSOLE << 
							std::to_string( lObjPos.x ) + ", " +
							std::to_string( lObjPos.y ) + ", " +
							std::to_string( lObjPos.z );
					}
					if( mCubePos.size() >= 4 )
					{
						mCurveUpdate = true;
						SKCONSOLE << "UPDATE " + std::to_string( mCubePos.size() );
					}
					break;
				case GLUT_UP:
					mLeftButtonDown = false;
					break;
			}
			break;
	}
}

void SceneSkiingTestStage::MouseMotion( int x, int y )
{
	Vector2 MousePos( x, mClientHeight - y );

}

bool SceneSkiingTestStage::Command( std::vector< std::string > commandTokens )
{
	if( ( commandTokens[0] == "start" ) && ( commandTokens.size() >= 2 ) )
	{
		if( commandTokens[1] == "on" )
			mStartSkier = true;
		else if( commandTokens[1] == "off" )
			mStartSkier = false;

		return true;
	}
	else if( ( commandTokens[0] == "eye" ) && ( commandTokens.size() >= 4 ) )
	{
		mEyePos = Vector3( std::stof( commandTokens[1] ), std::stof( commandTokens[2] ), std::stof( commandTokens[3] ) );

		return true;
	}
	else
	{
		return false;
	}
}