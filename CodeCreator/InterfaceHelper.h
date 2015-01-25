#ifndef INTERFACEHELPER_H
#define INTERFACEHELPER_H

#include <QString>

class QPlainTextEdit;

class InterfaceHelper
{
public:
  static QString createVirtualFunctionDeclarations(const QPlainTextEdit* plainTextEdit);
  static QString createFunctionDeclarations(const QPlainTextEdit* plainTextEdit);
};

#endif // INTERFACEHELPER_H
