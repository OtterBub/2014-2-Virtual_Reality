#ifndef __CONSOLESYSTEM_H__
#define __CONSOLESYSTEM_H__

#include "UtillFunc.h"
#include <list>
#include <string>
#include <ostream>

class ConsoleSystem
{
public:
	ConsoleSystem();
	~ConsoleSystem();

	static ConsoleSystem& GetInstance();

	void operator<<( std::string str );

	void Draw();
	void Reshape( int w, int h );
	void AddCharToCurrentStr( const unsigned char c );
	void DeleteCharToCurrentStr();
	void StringInput( std::string str );
	void SetCurrentString( std::string str );

	std::string NextLine();
	
private:
	

private:
	std::list< std::string > mStringList;
	std::list< std::string >::iterator mCurrentString;
	int mClientWidth, mClientHeight;
};

#define SKCONSOLE ConsoleSystem::GetInstance()

#endif