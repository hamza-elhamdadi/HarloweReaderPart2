#include <iostream>
#include <string>
#include "StoryTokenizer.h"

using namespace std;

int main()
{
	string line, story;

	getline(cin, line);
	while (cin && line != "</html>")
	{
		story += line + '\n';
		getline(cin, line);
	}

	StoryTokenizer st(story);
	while (st.hasNextPassage())
	{

	}

	return 0;
}
