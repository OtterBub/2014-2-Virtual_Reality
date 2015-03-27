#ifndef __SCENE_MAINMENU_H__
#define __SCENE_MAINMENU_H__

#include "Scene.h"
#include "ButtonUI.h"

class SceneMainMenu : public Scene
{
public:
	SceneMainMenu();
	~SceneMainMenu();

	void Enter();
	void Exit();
	void Draw();
	void Update( double dt );
	void Reshape( int w, int h );

	void Mouse( int button, int state, int x, int y );
	

	/*void KeyBoard( unsigned char key, int x, int y ) {}
	void KeyBoardUp( unsigned char key, int x, int y) {}
	void KeyBoardSpecial( int key, int x, int y ) {}
	void KeyBoardSpecialUp( int key, int x, int y ) {}
	void MouseMotion( int x, int y ) {}
	bool Command( std::vector< std::string > commandTokens ) { return false; }*/

protected:
	std::vector < std::shared_ptr<Object> > mVecObject;
	std::string mSceneName;
	ButtonUI mButtons;
};

#endif