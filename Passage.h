#pragma once

#include <string>
#include <vector>
#include "Section.h"
#include "PassageToken.h"

using namespace std;

class Passage {
private:
	string passageText;
	vector<Section*> sections;
public:
	Passage(PassageToken pt);
	string getText() const { return passageText; };
};
