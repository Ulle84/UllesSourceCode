#include "Members.h"

Members::Members()
{

}

Members::~Members()
{

}

bool Members::hasSetters() const
{
  for (auto it = begin(); it != end(); it++)
  {
    if (it->hasSetter())
    {
      return true;
    }
  }

  return false;
}

bool Members::hasGetters() const
{
  for (auto it = begin(); it != end(); it++)
  {
    if (it->hasGetter())
    {
      return true;
    }
  }

  return false;
}

QList<Member> Members::settableMembers() const
{
  QList<Member> members;

  for (auto it = begin(); it != end(); it++)
  {
    if (it->hasSetter())
    {
      members.append(*it);
    }
  }

  return members;
}

QList<Member> Members::gettableMembers() const
{
  QList<Member> members;

  for (auto it = begin(); it != end(); it++)
  {
    if (it->hasGetter())
    {
      members.append(*it);
    }
  }

  return members;
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

bool Members::hasDefaultValues() const
{
  for (auto it = begin(); it != end(); it++)
  {
    if (!it->defaultValue().isEmpty())
    {
      return true;
    }
  }

  return false;
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
