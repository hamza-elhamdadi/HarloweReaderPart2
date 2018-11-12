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
	friend class StoryTokenizer;
	string storyText;
	vector<Passage*> passages;
	unordered_map<string, bool> variables;
	unordered_map<string, int> lookUpPassage;
public:
	Story();
	void startProgram();
};

class StoryTokenizer /* Takes in story text, creates passage tokens */{
private:
	int index;
public:
	StoryTokenizer();
	bool hasNextPassage(string& storyText, vector<Passage*>& passages);
	void nextPassage(string& storyText, vector<Passage*>& passages);
};

#endif
