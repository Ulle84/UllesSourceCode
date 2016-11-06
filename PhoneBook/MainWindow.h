#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class PhoneBook;
class ProxyModel;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_lineEdit_textChanged(const QString& text);

private:
  Ui::MainWindow *ui;

  PhoneBook* m_phoneBook;
  ProxyModel* m_proxyModel;
};

#endif // MAINWINDOW_H
