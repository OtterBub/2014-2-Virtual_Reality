#include "SceneSkiingBonusStage.h"
#include <iterator>
#include <fstream>

SceneSkiingBonusStage::SceneSkiingBonusStage()
{
	mSceneName = "Bonus Skiing";
	for( unsigned int i = 0; i < UCHAR_MAX; ++i )
		mKey[i] = false;
	mLeftButtonDown = false;
	mCurveUpdate = false;
	mStartSkier = false;
	mHeight = 300;
	mAngleY = -30;
}

SceneSkiingBonusStage::~SceneSkiingBonusStage()
{

}

void SceneSkiingBonusStage::Enter()
{	
	Vector2 lClientSize = SCENEMGR_INST->GetClientSize();

	SCENEMGR_INST->SetPerspectiveMode( false );

	SKCONSOLE << "HELP";
	SKCONSOLE << "a/d - Camera Y Angle ";
	SKCONSOLE << "w/s - Camera Z Move ";
	SKCONSOLE << "r/f - Camera Y Move ";
	SKCONSOLE << "Mouse Left - Set Points(MAX 8)";
	SKCONSOLE << "Point Drag - Reset Points";
	SKCONSOLE << "Add Collision Animation";
	SKCONSOLE << "Add Last Line";
	SKCONSOLE << "Add Camera Follow Skier";
	SKCONSOLE << "Add Snow";

	mSkier.SetPosition( Vector3( 0, mHeight, lClientSize.y / 2.f ) );
	mSkier.SetVelocityAndIncrement( 0, 100 );
	mSkier.SetAutoRotate( true );
	mStartPos = mSkier.GetPosition();
	mCubePos.resize( 1 );

	mFirework.SetCreateMaxHeight( 600 );
	mFirework.SetCreateRange( 0, lClientSize.x );
	mFirework.SetDynamicColor( true );

	mEyePos = Vector3( 0, 400, 500 );
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
	mButton.AddButton( "Save", Vector2( SCENEMGR_INST->GetClientSize().x - 150, 160 ), 5 );
	mButton.AddButton( "Load", Vector2( SCENEMGR_INST->GetClientSize().x - 150, 210 ), 6 );

}

void SceneSkiingBonusStage::Exit()
{

}

