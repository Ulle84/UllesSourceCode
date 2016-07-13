#ifndef Member_h
#define Member_h

#include <QString>
#include <QStringList>

class Member
{
public:
  Member();
  ~Member();

  QString declaration() const;
  QString getterDeclaration() const;
  QString setterDeclaration() const;

  QString getterImplementation(const QString& leadingIndent, const QString& singleIndent, const QString& className) const;
  QString setterImplementation(const QString& leadingIndent, const QString& singleIndent, const QString& className) const;

  QString elementInitialisation(const QString &leadingIndent) const;
  QString copyInitialisation(const QString &leadingIndent, const QString& rhs) const;
  QString copyAssignment(const QString& rhs) const;

  QString type() const;
  void setType(const QString& type);

  QString name() const;
  void setName(const QString& name);

  QString nameWithoutPrefix() const;
  QString nameWithPrefix() const;

  QString defaultValue() const;
  void setDefaultValue(const QString& defaultValue);

  bool hasGetter() const;
  void setGetter(bool getter);

  bool hasSetter() const;
  void setSetter(bool setter);

  enum DeclarationType
  {
    Public,
    Protected,
    Private
  };
  DeclarationType declarationType() const;
  void setDeclarationType(DeclarationType declarationType);

private:
  QString upperCaseFirstLetter(const QString& string) const;
  QString setterSignature(const QString& className = QString()) const;

  QString m_type;
  QString m_name;
  QString m_defaultValue;
  DeclarationType m_declarationType;
  bool m_getter;
  bool m_setter;
  QString m_prefix;
  QStringList m_primitiveTypes;
};

#endif // Member_h
