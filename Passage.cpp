#include "Passage.h"

Passage::Passage(PassageToken& pt)
{
  ptIndex = 0;

  int passageNameBeginning = pt.getText().find("name=", ptIndex) + 6;
  ptIndex = pt.getText().find("\"", passageNameBeginning);

  name = pt.getText().substr(passageNameBeginning, ptIndex - passageNameBeginning);

  string passageText = pt.getText();
  PassageTokenizer ptkzr(passageText, *this);

  while(ptkzr.hasNextSection(*this))
  {
    //infinite loop
    ptkzr.nextSection(*this);
  }

}

PassageToken::PassageToken(string s)
{
  passageText = s;
}

PassageTokenizer::PassageTokenizer(string& text, Passage& pass)
{
  passageText = text;
  pass.ptIndex = passageText.find(">") + 1;
}

bool PassageTokenizer::hasNextSection(Passage& pass)
{
  if (passageText.substr(pass.ptIndex, 1) != "<") {
		return true;
	}
	else {
		return false;
	}
}

void PassageTokenizer::nextSection(Passage& pass)
{
  unsigned int sectionBeginning, sectionEnding;
  string ptokenText;

  while(passageText.substr(pass.ptIndex, 1) == "\n")
  {
    pass.ptIndex++;
  }

  //test to see if the next section is a Text Section.
  if ((passageText.substr(pass.ptIndex, 1) != "(") && (passageText.substr(pass.ptIndex, 1) != "["))
  {
    sectionBeginning = pass.ptIndex;

    textCheck(pass);

    ptokenText = passageText.substr(sectionBeginning, pass.ptIndex - sectionBeginning);
    SectionToken stok(ptokenText);
    Text text(stok);
    pass.sections.push_back(text);
  }
  else if(passageText.substr(pass.ptIndex, 3) == "[[[")
  {
    int counter = 1;
    sectionBeginning = pass.ptIndex;
    pass.ptIndex++;
    while(counter != 0){
      if(passageText.at(pass.ptIndex) == '['){
        counter++;
      }
      if(passageText.at(pass.ptIndex) == ']'){
        counter--;
      }
      pass.ptIndex++;
    }
    ptokenText = passageText.substr(sectionBeginning, pass.ptIndex - sectionBeginning);
    SectionToken stok(ptokenText);
    Block block(stok);
    pass.sections.push_back(block);
  }
  else if (passageText.substr(pass.ptIndex, 5) == "(set:")
  {
    sectionBeginning = passageText.find("(set:", pass.ptIndex);
    pass.ptIndex = passageText.find(")", sectionBeginning) + 1;
    ptokenText = passageText.substr(sectionBeginning, pass.ptIndex - sectionBeginning);
    SectionToken stok(ptokenText);
    Set set(stok);
    pass.sections.push_back(set);
  }
  else if (passageText.substr(pass.ptIndex, 7) == "(go-to:")
  {
    sectionBeginning = passageText.find("(go-to:", pass.ptIndex);
    pass.ptIndex = passageText.find(")", sectionBeginning) + 1;
    ptokenText = passageText.substr(sectionBeginning, pass.ptIndex - sectionBeginning);
    SectionToken stok(ptokenText);
    Goto tgoto(stok);
    pass.sections.push_back(tgoto);
  }
  else if (passageText.substr(pass.ptIndex, 4) == "(if:")
  {
    sectionBeginning = passageText.find("(if:", pass.ptIndex);
    pass.ptIndex = passageText.find(")", sectionBeginning) + 1;
    ptokenText = passageText.substr(sectionBeginning, pass.ptIndex - sectionBeginning);
    SectionToken stok(ptokenText);
    If ifSec(stok);
    pass.sections.push_back(ifSec);
  }
  else if (passageText.substr(pass.ptIndex, 9) == "(else-if:")
  {
    sectionBeginning = passageText.find("(else-if:", pass.ptIndex);
    pass.ptIndex = passageText.find(")", sectionBeginning) + 1;
    ptokenText = passageText.substr(sectionBeginning, pass.ptIndex - sectionBeginning);
    SectionToken stok(ptokenText);
    Elseif elseif(stok);
    pass.sections.push_back(elseif);
  }
  else if (passageText.substr(pass.ptIndex, 6) == "(else:")
  {
    sectionBeginning = passageText.find("(else:", pass.ptIndex);
    pass.ptIndex = passageText.find(")", sectionBeginning) + 1;
    ptokenText = passageText.substr(sectionBeginning, pass.ptIndex - sectionBeginning);
    SectionToken stok(ptokenText);
    Else el(stok);
    pass.sections.push_back(el);
  }
  else if (passageText.substr(pass.ptIndex, 2) == "[[")
  {
    sectionBeginning = passageText.find("[[", pass.ptIndex);
    pass.ptIndex = passageText.find("]]", sectionBeginning) + 2;
    ptokenText = passageText.substr(sectionBeginning, pass.ptIndex - sectionBeginning);
    SectionToken stok(ptokenText);
    Link link(stok);
    pass.sections.push_back(link);
  }
  else
  {
    int counter = 1;
    sectionBeginning = pass.ptIndex;
    pass.ptIndex++;
    while(counter != 0)
    {
      if(passageText.at(pass.ptIndex) == '[')
      {
        counter++;
      }
      if(passageText.at(pass.ptIndex) == ']')
      {
        counter--;
      }
      pass.ptIndex++;
    }
    ptokenText = passageText.substr(sectionBeginning, pass.ptIndex - sectionBeginning);
    SectionToken stok(ptokenText);
    Block block(stok);
    pass.sections.push_back(block);
  }
}

void PassageTokenizer::textCheck(Passage& pass)
{
  if ((passageText.find("(", pass.ptIndex) == string::npos) && (passageText.find("[", pass.ptIndex) == string::npos))
  {
    pass.ptIndex = passageText.find("<", pass.ptIndex);
  }
  else if (passageText.find("(", pass.ptIndex) < passageText.find("[", pass.ptIndex))
  {
    pass.ptIndex = passageText.find("(", pass.ptIndex);
    if((passageText.substr(pass.ptIndex, 7) != "(go-to:") && (passageText.substr(pass.ptIndex, 5) != "(set:") && (passageText.substr(pass.ptIndex, 4) != "(if:") && (passageText.substr(pass.ptIndex, 9) != "(else-if:") && (passageText.substr(pass.ptIndex, 6) != "(else:"))
    {
      pass.ptIndex = passageText.find(")", pass.ptIndex) + 1;
      textCheck(pass);
    }
  }
  else
  {
    pass.ptIndex = passageText.find("[", pass.ptIndex);
  }
}
