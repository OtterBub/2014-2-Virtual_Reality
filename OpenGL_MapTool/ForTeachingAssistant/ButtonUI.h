#ifndef __BUTTON_UI_H__
#define __BUTTON_UI_H__

#include "Object.h"
#include <string>
#include <vector>

class ButtonUI
{
public:
	ButtonUI();
	~ButtonUI();

	void Draw();
	void Reshape( int w, int h );

	void ClearButton();
	void AddButton( std::string str, Vector2 pos, int id );
	void SetButtonSize( float size );

	int CheckButtonId( int x, int y );

private:
	struct Button
	{
		std::string str;
		Vector2 pos;
		int id;
	};

	float mButtonSize;
	
	std::vector< Button > mButton;
	Vector2 mClientSize;
};

#endif 