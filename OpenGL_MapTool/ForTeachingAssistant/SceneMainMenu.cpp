#include "SceneMainMenu.h"

SceneMainMenu::SceneMainMenu( )
{
	mSceneName = "MainMenu";
}

SceneMainMenu::~SceneMainMenu()
{

}

void SceneMainMenu::Enter()
{
	Vector2 lClientSize = SCENEMGR_INST->GetClientSize();
	SCENEMGR_INST->SetPerspectiveMode( false );

	mButtons.SetButtonSize( 260 );

	float lHeight = lClientSize.y + 350;
	float lButtonX = lClientSize.x / 3.f;

	mButtons.AddButton( "Line Bresenham", Vector2( lButtonX, lHeight + 100 ), 8 );
	mButtons.AddButton( "Firework", Vector2( lButtonX, lHeight + 50 ), 9 );
	mButtons.AddButton( "Curve T", Vector2( lButtonX, lHeight ), 1 );
	mButtons.AddButton( "Curve Line", Vector2( lButtonX, lHeight - 50 ), 2 );
	mButtons.AddButton( "Curve Multi", Vector2( lButtonX, lHeight - 100 ), 3 );
	mButtons.AddButton( "Collision Test", Vector2( lButtonX, lHeight - 150 ), 4 );
	mButtons.AddButton( "BasicFrame", Vector2( lButtonX, lHeight - 200 ), 5 );
	mButtons.AddButton( "SkiingBasic", Vector2( lButtonX, lHeight - 250 ), 6 );
	mButtons.AddButton( "SkiingBonus", Vector2( lButtonX, lHeight - 300 ), 7 );
}

void SceneMainMenu::Exit()
{
}

void SceneMainMenu::Draw()
{
	glColor4f( 1, 1, 1, 1 );
	DrawStrokeText( "Skiing!", SCENEMGR_INST->GetClientSize( ).x / 3.f, SCENEMGR_INST->GetClientSize( ).y - 100, 2, 0.5 );
	DrawStrokeText( "by psk", SCENEMGR_INST->GetClientSize().x * ( 1 / 3.f ), SCENEMGR_INST->GetClientSize().y - 110, 2, 0.1 );
	mButtons.Draw();
}

void SceneMainMenu::Update( double dt )
{
}

void SceneMainMenu::Reshape( int w, int h )
{
	mButtons.Reshape( w, h );
	mButtons.ClearButton();
	
	Vector2 lClientSize = SCENEMGR_INST->GetClientSize();	

	float lHeight = lClientSize.y - 250;
	float lButtonX = lClientSize.x / 3.f;

	mButtons.AddButton( "Line Bresenham", Vector2( lButtonX, lHeight + 100 ), 8 );
	mButtons.AddButton( "Firework", Vector2( lButtonX, lHeight + 50 ), 9 );
	mButtons.AddButton( "Curve T", Vector2( lButtonX, lHeight ), 1 );
	mButtons.AddButton( "Curve Line", Vector2( lButtonX, lHeight - 50 ), 2 );
	mButtons.AddButton( "Curve Multi", Vector2( lButtonX, lHeight - 100 ), 3 );
	mButtons.AddButton( "Collision Test", Vector2( lButtonX, lHeight - 150 ), 4 );
	mButtons.AddButton( "BasicFrame", Vector2( lButtonX, lHeight - 200 ), 5 );
	mButtons.AddButton( "SkiingBasic", Vector2( lButtonX, lHeight - 250 ), 6 );
	mButtons.AddButton( "SkiingBonus", Vector2( lButtonX, lHeight - 300 ), 7 );
}

void SceneMainMenu::Mouse( int button, int state, int x, int y )
{
	int lButtonId = 0;
	if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
	{
		lButtonId = mButtons.CheckButtonId( x, y );
		SKCONSOLE << std::to_string( lButtonId );
	}
	switch( lButtonId )
	{
		case 1:
			SCENEMGR_INST->SceneChangeByName( "Curve1" );
			break;
		case 2:
			SCENEMGR_INST->SceneChangeByName( "Curve2" );
			break;
		case 3:
			SCENEMGR_INST->SceneChangeByName( "Curve3" );
			break;
		case 4:
			SCENEMGR_INST->SceneChangeByName( "Collision" );
			break;
		case 5:
			SCENEMGR_INST->SceneChangeByName( "Skiing1" );
			break;
		case 6:
			SCENEMGR_INST->SceneChangeByName( "Skiing2" );
			break;
		case 7:
			SCENEMGR_INST->SceneChangeByName( "Skiing3" );
			break;
		case 8:
			SCENEMGR_INST->SceneChangeByName( "Line1" );
			break;
		case 9:
			SCENEMGR_INST->SceneChangeByName( "Firework" );
			break;

	}
}