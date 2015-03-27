#include "ObjectSnowEffect.h"
#include "ConsoleSystem.h"

ObjectSnowEffect::ObjectSnowEffect()
{
	mMaxField = Vector3( 100, 0, 100 );
	mSnowCreateTime = 0;
	mSpeed = 30;
}
ObjectSnowEffect::~ObjectSnowEffect()
{
}

void ObjectSnowEffect::Draw()
{
	for( auto it : mSnow )
	{
		it->Draw();
	}
}

void ObjectSnowEffect::Update( double dt )
{
	if( clock() - mSnowCreateTime > 10 )
	{
		Vector3 lCreatePos;
		std::shared_ptr< ObjectOutLineCube > lobj = std::make_shared< ObjectOutLineCube >();
		lobj->SetColor( Vector4( 1, 1, 1, 1 ) );
		lobj->SetSize( 2 );
		
		lCreatePos.x = rand() % (int)mMaxField.x;
		lCreatePos.y = mMaxField.y;
		lCreatePos.z = rand() % (int)mMaxField.z;
		lobj->SetPosition( lCreatePos );
		mSnow.push_back( lobj );
		mSnowCreateTime = clock();
	}
	
	for( auto it : mSnow )
	{
		Vector3 lPos = it->GetPosition();
		lPos.y -= mSpeed * dt;
		it->SetPosition( lPos );
		if( mMinField.y >= lPos.y )
			mSnowDelete.push_back( it );
	}

	if( mSnowDelete.size() > 0 )
	{
		for( auto it : mSnowDelete )
		{
			auto ldel = std::find( mSnow.begin(), mSnow.end(), it );
			if( ldel != mSnow.end() )
			{
				mSnow.erase( ldel );
			}
				
		}
	}
}

void ObjectSnowEffect::Reshape( int w, int h )
{
	mMaxField = Vector3( w, 600, h );
}

void ObjectSnowEffect::Clear()
{
	mSnow.clear();
}