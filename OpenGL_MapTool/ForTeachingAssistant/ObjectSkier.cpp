#include "ObjectSkier.h"
#include "ConsoleSystem.h"
#include <iterator>

ObjectSkier::ObjectSkier()
{
	mMainBody.SetColor( Vector4( 0, 0, 1, 1 ) );
	mMainBody.SetSize( 30 );
	mSetDest = false;
	mSetCollisionTree = false;
	mAutoRotate = false;
	mSmoothFinish = false;
	mVelIncrement = 0;
	mVelocity = 0;
	mInitVel = 0;
	mAngleY = 0;
	mAngleZ = 0;
}

ObjectSkier::~ObjectSkier()
{
}


void ObjectSkier::Draw()
{
	glPushMatrix();
	{
		glTranslatef( mPosition.x, mPosition.y, mPosition.z );
		glRotatef( ( mAngleZ / 3.14f ) * 180, 0, 0, 1 );
		glRotatef( ( mAngleY / 3.14f ) * 180, 0, 1, 0 );
		glTranslatef( 0, 10, 0 );
		mMainBody.Draw();

		glTranslatef( 0, 20, 0 );
		glutSolidCube( 10 );
	}
	glPopMatrix();
}

void ObjectSkier::Update( double dt )
{
	Move( dt );

	if( !mSetCollisionTree )
	{
		if( mAutoRotate )
			Rotate();
	}
	else if( mSetDest )
	{
		mAngleZ++;
		mAngleY++;
	}
}

void ObjectSkier::Reshape( int w, int h )
{

}

void ObjectSkier::SetPosition( Vector3 pos )
{
	mPosition = pos;
	mSetDest = false;
	mVelocity = mInitVel;
}

void ObjectSkier::SetDest( std::list< Vector3 > listDest )
{
	mListDest = listDest;
}

void ObjectSkier::AddDest( std::list< Vector3 > listDest )
{
	std::copy( listDest.begin(), listDest.end(), std::back_inserter( mListDest ) );
}

void ObjectSkier::SetCollisionTree( bool set )
{
	mSetCollisionTree = set;
	if( set == false )
	{
		mAngleZ = 0;
		mAngleY = 0;
	}
}

void ObjectSkier::SetAutoRotate( bool set )
{
	mAutoRotate = set;
}

void ObjectSkier::SetSmooth( bool set )
{
	mSmoothFinish = set;
}

void ObjectSkier::SetVelocityAndIncrement( float initVel, float inc )
{
	mVelocity = initVel;
	mInitVel = initVel;
	mVelIncrement = inc;
}


Vector3 ObjectSkier::GetPosition()
{
	return mPosition;
}

// ----------------- Private Function -----------------

Vector3 ObjectSkier::GetNextDest()
{
	Vector3 lResult( FLT_MAX, FLT_MAX, FLT_MAX );
	if( mListDest.size() > 0 )
	{
		lResult = mListDest.front();
		mListDest.pop_front();
	}
	return lResult;
}

void ObjectSkier::Move( double dt )
{
	mLeftDistance = mVelocity * dt;
	do
	{
		if( !mSetDest )
		{
			mDest = GetNextDest();
			if( mDest.x != FLT_MAX )
			{
				mSetDest = true;
				mDir = mDest - mPosition;
				mDestDistance = VectorLength( mDir );
				mDir = VectorNormalize( mDir );
			}
			else if( ( mVelocity > 0 ) && ( mVelIncrement > 0 ) )
			{
				mVelocity -= ( ( mVelIncrement * 10 ) * dt );
				mPosition = mPosition + ( Vector3( 1, 0, 0 ) * mLeftDistance );
				mSetDest = false;
				mDest = mPosition;
				mLeftDistance = 0;
			}
			else
			{
				mSetDest = false;
				mDest = mPosition;
				mLeftDistance = 0;
			}
		}

		if( mSetDest )
		{
			if( mDest.y > mPosition.y )
				mVelocity -= ( ( mVelIncrement * 2 ) * dt );
			else
				mVelocity += ( mVelIncrement * dt );

			if( mVelocity < 0 )
			{
				mDir = Vector3( 0, 300, mPosition.z ) - mPosition;
				mDestDistance = VectorLength( mDir );
				mDir = VectorNormalize( mDir );
			}
			

			mDestDistance = mDestDistance - mLeftDistance;				
			mPosition = mPosition + ( mDir * mLeftDistance );

			if( mDestDistance <= 0 )
			{
				mPosition = mDest;
				mSetDest = false;
				mLeftDistance = abs( mDestDistance );
			}
			else
			{
				mLeftDistance = 0;
			}
		}

	} while( mLeftDistance );

	if( mPosition.y <= -1 )
	{
		SetCollisionTree( true );
		Vector3 lDestFly;
		lDestFly.x = mPosition.x - ( rand() % 10 );
		lDestFly.y = 0;
		lDestFly.z = mPosition.z + ( ( rand() % 10 ) - 5 );

		std::list< Vector3 > lList;
		lList.push_back( lDestFly );
		SetDest( lList );
	}
}

void ObjectSkier::Rotate()
{
	mAngleY = atan2f( mDest.x - mPosition.x, mDest.z - mPosition.z );
	mAngleZ = atan2f( -abs( mDest.y - mPosition.y ), abs( mDest.x - mPosition.x ) );	
}

Vector3 ObjectSkier::GetMidPosition()
{
	return Vector3( mPosition.x, mPosition.y + 20, mPosition.z );
}

float ObjectSkier::GetSize()
{
	return 40;
}

bool ObjectSkier::GetCollisionTree()
{
	return mSetCollisionTree;
}