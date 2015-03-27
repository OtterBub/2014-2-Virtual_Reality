#ifndef __OBJECT_OUTLINECUBE_H__
#define __OBJECT_OUTLINECUBE_H__

#include "Object.h"

class ObjectOutLineCube : public Object
{
public:
	ObjectOutLineCube();
	~ObjectOutLineCube();

	void Draw();
	void Update( double dt );
	void Reshape( int w, int h );

	void SetPosition( Vector3 pos );
	void SetScale( Vector3 scale );
	void SetColor( Vector4 color );
	void SetSize( double size );

	Vector3 GetPosition();
	Vector4 GetColor();
	double GetSize();

private:
	Vector3 mPosition;
	Vector3 mScale;
	Vector4 mColor;
	double mSize;
};

#endif