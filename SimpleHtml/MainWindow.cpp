#include <QSettings>

#include "Highlighter.h"
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "SimpleHtml", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  if (m_settings->contains("splitter"))
  {
    ui->splitter->restoreGeometry(m_settings->value("splitter").toByteArray());
  }

  ui->textEditInput->setPlainText(m_settings->value("input").toString());

  ui->tabWidget->setTabText(0, tr("Preview"));
  ui->tabWidget->setTabText(1, tr("HTML Code"));

  m_highlighter = new Highlighter(ui->textEditInput->document());
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  m_settings->setValue("input", ui->textEditInput->toPlainText());
  m_settings->setValue("splitter", ui->splitter->saveGeometry());
  delete ui;
}

void MainWindow::on_textEditInput_textChanged()
{
  ui->plainTextEditOutput->setPlainText(m_converter.toHtml(ui->textEditInput->toPlainText()));
  ui->textBrowserResult->setHtml(m_converter.toHtml(ui->textEditInput->toPlainText()));
}
