#include "Section.h"

Section::Section(SectionToken st)
{
  //remember there can be invalid sections
}

SectionToken::SectionToken(string s)
{

}

Link::Link(SectionToken stok) : Section(SectionToken)
{

}

Goto::Goto(SectionToken stok) : Section(SectionToken)
{

}

if::If(SectionToken stok) : Section(SectionToken)
{

}

Elseif::Elseif(SectionToken stok) : Section(SectionToken)
{

}

Else::Else(SectionToken stok) : Section(SectionToken)
{

}

Set::Set(SectionToken stok) : Section(SectionToken)
{

}

Text::Text(SectionToken stok) : Section(stok.getText())
{

}

Block::Block(SectionToken stok) : Section(stok.getText())
{

}
