#ifndef SECTION_H
#define SECTION_H

#include <utility>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

enum type_t {NULLTYPE, LINK, SET, GOTO, IF, ELSEIF, ELSE, TEXT, BLOCK};

const string PASSAGE_START_TAG = "<tw-passagedata";
const string PASSAGE_START_TAG_CLOSE = ">";
const string PASSAGE_END_TAG   = "</tw-passagedata>";
const string LINK_START = "[[";
const string LINK_SEPARATOR = "-&gt;";
const string LINK_END   = "]]";
const string GOTO_START = "(go-to:";
const string SET_START = "(set:";
const string IF_START = "(if:";
const string ELSEIF_START = "(else-if:";
const string ELSE_START = "(else:";
const string COMMAND_END = ")";
const string BLOCK_START = "[";
const string BLOCK_END   = "]";
const string PASSAGE_NAME_START = "name=\"";
const string PASSAGE_NAME_END = "\"";
const string GOTO_NAME_START = "&quot;";
const string GOTO_NAME_END = "&quot;";
const string VARIABLE_START = "$";

class SectionToken
{
	friend class BlockTokenizer;
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
	int secIndex;
public:
	Section(SectionToken& st) : secIndex(0), text(st.getText()), type(NULLTYPE) {};
	string getText() const { return text; };
	type_t getType() const { return type; };
	virtual string getPassName(){ return ""; };
	virtual int getValue(){ return 0; };
	virtual int getValueToCheck(){ return 0; };
	virtual void startBlock(unordered_map<string, bool>& lookUpPassage, vector<pair<string, string>>& listOfLinks, int gotoIndex, bool& gotoExists, string& passName) {};
};

class Link : public Section
{
private:
	string passName;
public:
	Link(SectionToken& stok);
	string getPassName() { return passName; };
};

class Block : public Section
{
	friend class BlockTokenizer;
private:
	vector<Section> blockSections;
	int blIndex = 0;
public:
	Block(SectionToken& stok);
	void addSection(Section blockSect);
	void startBlock(unordered_map<string, bool>& variables, vector<pair<string, string>>& listOfLinks, int gotoIndex, bool& gotoExists, string& passName);
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
	bool getValueToCheck() const { return valueToCheck; };
};

class Elseif : public Section
{
private:
	bool valueToCheck;
public:
	Elseif(SectionToken& stok);
	bool getValueToCheck() const { return valueToCheck; };
};

class Else : public Section
{
public:
	Else(SectionToken& stok);
};

class BlockTokenizer
{
public:
	BlockTokenizer(){};
	bool hasNextSection(Block& bl);
	void nextSection(Block& bl);
};

#endif
