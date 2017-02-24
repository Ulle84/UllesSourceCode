#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSettings;
class QSyntaxHighlighter;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_lineEdit_textChanged(const QString &arg1);

private:
  Ui::MainWindow *ui;
  QSettings* m_settings;

  QSyntaxHighlighter* m_syntaxHighlighter;
};

#endif
