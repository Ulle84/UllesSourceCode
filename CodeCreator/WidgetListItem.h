#ifndef WIDGETLISTITEM_H
#define WIDGETLISTITEM_H

#include <QWidget>

namespace Ui {
class WidgetListItem;
}

class WidgetListItem : public QWidget
{
  Q_OBJECT

public:
  explicit WidgetListItem(QWidget *parent = 0);
  ~WidgetListItem();

  void setItem(QWidget* item);

signals:
  void deleteItem();
  void moveUp();
  void moveDown();

private slots:
  void on_pushButtonDelete_clicked();

  void on_pushButtonUp_clicked();

  void on_pushButtonDown_clicked();

private:
  Ui::WidgetListItem *ui;
};

#endif // WIDGETLISTITEM_H
