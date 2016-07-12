#include "Members.h"

Members::Members()
{

}

Members::~Members()
{

}

bool Members::hasPublicMembers() const
{
  return hasDeclarationType(Member::DeclarationType::Public);
}

bool Members::hasProtectedMembers() const
{
  return hasDeclarationType(Member::DeclarationType::Protected);
}

bool Members::hasPrivateMembers() const
{
  return hasDeclarationType(Member::DeclarationType::Private);
}

QList<Member> Members::publicMembers() const
{
  return members(Member::DeclarationType::Public);
}

QList<Member> Members::protectedMembers() const
{
  return members(Member::DeclarationType::Protected);
}

QList<Member> Members::privateMembers() const
{
  return members(Member::DeclarationType::Private);
}

bool Members::hasDeclarationType(Member::DeclarationType declarationType) const
{
  for (auto it = begin(); it != end(); it++)
  {
    if (it->declarationType() == declarationType)
    {
      return true;
    }
  }

  return false;
}

QList<Member> Members::members(Member::DeclarationType declarationType) const
{
  QList<Member> members;

  for (auto it = begin(); it != end(); it++)
  {
    if (it->declarationType() == declarationType)
    {
      members.append(*it);
    }
  }

  return members;
}
