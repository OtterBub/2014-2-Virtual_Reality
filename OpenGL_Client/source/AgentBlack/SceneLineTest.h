#ifndef __SCENE_LINETEST_H__
#define __SCENE_LINETEST_H__

#include "Scene.h"
#include "ButtonUI.h"

class SceneLineTest : public Scene
{
public:
	SceneLineTest();
	~SceneLineTest();

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
	Vector2 mClientSize;
	Vector2 mStartPos;
	Vector2 mEndPos;
	bool mLeftMouseDown;
	ButtonUI mButton;
};

#endif