#ifndef DECORATOREXAMPLE_H
#define DECORATOREXAMPLE_H

#include <QWidget>

namespace Ui {
class DecoratorExample;
}

class DecoratorExample : public QWidget
{
  Q_OBJECT

public:
  explicit DecoratorExample(QWidget *parent = 0);
  ~DecoratorExample();

private:
  Ui::DecoratorExample *ui;
};

#endif // DECORATOREXAMPLE_H
