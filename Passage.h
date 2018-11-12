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
	string getText();
};

class Passage {
private:
	string name;
	vector<Section*> sections;
public:
	Passage(PassageToken& pt);
	string getText() const { return passageText; };
};

class PassageTokenizer /* Creates sectiontokens */{
private:
	string passageText;
	int ptIndex;
public:
	PassageTokenizer(string& passageText, vector<Section*>& sections);
	bool hasNextSection(string& passageText, vector<Section*>& sections);
	virtual SectionToken nextSection();
};


#endif
