#ifndef PATHSELECTOR_H
#define PATHSELECTOR_H

#include <QWidget>
#include <QString>

namespace Ui
{
  class PathSelector;
}

class PathSelector : public QWidget
{
  Q_OBJECT

public:
  explicit PathSelector(QWidget *parent = 0);
  ~PathSelector();

  bool setPath(const QString& path);
  QString path();

private slots:
  void on_lineEdit_textChanged(const QString& path);
  void on_pushButton_clicked();

private:
  Ui::PathSelector *ui;
};

#endif // PATHSELECTOR_H
