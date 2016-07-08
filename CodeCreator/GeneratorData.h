#ifndef GENERATORDATA_H
#define GENERATORDATA_H

#include <QWidget>

namespace Ui {
class GeneratorData;
}

class GeneratorData : public QWidget
{
  Q_OBJECT

public:
  explicit GeneratorData(QWidget *parent = 0);
  ~GeneratorData();

private:
  Ui::GeneratorData *ui;
};

#endif // GENERATORDATA_H
