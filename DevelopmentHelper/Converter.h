#ifndef CONVERTER_H
#define CONVERTER_H

#include <QWidget>

namespace Ui {
class Converter;
}

class Converter : public QWidget
{
  Q_OBJECT

public:
  explicit Converter(QWidget *parent = 0);
  ~Converter();

private:
  Ui::Converter *ui;
};

#endif // CONVERTER_H
