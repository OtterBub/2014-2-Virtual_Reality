#include "ObjectFireworkEffect.h"
#include <ctime>

ObjectFireworkEffect::ObjectFireworkEffect()
{
	mCreateTime = 100;
	mPrevCreateTime = std::clock();
	mMaxHeight = 300;
	mMaxLength = 50;
	mMaxRadius = 100;
	mMaxTime = 1500;
	mDrawZaxis = 0;

	mMinPos = 0;
	mMaxPos = 300;

	mMinSpeed = 100;
	mMaxSpeed = 300;

	mDynamicColor = false;
}

ObjectFireworkEffect::~ObjectFireworkEffect()
{

}

void ObjectFireworkEffect::Draw()
{
	glPushMatrix();
	glTranslatef( 0, 0, 0 );
	for( auto it : mVecFirework )
	{
		if( it->explosion && mDynamicColor )
		{
			for( float degree = 0; degree <= 360; degree += ( 360.f / 20.f ) )
			{
				float lx = it->explosionPos.x + ( std::sin( degree * ( 3.14 / 180 ) )
					* ( ( it->time - it->explosionTime ) / it->explosionTime )
					* ( it->maxRadius ) );
				
				float ly = it->explosionPos.y + ( std::cos( degree * ( 3.14 / 180 ) )
					* ( ( it->time - it->explosionTime ) / it->explosionTime )
					* ( it->maxRadius ) );

				LineDraw( it->explosionPos, Vector2( lx, ly ), it->startColor, it->endColor );
			}
		}
		else
		{
			if( mDynamicColor )
				LineDraw( it->startPos, Vector2( it->startPos.x, it->startPos.y + it->time ), it->startColor, it->endColor );
			else
				LineDraw( it->startPos, Vector2( it->startPos.x + it->time / 2.f, it->startPos.y + it->time ) );
		}
	}
	glPopMatrix();
}

void ObjectFireworkEffect::Update( double dt )
{
	CreateFirework( dt );
	UpdateFirework( dt );
}

void ObjectFireworkEffect::CreateFirework( double dt )
{
	if( std::clock() - mPrevCreateTime > mCreateTime )
	{
		mPrevCreateTime = std::clock();

		std::shared_ptr< Firework > lObj = std::make_shared< Firework >();
		lObj->maxHeight = rand() % (int)mMaxHeight;
		lObj->maxLength = rand() % (int)mMaxLength;
		lObj->maxTime = rand() % (int)mMaxTime;
		lObj->maxRadius = rand() % (int)mMaxRadius;
		lObj->startPos.x = ( rand() % (int)( mMaxPos - mMinPos ) ) + ( mMinPos );
		lObj->speed = ( rand() % (int)( mMaxSpeed - mMinSpeed ) ) + ( mMinSpeed );
		
		lObj->startColor = Vector4( rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 1 );
		lObj->endColor = Vector4( rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 1 );

		mVecFirework.push_back( lObj );
	}
}

void ObjectFireworkEffect::UpdateFirework( double dt )
{
	// Firework Update
	for( auto it : mVecFirework )
	{
		it->time += it->speed * dt;

		if( it->time > it->maxTime )
			mVecDel.push_back( it );
		else if( ( it->time > ( it->maxTime / 2.f ) ) && ( it->explosion == false ) )
		{
			it->explosion = true;
			it->explosionTime = it->time;
			it->explosionPos = Vector2( it->startPos.x, it->startPos.y + it->time );
		}
	}

	// Delete TimeOut Effect
	if( mVecDel.size() > 0 )
	{
		for( auto it : mVecDel )
		{
			auto lDelObj = std::find( mVecFirework.begin(), mVecFirework.end(), it );
			mVecFirework.erase( lDelObj );
		}
		mVecDel.clear();
	}
	
}

void ObjectFireworkEffect::Reshape( int w, int h )
{
	
}

void ObjectFireworkEffect::SetCreateMaxHeight( float Height )
{
	mMaxHeight = Height;
}

void ObjectFireworkEffect::SetCreateMaxLength( float length )
{
	mMaxLength = length;
}

void ObjectFireworkEffect::SetCreateMaxRadius( float radius )
{
	mMaxRadius = radius;
}

void ObjectFireworkEffect::SetCreateMaxTime( float time )
{
	mMaxTime = time;
}

void ObjectFireworkEffect::SetCreateMaxSpeedRange( float min, float max )
{
	mMinSpeed = min;
	mMaxSpeed = max;
}

void ObjectFireworkEffect::SetCreateRange( float min, float max)
{
	mMinPos = min;
	mMaxPos = max;
}

void ObjectFireworkEffect::SetDrawZaxis( float zaxis )
{
	mDrawZaxis = zaxis;
}

void ObjectFireworkEffect::SetDynamicColor( bool set )
{
	mDynamicColor = set;
}