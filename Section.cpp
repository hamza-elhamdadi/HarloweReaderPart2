#include "Section.h"

SectionToken::SectionToken(string& s)
{
  sectionText = s;
}

Section::Section(SectionToken& st)
{
  text = st.getText();
  type = NULLTYPE;
}

Link::Link(SectionToken& stok) : Section(stok)
{
  secIndex = 0;
  type = LINK;
  if(stok.getText().find("-&gt;", secIndex) != string::npos)
  {
    secIndex = stok.getText().find("-&gt;", secIndex);
    text = stok.getText().substr(2, secIndex - 2);
    secIndex += 5;
    passName = stok.getText().substr(secIndex, stok.getText().length() - secIndex - 2);
  }
  else{
    text = stok.getText().substr(2, stok.getText().length - 4);
    passName = text;
  }
}

string Link::getPassName() const
{
  return passName;
}

Block::Block(SectionToken& stok) : Section(stok)
{
  type = BLOCK;
  blIndex = 2;
  BlockTokenizer btkzr();

  while(btkzr.hasNextPassage(*this))
  {
    btkzr.nextPassage(*this);
  }
}

void Block::addSection(Section* blockSect) const
{
  blockSections.push_back(blockSect);
}

Text::Text(SectionToken& stok) : Section(stok)
{
  type = TEXT;
}

Goto::Goto(SectionToken& stok) : Section(stok)
{
  secIndex = stok.getText().find("&quot;") + 6;
  type = GOTO;
  passName = stok.getText().substr(secIndex, stok.getText().find("&quot;", secIndex) - secIndex);
}

string Goto::getPassName() const
{
  return passName;
}

Set::Set(SectionToken& stok) : Section(stok)
{
  secIndex = stok.getText().find("$") + 1;
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

bool Set::getValue() const
{
  return value;
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

bool If::getValueToCheck() const
{
  return valueToCheck;
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

bool Elseif::getValueToCheck() const
{
  return valueToCheck;
}

Else::Else(SectionToken& stok) : Section(stok)
{
  type = ELSE;
}

bool BlockTokenizer::hasNextSection(Block& bl)
{
  if (bl.sectionText.find("(set:", bl.blIndex) != string::npos) {
		return true;
	}
	else if (bl.sectionText.find("(go-to:", bl.blIndex) != string::npos) {
		return true;
	}
	else if (bl.sectionText.find("(if:", bl.blIndex) != string::npos) {
		return true;
	}
	else if (bl.sectionText.find("(else-if:", bl.blIndex) != string::npos) {
		return true;
	}
	else if (bl.sectionText.find("(else:", bl.blIndex) != string::npos) {
		return true;
	}
	else if (bl.sectionText.find("[[", bl.blIndex) != string::npos) {
		return true;
	}
	else if (bl.sectionText.substr(bl.blIndex, 1) != "<") {
		return true;
	}
	else {
		return false;
	}
}

void BlockTokenizer::nextSection()
{
  int sectionBeginning;
  bl.blIndex += 2;

  //test to see if the next section is a Text Section.
  if ((bl.getText().substr(bl.blIndex, 1) != "(") && (bl.getText().substr(bl.blIndex, 1) != "["))
  {
    sectionBeginning = bl.blIndex;

    if ((bl.getText().find("(", bl.blIndex) == string::npos) && (bl.getText().find("[", bl.blIndex) == string::npos))
    {
      bl.blIndex = bl.getText().find("<", bl.blIndex);
    }
    else if (bl.getText().find("(", bl.blIndex) < bl.getText().find("[", bl.blIndex))
    {
      bl.blIndex = bl.getText().find("(", bl.blIndex);
    }
    else
    {
      bl.blIndex = bl.getText().find("[", bl.blIndex);
    }
    SectionToken stok(bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning));
    Text text(stok);
    bl.addSection(&text);
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
    SectionToken stok(bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning));
    Block block(stok);
    bl.addSection(&block);
  }
  else if (bl.getText().substr(bl.blIndex, 5) == "(set:")
  {
    sectionBeginning = bl.getText().find("(set:", bl.blIndex);
    bl.blIndex = bl.getText().find(")", sectionBeginning) + 1;
    SectionToken stok(bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning));
    Set set(stok);
    bl.addSection(&set);
  }
  else if (bl.getText().substr(bl.blIndex, 7) == "(go-to:")
  {
    sectionBeginning = bl.getText().find("(go-to:", bl.blIndex);
    bl.blIndex = bl.getText().find(")", sectionBeginning) + 1;
    SectionToken stok(bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning));
    Goto goto(stok);
    bl.addSection(&goto);
  }
  else if (bl.getText().substr(bl.blIndex, 4) == "(if:")
  {
    sectionBeginning = bl.getText().find("(if:", bl.blIndex);
    bl.blIndex = bl.getText().find(")", sectionBeginning) + 1;
    SectionToken stok(bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning));
    If ifSec(stok);
    bl.addSection(&ifSec);
  }
  else if (bl.getText().substr(bl.blIndex, 9) == "(else-if:")
  {
    sectionBeginning = bl.getText().find("(else-if:", bl.blIndex);
    bl.blIndex = bl.getText().find(")", sectionBeginning) + 1;
    SectionToken stok(bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning));
    Elseif elseif(stok);
    bl.addSection(&elseif);
  }
  else if (bl.getText().substr(bl.blIndex, 6) == "(else:")
  {
    sectionBeginning = bl.getText().find("(else:", bl.blIndex);
    bl.blIndex = bl.getText().find(")", sectionBeginning) + 1;
    SectionToken stok(bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning));
    Else el(stok);
    bl.addSection(&el);
  }
  else if (bl.getText().substr(bl.blIndex, 2) == "[[")
  {
    sectionBeginning = bl.getText().find("[[", bl.blIndex);
    bl.blIndex = bl.getText().find("]]", sectionBeginning) + 2;
    SectionToken stok(bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning));
    Link link(stok);
    bl.addSection(&link);
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
    SectionToken stok(bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning), BLOCK);
    Block block(stok);
    bl.addSection(&block);
  }
}
