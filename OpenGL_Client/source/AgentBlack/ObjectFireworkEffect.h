#ifndef __OBJECT_FIREWORKEFFECT_H__
#define __OBJECT_FIREWORKEFFECT_H__

#include "Object.h"
#include <memory>

class ObjectFireworkEffect : public Object
{
public:
	ObjectFireworkEffect();
	~ObjectFireworkEffect();

	void Draw();
	void Update( double dt );
	void Reshape( int w, int h );

	void SetCreateMaxHeight( float Height );
	void SetCreateMaxLength( float length );
	void SetCreateMaxRadius( float radius );
	void SetCreateMaxTime( float time );
	void SetCreateMaxSpeedRange( float min, float max );
	void SetCreateRange( float min, float max);
	void SetDrawZaxis( float zaxis );
	void SetDynamicColor( bool set );

private:
	void CreateFirework( double dt );
	void UpdateFirework( double dt );

private:
	struct Firework
	{
		float maxHeight;
		float maxLength;
		float maxRadius;
		float maxTime;
		float speed;
		float time;

		Vector2 startPos;
		Vector2 explosionPos;
		Vector4 startColor;
		Vector4 endColor;

		bool explosion;
		float explosionTime;

		Firework()
		{
			maxHeight = 0, maxLength = 0, maxRadius = 0, maxTime = 0, speed = 0, time = 0;
			explosion = false, explosionTime = 0;
		}
	};

	float mMaxHeight;
	float mMaxLength;
	float mMaxRadius;
	float mMaxSpeed;
	float mMinSpeed;
	float mMaxTime;
	float mPrevCreateTime;
	float mCreateTime;
	float mDrawZaxis;

	float mMinPos, mMaxPos;

	bool mDynamicColor;

	std::vector< std::shared_ptr< Firework > > mVecDel;
	std::vector< std::shared_ptr< Firework > > mVecFirework;
};

#endif