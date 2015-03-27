#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "MathUtill.h"

class Object
{
public:
	Object();
	~Object();
	virtual void Draw() = 0;
	virtual void Update( double dt ) = 0;
	virtual void Reshape( int w, int h );

private:

};

#endif