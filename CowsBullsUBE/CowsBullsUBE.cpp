#include <qmath.h>

#include <QDateTime>
#include <QMessageBox>

#include "CowsBullsUBE.h"
#include "ui_CowsBullsUBE.h"

CowsBullsUBE::CowsBullsUBE(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CowsBullsUBE)
{
  ui->setupUi(this);

  qsrand(QDateTime::currentDateTime().toTime_t());

  ui->lineEditGuess->setText(QString::number((qrand() % 9000) + 1000)); // TODO random number
}

CowsBullsUBE::~CowsBullsUBE()
{
  delete ui;
}

void CowsBullsUBE::on_pushButtonSubmitAnswer_clicked()
{
  m_answers[ui->lineEditGuess->text().toInt()] = qMakePair(ui->spinBoxBulls->value(), ui->spinBoxCows->value());

  if (ui->spinBoxBulls->value() == 4 && ui->spinBoxCows->value() == 4)
  {
    QMessageBox::information(this, tr("Success"), tr("I needed %1 guesses.").arg(m_answers.count()));
    return;
  }

  calculateNextGuess();
}

void CowsBullsUBE::calculateNextGuess()
{
  // TODO -> analyse m_answers and make next guess
}
