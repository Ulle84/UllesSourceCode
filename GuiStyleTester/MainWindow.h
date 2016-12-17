#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>

class QSettings;
class QTimer;

namespace Ui
{
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_pushButtonApplyUi_clicked();
  void on_pushButtonApplyCss_clicked();
  void checkFiles();

private:
  void applyCss();

  Ui::MainWindow *ui;
  QSettings* m_settings;

  QWidget* m_lastLoadedWidget = nullptr;

  QDateTime m_cssLastModified;
  QTimer* m_timer = nullptr;
};

#endif // MAINWINDOW_H
