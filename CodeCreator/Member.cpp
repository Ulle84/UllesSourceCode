#include "Member.h"

Member::Member()
{

}

Member::~Member()
{

}

Member::DeclarationType Member::declarationType() const
{
  return m_declarationType;
}

void Member::setDeclarationType(Member::DeclarationType declarationType)
{
  m_declarationType = declarationType;
}
