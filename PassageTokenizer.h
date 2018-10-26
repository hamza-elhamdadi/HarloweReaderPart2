#pragma once

#include <string>
#include "SectionToken.h"

using namespace std;

class PassageTokenizer // Creates sectiontokens
{
private:
	string passageText;
public:
	PassageTokenizer(string s);
	virtual ~PassageTokenizer();
	bool hasNextSection();
	virtual SectionToken nextSection();
};

