#include <fstream>
#include "Story.h"

int main()
{
  string s, line;

  ifstream inFS;
  inFS.open("if.html");

  getline(inFS, );
  while (!inFS.eof() && line != "</html>")
  {
    s += line + '\n';
    getline(inFS, line);
  }

  Story st(s);
  Passage* p;
  int count = 0;

  StoryTokenizer storyTok;
  while(storyTok.hasNextPassage(st))
  {
    storyTok.nextPassage(st);
    *p = st.getPassages().at(count);
    st.addLookup(*p.getText(), count);
    count++;
  }

  st.startPassage(0);

}
