#ifndef REQUIREFILEHELPER_H
#define REQUIREFILEHELPER_H

#include <QWidget>
#include <QDomDocument>
#include <QFile>

namespace Ui {
class RequireFileHelper;
}

class RequireFileHelper : public QWidget
{
  Q_OBJECT

public:
  explicit RequireFileHelper(QWidget *parent = 0);
  ~RequireFileHelper();
  void setFile(QString fileName);

private slots:
  void on_pushButtonFixlevel_clicked();
  void on_pushButtonMajor_clicked();
  void on_pushButtonMinor_clicked();

private:
  void readFile();
  void updateFile();
  void writeFile();
  int readInt(QString tagName);
  void writeInt(QString tagName, int value);
  void updateVersionLabel();

  Ui::RequireFileHelper *ui;
  QString fileName;

  int major;
  int minor;
  int fixlevel;
  QDomDocument domDocument;

};

#endif // REQUIREFILEHELPER_H
