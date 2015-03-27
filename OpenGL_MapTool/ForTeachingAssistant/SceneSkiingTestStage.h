#ifndef __SCENE_SKIINGTESTSTAGE_H__
#define __SCENE_SKIINGTESTSTAGE_H__

#include "Scene.h"
#include "ObjectOutLineCube.h"
#include "ObjectSkier.h"
#include "ButtonUI.h"

class SceneSkiingTestStage : public Scene
{
public:
	SceneSkiingTestStage();
	~SceneSkiingTestStage();

	void Enter();
	void Exit();
	void Draw();
	void Update( double dt );
	void Reshape( int w, int h );

	void KeyBoard( unsigned char key, int x, int y );
	void KeyBoardUp( unsigned char key, int x, int y);
	void Mouse( int button, int state, int x, int y );
	void MouseMotion( int x, int y );
	bool Command( std::vector< std::string > commandTokens );
	
	/*
	void KeyBoardSpecial( int key, int x, int y ) {}
	void KeyBoardSpecialUp( int key, int x, int y ) {}
	*/

private:
	int mClientWidth, mClientHeight;
	bool mKey[UCHAR_MAX];
	bool mLeftButtonDown;
	bool mCurveUpdate;
	bool mStartSkier;

	std::vector< std::shared_ptr< ObjectOutLineCube > > mCubeVec;
	std::vector< Vector3 > mCubePos;
	std::vector< Vector3 > mLineVec;

	float mAngleY;
	Vector3 mEyePos;
	Vector3 mLookatPos;

	ObjectSkier mSkier;
	ButtonUI mButton;
};

#endif