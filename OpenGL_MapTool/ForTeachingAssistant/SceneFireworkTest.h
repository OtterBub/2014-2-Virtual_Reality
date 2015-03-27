#ifndef __SCENE_LINEFIREWORK_H__
#define __SCENE_LINEFIREWORK_H__

#include "Scene.h"
#include "ObjectFireworkEffect.h"
#include "ButtonUI.h"

class SceneFireworkTest : public Scene
{
public:
	SceneFireworkTest();
	~SceneFireworkTest();

	void Enter();
	void Exit();
	void Draw();
	void Update( double dt );
	void Reshape( int w, int h );

	void Mouse( int button, int state, int x, int y );
	void MouseMotion( int x, int y );

	/*void KeyBoard( unsigned char key, int x, int y ) {}
	void KeyBoardUp( unsigned char key, int x, int y) {}
	void KeyBoardSpecial( int key, int x, int y ) {}
	void KeyBoardSpecialUp( int key, int x, int y ) {}
	bool Command( std::vector< std::string > commandTokens ) { return false; }*/

private:
	ObjectFireworkEffect mFireworkEffect;
	ButtonUI mButton;
	bool mDynamicFirework;
};

#endif