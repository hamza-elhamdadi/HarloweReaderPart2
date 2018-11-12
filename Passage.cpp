#include "Passage.h"

string PassageToken::getText()
{
  return passageText;
}

bool PassageTokenizer::hasNextSection(string& passageText, vector<Section*>& sections)
{
  if (passageText.find("(set:", index) != string::npos) {
		return true;
	}
	else if (passageText.find("(go-to:", index) != string::npos) {
		return true;
	}
	else if (passageText.find("(if:", index) != string::npos) {
		return true;
	}
	else if (passageText.find("(else-if:", index) != string::npos) {
		return true;
	}
	else if (passageText.find("(else:", index) != string::npos) {
		return true;
	}
	else if (passageText.find("[[", index) != string::npos) {
		return true;
	}
	else if (passageText.substr(index, 1) != "<") {
		return true;
	}
	else {
		return false;
	}
}

void PassageTokenizer::nextSection(string& passageText, vector<Section*>& sections)
{
  int sectionBeginning;

  if ((passageText.substr(index, 1) != "(") && (passageText.substr(index, 1) != "[")) {
    sectionBeginning = index;

    if ((passageText.find("(", index) == string::npos) && (passageText.find("[", index) == string::npos)) {
      index = passageText.find("<", index);
    }
    else if (passageText.find("(", index) < passageText.find("[", index)) {
      index = passageText.find("(", index);
    }
    else {
      index = passageText.find("[", index);
    }
    SectionToken stok(passageText.substr(sectionBeginning, index - sectionBeginning), TEXT);
    Text text(stok);
    sections.push_back(&text);
  }
  else if(passageText.substr(index, 3) == "[[["){
    int counter = 1;
    sectionBeginning = index;
    index++;
    while(counter != 0){
      if(passageText.at(index) == '['){
        counter++;
      }
      if(passageText.at(index) == ']'){
        counter--;
      }
      index++;
    }
    SectionToken stok(passageText.substr(sectionBeginning, index - sectionBeginning), BLOCK);
    Block block(stok);
    sections.push_back(&block);
  }
  else if (passageText.substr(index, 5) == "(set:") {
    sectionBeginning = passageText.find("(set:", index);
    index = passageText.find(")", sectionBeginning) + 1;
    SectionToken stok(passageText.substr(sectionBeginning, index - sectionBeginning), SET);
    Set set(stok);
    sections.push_back(&set);
  }
  else if (passageText.substr(index, 7) == "(go-to:") {
    sectionBeginning = passageText.find("(go-to:", index);
    index = passageText.find(")", sectionBeginning) + 1;
    SectionToken stok(passageText.substr(sectionBeginning, index - sectionBeginning), GOTO);
    Goto goto(stok);
    sections.push_back(&goto);
  }
  else if (passageText.substr(index, 4) == "(if:") {
    sectionBeginning = passageText.find("(if:", index);
    index = passageText.find(")", sectionBeginning) + 1;
    SectionToken stok(passageText.substr(sectionBeginning, index - sectionBeginning), IF);
    If ifSec(stok);
    sections.push_back(&ifSec);
  }
  else if (passageText.substr(index, 9) == "(else-if:") {
    sectionBeginning = passageText.find("(else-if:", index);
    index = passageText.find(")", sectionBeginning) + 1;
    SectionToken stok(passageText.substr(sectionBeginning, index - sectionBeginning), ELSEIF);
    Elseif elseif(stok);
    sections.push_back(&elseif);
  }
  else if (passageText.substr(index, 6) == "(else:") {
    sectionBeginning = passageText.find("(else:", index);
    index = passageText.find(")", sectionBeginning) + 1;
    SectionToken stok(passageText.substr(sectionBeginning, index - sectionBeginning), ELSE);
    Else el(stok);
    sections.push_back(&el);
  }
  else if (passageText.substr(index, 2) == "[[") {
    sectionBeginning = passageText.find("[[", index);
    index = passageText.find("]]", sectionBeginning) + 2;
    SectionToken stok(passageText.substr(sectionBeginning, index - sectionBeginning), LINK);
    Link link(stok);
    sections.push_back(&link);
  }
  else {
    int counter = 1;
    sectionBeginning = index;
    index++;
    while(counter != 0){
      if(passageText.at(index) == '['){
        counter++;
      }
      if(passageText.at(index) == ']'){
        counter--;
      }
      index++;
    }
    SectionToken stok(passageText.substr(sectionBeginning, index - sectionBeginning), BLOCK);
    Block block(stok);
    sections.push_back(&block);
  }
}

Passage::Passage(PassageToken pt)
{
  int passageNameBeginning = pt.getText().find("name=", ptIndex) + 6;
  index = pt.getText().find("\"", passageNameBeginning);

  name = pt.getText().substr(passageNameBeginning, index);

  PassageTokenizer ptkzr();
  while(ptkzr.hasNextSection())
  {
    ptkzr.nextSection();
  }

}

PassageToken::PassageToken(string s)
{
  passageText = s;
}
