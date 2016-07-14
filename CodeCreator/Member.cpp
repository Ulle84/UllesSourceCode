#include "Member.h"
#include "StringHelper.h"

Member::Member() :
  m_getter(false),
  m_setter(false),
  m_prefix("m_"),
  m_declarationType(DeclarationType::Private)
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
  QString code;

  code.append(m_type);
  code.append(" ");

  if (!m_name.startsWith(m_prefix))
  {
    code.append(m_prefix);
  }

  code.append(m_name);
  code.append(";");

  return code;
}

QString Member::getterDeclaration() const
{
  QString code;

  code.append(m_type);
  code.append(" ");
  code.append(getterName());
  code.append("() const;");

  return code;
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
  code.append(getterName());
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
  code.append(StringHelper::upperCaseFirstLetter(nameWithoutPrefix()));
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

QString Member::getterName() const
{
  QString code;

  if (m_type.toLower() == "bool")
  {
    code.append("is");
    code.append(StringHelper::upperCaseFirstLetter(nameWithoutPrefix()));
  }
  else
  {
    code.append(nameWithoutPrefix());
  }

  return code;
}
