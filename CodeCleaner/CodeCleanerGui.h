#ifndef CODECLEANERGUI_H
#define CODECLEANERGUI_H

#include <QWidget>

namespace Ui {
class CodeCleanerGui;
}

class CodeCleanerGui : public QWidget
{
  Q_OBJECT

public:
  explicit CodeCleanerGui(QWidget *parent = 0);
  ~CodeCleanerGui();

private slots:
  void on_plainTextEditInput_textChanged();

private:
  Ui::CodeCleanerGui *ui;
};

#endif // CODECLEANERGUI_H
