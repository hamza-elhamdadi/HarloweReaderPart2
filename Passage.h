#ifndef PASSAGE_H
#define PASSAGE_H

#include <string>
#include <vector>
#include "Section.h"

using namespace std;

class Passage {
private:
	string passageText;
	vector<Section*> sections;
public:
	Passage(PassageToken pt);
	string getText() const { return passageText; };
};

class PassageToken /* Created by storytokenizer and calls passagetokenizer */{
private:
	string passageText;
public:
	PassageToken(string s);
	string getText();
};

class PassageTokenizer /* Creates sectiontokens */{
private:
	string passageText;
public:
	PassageTokenizer(string s);
	virtual ~PassageTokenizer();
	bool hasNextSection();
	virtual SectionToken nextSection();
};


#endif
