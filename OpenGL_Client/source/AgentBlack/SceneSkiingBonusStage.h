#ifndef __SCENE_SKIINGBONUSSTAGE_H__
#define __SCENE_SKIINGBONUSSTAGE_H__

#include "Scene.h"
#include "ObjectSnowEffect.h"
#include "ObjectFireworkEffect.h"
#include "ObjectOutLineCube.h"
#include "ObjectSkier.h"
#include "ButtonUI.h"


class SceneSkiingBonusStage : public Scene
{
public:
	SceneSkiingBonusStage();
	~SceneSkiingBonusStage();

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
	float mHeight;

	std::vector< std::shared_ptr< ObjectOutLineCube > > mTreeVec;
	std::vector< std::shared_ptr< ObjectOutLineCube > > mCubeVec;
	std::vector< Vector3 > mCubePos;
	std::vector< Vector3 > mLineVec;
	std::shared_ptr< ObjectOutLineCube > mSelectCube;

	float mAngleY;
	Vector3 mStartPos;
	Vector3 mEyePos;
	Vector3 mLookatPos;
	Vector3 mLastPos;

	ObjectSkier mSkier;
	ObjectSnowEffect mSnow;
	ObjectFireworkEffect mFirework;

	ButtonUI mButton;
};

#endif