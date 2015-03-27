#include "SceneManager.h"
#include "ConsoleSystem.h"
#include <string>

// other Scenes
#include "SceneCollisionTest.h"
#include "SceneCurveTest.h"
#include "SceneCurveLine.h"
#include "SceneMultiCurveLine.h"
#include "SceneSkiingTestStage.h"
#include "SceneSkiingMainStage.h"
#include "SceneSkiingBonusStage.h"
#include "SceneMainMenu.h"
#include "SceneLineTest.h"
#include "SceneFireworkTest.h"


SceneManager::SceneManager()
{
	mCurrentScene = nullptr;
	mSceneChange = false;
}

SceneManager::~SceneManager()
{

}

SceneManager* SceneManager::GetInstance()
{
	static SceneManager inst;
	return &inst;
}

void SceneManager::Init( std::shared_ptr< GameSystem > gamesys )
{
	mGameSys = gamesys;
	SceneChange ( std::shared_ptr< SceneMainMenu >( new SceneMainMenu() ) );
}


void SceneManager::Draw()
{
	if( mCurrentScene )
		mCurrentScene->Draw();
}

void SceneManager::Update( double dt )
{
	if( mCurrentScene )
		mCurrentScene->Update( dt );

	if( clock() - mChangeTime >= 1000 )
	{
		mSceneChange = false;
	}
}

void SceneManager::Reshape( int w, int h )
{
	if( mCurrentScene )
		mCurrentScene->Reshape( w, h );
	mClientWidth = w;
	mClientHeight = h;
}

void SceneManager::KeyBoard( unsigned char key, int x, int y )
{
	if( mCurrentScene )
		mCurrentScene->KeyBoard( key, x, y );
}

void SceneManager::KeyBoardUp( unsigned char key, int x, int y )
{
	if( mCurrentScene )
		mCurrentScene->KeyBoardUp( key, x, y );
}

void SceneManager::KeyBoardSpecial( int key, int x, int y )
{
	if( mCurrentScene )
		mCurrentScene->KeyBoardSpecial( key, x, y );
}

void SceneManager::KeyBoardSpecialUp( int key, int x, int y )
{
	if( mCurrentScene )
		mCurrentScene->KeyBoardSpecialUp( key, x, y );
}

void SceneManager::Mouse( int button, int state, int x, int y )
{
	if( mCurrentScene )
		mCurrentScene->Mouse( button, state, x, y );
}

void SceneManager::MouseMotion( int x, int y )
{
	if( mCurrentScene )
		mCurrentScene->MouseMotion( x, y );
}

bool SceneManager::SendCommandToScene( std::vector< std::string > commandTokens )
{
	if( mCurrentScene )
		return mCurrentScene->Command( commandTokens );
	else
		return false;
}

bool SceneManager::SceneChange( std::shared_ptr< Scene > otherScene )
{
	if( ( mCurrentScene == nullptr ) && ( otherScene != nullptr ) )
	{
		mCurrentScene = otherScene;
	} 
	else if( ( mCurrentScene != nullptr ) && ( otherScene != nullptr ) )
	{
		mCurrentScene->Exit();
		mCurrentScene = otherScene;
	}
	else
	{
		SKCONSOLE << "SceneMGR SceneChange Fail";
	}

	std::string lConsoleStr = "SceneName: ";
	lConsoleStr += mCurrentScene->GetSceneName();

	SKCONSOLE << " ";
	SKCONSOLE << "SceneMGR SceneChange Complete";
	SKCONSOLE << lConsoleStr;

	if( mCurrentScene != nullptr )
	{
		mCurrentScene->Enter();
		mCurrentScene->Reshape( mClientWidth, mClientHeight );
	}
	return true;
}

bool SceneManager::SceneChangeByName( std::string SceneName )
{
	bool lResult = false;

	if( SceneName == "Main" )
	{
		lResult = SceneChange( std::shared_ptr< SceneMainMenu >( new SceneMainMenu() ) );
	}
	else if( SceneName == "Collision" )
	{
		lResult = SceneChange( std::make_shared< SceneCollisionTest >() );
	}
	else if( SceneName == "Curve1" )
	{
		lResult = SceneChange( std::make_shared< SceneCurveTest >() );
	}
	else if( SceneName == "Curve2" )
	{
		lResult = SceneChange( std::make_shared< SceneCurveLine >() );
	}
	else if( SceneName == "Curve3" )
	{
		lResult = SceneChange( std::make_shared< SceneMultiCurveLine >() );
	}
	else if( SceneName == "Skiing1" )
	{
		lResult = SceneChange( std::make_shared< SceneSkiingTestStage >() );
	}
	else if( SceneName == "Skiing2" )
	{
		lResult = SceneChange( std::make_shared< SceneSkiingMainStage >() );
	}
	else if( SceneName == "Skiing3" )
	{
		lResult = SceneChange( std::make_shared< SceneSkiingBonusStage >() );
	}
	else if( SceneName == "Line1" )
	{
		lResult = SceneChange( std::make_shared< SceneLineTest >() );
	}
	else if( SceneName == "Firework" )
	{
		lResult = SceneChange( std::make_shared< SceneFireworkTest >() );
	}
	else
	{
		SKCONSOLE << "Don't exist scene name";
	}
	if( lResult )
	{
		mChangeTime = clock();
		mSceneChange = true;
	}
	return lResult;
}

void SceneManager::SetPerspectiveMode( bool set )
{
	if( mGameSys )
		mGameSys->SetPerspectiveMode( set );
	else
		SKCONSOLE << "SceneMGR SetPerspectiveMode() Don't Load GameSystem";
}

bool SceneManager::GetSceneChange()
{
	return mSceneChange;
}

bool SceneManager::GetPerspectiveMode()
{
	if( mGameSys )
		return mGameSys->GetPerspectiveMode();
	else
	{
		SKCONSOLE << "SceneMGR GetPerspectiveMode() Don't Load GameSystem";
		return false;
	}
}

Vector2 SceneManager::GetClientSize()
{
	if( mGameSys )
		return mGameSys->GetClientSize();
	else
	{
		SKCONSOLE << "SceneMGR GetClientSize() Don't Load GameSystem";
		return Vector2( mClientWidth, mClientHeight );
	}
}