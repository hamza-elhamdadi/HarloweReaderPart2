#include "Section.h"

SectionToken::SectionToken(string& s)
{
  sectionText = s;
}

Link::Link(SectionToken& stok) : Section(stok)
{
  type = LINK;
  if(stok.getText().find(LINK_SEPARATOR, secIndex) != string::npos)
  {
    secIndex = stok.getText().find(LINK_SEPARATOR, secIndex) + 5;
    text = stok.getText().substr(2, secIndex - 2);
    secIndex += 5;
    passName = stok.getText().substr(secIndex, stok.getText().length() - secIndex - 2);
  }
  else{
    text = stok.getText().substr(2, stok.getText().length() - 4);
    passName = text;
  }
}

Text::Text(SectionToken& stok) : Section(stok)
{
  type = TEXT;
}

Goto::Goto(SectionToken& stok) : Section(stok)
{
  secIndex = stok.getText().find(GOTO_NAME_START, secIndex) + 6;
  type = GOTO;
  passName = stok.getText().substr(secIndex, stok.getText().find(GOTO_NAME_END, secIndex) - secIndex);
}

Set::Set(SectionToken& stok) : Section(stok)
{
  secIndex = stok.getText().find(VARIABLE_START) + 1;
  type = SET;
  text = stok.getText().substr(secIndex, stok.getText().find(" to ", secIndex) - secIndex);

  secIndex = stok.getText().find(" to ", secIndex) + 4;
  if(stok.getText().substr(secIndex, 4) == "true"){
    value = true;
  }
  else{
    value = false;
  }
}

If::If(SectionToken& stok) : Section(stok)
{
  secIndex = stok.getText().find("$") + 1;
  type = IF;
  text = stok.getText().substr(secIndex, stok.getText().find(" is ", secIndex) - secIndex);

  secIndex = stok.getText().find(" is ", secIndex) + 4;
  if(stok.getText().substr(secIndex, 4) == "true"){
    valueToCheck = true;
  }
  else{
    valueToCheck = false;
  }
}

Elseif::Elseif(SectionToken& stok) : Section(stok)
{
  secIndex = stok.getText().find("$") + 1;
  type = ELSEIF;
  text = stok.getText().substr(secIndex, stok.getText().find(" is ", secIndex) - secIndex);

  secIndex = stok.getText().find(" is ", secIndex) + 4;
  if(stok.getText().substr(secIndex, 4) == "true"){
    valueToCheck = true;
  }
  else{
    valueToCheck = false;
  }
}

Else::Else(SectionToken& stok) : Section(stok)
{
  type = ELSE;
}

bool BlockTokenizer::hasNextSection(Block& bl)
{
  if (bl.getText().find("(set:", bl.blIndex) != string::npos) {
		return true;
	}
	else if (bl.getText().find(GOTO_START, bl.blIndex) != string::npos) {
		return true;
	}
	else if (bl.getText().find(IF_START, bl.blIndex) != string::npos) {
		return true;
	}
	else if (bl.getText().find(ELSEIF_START, bl.blIndex) != string::npos) {
		return true;
	}
	else if (bl.getText().find(ELSE_START, bl.blIndex) != string::npos) {
		return true;
	}
	else if (bl.getText().find(LINK_START, bl.blIndex) != string::npos) {
		return true;
	}
	else if (bl.getText().substr(bl.blIndex, 1) != "]") {
		return true;
	}
	else {
		return false;
	}
}

