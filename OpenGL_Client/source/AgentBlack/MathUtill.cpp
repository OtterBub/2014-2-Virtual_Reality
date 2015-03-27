#include "MathUtill.h"
#include "ConsoleSystem.h"

Vector2 operator+( const Vector2& a, const Vector2& b )
{
	return Vector2( a.x + b.x, a.y + b.y );
}

Vector2 operator-( const Vector2& a, const Vector2& b )
{
	return Vector2( a.x - b.x, a.y - b.y );
}

Vector2 operator*( const Vector2& a, const float& b )
{
	return Vector2( a.x * b, a.y * b );
}

Vector2 operator*( const float& b, const Vector2& a )
{
	return Vector2( a.x * b, a.y * b );
}

Vector3 operator+( const Vector3& a, const Vector3& b )
{
	return Vector3( a.x + b.x, a.y + b.y, a.z + b.z );
}

Vector3 operator-( const Vector3& a, const Vector3& b )
{
	return Vector3( a.x - b.x, a.y - b.y, a.z - b.z );
}

Vector3 operator*( const Vector3& a, const float& b )
{
	return Vector3( a.x * b, a.y * b, a.z * b );
}

Vector3 operator*( const float& b, const Vector3& a )
{
	return Vector3( a.x * b, a.y * b, a.z * b );
}

Vector4 operator+( const Vector4& a, const Vector4& b )
{
	return Vector4( a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w );
}

Vector4 operator-( const Vector4& a, const Vector4& b )
{
	return Vector4( a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w );
}

Vector4 operator*( const Vector4& a, const float& b )
{
	return Vector4( a.x * b, a.y * b, a.z * b, a.w * b );
}

Vector4 operator*( const float& b, const Vector4& a )
{
	return Vector4( a.x * b, a.y * b, a.z * b, a.w * b );
}

float VectorLength( const Vector2& a )
{
	return std::sqrt( ( a.x * a.x ) + ( a.y * a.y ) );
}

float VectorLength( const Vector3& a )
{
	return std::sqrt( ( a.x * a.x ) + ( a.y * a.y ) + ( a.z * a.z ) );
}

float VectorLength( const Vector4& a )
{
	return std::sqrt( ( a.x * a.x ) + ( a.y * a.y ) + ( a.z * a.z ) + ( a.w * a.w ) ); 
}

Vector2 VectorNormalize( const Vector2& a )
{
	float lLength = VectorLength( a );
	lLength = abs( lLength );
	return Vector2( a.x / lLength, a.y / lLength );
}

Vector3 VectorNormalize( const Vector3& a )
{
	float lLength = VectorLength( a );
	lLength = abs( lLength );
	return Vector3( a.x / lLength, a.y / lLength, a.z / lLength );
}

Vector4 VectorNormalize( const Vector4& a )
{
	float lLength = VectorLength( a );
	lLength = abs( lLength );
	return Vector4( a.x / lLength, a.y / lLength, a.z / lLength, a.w / lLength );
}

Vector3 VectorCross( const Vector3& a, const Vector3& b )
{
	return Vector3( ( a.y * b.z ) - ( b.y * a.z ),
					( a.z * b.x ) - ( b.z * a.x ),
					( a.x * b.y ) - ( b.x * a.y ) );
}

bool CollisionCheck1DLine( const float& Line1Start, const float& Line1End, const float& Line2Start, const float& Line2End )
{
	return ( ( Line1End > Line2Start ) && ( Line1Start < Line2End ) );
}

bool CollisionCheck2DBox( const Vector2& a1, const Vector2& a2, const Vector2& b1, const Vector2& b2 )
{
	return ( CollisionCheck1DLine( a1.x, a2.x, b1.x, b2.x ) &&
			 CollisionCheck1DLine( a1.y, a2.y, b1.y, b2.y ) );
}

