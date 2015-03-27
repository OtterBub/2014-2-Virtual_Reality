#ifndef __SCENE_SKIINGMAINSTAGE_H__
#define __SCENE_SKIINGMAINSTAGE_H__

#include "Scene.h"
#include "ObjectOutLineCube.h"
#include "ObjectFireworkEffect.h"
#include "ObjectSkier.h"
#include "ButtonUI.h"

class SceneSkiingMainStage : public Scene
{
public:
	SceneSkiingMainStage();
	~SceneSkiingMainStage();

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

	ObjectSkier mSkier;
	ObjectFireworkEffect mFirework;

	ButtonUI mButton;
};

#endif