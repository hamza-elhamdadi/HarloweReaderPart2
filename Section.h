#ifndef SECTION_H
#define SECTION_H

#include <string>

using namespace std;

enum type_t {NULL, LINK, SET, GOTO, IF, ELSEIF, ELSE, TEXT, BLOCK};

class SectionToken
{
protected:
	string sectionText;
public:
	SectionToken(string& s);
	string getText() const { return sectionText; };
};

class Section
{
protected:
	string text;
	type_t type;
public:
	Section(SectionToken& st);
	string getText() const { return text; };
	type_t getType() const { return type; };
};

class Link : public Section
{
private:
	string passName;
public:
	Link(SectionToken& stok);
	string getPassName() const { return passName; };
};

class Block : public Section
{
	friend class PassageTokenizer;
private:
	vector<Section*> blockSections;
public:
	Block(SectionToken& stok);
};

class Text : public Section
{
public:
	Text(SectionToken& stok);
};

class Goto : public Section
{
private:
	string passName;
public:
	Goto(SectionToken& stok);
	string getPassName() const { return passName; };
};

class Set : public Section
{
private:
	bool value;
public:
	Set(SectionToken& stok);
	bool getValue() const { return value;};
};

class If : public Section
{
private:
	bool valueToCheck;
public:
	If(SectionToken& stok);
	bool getValueToCheck() const { return value; };
};

class Elseif : public Section
{
private:
	bool valueToCheck;
public:
	Elseif(SectionToken& stok);
	bool getValueToCheck() const { return value; };
};

class Else : public Section
{
public:
	Else(SectionToken& stok);
};


#endif
