#include <QSettings>

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "CppHighlighter.h"
#include "SimpleHtmlHighlighter.h"
#include "XmlHighlighter.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  m_settings = new QSettings("Ulle", "CodeEdit", this);

  ui->textEdit->setPlainText(m_settings->value("code").toString());

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  //m_syntaxHighlighter = new CppHighlighter(ui->textEdit->document());
  //m_syntaxHighlighter = new SimpleHtmlHighlighter(ui->textEdit->document());
  //m_syntaxHighlighter = new XmlHighlighter(ui->textEdit->document());
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  m_settings->setValue("code", ui->textEdit->toPlainText());
  delete m_syntaxHighlighter;
  delete ui;
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{

}
