#include "Section.h"

SectionToken::SectionToken(string& s)
{
  sectionText = s;
}

Section::Section(SectionToken& st)
{
  text = st.getText();
  type = NULL;
}

Link::Link(SectionToken& stok) : Section(stok)
{
  type = LINK;
}

Block::Block(SectionToken& stok) : Section(stok)
{
  type = BLOCK;

  while(storyTok.hasNextPassage(st))
  {
    storyTok.nextPassage(st);
  }
}

Text::Text(SectionToken& stok) : Section(stok)
{
  type = TEXT;
}

Goto::Goto(SectionToken& stok) : Section(stok)
{
  type = GOTO;
}

Set::Set(SectionToken& stok) : Section(stok)
{
  type = SET;
}

If::If(SectionToken& stok) : Section(stok)
{
  type = IF;
}

Elseif::Elseif(SectionToken& stok) : Section(stok)
{
  type = ELSEIF;
}

Else::Else(SectionToken& stok) : Section(stok)
{
  type = ELSE;
}
