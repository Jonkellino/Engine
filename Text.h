#ifndef _TEXT_H_
#define _TEXT_H_

#include <string>
#include "RenderMessage.h"

class Text
{
public:
	Text(void);
	~Text(void);

	void Load(const std::string& aText, const std::string& anID);
	RenderMessage& Data();
	void Render();

private:

	RenderMessage myRenderMessage;
	std::string myString;
	std::string myID;

};

#endif