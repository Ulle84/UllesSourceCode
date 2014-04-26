#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
class QCalendarWidget;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget* parent = 0);
  ~MainWindow();

public slots:
  bool createClipboardContent01();
  bool createClipboardContent02();
  bool goToToday();

private:
  QCalendarWidget* calendar;
};

#endif // MAINWINDOW_H
