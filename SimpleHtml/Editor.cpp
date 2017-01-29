#include <QDebug>
#include <QKeyEvent>
#include <QTextCursor>

#include "Editor.h"

Editor::Editor(QWidget *parent) :
  QTextEdit(parent)
{
  connect(this, &Editor::textChanged, this, &Editor::onTextChanged);
  connect(this, &Editor::cursorPositionChanged, this, &Editor::onCursorPositionChanged);
}

void Editor::keyPressEvent(QKeyEvent *e)
{
  if (e->key() == Qt::Key_Tab)
  {
    QTextCursor cursor = textCursor();
    cursor.insertText("  ");
    setTextCursor(cursor);
    return;
  }

  if (e->key() == Qt::Key_Return)
  {
    // TODO check indentation
    QTextCursor cursor = textCursor();
    cursor.insertText("\n");
    setTextCursor(cursor);
    return;
  }

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

void Editor::onCursorPositionChanged()
{
  QTextCursor cursor = textCursor();

  if (toPlainText().at(cursor.position()) == '(')
  {
    int index = indexOfMatchingClosingParenthesis(toPlainText(), cursor.position());
    if (index == -1)
    {
      highlightIndices(QList<int>() << cursor.position(), HighlightingType::MismachtingParenthesis);
    }
    else
    {
      highlightIndices(QList<int>() << cursor.position() << index, HighlightingType::MachtingParenthesis);
    }
  }
  else if (toPlainText().at(cursor.position()) == ')')
  {
    int index = indexOfMatchingOpeningParenthesis(toPlainText(), cursor.position());
    if (index == -1)
    {
      highlightIndices(QList<int>() << cursor.position(), HighlightingType::MismachtingParenthesis);
    }
    else
    {
      highlightIndices(QList<int>() << cursor.position() << index, HighlightingType::MachtingParenthesis);
    }
  }
  else
  {
    setExtraSelections(QList<QTextEdit::ExtraSelection>());
  }
}

int Editor::indexOfMatchingClosingParenthesis(const QString &code, int index)
{
  int nOpenendParenthesis = 1;
  for (int i = index + 1; i < code.length(); ++i)
  {
    if (code[i] == ')')
    {
      nOpenendParenthesis--;
    }
    else if (code[i] == '(')
    {
      nOpenendParenthesis++;
    }

    if (nOpenendParenthesis == 0)
    {
      return i;
    }
  }

  return -1;
}

int Editor::indexOfMatchingOpeningParenthesis(const QString &code, int index)
{
  int nClosedParenthesis = 1;
  for (int i = index - 1; i >= 0; --i)
  {
    if (code[i] == ')')
    {
      nClosedParenthesis++;
    }
    else if (code[i] == '(')
    {
      nClosedParenthesis--;
    }

    if (nClosedParenthesis == 0)
    {
      return i;
    }
  }

  return -1;
}

void Editor::highlightIndices(QList<int> indices, HighlightingType highlightingType)
{
  QList<QTextEdit::ExtraSelection> selections;

  QTextEdit::ExtraSelection selection;
  QTextCharFormat format = selection.format;

  if (highlightingType == HighlightingType::MachtingParenthesis)
  {
    format.setBackground(Qt::green);
  }
  else if (highlightingType == HighlightingType::MismachtingParenthesis)
  {
    format.setBackground(Qt::red);
  }

  selection.format = format;

  QTextCursor cursor = textCursor();

  for (auto it = indices.begin(); it != indices.end(); ++it)
  {
    cursor.setPosition(*it);
    cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
    selection.cursor = cursor;
    selections.append(selection);
  }

  setExtraSelections(selections);
}
