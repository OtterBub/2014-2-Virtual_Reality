#include "ObjectOutLineCube.h"

ObjectOutLineCube::ObjectOutLineCube()
{
	mSize = 10;
	mScale = Vector3( 1, 1, 1 );
}

ObjectOutLineCube::~ObjectOutLineCube()
{
}


void ObjectOutLineCube::Draw()
{
	glPushMatrix();
	{
		glTranslatef( mPosition.x, mPosition.y, mPosition.z );
		glScalef( mScale.x, mScale.y, mScale.z );

		glColor4f( mColor.x, mColor.y, mColor.z, mColor.w );
		glutSolidCube( mSize );

		glColor4f( 1 - mColor.x, 1 - mColor.y, 1 - mColor.z, mColor.w );
		glutWireCube( mSize + 0.5 );
	}
	glPopMatrix();
}

void ObjectOutLineCube::Update( double dt )
{
}

void ObjectOutLineCube::Reshape( int w, int h )
{
}


void ObjectOutLineCube::SetPosition( Vector3 pos )
{
	mPosition = pos;
}

void ObjectOutLineCube::SetScale( Vector3 scale )
{
	mScale = scale;
}

void ObjectOutLineCube::SetColor( Vector4 color )
{
	mColor = color;
}

void ObjectOutLineCube::SetSize( double size )
{
	mSize = size;
}

Vector3 ObjectOutLineCube::GetPosition()
{
	return mPosition;
}

Vector4 ObjectOutLineCube::GetColor()
{
	return mColor;
}

double ObjectOutLineCube::GetSize()
{
	return  mSize;
}