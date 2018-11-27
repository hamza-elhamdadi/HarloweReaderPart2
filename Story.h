#ifndef STORY_H
#define STORY_H


#include "Passage.h"

using namespace std;

class Story
{
private:
	friend class Section;
	friend class Passage;
	friend class StoryTokenizer;
	string storyText;
	vector<Passage> passages;
	vector<pair<string, string>> listOfLinks;
	unordered_map<string, bool> variables;
	unordered_map<string, int> lookUpPassage;
public:
	Story(string text);
	void addLookup(string& name, int& index);
	void addVariable(string& varName, bool& value);
	bool getVarVal(string& varName) const;
	int lookup(string& passName) const;
	vector<Passage> getPassages(){ return passages; };
	void startPassage(int index);
};

class StoryTokenizer /* Takes in story text, creates passage tokens */{
private:
	int index;
public:
	StoryTokenizer(){};
	bool hasNextPassage(Story& theStory);
	void nextPassage(Story& theStory);
};

#endif
