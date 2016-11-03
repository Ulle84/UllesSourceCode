#include <QSettings>
#include <QFileDialog>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "AutoHotKeyHelper", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  if (m_settings->contains("file"))
  {
    ui->lineEditFile->setText(m_settings->value("file").toString());
  }
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  m_settings->setValue("file", ui->lineEditFile->text());

  delete ui;
}

void MainWindow::on_pushButtonSelectFile_clicked()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("select folder"), ui->lineEditFile->text());

  if (!fileName.isEmpty())
  {
    ui->lineEditFile->setText(fileName);
  }
}

void MainWindow::on_pushButtonAppendToFile_clicked()
{
  m_autoHotKeyHelper.appendToFile(ui->lineEditFile->text(), ui->lineEditWrong->text(), ui->lineEditCorrect->text());
}
