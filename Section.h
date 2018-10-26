#pragma once

#include <string>
#include "SectionToken.h"

using namespace std;

class Section
{
protected:
	string text;
public:
	Section(SectionToken st);
	string getText() const { return text; };
};
