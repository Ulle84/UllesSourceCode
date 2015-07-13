#ifndef COWSBULLSUBE_H
#define COWSBULLSUBE_H

#include <QWidget>
#include <QMap>
#include <QPair>

namespace Ui {
class CowsBullsUBE;
}

class CowsBullsUBE : public QWidget
{
  Q_OBJECT

public:
  explicit CowsBullsUBE(QWidget *parent = 0);
  ~CowsBullsUBE();

private slots:
  void on_pushButtonSubmitAnswer_clicked();

private:
  void calculateNextGuess();

  Ui::CowsBullsUBE *ui;
  QMap<int, QPair<int, int>> m_answers;
};

#endif // COWSBULLSUBE_H
