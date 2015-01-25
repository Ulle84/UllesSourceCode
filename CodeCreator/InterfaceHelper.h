#ifndef INTERFACEHELPER_H
#define INTERFACEHELPER_H

#include <QString>

class QPlainTextEdit;

class InterfaceHelper
{
public:
  static QString createVirtualFunctionDeclarations(const QPlainTextEdit* plainTextEdit);
  static QString createFunctionDeclarations(const QPlainTextEdit* plainTextEdit);
  static QString createFunctionImplementations(const QPlainTextEdit* plainTextEdit, const QString& className);
};

#endif // INTERFACEHELPER_H
