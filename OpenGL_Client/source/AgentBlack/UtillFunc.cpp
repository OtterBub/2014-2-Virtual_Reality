#include "UtillFunc.h"
#include <gl\glut.h>

void DrawStrokeText( const char *string, float x, float y, float z, float scale )
{
	const char *c = string;
	{
		glPushMatrix();
		{
			glTranslatef( x, y, z );
			//glColor3f( 1.0f, 1.0f, 1.0f );
			glScalef( scale, scale, scale );
			
			while( *c != '\0' )
			{
				glutStrokeCharacter( GLUT_STROKE_ROMAN, *c );
				c++;
			}			
		}
		glPopMatrix();
	}
}