void SceneSkiingBonusStage::Draw()
{
	glPushMatrix();
	{
		if( SCENEMGR_INST->GetPerspectiveMode() )
		{
			gluLookAt( mEyePos.x, mEyePos.y, mEyePos.z, 0, 0, 0, 0, 1, 0 );
			glRotatef( mAngleY, 0, 1, 0 );
			glTranslatef( -mLastPos.x, -mLastPos.y, -mLastPos.z );
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

		mSnow.Draw();
		mFirework.Draw();
		mButton.Draw();
	}
	glPopMatrix();

}

void SceneSkiingBonusStage::Update( double dt )
{
	// Update CurveLine
	unsigned int cubeIndex = 0;
	if( mCubePos.size() <= mCubeVec.size() )
	{
		mCubePos.clear();
		mCubePos.reserve( mCubeVec.size() + 1 );
	}
	mCubePos[cubeIndex] = mStartPos;
	for( auto it : mCubeVec )
	{
		cubeIndex++;
		if( cubeIndex >= mCubePos.size() )
			break;
		mCubePos[cubeIndex] = it->GetPosition();
	}
	SetMultiCurve( mCubePos, 50, mLineVec );
				
	if( mCubeVec.size() > 8 )
	{
		Vector3 lLastPos = mCubePos[cubeIndex];
		lLastPos.x = mClientWidth;
		lLastPos.y = 0;
		mLineVec.push_back( lLastPos );
	}

	if( mStartSkier )
	{
		mSkier.Update( dt );
		mSnow.Update( dt );
		mFirework.Update( dt );
		if( !mSkier.GetCollisionTree() )
		{
			mLastPos = mSkier.GetPosition();
			for( auto it : mTreeVec )
			{
				if( CollisionCheck3DBox( mSkier.GetMidPosition(), mSkier.GetSize(), it->GetPosition(), it->GetSize() ) )
				{
					mSkier.SetCollisionTree( true );

					Vector3 lSkierPos = mSkier.GetPosition();
					Vector3 lDestFly;
					lDestFly.x = lSkierPos.x - ( rand() % 300 );
					lDestFly.y = 900;
					lDestFly.z = lSkierPos.z + ( ( rand() % 300 ) - 150 );

					std::list< Vector3 > lList;
					lList.push_back( lDestFly );
					mSkier.SetDest( lList );
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

void SceneSkiingBonusStage::Reshape( int w, int h )
{
	mClientWidth = w;
	mClientHeight = h;
	mButton.Reshape( w, h );
	mSnow.Reshape( w, h );
	mFirework.SetCreateRange( 0, w );
	mFirework.SetDrawZaxis( w );
}
	 
void SceneSkiingBonusStage::KeyBoard( unsigned char key, int x, int y )
{
	mKey[key] = true;
}

void SceneSkiingBonusStage::KeyBoardUp( unsigned char key, int x, int y)
{
	mKey[key] = false;
}

void SceneSkiingBonusStage::Mouse( int button, int state, int x, int y )
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
								break;
							case 3:
							{
								mStartSkier = false;
								mSkier.SetPosition( mStartPos );
								mSkier.SetCollisionTree( false );
								mSnow.Clear();
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
							case 5: // Save
							{
								std::ofstream lMapFile( "Map.txt", std::ios::out );
								
								int count = 0;
								for( auto it : mCubePos )
								{
									count++;
									if( 1 == count )
									{
										continue;
									}

									Vector3 lPos = it;
									lMapFile	<< std::to_string( lPos.x ) << ' '
												<< std::to_string( lPos.y ) << ' '
												<< std::to_string( lPos.z ) << std::endl;
								}
								lMapFile.close();
							}
								break;
							case 6: // Load
							{
								std::ifstream lMapFile( "Map.txt", std::ios::in );

								mCubeVec.clear();
								mCubePos.clear();
								mCubePos.resize( 1 );
								mCubePos.reserve( 1 );

								while( !lMapFile.eof() )
								{
									char garbage;
									Vector3 lLoadPos;
									lMapFile >> lLoadPos.x >> lLoadPos.y >> lLoadPos.z;
									lMapFile.get( garbage );

									if( ( lLoadPos.x == 0 ) &&
										( lLoadPos.y == 0 ) &&
										( lLoadPos.z == 0 ) )
									{
										break;
									}

									std::shared_ptr< ObjectOutLineCube > lObj = std::make_shared<ObjectOutLineCube>();
									lObj->SetPosition( lLoadPos );
									lObj->SetSize( 10 );
									mCubeVec.push_back( lObj );

									Vector3 lObjPos = lObj->GetPosition();
									mCubePos.push_back( lObjPos );
								}

								lMapFile.close();
								
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

void SceneSkiingBonusStage::MouseMotion( int x, int y )
{
	Vector3 MousePos( x, ( 1 - ( x / (float)mClientWidth ) ) * mHeight, y );
	if( mLeftButtonDown && ( mSelectCube != nullptr ) )
	{
		mSelectCube->SetPosition( MousePos );
	}
}

bool SceneSkiingBonusStage::Command( std::vector< std::string > commandTokens )
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
		mSnow.Clear();
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

//Vector3 SceneSkiingBonusStage::GetBezierCurve( std::vector< Vector3 > points, float t )
//{
//	Vector3 lResult;
//
//	if( ( points.size() < 4 ) )
//	{
//		SKCONSOLE << "GetBezierCurve() Size Fail " + std::to_string( points.size() );
//		return lResult;
//	}
//	lResult = 
//		( std::powf( 1 - t, 3 ) * std::powf( t, 0 ) * ( points[0] ) ) +
//		( 3 * std::powf( 1 - t, 2 ) * std::powf( t, 1 ) * ( points[1] ) ) +
//		( 3 * std::powf( 1 - t, 1 ) * std::powf( t, 2 ) * ( points[2] ) ) +
//		( std::powf( 1 - t, 0 ) * std::powf( t, 3 ) * ( points[3] ) );
//
//	return lResult;
//}
//
//std::vector< Vector3 > SceneSkiingBonusStage::CreateCurve( std::vector< Vector3 > points, int separate )
//{
//	std::vector< Vector3 > lResult;
//
//	if( ( points.size() < 4 ) )
//	{
//		SKCONSOLE << "CreateCurve() Size Fail " + std::to_string( points.size() );
//		return lResult;
//	}
//
//	for( float i = 0; ( i / separate ) <= 1; ++i )
//	{
//		float lT = ( i / separate );
//		lResult.push_back( GetBezierCurve( points, lT ) );
//	}
//
//	return lResult;
//}
//
//bool SceneSkiingBonusStage::AddMultiCurve( std::vector< Vector3 > points, int separate, std::vector< Vector3 >& vecDest )
//{
//	std::vector< Vector3 > lResult = CreateCurve( points, separate );
//
//	if( lResult.size() == 0 )
//	{
//		SKCONSOLE << "AddMultiCurve() Get Result Fail " + std::to_string( points.size() );
//		return false;
//	}
//	else 
//	{
//		std::copy( lResult.begin(), lResult.end(), std::back_inserter( vecDest ) );
//
//		return true;
//	}
//}
//
//bool SceneSkiingBonusStage::SetMultiCurve( std::vector< Vector3 > points, int separate, std::vector< Vector3 >& vecDest )
//{
//	int lPointCount = points.size();
//
//	if( lPointCount >= 4 )
//	{
//		std::vector< Vector3 >::iterator it = points.begin();
//		vecDest.clear();
//		while( lPointCount >= 4 )
//		{
//			std::vector< Vector3 > lResult = CreateCurve( std::vector< Vector3 >( it, it + 4 ), separate );
//			std::copy( lResult.begin(), lResult.end(), std::back_inserter( vecDest ) );
//			lPointCount -= 3;
//			if( ( lPointCount ) >= 4 )
//			{
//				it = it + 3;
//			}
//		}
//	}
//	
//
//	return true;
//}