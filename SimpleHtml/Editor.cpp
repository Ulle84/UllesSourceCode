#include <QDebug>
#include <QKeyEvent>
#include <QTextCursor>

#include "Editor.h"

Editor::Editor(QWidget *parent) :
  QTextEdit(parent)
{
  connect(this, &Editor::textChanged, this, &Editor::onTextChanged);
}

void Editor::keyPressEvent(QKeyEvent *e)
{
  QString string;

  if (e->key() == '\'')
  {
    string = "\'\'";
  }
  else if (e->key() == '\"')
  {
    string = "\"\"";
  }
  else if (e->key() == '(')
  {
    string = "()";
  }
  else if (e->text() == "[")
  {
    string = "[]";
  }
  else if (e->text() == "{")
  {
    string = "{}";
  }

  if (string.isEmpty())
  {
    QTextEdit::keyPressEvent(e);
  }
  else
  {
    QTextCursor cursor = textCursor();
    cursor.insertText(string);
    cursor.movePosition(QTextCursor::PreviousCharacter);
    setTextCursor(cursor);
  }
}

void Editor::onTextChanged()
{
  int nOpeningParenthesis = 0;
  int nClosingParenthesis = 0;

  QString text = toPlainText();
  for (auto it = text.begin(); it != text.end(); ++it)
  {
    if (*it == '(')
    {
      nOpeningParenthesis++;
    }
    else if (*it == ')')
    {
      nClosingParenthesis++;
    }
  }

  // TODO signal if nOpeningParenthesis != nClosingParenthesis

  //setTextBackgroundColor(Qt::red);
  //setBackgroundRole();

  //setStyleSheet(QString("background-color: %1").arg(nOpeningParenthesis == nClosingParenthesis ? "#FFFFFF" : "#FFEEEE"));
}
