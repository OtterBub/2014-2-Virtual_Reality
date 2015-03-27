#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "GameSystem.h"

class Scene;

// Singleton
class SceneManager
{
public:
	~SceneManager();

	static SceneManager* GetInstance();

	void Init( std::shared_ptr< GameSystem > gamesys );
	void Draw();
	void Update( double dt );
	void Reshape( int w, int h );
	void KeyBoard( unsigned char key, int x, int y );
	void KeyBoardUp( unsigned char key, int x, int y );
	void KeyBoardSpecial( int key, int x, int y );
	void KeyBoardSpecialUp( int key, int x, int y );
	void Mouse( int button, int state, int x, int y );
	void MouseMotion( int x, int y );
	bool SendCommandToScene( std::vector< std::string > commandTokens );

	bool SceneChange( std::shared_ptr< Scene > otherScene );
	bool SceneChangeByName( std::string SceneName );

	void SetPerspectiveMode( bool set );

	bool GetSceneChange();
	bool GetPerspectiveMode();
	Vector2 GetClientSize();

private:
	SceneManager();

private:
	std::shared_ptr< Scene > mCurrentScene;
	int mClientWidth, mClientHeight;
	std::shared_ptr< GameSystem > mGameSys;
	bool mSceneChange;

	clock_t mChangeTime;
};

#define SCENEMGR_INST SceneManager::GetInstance()

#endif