#include "Story.h"

int main()
{
  string s;
  Story st(s);
  int count = 0;

  StoryTokenizer storyTok;
  while(storyTok.hasNextPassage(st))
  {
    storyTok.nextPassage(st);
    st.addLookup(st.getPassage(count).getText(), count);
    count++;
  }



}
