#ifndef Members_h
#define Members_h

#include <QList>

#include "Member.h"

class Members : public QList<Member>
{
public:
  Members();
  ~Members();

  bool hasSetters() const;
  bool hasGetters() const;

  QList<Member> settableMembers() const;
  QList<Member> gettableMembers() const;

  bool hasPublicMembers() const;
  bool hasProtectedMembers() const;
  bool hasPrivateMembers() const;

  QList<Member> publicMembers() const;
  QList<Member> protectedMembers() const;
  QList<Member> privateMembers() const;

private:
  bool hasDeclarationType(Member::DeclarationType declarationType) const;
  QList<Member> members(Member::DeclarationType declarationType) const;
};

#endif // Members_h
