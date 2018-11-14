#ifndef PASSAGE_H
#define PASSAGE_H

#include <string>
#include <vector>
#include "Section.h"

using namespace std;

class PassageToken /* Created by storytokenizer and calls passagetokenizer */{
private:
	string passageText;
public:
	PassageToken(string s);
	string getText() const{ return passageText; };
};

class Passage {
	friend class PassageTokenizer;
private:
	string name;
	vector<Section*> sections;
	int ptIndex;
public:
	Passage(PassageToken& pt);
};

class PassageTokenizer /* Creates sectiontokens */{
private:
	string passageText;
public:
	PassageTokenizer(string& passageText);
	bool hasNextSection(Passage& pass);
	void nextSection(Passage& pass);
};

#endif
