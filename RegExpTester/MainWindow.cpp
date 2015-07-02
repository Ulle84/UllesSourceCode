#include <QRegExp>
#include <QSettings>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  m_settings = new QSettings("company.com", "LogFileViewer", this);

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

MainWindow::~MainWindow()
{
  m_settings->setValue("regExp", ui->lineEditRegExp->text());
  m_settings->setValue("testString", ui->lineEditTestString->text());
  delete ui;
}

void MainWindow::on_lineEditRegExp_textEdited(const QString& regExp)
{
  evaluate();
}

void MainWindow::on_lineEditTestString_textEdited(const QString& testString)
{
  evaluate();
}

void MainWindow::evaluate()
{
  QRegExp regExp(ui->lineEditRegExp->text());
  bool exactMatch = regExp.exactMatch(ui->lineEditTestString->text());
  ui->labelExactMatch->setText(exactMatch ? "yes" : "no");
  ui->labelStringLength->setText(QString::number(ui->lineEditTestString->text().length()));
}
