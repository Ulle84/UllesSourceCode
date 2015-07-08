#include <QRegExp>
#include <QSettings>

#include "RegExpTester.h"
#include "ui_RegExpTester.h"

RegExpTester::RegExpTester(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::RegExpTester)
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "DevelopmentHelper", this);

  if (m_settings->contains("regExp"))
  {
    ui->lineEditRegExp->setText(m_settings->value("regExp").toString());
  }

  if (m_settings->contains("testString"))
  {
    ui->lineEditTestString->setText(m_settings->value("testString").toString());
  }

  evaluate();
}

RegExpTester::~RegExpTester()
{
  m_settings->setValue("regExp", ui->lineEditRegExp->text());
   m_settings->setValue("testString", ui->lineEditTestString->text());
   delete ui;
}

void RegExpTester::on_lineEditRegExp_textEdited(const QString& regExp)
{
  evaluate();
}

void RegExpTester::on_lineEditTestString_textEdited(const QString& testString)
{
  evaluate();
}

void RegExpTester::evaluate()
{
  QRegExp regExp(ui->lineEditRegExp->text());
  bool exactMatch = regExp.exactMatch(ui->lineEditTestString->text());
  ui->labelExactMatch->setText(exactMatch ? "yes" : "no");
  ui->labelStringLength->setText(QString::number(ui->lineEditTestString->text().length()));
}

