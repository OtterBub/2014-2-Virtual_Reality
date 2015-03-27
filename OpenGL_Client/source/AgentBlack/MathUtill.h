#ifndef __VECTOR_UTILL_H__
#define __VECTOR_UTILL_H__

#include <iostream>
#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <cmath>
#include <vector>

struct Vector2i
{
	GLint x, y;

	Vector2i()
	{
		x = 0;
		y = 0;
	}

	Vector2i( GLint x, GLint y )
	{
		this->x = x, this->y = y;
	}
};

struct Vector2
{
	GLfloat x, y;
	
	Vector2()
	{
		x = 0, y = 0;
	}

	Vector2( GLfloat x, GLfloat y )
	{
		this->x = x, this->y = y;
	}
};

struct Vector3
{
	GLfloat x, y, z;
	
	Vector3()
	{
		x = 0, y = 0, z = 0;
	}

	Vector3( GLfloat x, GLfloat y, GLfloat z )
	{
		this->x = x, this->y = y, this->z = z;
	}
};

struct Vector4
{
	GLfloat x, y, z, w;

	Vector4()
	{
		x = 0, y = 0, z = 0, w = 1;
	}

	Vector4( GLfloat x, GLfloat y, GLfloat z, GLfloat w )
	{
		this->x = x, this->y = y, this->z = z, this->w = w;
	}
};

// Define Vector Operator
Vector2 operator+( const Vector2& a, const Vector2& b );
Vector2 operator-( const Vector2& a, const Vector2& b );
Vector2 operator*( const Vector2& a, const float& b );
Vector2 operator*( const float& b, const Vector2& a );

Vector3 operator+( const Vector3& a, const Vector3& b );
Vector3 operator-( const Vector3& a, const Vector3& b );
Vector3 operator*( const Vector3& a, const float& b );
Vector3 operator*( const float& b, const Vector3& a );

Vector4 operator+( const Vector4& a, const Vector4& b );
Vector4 operator-( const Vector4& a, const Vector4& b );
Vector4 operator*( const Vector4& a, const float& b );
Vector4 operator*( const float& b, const Vector4& a );

// UtillFunction for Vector
float VectorLength( const Vector2& a );
float VectorLength( const Vector3& a );
float VectorLength( const Vector4& a );

Vector2 VectorNormalize( const Vector2& a );
Vector3 VectorNormalize( const Vector3& a );
Vector4 VectorNormalize( const Vector4& a );

Vector3 VectorCross( const Vector3& a, const Vector3& b );

bool CollisionCheck1DLine( const float& Line1Start, const float& Line1End, const float& Line2Start, const float& Line2End );
bool CollisionCheck2DBox( const Vector2& a1, const Vector2& a2, const Vector2& b1, const Vector2& b2 );
bool CollisionCheck3DBox( const Vector3& a1, const Vector3& a2, const Vector3& b1, const Vector3& b2 );
bool CollisionCheck3DBox( const Vector3& box1MidPos, const float& box1Size, const Vector3& box2MidPos, const float& box2Size );

// Curve Function
Vector3 GetBezierCurve( std::vector< Vector3 > points, float t );
std::vector< Vector3 > CreateCurve( std::vector< Vector3 > points, int separate );
bool AddMultiCurve( std::vector< Vector3 > points, int separate, std::vector< Vector3 >& vecDest );
bool SetMultiCurve( std::vector< Vector3 > points, int separate, std::vector< Vector3 >& vecDest );

// Line Function
// Source : http://forum.falinux.com/zbxe/index.php?document_srl=406146
void LineDraw( Vector2 start, Vector2 end, Vector4 startColor = Vector4( 1, 1, 1, 1 ), Vector4 endColor = Vector4( 1, 1, 1, 1 ) ); // Bresenham

#endif