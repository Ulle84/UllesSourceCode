#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QString>

class QSettings;

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
  void on_actionAddNewNode_triggered();
  void on_actionAddNewChildNode_triggered();
  void on_actionRemoveNode_triggered();
  void on_actionMoveUp_triggered();
  void on_actionMoveDown_triggered();
  void on_actionMoveLeft_triggered();
  void on_actionMoveRight_triggered();
  void on_actionInsertColunn_triggered();
  void on_actionRemoveColumn_triggered();

  void onTreeEditIdChanged(int id);

private:
  const QString m_fileName = "/Users/Ulle/temp/content.txt";
  QJsonObject readFile();
  void setContent(const QJsonArray& json);
  QJsonArray contentToJson();
  void writeFile();

  int m_currentId = -1;
  QMap<int, QString> m_textContent;

  Ui::MainWindow *ui;
  QSettings* m_settings;
};

#endif
