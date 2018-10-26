#pragma once

#include <string>

using namespace std;

enum type_t { LINK, COMMAND, BLOCK, TEXT, GOTO, SET, IF, ELSEIF, ELSE };

class SectionToken
{
protected:
	string sectionText;
	type_t type;
public:
	SectionToken(string s);
	string getText() const { return sectionText; };
	type_t getType() const { return type; };
};

class Link : SectionToken::SectionToken
{

};

class Command : SectionToken::SectionToken
{

};

class Block : SectionToken::SectionToken
{

};

class Text : SectionToken::SectionToken
{

};

class Goto : SectionToken::SectionToken
{

};

class Set : SectionToken::SectionToken
{

};

class If : SectionToken::SectionToken
{

};

class Elseif : SectionToken::SectionToken
{

};

class Else : SectionToken::SectionToken
{

};
