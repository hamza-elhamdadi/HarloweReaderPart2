#pragma once

#include <string>

using namespace std;

class PassageToken // Created by storytokenizer and calls passagetokenizer
{
private:
	string passageText;
public:
	PassageToken(string s);
	string getText();
};

