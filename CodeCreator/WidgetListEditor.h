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
  QList<QWidget*> items();

  void clear();
  void setButtonText(const QString& buttonText);

signals:
  void addClicked();

private slots:
  void on_pushButtonAdd_clicked();
  void on_deleteItem();
  void on_moveUp();
  void on_moveDown();

  void on_buttonBox_accepted();

  void on_buttonBox_rejected();

private:
  Ui::WidgetListEditor *ui;
};

#endif // WIDGETLISTEDITOR_H
