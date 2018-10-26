#pragma once

#include <vector>
#include <unordered_map>
#include "StoryTokenizer.h"
#include "Passage.h"

using namespace std;

class Story
{
private:
	vector<Passage*> passages;
	unordered_map<string, bool> variables;
	unordered_map<string, int> lookUpPassage;
public:
	Story();
	void startProgram();
};
