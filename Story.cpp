#include "Story.h"

bool StoryTokenizer::hasNextPassage(Story& theStory)
{
	if (theStory.storyText.find("<tw-passagedata ", index) == string::npos) {
		return false;
	}
	else {
		return true;
	}
}

void StoryTokenizer::nextPassage(Story& theStory)
{
	int passageBeginning;

	passageBeginning = theStory.storyText.find("<tw-passagedata ", index);
	index = theStory.storyText.find("</tw-passagedata>", passageBeginning) + 17;

	PassageToken ptok(theStory.storyText.substr(passageBeginning, index - passageBeginning));
	Passage p(ptok);

	theStory.passages.push_back(&p);
}

Story::Story(string text)
{
	theStory.storyText = text;
}

void Story::addLookup(string& name, int& index)
{
	variables[name] = index;
}

void Story::addVariable(string& varName, bool& value)
{
	lookUpPassage[varName] = value;
}

bool Story::getVarVal(string& varName) const
{
	return variables.at(varName);
}
