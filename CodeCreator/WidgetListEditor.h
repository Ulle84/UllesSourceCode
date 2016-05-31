#ifndef WIDGETLISTEDITOR_H
#define WIDGETLISTEDITOR_H

#include <QDialog>

namespace Ui {
class WidgetListEditor;
}

class WidgetListEditor : public QDialog
{
  Q_OBJECT

public:
  explicit WidgetListEditor(QWidget *parent = 0);
  ~WidgetListEditor();

  void addItem(QWidget* item);

signals:
  void pushButtonAddClicked();

private slots:
  void on_pushButtonAdd_clicked();
  void on_deleteItem();
  void on_moveUp();
  void on_moveDown();

private:
  Ui::WidgetListEditor *ui;
};

#endif // WIDGETLISTEDITOR_H
