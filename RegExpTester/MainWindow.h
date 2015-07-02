#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSettings;

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();

private slots:
  void on_lineEditRegExp_textEdited(const QString& regExp);
  void on_lineEditTestString_textEdited(const QString& testString);

private:
  void evaluate();

  Ui::MainWindow* ui;
  QSettings* m_settings;
};

#endif // MAINWINDOW_H
