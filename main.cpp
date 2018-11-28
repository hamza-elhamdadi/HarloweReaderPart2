#include <fstream>
#include "Story.h"

int main()
{
  string s, line, name;

  ifstream inFS;
  inFS.open("if.html");

  getline(inFS, line);
  while (line != "</html>")
  {
    s = s + line + '\n';
    getline(inFS, line);
  }

  Story st(s);
  int count = 0;

  StoryTokenizer storyTok;

  while(storyTok.hasNextPassage(st))
  {
    storyTok.nextPassage(st);
    name = st.getPassages().at(count).getName();
    st.addLookup(name, count);
    count++;
  }

  st.startPassage(0);

}
