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

int Story::lookup(string& passName) const
{
	return lookUpPassage.at(passName);
}

void Story::startPassage(int index)
{
  bool ifElseIfElse = true;
	bool gotoExists = false;
	int j, chosen;
	string passName;

	for(int i = 0; i < passages.at(index).getSec().size(); i++)
	{
		if(passages.at(index).getSec().at(i).getType() == GOTO)
		{
			j = i;
			gotoExists = true;
			passName = passages.at(index).getSec().at(i).getPassName();
		}
		else
		{
			j = passages.at(index).getSec().at(i).getType();
		}
	}

  for(int i = 0; i < j; i++)
  {
    type_t currentLinksType = passages.at(index).getSec().at(i).getType();
    string currentLinksText = passages.at(index).getSec().at(i).getText()
    //We will eventually need to add a test case for when the passages.at(0).getSec().at(i) has type null
    //We should probably use throw, try, and catch to fix the errors
    if(currentLinksType == SET)
    {
      addVariable(currentLinksText, passages.at(index).getSec().at(i).getValue());
    }
    else if(currentLinksType == TEXT)
    {
      cout << currentLinksText << endl;
    }
    else if(currentLinksType == LINK)
    {
			if(gotoExists == false)
			{
				passName = passages.at(index).getSec().at(i).getPassName();

	      cout << "\"" + currentLinksText + "\"" << endl;
	      listOfLinks.push_back(make_pair(currentLinksText, passName));
			}
    }
    else if(currentLinksType == IF)
    {
      if(passages.at(index).getSec().at(i).getValueToCheck() == getVarVal(currentLinksText))
      {
        ifElseIfElse = false;
      }
      else
      {
        i++;
      }
    }
    else if(currentLinksType == ELSEIF)
    {
      if(passages.at(index).getSec().at(i).getValueToCheck() == getVarVal(currentLinksText) && ifElseIfElse == true)
      {
        ifElseIfElse = false;
      }
      else
      {
        i++;
      }
    }
    else if(currentLinksType == ELSE)
    {
      if(ifElseIfElse == false)
      {
        i++;
      }
    }
    else
    {
			//This is for blocks. The problem is we need to run through this startPassage function again for the block itself.
			//i.e. check each of the sections in the vector blockSections just like we checked each of the sections in the passage
    }

  }

	if(listOfLinks.size() > 0)
	{
		for(int i = 0; i < listOfLinks.size(); i++)
		{
			cout << (i + 1) << ". " << listOfLinks.at(i).first << endl;
		}

		cin >> chosen;
		chosen--;
		passName = listOfLinks.at(chosen);

	}

	chosen = lookup(passName);

	startPassage(chosen);
}
