#ifndef SECTION_H
#define SECTION_H

#include <string>

using namespace std;

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
public:
	Section(SectionToken& st);
	string getText() const { return text; };
};

class Link : public Section
{
private:
public:

};

class Block : public Section
{
private:
public:
};

class Text : public Section
{
private:
public:
};

class Goto : public Section
{
private:
public:
};

class Set : public Section
{
private:
public:
};

class If : public Section
{
private:
public:
};

class Elseif : public Section
{
private:
public:
};

class Else : public Section
{
private:
public:
};


#endif
