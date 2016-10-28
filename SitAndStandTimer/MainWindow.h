#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QString>

class QSettings;
class QTimer;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  enum Position {
    Undefined,
    Standing,
    Sitting
  };

  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void update();
  void on_pushButtonStartSitting_clicked();
  void on_pushButtonStartStanding_clicked();

private:
  QString timeToString(int minutes, int seconds);

  Ui::MainWindow *ui;
  QSettings* m_settings;
  QTimer* m_timer;

  Position m_position;

  QDateTime m_dateTimePositionChange;
};

#endif // MAINWINDOW_H
