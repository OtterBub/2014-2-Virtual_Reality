#ifndef __SCENE_MULTICURVELINE_H__
#define __SCENE_MULTICURVELINE_H__

#include "Scene.h"
#include "ObjectOutLineCube.h"
#include "ButtonUI.h"

class SceneMultiCurveLine : public Scene
{
public:
	SceneMultiCurveLine();
	~SceneMultiCurveLine();

	void Enter();
	void Exit();
	void Draw();
	void Update( double dt );
	void Reshape( int w, int h );

	void KeyBoard( unsigned char key, int x, int y );
	void KeyBoardUp( unsigned char key, int x, int y);
	void Mouse( int button, int state, int x, int y );
	void MouseMotion( int x, int y );
	
	/*
	void KeyBoardSpecial( int key, int x, int y ) {}
	void KeyBoardSpecialUp( int key, int x, int y ) {}
	*/

private:
	int mClientWidth, mClientHeight;
	bool mKey[UCHAR_MAX];
	bool mLeftButtonDown;
	bool mCurveUpdate;

	ObjectOutLineCube mResult;
	std::vector< std::shared_ptr< ObjectOutLineCube > > mCubeVec;
	std::vector< Vector3 > mCubePos;
	std::vector< Vector3 > mLineVec;

	ButtonUI mButton;
};

#endif