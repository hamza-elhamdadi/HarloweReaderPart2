#include "Section.h"

SectionToken::SectionToken(string& s)
{
  sectionText = s;
}

Section::Section(SectionToken& st)
{

}

Link::Link(SectionToken& stok) : Section(stok)
{

}

Goto::Goto(SectionToken& stok) : Section(stok)
{

}

if::If(SectionToken& stok) : Section(stok)
{

}

Elseif::Elseif(SectionToken& stok) : Section(stok)
{

}

Else::Else(SectionToken& stok) : Section(stok)
{

}

Set::Set(SectionToken& stok) : Section(stok)
{

}

Text::Text(SectionToken& stok) : Section(stok)
{

}

Block::Block(SectionToken& stok) : Section(stok)
{

}
