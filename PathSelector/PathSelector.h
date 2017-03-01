#ifndef PATHSELECTOR_H
#define PATHSELECTOR_H

// TODO order items in combobox by last usage - latest should be on top
// TODO provide clearHistory method
// TODO save state
// TODO load state

/* Idea
   instead of combobox:
   line edit + push-button which opens dialog with searchable and editable history - much more flexible than edit-box
*/

/* Idea
   PathEditor with autocompletion (parses file system)
   every part of the path (every directory) is clickable so directory jumps are easy
*/

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
  //void on_lineEdit_textChanged(const QString& path);
  void on_pushButton_clicked();
  void on_comboBox_currentIndexChanged(int index);

  void on_comboBox_activated(int index);

  void on_comboBox_activated(const QString &selectedText);

private:
  Ui::PathSelector *ui;
};

#endif // PATHSELECTOR_H