bool CollisionCheck3DBox( const Vector3& a1, const Vector3& a2, const Vector3& b1, const Vector3& b2 )
{
	return ( CollisionCheck2DBox( Vector2( a1.x, a1.y ), Vector2( a2.x, a2.y ), Vector2( b1.x, b1.y ), Vector2( b2.x, b2.y ) ) && 
			 CollisionCheck2DBox( Vector2( a1.y, a1.z ), Vector2( a2.y, a2.z ), Vector2( b1.y, b1.z ), Vector2( b2.y, b2.z ) ) &&
			 CollisionCheck2DBox( Vector2( a1.z, a1.x ), Vector2( a2.z, a2.x ), Vector2( b1.z, b1.x ), Vector2( b2.z, b2.x ) ) );
}

bool CollisionCheck3DBox( const Vector3& box1MidPos, const float& box1Size, const Vector3& box2MidPos, const float& box2Size )
{
	float lBox1HalfSize = box1Size / 2.f;
	float lBox2HalfSize = box2Size / 2.f;

	Vector3 lBox1Vector1( box1MidPos.x - lBox1HalfSize, 
						  box1MidPos.y - lBox1HalfSize, 
						  box1MidPos.z - lBox1HalfSize );

	Vector3 lBox1Vector2( box1MidPos.x + lBox1HalfSize, 
						  box1MidPos.y + lBox1HalfSize, 
						  box1MidPos.z + lBox1HalfSize );

	Vector3 lBox2Vector1( box2MidPos.x - lBox2HalfSize, 
						  box2MidPos.y - lBox2HalfSize, 
						  box2MidPos.z - lBox2HalfSize );

	Vector3 lBox2Vector2( box2MidPos.x + lBox2HalfSize, 
						  box2MidPos.y + lBox2HalfSize, 
						  box2MidPos.z + lBox2HalfSize );

	return CollisionCheck3DBox( lBox1Vector1, lBox1Vector2, lBox2Vector1, lBox2Vector2 );
}

Vector3 GetBezierCurve( std::vector< Vector3 > points, float t )
{
	Vector3 lResult;

	if( ( points.size() < 4 ) )
	{
		SKCONSOLE << "GetBezierCurve() Size Fail " + std::to_string( points.size() );
		return lResult;
	}
	lResult = 
		( std::powf( 1 - t, 3 ) * std::powf( t, 0 ) * ( points[0] ) ) +
		( 3 * std::powf( 1 - t, 2 ) * std::powf( t, 1 ) * ( points[1] ) ) +
		( 3 * std::powf( 1 - t, 1 ) * std::powf( t, 2 ) * ( points[2] ) ) +
		( std::powf( 1 - t, 0 ) * std::powf( t, 3 ) * ( points[3] ) );

	return lResult;
}

std::vector< Vector3 > CreateCurve( std::vector< Vector3 > points, int separate )
{
	std::vector< Vector3 > lResult;

	if( ( points.size() < 4 ) )
	{
		SKCONSOLE << "CreateCurve() Size Fail " + std::to_string( points.size() );
		return lResult;
	}

	for( float i = 0; ( i / separate ) <= 1; ++i )
	{
		float lT = ( i / separate );
		lResult.push_back( GetBezierCurve( points, lT ) );
	}

	return lResult;
}

bool AddMultiCurve( std::vector< Vector3 > points, int separate, std::vector< Vector3 >& vecDest )
{
	std::vector< Vector3 > lResult = CreateCurve( points, separate );

	if( lResult.size() == 0 )
	{
		SKCONSOLE << "AddMultiCurve() Get Result Fail " + std::to_string( points.size() );
		return false;
	}
	else 
	{
		std::copy( lResult.begin(), lResult.end(), std::back_inserter( vecDest ) );

		return true;
	}
}

