#ifndef AUTOHOTKEYHELPER_H
#define AUTOHOTKEYHELPER_H

#include <QString>
#include <QStringList>

class AutoHotKeyHelper
{
public:
  AutoHotKeyHelper();

  void appendToFile(const QString& fileName, const QString& wrong, const QString& correct);

private:
  QStringList m_keys;
};

#endif // AUTOHOTKEYHELPER_H
