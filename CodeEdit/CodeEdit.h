#ifndef CODEEDIT_H
#define CODEEDIT_H

#include <QTextEdit>
#include <QString>

class CodeEdit : public QTextEdit
{
  Q_OBJECT

public:
  explicit CodeEdit(QWidget *parent = 0);

  void searchText(const QString& text, bool caseSenstive);

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

  QString m_searchText;
};

#endif
