#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include <memory>
#include "SceneManager.h"
#include "Object.h"
#include "ConsoleSystem.h"

class Scene
{
public:
	Scene();
	~Scene();

	virtual void Enter() = 0;
	virtual void Exit() {};
	virtual void Draw();
	virtual void Update( double dt );
	virtual void Reshape( int w, int h );

	virtual void KeyBoard( unsigned char key, int x, int y ) {}
	virtual void KeyBoardUp( unsigned char key, int x, int y) {}
	virtual void KeyBoardSpecial( int key, int x, int y ) {}
	virtual void KeyBoardSpecialUp( int key, int x, int y ) {}
	virtual void Mouse( int button, int state, int x, int y ) {}
	virtual void MouseMotion( int x, int y ) {}
	virtual bool Command( std::vector< std::string > commandTokens ) { return false; }

	// For Object
	virtual void ObjectDraw();
	virtual void ObjectUpdate( double dt );
	virtual void ObjectReshape( int w, int h );
	void AddObject( std::shared_ptr<Object> obj );

	// Getter
	std::string GetSceneName();

protected:
	std::vector < std::shared_ptr<Object> > mVecObject;
	std::string mSceneName;
};

#endif