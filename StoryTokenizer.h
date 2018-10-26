#pragma once

#include <iostream>
#include <string>
#include "PassageToken.h"

using namespace std;

class StoryTokenizer // Takes in story text, creates passage tokens
{
private:
	string storyText;
	int index;
public:
	StoryTokenizer(string s);
	bool hasNextPassage();
	PassageToken nextPassage();
};

