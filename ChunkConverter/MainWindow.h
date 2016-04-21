#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMap>
#include <QString>
#include <QMainWindow>


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
  void on_lineEditChunkCode_returnPressed();
  void on_lineEditChunkName_returnPressed();

private:
  void setUpCharacterForCodeMap();
  void setUpCodeForCharacterMap();

  Ui::MainWindow *ui;

  QMap<QString, QString> m_characterForCode;
  QMap<QString, QString> m_codeForCharacter;
};

#endif // MAINWINDOW_H
