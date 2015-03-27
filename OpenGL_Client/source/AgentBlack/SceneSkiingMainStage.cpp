#include "SceneSkiingMainStage.h"
#include <iterator>

SceneSkiingMainStage::SceneSkiingMainStage()
{
	mSceneName = "Basic Skiing";
	for( unsigned int i = 0; i < UCHAR_MAX; ++i )
		mKey[i] = false;
	mLeftButtonDown = false;
	mCurveUpdate = false;
	mStartSkier = false;
	mHeight = 300;
	mAngleY = -30;
}

SceneSkiingMainStage::~SceneSkiingMainStage()
{

}

void SceneSkiingMainStage::Enter()
{	
	Vector2 lClientSize = SCENEMGR_INST->GetClientSize();

	SCENEMGR_INST->SetPerspectiveMode( false );

	SKCONSOLE << "HELP";
	SKCONSOLE << "a/d - Camera Y Angle ";
	SKCONSOLE << "w/s - Camera Z Move ";
	SKCONSOLE << "r/f - Camera Y Move ";
	SKCONSOLE << "Mouse Left - Set Points(MAX 8)";
	SKCONSOLE << "Point Drag - Reset Points";

	mSkier.SetPosition( Vector3( 0, mHeight, lClientSize.y / 2.f ) );
	mSkier.SetVelocityAndIncrement( 100, 0 );
	mStartPos = mSkier.GetPosition();
	mCubePos.resize( 1 );

	mFirework.SetCreateMaxHeight( 600 );
	mFirework.SetCreateRange( 0, lClientSize.x );

	mEyePos = Vector3( 0, 400, 800 );
	mLookatPos = Vector3( lClientSize.x / 2.f, 0, lClientSize.y / 2.f );

	// random Tree
	int lTreeCount = 3 + ( rand() % 3 );

	for( int i = 0; lTreeCount > i; ++i )
	{
		std::shared_ptr< ObjectOutLineCube > lObjTree = std::make_shared< ObjectOutLineCube >();
		lObjTree->SetColor( Vector4( 1.f, 0.5f, 0.f, 1 ) );
		lObjTree->SetSize( 20 );
		lObjTree->SetScale( Vector3( 1, 5, 1 ) );
		
		Vector3 lTreePos;
		lTreePos.x = 50 + rand() % ( (int)lClientSize.x - 50 );
		lTreePos.y = ( 1 - ( lTreePos.x / lClientSize.x ) ) * mHeight;
		lTreePos.z = ( lClientSize.y / 3.f ) + ( rand() % (int)( lClientSize.y / 3.f ) );

		lObjTree->SetPosition( lTreePos );
		mTreeVec.push_back( lObjTree );
	}
	
	mButton.SetButtonSize( 170 );
	mButton.AddButton( "MainMenu", Vector2( 0, 10 ), 1 );
	mButton.AddButton( ">>", Vector2( SCENEMGR_INST->GetClientSize().x - 150, 10 ), 2 );
	mButton.AddButton( "Reset", Vector2( SCENEMGR_INST->GetClientSize().x - 150, 60 ), 3 );
	mButton.AddButton( "Start", Vector2( SCENEMGR_INST->GetClientSize().x - 150, 110 ), 4 );

}

void SceneSkiingMainStage::Exit()
{

}

void SceneSkiingMainStage::Draw()
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

			glBegin( GL_QUADS );
			glColor4f( 1, 1, 1, 1 );
			glVertex3fv( reinterpret_cast< GLfloat* >( &Vector3( 0, mHeight, 0) ) );
			glVertex3fv( reinterpret_cast< GLfloat* >( &Vector3( 0, mHeight, mClientHeight ) ) );
			glColor4f( 0.5f, 0.5f, 0.5f, 1 );
			glVertex3fv( reinterpret_cast< GLfloat* >( &Vector3( mClientWidth, 0, mClientHeight ) ) );
			glVertex3fv( reinterpret_cast< GLfloat* >( &Vector3( mClientWidth, 0, 0 ) ) );

			glEnd();
		}
		glPopMatrix();

		for( auto it : mCubeVec )
			it->Draw();

		glPushMatrix();
		{
			glTranslatef( 0, 40, 0 );
			for( auto it : mTreeVec )
				it->Draw();
		}
		glPopMatrix();
		

		mSkier.Draw();
		
		glPushMatrix();
		{
			glTranslatef( 0, 1, 0 );
			glBegin( GL_LINE_STRIP );
			glColor4f( 0, 0, 0, 1 );
			for( auto it : mLineVec )
			{
				glVertex3fv( reinterpret_cast<GLfloat*>( &it ) );
			}
			glEnd();
		}
		glPopMatrix();

		mFirework.Draw();
		//mButton.Draw();
	}
	glPopMatrix();

}

