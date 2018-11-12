#include "Story.h"

bool StoryTokenizer::hasNextPassage(string& storyText, vector<Passage*>& passages)
{
	if (storyText.find("<tw-passagedata ", index) == string::npos) {
		return false;
	}
	else {
		return true;
	}
}

void StoryTokenizer::nextPassage(string& storyText, vector<Passage*>& passages)
{
	int passageBeginning;

	passageBeginning = storyText.find("<tw-passagedata ", index);
	index = storyText.find("</tw-passagedata>", passageBeginning) + 17;

	PassageToken ptok(storyText.substr(passageBeginning, index - passageBeginning));
	Passage p(ptok);

	passages.push_back(&p);
}

Story::Story(string text)
{
	storyText = text;
}

//starts the program
void Story::startProgram()
{
	StoryTokenizer storyTok();
	while(storyTok.hasNextPassage())
	{
		storyTok.nextPassage();
	}
}
