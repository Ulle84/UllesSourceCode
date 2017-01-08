#ifndef EDITOR_H
#define EDITOR_H

#include <QTextEdit>

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
};

#endif
