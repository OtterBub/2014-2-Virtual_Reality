#include "SceneFireworkTest.h"

SceneFireworkTest::SceneFireworkTest()
{
	mDynamicFirework = false;
}

SceneFireworkTest::~SceneFireworkTest()
{
}

void SceneFireworkTest::Enter()
{
	Vector2 lClientSize = SCENEMGR_INST->GetClientSize();
	mFireworkEffect.SetCreateMaxLength( lClientSize.y - 30 );
	mFireworkEffect.SetCreateRange( 0, lClientSize.x );

	mButton.SetButtonSize( 170 );
	mButton.AddButton( "MainMenu", Vector2( 0, 10 ), 1 );
	mButton.AddButton( "Dynamic", Vector2( SCENEMGR_INST->GetClientSize().x - 150, 60 ), 2 );
	mButton.AddButton( ">>", Vector2( SCENEMGR_INST->GetClientSize().x - 150, 10 ), 3 );
}

void SceneFireworkTest::Exit()
{
}

void SceneFireworkTest::Draw()
{
	mFireworkEffect.Draw();
	mButton.Draw();
}

void SceneFireworkTest::Update( double dt )
{
	mFireworkEffect.Update( dt );
}

void SceneFireworkTest::Reshape( int w, int h )
{
	mButton.Reshape( w, h );
}

void SceneFireworkTest::Mouse( int button, int state, int x, int y )
{
	switch( state )
	{
		case GLUT_DOWN:
			switch( button )
			{
				case GLUT_LEFT_BUTTON:
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
								mDynamicFirework = !mDynamicFirework;
								mFireworkEffect.SetDynamicColor( mDynamicFirework );
								break;
							case 3:
								SCENEMGR_INST->SceneChangeByName( "Curve1" );
								break;
						}
					}
					break;
				}
			}
			break;
	}
}

void SceneFireworkTest::MouseMotion( int x, int y )
{
}