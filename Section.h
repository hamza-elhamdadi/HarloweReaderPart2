#ifndef SECTION_H
#define SECTION_H

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

class Link : public SectionToken
{

};

class Command : public SectionToken
{

};

class Block : public SectionToken
{

};

class Text : public SectionToken
{

};

class Goto : public SectionToken
{

};

class Set : public SectionToken
{

};

class If : public SectionToken
{

};

class Elseif : public SectionToken
{

};

class Else : public SectionToken
{

};

class Section
{
protected:
	string text;
public:
	Section(SectionToken st);
	string getText() const { return text; };
};

#endif