void SceneSkiingMainStage::Update( double dt )
{
	// Update CurveLine
	int cubeIndex = 0;
	mCubePos[cubeIndex++] = mStartPos;
	for( auto it : mCubeVec )
	{
		mCubePos[cubeIndex++] = it->GetPosition();
	}
	SetMultiCurve( mCubePos, 50, mLineVec );

	if( mStartSkier )
	{
		mSkier.Update( dt );
		mFirework.Update( dt );
		if( !mSkier.GetCollisionTree() )
		{
			for( auto it : mTreeVec )
			{
				if( CollisionCheck3DBox( mSkier.GetMidPosition(), mSkier.GetSize(), it->GetPosition(), it->GetSize() ) )
				{
					mStartSkier = false;
				}
			}
		}
	}

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

void SceneSkiingMainStage::Reshape( int w, int h )
{
	mClientWidth = w;
	mClientHeight = h;
	mButton.Reshape( w, h );
	mFirework.SetCreateRange( 0, w );
	mFirework.SetDrawZaxis( w );
}
	 
void SceneSkiingMainStage::KeyBoard( unsigned char key, int x, int y )
{
	mKey[key] = true;
}

void SceneSkiingMainStage::KeyBoardUp( unsigned char key, int x, int y)
{
	mKey[key] = false;
}

void SceneSkiingMainStage::Mouse( int button, int state, int x, int y )
{
	Vector3 MousePos( x, ( 1 - ( x / (float)mClientWidth ) ) * mHeight, y );

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
								SCENEMGR_INST->SceneChangeByName( "Skiing3" );
								break;
							case 3:
							{
								mStartSkier = false;
								mSkier.SetPosition( mStartPos );
								mSkier.SetCollisionTree( false );
								SCENEMGR_INST->SetPerspectiveMode( false );
							}
								break;
							case 4:
							{
								mStartSkier = true;
								mSkier.SetDest( std::list<Vector3>( mLineVec.begin(), mLineVec.end() ) );
								SCENEMGR_INST->SetPerspectiveMode( true );
							}
								break;
						}
						break;
					}
				}
					mLeftButtonDown = true;
					{
						mSelectCube = nullptr;
						for( auto it : mCubeVec )
						{
							float lHalfSize = it->GetSize() / 2.f;
							Vector3 lObjPos = it->GetPosition();
							Vector2 l2DBoxStart = Vector2( lObjPos.x - lHalfSize, lObjPos.z - lHalfSize );
							Vector2 l2DBoxEnd = Vector2( lObjPos.x + lHalfSize, lObjPos.z + lHalfSize );
							Vector2 lMousePos = Vector2( MousePos.x, MousePos.z );

							if( CollisionCheck2DBox( l2DBoxStart, l2DBoxEnd, lMousePos, lMousePos ) )
								mSelectCube = it;
						}

						if( mSelectCube != nullptr )
						{
							SKCONSOLE << "2d Collision Check";
						}
						else if( mCubeVec.size() <= 8 )
						{
							std::shared_ptr< ObjectOutLineCube > lObj = std::make_shared<ObjectOutLineCube>();
							lObj->SetPosition( MousePos );
							lObj->SetSize( 10 );
							mCubeVec.push_back( lObj );

							Vector3 lObjPos = lObj->GetPosition();
							mCubePos.push_back( lObjPos );

							SKCONSOLE <<
								std::to_string( lObjPos.x ) + ", " +
								std::to_string( lObjPos.y ) + ", " +
								std::to_string( lObjPos.z );
						}
					}
					
					break;
				case GLUT_UP:
					mLeftButtonDown = false;
					break;
			}
			break;
	}
}

void SceneSkiingMainStage::MouseMotion( int x, int y )
{
	Vector3 MousePos( x, ( 1 - ( x / (float)mClientWidth ) ) * mHeight, y );
	if( mLeftButtonDown && ( mSelectCube != nullptr ) )
	{
		mSelectCube->SetPosition( MousePos );
	}
}

bool SceneSkiingMainStage::Command( std::vector< std::string > commandTokens )
{
	if( ( commandTokens[0] == "start" ) && ( commandTokens.size() >= 1 ) )
	{
		mStartSkier = true;
		mSkier.SetDest( std::list<Vector3>( mLineVec.begin(), mLineVec.end() ) );
		SCENEMGR_INST->SetPerspectiveMode( true );

		return true;
	}
	else if( ( commandTokens[0] == "reset" ) && ( commandTokens.size() >= 1 ) )
	{
		mStartSkier = false;
		mSkier.SetPosition( mStartPos );
		mSkier.SetCollisionTree( false );
		SCENEMGR_INST->SetPerspectiveMode( false );
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