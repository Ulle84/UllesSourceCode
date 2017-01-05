#include <QSettings>

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

  ui->plainTextEditInput->setPlainText(m_settings->value("input").toString());

  ui->tabWidget->setTabText(0, tr("Preview"));
  ui->tabWidget->setTabText(1, tr("HTML Code"));
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  m_settings->setValue("input", ui->plainTextEditInput->toPlainText());
  delete ui;
}

void MainWindow::on_plainTextEditInput_textChanged()
{
  ui->plainTextEditOutput->setPlainText(m_converter.toHtml(ui->plainTextEditInput->toPlainText()));
  ui->textBrowserResult->setHtml(m_converter.toHtml(ui->plainTextEditInput->toPlainText()));
}
