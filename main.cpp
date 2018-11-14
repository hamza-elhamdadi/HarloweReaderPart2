#include "Story.h"

int main()
{
  string s;
  Story st(s);

  StoryTokenizer storyTok;
  while(storyTok.hasNextPassage(st))
  {
    storyTok.nextPassage(st);
  }



}
