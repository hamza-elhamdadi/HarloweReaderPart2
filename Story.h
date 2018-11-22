#ifndef STORY_H
#define STORY_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include "Passage.h"

using namespace std;

class Story
{
private:
	friend class Section;
	friend class Passage;
	friend class StoryTokenizer;
	string storyText;
	vector<Passage*> passages;
	unordered_map<string, bool> variables;
	unordered_map<string, int> lookUpPassage;
public:
	Story(string s);
	void addLookup(string& name, int& index);
	void addVariable(string& varName, bool& value);
	bool getVarVal(string& varName) const;
	vector<Passage*> getPassages(int index) const{ return passages};
};

class StoryTokenizer /* Takes in story text, creates passage tokens */{
private:
	int index;
public:
	StoryTokenizer();
	bool hasNextPassage(Story& theStory);
	void nextPassage(Story& theStory);
};

#endif
