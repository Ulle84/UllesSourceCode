#ifndef Member_h
#define Member_h

#include <QString>

class Member
{
public:
  Member();
  ~Member();

  QString declaration() const;

  QString type() const;
  void setType(const QString& type);

  QString name() const;
  void setName(const QString& name);

  QString defaultValue() const;
  void setDefaultValue(const QString& defaultValue);

  enum DeclarationType
  {
    Public,
    Protected,
    Private
  };
  DeclarationType declarationType() const;
  void setDeclarationType(DeclarationType declarationType);

private:
  QString m_type;
  QString m_name;
  QString m_defaultValue;
  DeclarationType m_declarationType;
};

#endif // Member_h
