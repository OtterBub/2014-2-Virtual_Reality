#ifndef __SCENE_COLLISIONTEST_H__
#define __SCENE_COLLISIONTEST_H__

#include "Scene.h"
#include "ObjectOutLineCube.h"
#include "ButtonUI.h"

class SceneCollisionTest : public Scene
{
public:
	SceneCollisionTest();
	~SceneCollisionTest();

	void Enter();
	void Exit();
	void Draw();
	void Update( double dt );
	void Reshape( int w, int h );

	void KeyBoard( unsigned char key, int x, int y );
	void KeyBoardUp( unsigned char key, int x, int y);
	void Mouse( int button, int state, int x, int y );


	/*
	void KeyBoardSpecial( int key, int x, int y ) {}
	void KeyBoardSpecialUp( int key, int x, int y ) {}
	void MouseMotion( int x, int y ) {}
	*/

private:
	int mClientWidth, mClientHeight;
	bool mKey[UCHAR_MAX];
	bool mCollision;

	Vector3 mControlPos;

	ObjectOutLineCube mObjControlCube;
	ObjectOutLineCube mObjCollisionCube;

	ButtonUI mButton;
};

#endif