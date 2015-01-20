#ifndef CODECREATOR_H
#define CODECREATOR_H

#include <QWidget>

class ClassGenerator;

namespace Ui {
class CodeCreator;
}

class CodeCreator : public QWidget
{
  Q_OBJECT

public:
  explicit CodeCreator(QWidget *parent = 0);
  ~CodeCreator();

private:
  Ui::CodeCreator *ui;
  ClassGenerator* m_classGenerator;
};

#endif // CODECREATOR_H
