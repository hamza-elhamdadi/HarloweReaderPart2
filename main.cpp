#include <utility>
#include "Story.h"

int main()
{
  string s;

  Story st(s);
  Passage* p;

  vector<pair<string, string>> listOfLinks;
  int count = 0;

  StoryTokenizer storyTok;
  while(storyTok.hasNextPassage(st))
  {
    storyTok.nextPassage(st);
    *p = st.getPassages().at(count);
    st.addLookup(*p.getText(), count);
    count++;
  }
  //testing this coding method on the first passage, we need to eventually embed the following
  //code into another loop that doesnt stop after running this loop.
  //We can possible use recursion by putting the following code into another function above
  //int main and then when we need to go to another passage (like when an if/elseif/else is true
  //or when we hit a goto) we can just call the function again with the passage index as a parameter
  //then the function will run for the passage in the vector of passages at that index.
  for(int i = 0; i < st.getPassages().at(0).getSec().size(); i++)
  {
    type_t currentLinksType = st.getPassages().at(0).getSec().at(i).getType();
    string currentLinksText = st.getPassages().at(0).getSec().at(i).getText()
    //We will eventually need to add a test case for when the st.getPassages().at(0).getSec().at(i) has type null
    //We should probably use throw, try, and catch to fix the errors
    if(currentLinksType == SET)
    {
      addVariable(currentLinksText, st.getPassages().at(0).getSec().at(i).getValue());
    }
    elseif(currentLinksType == TEXT)
    {
      cout << currentLinksText << endl;
    }
    elseif(currentLinksType == LINK)
    {
      thisPassName = st.getPassages().at(0).getSec().at(i).getPassName();

      cout << "\"" + currentLinksText + "\"" << endl;
      listOfLinks.push_back(make_pair(currentLinksText, thisPassName));
    }
    elseif(currentLinksType == IF)
    {
      if(st.getPassages().at(0).getSec().at(i).getValueToCheck() == st.getVarVal(currentLinksText))
      {

      }
    }
  }

}
