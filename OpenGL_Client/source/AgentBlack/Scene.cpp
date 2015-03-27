#include "Scene.h"

Scene::Scene()
{
	mSceneName = "NONE";
}
Scene::~Scene()
{
}

void Scene::Draw()
{
	Scene::ObjectDraw();
}

void Scene::Update( double dt )
{
	Scene::ObjectUpdate( dt );
}

void Scene::Reshape( int w, int h )
{
	Scene::ObjectReshape( w, h );
}

// For Object
void Scene::ObjectDraw()
{
	for( std::shared_ptr<Object> it : mVecObject )
	{
		it->Draw();
	}
}

void Scene::ObjectUpdate( double dt )
{
	for( std::shared_ptr<Object> it : mVecObject )
	{
		it->Update( dt );
	}
}

void Scene::ObjectReshape( int w, int h )
{
	for( std::shared_ptr<Object> it : mVecObject )
	{
		it->Reshape( w, h );
	}
}

void Scene::AddObject( std::shared_ptr<Object> obj )
{
	mVecObject.push_back( obj );
}

// ---------------- GETTER ----------------

std::string Scene::GetSceneName()
{
	return mSceneName;
}