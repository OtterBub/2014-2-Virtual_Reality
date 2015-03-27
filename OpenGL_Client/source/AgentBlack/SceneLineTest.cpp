#include "SceneLineTest.h"

SceneLineTest::SceneLineTest()
{

}

SceneLineTest::~SceneLineTest()
{

}

void SceneLineTest::Enter()
{
	SCENEMGR_INST->SetPerspectiveMode( false );

	mButton.SetButtonSize( 170 );
	mButton.AddButton( "MainMenu", Vector2( 0, 10 ), 1 );	
	mButton.AddButton( ">>", Vector2( SCENEMGR_INST->GetClientSize().x - 150, 10 ), 3 );

}

void SceneLineTest::Exit()
{

} 

void SceneLineTest::Draw()
{
	LineDraw( mStartPos, mEndPos, Vector4( 1, 0, 0, 1 ), Vector4( 0, 1, 0, 1 ) );
	mButton.Draw();
}

void SceneLineTest::Update( double dt )
{

}

void SceneLineTest::Reshape( int w, int h )
{
	mClientSize.x = w;
	mClientSize.y = h;
	mButton.Reshape( w, h );
}

void SceneLineTest::Mouse( int button, int state, int x, int y )
{
	Vector2 lMousePos = Vector2( x, mClientSize.y - y );
	switch( state )
	{
		case GLUT_DOWN:
			switch( button )
			{
				case GLUT_LEFT_BUTTON:
				{
					mLeftMouseDown = true;
					mStartPos = lMousePos;

					int lButtonId = mButton.CheckButtonId( x, y );
					if( lButtonId )
					{
						switch( lButtonId )
						{
							case 1:
								SCENEMGR_INST->SceneChangeByName( "Main" );
								break;
							case 3:
								SCENEMGR_INST->SceneChangeByName( "Firework" );
								break;
						}
					}
					break;
				}
			}
			break;

		case GLUT_UP:
			switch( button )
			{
				case GLUT_LEFT_BUTTON:
					mLeftMouseDown = false;
					mEndPos = lMousePos;
					break;
			}
			break;
	}
}

void SceneLineTest::MouseMotion( int x, int y )
{
	Vector2 lMousePos = Vector2( x, mClientSize.y - y );
	if( mLeftMouseDown )
	{
		mEndPos = lMousePos;
	}
	else
	{

	}
}