void BlockTokenizer::nextSection(Block& bl)
{
  int sectionBeginning;
  string stokenText;

  while(bl.getText().substr(bl.blIndex, 1) == "\n")
  {
    bl.blIndex++;
  }

  //test to see if the next section is a Text Section.
  if ((bl.getText().substr(bl.blIndex, 1) != "(") && (bl.getText().substr(bl.blIndex, 1) != BLOCK_START))
  {
    sectionBeginning = bl.blIndex;

    if ((bl.getText().find("(", bl.blIndex) == string::npos) && (bl.getText().find(BLOCK_START, bl.blIndex) == string::npos))
    {
      bl.blIndex = bl.getText().find("]", bl.blIndex);
    }
    else if (bl.getText().find("(", bl.blIndex) < bl.getText().find(BLOCK_START, bl.blIndex))
    {
      bl.blIndex = bl.getText().find("(", bl.blIndex);
    }
    else
    {
      bl.blIndex = bl.getText().find(BLOCK_START, bl.blIndex);
    }
    stokenText = bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning);
    SectionToken stok(stokenText);
    Text text(stok);
    bl.addSection(text);
  }
  else if(bl.getText().substr(bl.blIndex, 3) == "[[[")
  {
    int counter = 1;
    sectionBeginning = bl.blIndex;
    bl.blIndex++;
    while(counter != 0){
      if(bl.getText().at(bl.blIndex) == '['){
        counter++;
      }
      if(bl.getText().at(bl.blIndex) == ']'){
        counter--;
      }
      bl.blIndex++;
    }
    stokenText = bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning);
    SectionToken stok(stokenText);
    Block block(stok);
    bl.addSection(block);
  }
  else if (bl.getText().substr(bl.blIndex, 5) == "(set:")
  {
    sectionBeginning = bl.getText().find("(set:", bl.blIndex);
    bl.blIndex = bl.getText().find(COMMAND_END, sectionBeginning) + 1;
    stokenText = bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning);
    SectionToken stok(stokenText);
    Set set(stok);
    bl.addSection(set);
  }
  else if (bl.getText().substr(bl.blIndex, 7) == GOTO_START)
  {
    sectionBeginning = bl.getText().find(GOTO_START, bl.blIndex);
    bl.blIndex = bl.getText().find(COMMAND_END, sectionBeginning) + 1;
    stokenText = bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning);
    SectionToken stok(stokenText);
    Goto go_to(stok);
    bl.addSection(go_to);
  }
  else if (bl.getText().substr(bl.blIndex, 4) == IF_START)
  {
    sectionBeginning = bl.getText().find(IF_START, bl.blIndex);
    bl.blIndex = bl.getText().find(COMMAND_END, sectionBeginning) + 1;
    stokenText = bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning);
    SectionToken stok(stokenText);
    If ifSec(stok);
    bl.addSection(ifSec);
  }
  else if (bl.getText().substr(bl.blIndex, 9) == ELSEIF_START)
  {
    sectionBeginning = bl.getText().find(ELSEIF_START, bl.blIndex);
    bl.blIndex = bl.getText().find(COMMAND_END, sectionBeginning) + 1;
    stokenText = bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning);
    SectionToken stok(stokenText);
    Elseif elseif(stok);
    bl.addSection(elseif);
  }
  else if (bl.getText().substr(bl.blIndex, 6) == ELSE_START)
  {
    sectionBeginning = bl.getText().find(ELSE_START, bl.blIndex);
    bl.blIndex = bl.getText().find(COMMAND_END, sectionBeginning) + 1;
    stokenText = bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning);
    SectionToken stok(stokenText);
    Else el(stok);
    bl.addSection(el);
  }
  else if (bl.getText().substr(bl.blIndex, 2) == LINK_START)
  {
    sectionBeginning = bl.getText().find(LINK_START, bl.blIndex);
    bl.blIndex = bl.getText().find(LINK_END, sectionBeginning) + 2;
    stokenText = bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning);
    SectionToken stok(stokenText);
    Link link(stok);
    bl.addSection(link);
  }
  else
  {
    int counter = 1;
    sectionBeginning = bl.blIndex;
    bl.blIndex++;
    while(counter != 0)
    {
      if(bl.getText().at(bl.blIndex) == '[')
      {
        counter++;
      }
      if(bl.getText().at(bl.blIndex) == ']')
      {
        counter--;
      }
      bl.blIndex++;
    }
    stokenText = bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning);
    SectionToken stok(stokenText);
    Block block(stok);
    bl.addSection(block);
  }
}

Block::Block(SectionToken& stok) : Section(stok)
{
  type = BLOCK;
  blIndex = 2;
  BlockTokenizer btkzr;

  while(btkzr.hasNextSection(*this))
  {
    btkzr.nextSection(*this);
  }
}

void Block::addSection(Section blockSect)
{
  blockSections.push_back(blockSect);
}

void Block::startBlock(unordered_map<string, bool>& variables, vector<pair<string, string>>& listOfLinks, int gotoIndex, bool& gotoExists, string& passName)
{
  bool ifElseIfElse = true;

  if(gotoExists == false)
  {
    for(int i = 0; i < blockSections.size(); i++)
  	{
  		if(blockSections.at(i).getType() == GOTO)
  		{
  			gotoIndex = i;
  			gotoExists = true;
  			passName = blockSections.at(i).getPassName();
        break;
  		}
  		else
  		{
  			gotoIndex = blockSections.at(i).getType();
  		}
  	}
  }

  for(int i = 0; i < gotoIndex; i++)
  {
    type_t currentType = blockSections.at(i).getType();
    string currentText = blockSections.at(i).getText();

    if(currentType == SET)
    {
      bool value = blockSections.at(i).getValue();
      variables[currentText] = value;
    }
    else if(currentType == TEXT)
    {
      cout << currentText << endl; // @suppress("Invalid overload")
    }
    else if(currentType == LINK)
    {
			if(gotoExists == false)
			{
				passName = blockSections.at(i).getPassName();

	      cout << "\"" + currentText + "\"" << endl; // @suppress("Invalid overload")
	      listOfLinks.push_back(make_pair(currentText, passName));
			}
    }
    else if(currentType == IF)
    {
      if(blockSections.at(i).getValueToCheck() == variables[currentText])
      {
        ifElseIfElse = false;
      }
      else
      {
        i++;
      }
    }
    else if(currentType == ELSEIF)
    {
      if(blockSections.at(i).getValueToCheck() == variables[currentText] && ifElseIfElse == true)
      {
        ifElseIfElse = false;
      }
      else
      {
        i++;
      }
    }
    else if(currentType == ELSE)
    {
      if(ifElseIfElse == false)
      {
        i++;
      }
    }
    else
    {
			blockSections.at(i).startBlock(variables, listOfLinks, gotoIndex, gotoExists, passName);
    }
  }
}
