#include "GameSystem.h"
#include "SceneManager.h"

#include <iostream>
#include <string>
#include <sstream>

GameSystem* GameSystem::GetInstance()
{
	static GameSystem* instance = new GameSystem();
	return instance;
}

GameSystem::GameSystem()
{
	mCurrentTime = clock();
	mDeltaTime = clock();

	mActivateConsole = false;
	mPerspectiveMode = false;
	mDepthTest = true;
	mReshape = false;
	mChangeScene = false;
}

GameSystem::~GameSystem()
{
}

void GameSystem::Init()
{
	// SceneMgr Initailize
	SCENEMGR_INST->Init( std::shared_ptr< GameSystem >( this ) );
}

void GameSystem::Draw()
{
	// Game Scene Draw
	SCENEMGR_INST->Draw();

	// Console Draw
	if( mActivateConsole || mChangeScene )
		SKCONSOLE.Draw();
}

void GameSystem::Update( double dt )
{
	// Delta Time Calculator
	mDeltaTime = ( clock() - mCurrentTime ) / 1000.0;
	mCurrentTime = clock();

	// Game Scene Update
	mChangeScene = SCENEMGR_INST->GetSceneChange();
	SCENEMGR_INST->Update( mDeltaTime );
}

void GameSystem::Reshape( int w, int h )
{
	mClientSize.x = w;
	mClientSize.y = h;

	// Game Scene Reshape
	SCENEMGR_INST->Reshape( w, h );

	// Console Reshape
	SKCONSOLE.Reshape( w, h );
}

void GameSystem::KeyBoard( unsigned char key, int x, int y )
{
	std::string lCommandLine( "" );

	if( mActivateConsole && ( key != '`' ) && ( key != 13 ) && ( key != 8 ) )
		SKCONSOLE.AddCharToCurrentStr( key );

	switch( key )
	{
		case 13: // Enter
			if( mActivateConsole )
				lCommandLine = SKCONSOLE.NextLine();
			break;

		case 8: // Back Space
			if( mActivateConsole )
				SKCONSOLE.DeleteCharToCurrentStr();
			break;

		case '`':
			mActivateConsole = !mActivateConsole;
			break;
	}

	if( mActivateConsole )
	{
		bool lTypeCommand = false;
		std::vector< std::string > lTokens;

		// Split String by Space
		if( lCommandLine[0] == '/' )
		{
			std::stringstream lStrStream( &lCommandLine[1] );
			std::string lBuf;
			lTypeCommand = true;

			while( lStrStream >> lBuf )
				lTokens.push_back( lBuf );
		}

		if( lTypeCommand )
		{
			CommandProcess( lTokens );
		}
	}

	if( !mActivateConsole )
		SCENEMGR_INST->KeyBoard( key, x, y );
}

void GameSystem::KeyBoardUp( unsigned char key, int x, int y )
{
	SCENEMGR_INST->KeyBoardUp( key, x, y );
}

void GameSystem::KeyBoardSpecial( int key, int x, int y )
{
	std::cout << "SK: " << key << std::endl;
	SCENEMGR_INST->KeyBoardSpecial( key, x, y );
}

void GameSystem::KeyBoardSpecialUp( int key, int x, int y )
{
	SCENEMGR_INST->KeyBoardSpecialUp( key, x, y );
}

void GameSystem::Mouse( int button, int state, int x, int y )
{
	SCENEMGR_INST->Mouse( button, state, x, y );
}

void GameSystem::MouseMotion( int x, int y )
{
	SCENEMGR_INST->MouseMotion( x, y );
}

void GameSystem::CommandProcess( std::vector<std::string> commandTokens )
{

	if(  commandTokens[0] == "help" ||  commandTokens[0] == "?" )
	{
		SKCONSOLE << "------ Command List ------";
		SKCONSOLE << "/depth [on OR off] - depth Mode Change";
		SKCONSOLE << "/3d [on OR off] - 3d Mode Change";
		SKCONSOLE << "/scene [Scene Name] - Scene Change";
		SKCONSOLE << "/exit - Program Exit";

		// Custom Help
		SCENEMGR_INST->SendCommandToScene( commandTokens );
	}
	else if( (  commandTokens[0] == "depth" ) &&
			 (  commandTokens.size() >= 2 ) )
	{
		if(  commandTokens[1] == "on" )
		{
			mDepthTest = true;
			SKCONSOLE << "Depth Test on";
		}
		else if(  commandTokens[1] == "off" )
		{
			mDepthTest = false;
			SKCONSOLE << "Depth Test off";
		}
	}
	else if( (  commandTokens[0] == "3d" ) &&
			 (  commandTokens.size() >= 2 ) )
	{
		if(  commandTokens[1] == "on" )
		{
			mPerspectiveMode = true;
			SKCONSOLE << "3d Mode on";
		}
		else if(  commandTokens[1] == "off" )
		{
			mPerspectiveMode = false;
			SKCONSOLE << "3d Mode off";
		}
		CallDrawSysReshape();
	}
	else if( (  commandTokens[0] == "scene" ) &&
			 (  commandTokens.size() >= 2 ) )
	{
		bool lSceneChange = false;

		lSceneChange = SCENEMGR_INST->SceneChangeByName( commandTokens[1] );

		if( lSceneChange )
		{
			mDeltaTime = clock();
			mCurrentTime = clock();
		}
	}
	else if(  commandTokens[0] == "exit" )
	{
		exit( 0 );
	}
	else if( SCENEMGR_INST->SendCommandToScene( commandTokens ) )
	{

	}
	else
	{
		SKCONSOLE << "Can't exist command, reference /help or /?";
	}
}

void GameSystem::SetPerspectiveMode( bool set )
{
	mPerspectiveMode = set;
	CallDrawSysReshape();
	//SKCONSOLE << "PersPectiveMode: " + std::to_string( set );
}


void GameSystem::CallDrawSysReshape()
{
	mReshape = true;
}

bool GameSystem::GetPerspectiveMode()
{
	return mPerspectiveMode;
}

bool GameSystem::GetDepthTest()
{
	return mDepthTest;
}

bool GameSystem::GetReshape()
{
	if( mReshape )
	{
		mReshape = false;
		return true;
	}
	else
		return false;
}

Vector2 GameSystem::GetClientSize()
{
	return mClientSize;
}