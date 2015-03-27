#include "SceneMultiCurveLine.h"
#include <iterator>

SceneMultiCurveLine::SceneMultiCurveLine()
{
	mSceneName = "CurveMultiLine";
	for( unsigned int i = 0; i < UCHAR_MAX; ++i )
		mKey[i] = false;
	mLeftButtonDown = false;
	mCurveUpdate = false;

	mResult.SetColor( Vector4( 1, 0, 0, 1 ) );
	mResult.SetSize( 10 );
}

SceneMultiCurveLine::~SceneMultiCurveLine()
{

}

void SceneMultiCurveLine::Enter()
{	
	SCENEMGR_INST->SetPerspectiveMode( false );

	SKCONSOLE << "HELP";
	SKCONSOLE << "Mouse Left Click: Set Points (infinite)";

	mButton.SetButtonSize( 170 );
	mButton.AddButton( "MainMenu", Vector2( 0, 10 ), 1 );	
	mButton.AddButton( "Reset", Vector2( SCENEMGR_INST->GetClientSize().x - 150, 60 ), 2 );
	mButton.AddButton( ">>", Vector2( SCENEMGR_INST->GetClientSize().x - 150, 10 ), 3 );
}

void SceneMultiCurveLine::Exit()
{

}

void SceneMultiCurveLine::Draw()
{
	glPushMatrix();
	{
		for( auto it : mCubeVec )
			it->Draw();
		
		glBegin( GL_LINE_STRIP );
		for( auto it : mLineVec )
		{
			glVertex3fv( reinterpret_cast<GLfloat*>( &it ) );
		}
		glEnd();

		mResult.Draw();
		
	}
	glPopMatrix();
	mButton.Draw();

}

void SceneMultiCurveLine::Update( double dt )
{
	//mLineVec = CreateCurve( mCubePos, 100 );
	if( mCurveUpdate && ( mCubePos.size() >= 4 ) )
	{
		AddMultiCurve( mCubePos, 100, mLineVec );
		mCurveUpdate = false;
		Vector3 lLastPos = mCubePos[3];
		mCubePos.clear();
		mCubePos.push_back( lLastPos );
	}
}

void SceneMultiCurveLine::Reshape( int w, int h )
{
	mClientWidth = w;
	mClientHeight = h;
	mButton.Reshape( w, h );
}
	 
void SceneMultiCurveLine::KeyBoard( unsigned char key, int x, int y )
{
	mKey[key] = true;
}

void SceneMultiCurveLine::KeyBoardUp( unsigned char key, int x, int y)
{
	mKey[key] = false;
}

void SceneMultiCurveLine::Mouse( int button, int state, int x, int y )
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
								SCENEMGR_INST->SceneChangeByName( "Collision" );
								break;
						}
						break;
					}
				}
					mLeftButtonDown = true;
					if( mCubePos.size() < 4 )
					{
						std::shared_ptr< ObjectOutLineCube > lObj = std::make_shared<ObjectOutLineCube>();
						lObj->SetPosition( Vector3( MousePos.x, MousePos.y, 0 ) );
						lObj->SetSize( 15 );
						mCubeVec.push_back( lObj );
						mCubePos.push_back( lObj->GetPosition() );
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

void SceneMultiCurveLine::MouseMotion( int x, int y )
{
	Vector2 MousePos( x, mClientHeight - y );

	if( mLeftButtonDown )
	{
		/*if( mCubeVec.size() >= 4 )
			mResult.SetPosition( GetBezierCurve( mCubePos, MousePos.y / (float)mClientHeight ) );

		SKCONSOLE << "t: " + std::to_string( MousePos.y / (float)mClientHeight );*/
	}
}