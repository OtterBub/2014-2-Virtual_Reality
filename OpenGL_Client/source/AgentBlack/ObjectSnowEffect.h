#ifndef __OBJECT_SNOWEFFECT_H__
#define __OBJECT_SNOWEFFECT_H__

#include "ObjectOutLineCube.h"
#include <vector>
#include <memory>
#include <chrono>

class ObjectSnowEffect : public Object
{
public:
	ObjectSnowEffect();
	~ObjectSnowEffect();

	void Draw();
	void Update( double dt );
	void Reshape( int w, int h );
	void Clear();

private:
	std::vector< std::shared_ptr< ObjectOutLineCube > > mSnow;
	std::vector< std::shared_ptr< ObjectOutLineCube > > mSnowDelete;
	Vector3 mMinField;
	Vector3 mMaxField;

	float mSpeed;
	clock_t mSnowCreateTime;
};

#endif