#ifndef CODEEDIT_H
#define CODEEDIT_H

#include <QTextEdit>

class CodeEdit : public QTextEdit
{
  Q_OBJECT

public:
  explicit CodeEdit(QWidget *parent = 0);

protected:
  virtual void keyPressEvent(QKeyEvent *e) override;

private slots:
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
