#ifndef EDITOR_H
#define EDITOR_H

#include <QTextEdit>
#include <QList>

class QKeyEvent;

class Editor : public QTextEdit
{
  Q_OBJECT

public:
  explicit Editor(QWidget *parent = 0);

protected:
  virtual void keyPressEvent(QKeyEvent *e) override;

private slots:
  void onTextChanged();
  void onCursorPositionChanged();

private:
  int indexOfMatchingClosingParenthesis(const QString& code, int index);
  int indexOfMatchingOpeningParenthesis(const QString& code, int index);

  enum class HighlightingType
  {
    MachtingParenthesis,
    MismachtingParenthesis
  };


  void highlightIndices(QList<int> indices, HighlightingType highlightingType);
};

#endif