bool SetMultiCurve( std::vector< Vector3 > points, int separate, std::vector< Vector3 >& vecDest )
{
	int lPointCount = points.size();

	if( lPointCount >= 4 )
	{
		std::vector< Vector3 >::iterator it = points.begin();
		vecDest.clear();
		while( lPointCount >= 4 )
		{
			std::vector< Vector3 > lResult = CreateCurve( std::vector< Vector3 >( it, it + 4 ), separate );
			std::copy( lResult.begin(), lResult.end(), std::back_inserter( vecDest ) );
			lPointCount -= 3;
			if( ( lPointCount ) >= 4 )
			{
				it = it + 3;
			}
		}
	}
	
	return true;
}

void LineDraw( Vector2 start, Vector2 end, Vector4 startColor , Vector4 endColor )
{
	int dx, dy;
	int p_value;
	int inc_2dy;
	int inc_2dydx;
	int inc_value;
	int ndx;
	bool colorReverse = false;

	dx = abs( end.x - start.x );
	dy = abs( end.y - start.y );

	glBegin( GL_POINTS );
	if( dy <= dx )
	{
		inc_2dy = 2 * dy;
		inc_2dydx = 2 * ( dy - dx );

		if( end.x < start.x )
		{
			ndx = start.x;
			start.x = end.x;
			end.x = ndx;

			ndx = start.y;
			start.y = end.y;
			end.y = ndx;
			std::swap( startColor, endColor );
		}
		if( start.y < end.y )  
			inc_value = 1;
		else           
			inc_value = -1;

		glColor4fv( reinterpret_cast< GLfloat* >( &startColor ) );
		glVertex2i( (GLint)start.x, (GLint)start.y );

		p_value = 2 * dy - dx;
		
		for( ndx = start.x; ndx < end.x; ++ndx )
		{
			if( 0 > p_value )    
				p_value += inc_2dy;
			else
			{
				p_value += inc_2dydx;
				start.y += inc_value;
			}
			Vector4 lColor( startColor.x + ( ( ndx - start.x ) / ( dx ) * ( endColor.x - startColor.x ) ),
							startColor.y + ( ( ndx - start.x ) / ( dx ) * ( endColor.y - startColor.y ) ),
							startColor.z + ( ( ndx - start.x ) / ( dx ) * ( endColor.z - startColor.z ) ),
							startColor.w + ( ( ndx - start.x ) / ( dx ) * ( endColor.w - startColor.w ) ) );
			glColor4fv( reinterpret_cast<GLfloat*>( &lColor ) );
			glVertex2i( ndx, (GLint)start.y );
		}
	}
	else
	{
		inc_2dy = 2 * dx;
		inc_2dydx = 2 * ( dx - dy );

		if( end.y < start.y )
		{
			ndx = start.y;
			start.y = end.y;
			end.y = ndx;

			ndx = start.x;
			start.x = end.x;
			end.x = ndx;
			std::swap( startColor, endColor );
		}
		if( start.x < end.x )  
			inc_value = 1;
		else				
			inc_value = -1;

		glColor4fv( reinterpret_cast< GLfloat* >( &startColor ) );
		glVertex2i( (GLint)start.x, (GLint)start.y );

		p_value = 2 * dx - dy;
		for( ndx = start.y; ndx < end.y; ++ndx )
		{
			if( 0 > p_value )    
				p_value += inc_2dy;
			else
			{
				p_value += inc_2dydx;
				start.x += inc_value;
			}
			Vector4 lColor( startColor.x + ( ( ndx - start.y ) / ( dy ) * ( endColor.x - startColor.x ) ),
							startColor.y + ( ( ndx - start.y ) / ( dy ) * ( endColor.y - startColor.y ) ),
							startColor.z + ( ( ndx - start.y ) / ( dy ) * ( endColor.z - startColor.z ) ),
							startColor.w + ( ( ndx - start.y ) / ( dy ) * ( endColor.w - startColor.w ) ) );
			glColor4fv( reinterpret_cast<GLfloat*>( &lColor ) );
			glVertex2i( (GLint)start.x, ndx );
		}
	}
	glEnd();
}