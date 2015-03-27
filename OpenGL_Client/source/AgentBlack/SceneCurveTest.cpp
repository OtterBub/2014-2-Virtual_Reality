#include "SceneCurveTest.h"

SceneCurveTest::SceneCurveTest()
{
	mSceneName = "CurveTest";
	for( unsigned int i = 0; i < UCHAR_MAX; ++i )
		mKey[i] = false;
	mLeftButtonDown = false;

	mResult.SetColor( Vector4( 1, 0, 0, 1 ) );
	mResult.SetSize( 10 );
}

SceneCurveTest::~SceneCurveTest()
{

}

void SceneCurveTest::Enter()
{	
	SCENEMGR_INST->SetPerspectiveMode( false );

	SKCONSOLE << "HELP";
	SKCONSOLE << "Mouse Left Click: Set Points";
	SKCONSOLE << "Mouse Drag Y: Change T Value";

	mButton.SetButtonSize( 170 );
	mButton.AddButton( "MainMenu", Vector2( 0, 10 ), 1 );	
	mButton.AddButton( "Reset", Vector2( SCENEMGR_INST->GetClientSize().x - 150, 60 ), 2 );
	mButton.AddButton( ">>", Vector2( SCENEMGR_INST->GetClientSize().x - 150, 10 ), 3 );
}

void SceneCurveTest::Exit()
{

}

void SceneCurveTest::Draw()
{
	glPushMatrix();
	{
		for( auto it : mCubeVec )
			it->Draw();

		mResult.Draw();

		mButton.Draw();
	}
	glPopMatrix();

}

void SceneCurveTest::Update( double dt )
{
	
}

void SceneCurveTest::Reshape( int w, int h )
{
	mClientWidth = w;
	mClientHeight = h;
	mButton.Reshape( w, h );
}
	 
void SceneCurveTest::KeyBoard( unsigned char key, int x, int y )
{
	mKey[key] = true;
}

void SceneCurveTest::KeyBoardUp( unsigned char key, int x, int y)
{
	mKey[key] = false;
}

void SceneCurveTest::Mouse( int button, int state, int x, int y )
{
	Vector2 MousePos( x, mClientHeight - y );

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
							{
								mCubeVec.clear();
								mCubePos.clear();
								mLineVec.clear();
								mResult.SetPosition( Vector3( 0, 0, 0 ) );
							}
								break;
							case 3:
								SCENEMGR_INST->SceneChangeByName( "Curve2" );
								break;
						}
						break;
					}
				}
					mLeftButtonDown = true;
					if( mCubeVec.size() < 4 )
					{
						std::shared_ptr< ObjectOutLineCube > lObj = std::make_shared<ObjectOutLineCube>();
						lObj->SetPosition( Vector3( MousePos.x, MousePos.y, 0 ) );
						lObj->SetSize( 15 );
						mCubeVec.push_back( lObj );
						mCubePos.push_back( lObj->GetPosition() );
					}
					break;
				case GLUT_UP:
					mLeftButtonDown = false;
					break;
			}
			break;
	}
}

void SceneCurveTest::MouseMotion( int x, int y )
{
	Vector2 MousePos( x, mClientHeight - y );

	if( mLeftButtonDown )
	{
		if( mCubeVec.size() >= 4 )
			mResult.SetPosition( GetBezierCurve( mCubePos, MousePos.y / (float)mClientHeight ) );

		SKCONSOLE << "t: " + std::to_string( MousePos.y / (float)mClientHeight );
		/*SKCONSOLE << std::to_string( mResult.GetPosition().x ) + ", " +
					std::to_string( mResult.GetPosition().y ) + ", " +
					std::to_string( mResult.GetPosition().z );*/
	}
}