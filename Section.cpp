#include "Section.h"

SectionToken::SectionToken(string& s)
{
  sectionText = s;
}

Section::Section(SectionToken& st)
{
  text = st.getText();
  type = NULL;
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

  while(storyTok.hasNextPassage(st))
  {
    storyTok.nextPassage(st);
  }
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
