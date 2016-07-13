#include "Member.h"

Member::Member() :
  m_getter(false),
  m_setter(false),
  m_prefix("m_")
{
  m_primitiveTypes.append("bool");
  m_primitiveTypes.append("int");
  m_primitiveTypes.append("double");
  m_primitiveTypes.append("long");
  m_primitiveTypes.append("short");
}

Member::~Member()
{

}

QString Member::declaration() const
{
  QString declaration;

  declaration.append(m_type);
  declaration.append(" ");

  if (!m_name.startsWith(m_prefix))
  {
    declaration.append(m_prefix);
  }

  declaration.append(m_name);
  declaration.append(";");

  return declaration;
}

QString Member::getterDeclaration() const
{
  QString declaration;

  declaration.append(m_type);
  declaration.append(" ");
  declaration.append(nameWithoutPrefix());
  declaration.append("() const;");

  return declaration;
}

QString Member::setterDeclaration() const
{
  return setterSignature();
}

QString Member::getterImplementation(const QString& leadingIndent, const QString& singleIndent, const QString& className) const
{
  QString code = leadingIndent;

  code.append(m_type);
  code.append(" ");
  code.append(className);
  code.append("::");
  code.append(nameWithoutPrefix());
  code.append("() const\n");
  code.append(leadingIndent);
  code.append("{\n");
  code.append(leadingIndent);
  code.append(singleIndent);
  code.append("return ");
  code.append(nameWithPrefix());
  code.append(";\n");
  code.append(leadingIndent);
  code.append("}");

  return code;
}

QString Member::setterImplementation(const QString& leadingIndent, const QString& singleIndent, const QString& className) const
{
/*
void setType(const QString& type);

void Member::setType(const QString &type)
{
  m_type = type;
}
*/

  QString code = leadingIndent;

  code.append(setterSignature(className));

  code.append("\n");
  code.append(leadingIndent);
  code.append("{\n");
  code.append(leadingIndent);
  code.append(singleIndent);
  code.append(nameWithPrefix());
  code.append(" = ");
  code.append(nameWithoutPrefix());
  code.append(";\n");
  code.append(leadingIndent);
  code.append("}");

  return code;
}

QString Member::elementInitialisation(const QString& leadingIndent) const
{
  QString code = leadingIndent;

  code.append(nameWithPrefix());
  code.append("(");
  code.append(m_defaultValue);
  code.append(")");

  return code;
}

QString Member::copyInitialisation(const QString &leadingIndent, const QString &rhs) const
{
  QString code = leadingIndent;

  code.append(nameWithPrefix());
  code.append("(");
  code.append(rhs);
  code.append(".");
  code.append(nameWithPrefix());
  code.append(")");

  return code;
}

QString Member::copyAssignment(const QString &rhs) const
{
  QString code;

  code.append(nameWithPrefix());
  code.append(" = ");
  code.append(rhs);
  code.append(".");
  code.append(nameWithPrefix());
  code.append(";\n");

  return code;
}

QString Member::type() const
{
  return m_type;
}

void Member::setType(const QString &type)
{
  m_type = type;
}

QString Member::name() const
{
  return m_name;
}

void Member::setName(const QString &name)
{
  m_name = name;
}

QString Member::defaultValue() const
{
  return m_defaultValue;
}

void Member::setDefaultValue(const QString &defaultValue)
{
  m_defaultValue = defaultValue;
}

bool Member::hasGetter() const
{
  return m_getter;
}

void Member::setGetter(bool getter)
{
  m_getter = getter;
}

bool Member::hasSetter() const
{
  return m_setter;
}

void Member::setSetter(bool setter)
{
  m_setter = setter;
}

Member::DeclarationType Member::declarationType() const
{
  return m_declarationType;
}

void Member::setDeclarationType(Member::DeclarationType declarationType)
{
  m_declarationType = declarationType;
}

QString Member::nameWithoutPrefix() const
{
  QString name = m_name;

  if (name.startsWith(m_prefix))
  {
    name = name.mid(m_prefix.length());
  }

  return name;
}

QString Member::nameWithPrefix() const
{
  QString name = m_name;

  if (!name.startsWith(m_prefix))
  {
    name.prepend(m_prefix);
  }

  return name;
}

QString Member::upperCaseFirstLetter(const QString& string) const
{
  QString copy = string;

  if (!copy.isEmpty())
  {
    copy[0] = copy[0].toUpper();
  }

  return copy;
}

QString Member::setterSignature(const QString& className) const
{
  QString code;

  bool primitiveType = m_primitiveTypes.contains(m_type);

  code.append("void ");

  if (!className.isEmpty())
  {
    code.append(className);
    code.append("::");
  }

  code.append("set");
  code.append(upperCaseFirstLetter(nameWithoutPrefix()));
  code.append("(");

  if (!primitiveType)
  {
    code.append("const ");
  }

  code.append(m_type);

  if (!primitiveType)
  {
    code.append("&");
  }

  code.append(" ");
  code.append(nameWithoutPrefix());
  code.append(")");

  if (className.isEmpty())
  {
    code.append(";");
  }

  return code;
}
