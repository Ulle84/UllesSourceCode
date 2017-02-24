#include <QFont>
#include <QDebug>
#include <QKeyEvent>

#include "CodeEdit.h"

CodeEdit::CodeEdit(QWidget *parent) :
  QTextEdit(parent)
{
#ifdef Q_OS_MAC
  setFont(QFont("Monaco", 12));
#else
  setFont(QFont("Courier New", 10));
#endif

  connect(this, &CodeEdit::cursorPositionChanged, this, &CodeEdit::onCursorPositionChanged);

}

void CodeEdit::searchText(const QString &text, bool caseSenstive)
{
  m_searchText = text;

  //ui->results->setVisible(!m_searchText.isEmpty());

  // TODO is this correct?
  document->undo();

  m_startPositions.clear();

  if (m_searchText.isEmpty())
  {
    updateResultLabel(-1);
    return;
  }

  QTextCursor highlightCursor(document);
  QTextCursor cursor(document);

  cursor.beginEditBlock();

  QTextCharFormat plainFormat(highlightCursor.charFormat());
  QTextCharFormat colorFormat = plainFormat;
  colorFormat.setForeground(Qt::red);

  while (!highlightCursor.isNull() && !highlightCursor.atEnd())
  {
    highlightCursor = document->find(m_searchText, highlightCursor, caseSenstive ? QTextDocument::FindCaseSensitively : QTextDocument::FindFlags());

    if (!highlightCursor.isNull())
    {
      highlightCursor.mergeCharFormat(colorFormat);
      m_startPositions.append(highlightCursor.position() - m_searchText.length());
    }
  }

  cursor.endEditBlock();

  if (!m_startPositions.isEmpty())
  {
    markSearchResult(0);
  }
  else
  {
    updateResultLabel(-1);
  }




  //ui->results->setVisible(!m_startPositions.isEmpty());
}

void CodeEdit::keyPressEvent(QKeyEvent *e)
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

void CodeEdit::onCursorPositionChanged()
{
  QTextCursor cursor = textCursor();

  if (cursor.position() < 0 || cursor.position() >= toPlainText().length())
  {
    return;
  }

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

int CodeEdit::indexOfMatchingClosingParenthesis(const QString &code, int index)
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

int CodeEdit::indexOfMatchingOpeningParenthesis(const QString &code, int index)
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

void CodeEdit::highlightIndices(QList<int> indices, CodeEdit::HighlightingType highlightingType)
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
