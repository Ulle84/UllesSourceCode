#include <QFile>
#include <QDebug>
#include <QSettings>
#include <QClipboard>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setWindowTitle("Qt Connection Helper");

  m_settings = new QSettings("Ulle", "QtConnectionHelper", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  // TODO put file in resources
  readFile();

  if (m_settings->contains("type"))
  {
    ui->comboBoxType->setCurrentIndex(ui->comboBoxType->findText(m_settings->value("type").toString()));
  }

  if (m_settings->contains("signal"))
  {
    ui->comboBoxSignal->setCurrentIndex(ui->comboBoxSignal->findText(m_settings->value("signal").toString()));
  }

  if (m_settings->contains("controlName"))
  {
    ui->lineEditControlName->setText(m_settings->value("controlName").toString());
  }
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  m_settings->setValue("type", ui->comboBoxType->currentText());
  m_settings->setValue("signal", ui->comboBoxSignal->currentText());
  m_settings->setValue("controlName", ui->lineEditControlName->text());

  delete ui;
}

void MainWindow::on_comboBoxType_currentIndexChanged(const QString& type)
{
  ui->comboBoxSignal->clear();
  ui->comboBoxSignal->addItems(ui->comboBoxType->currentData().toStringList());

  if (ui->lineEditControlName->text().isEmpty())
  {
    QString controlName = ui->comboBoxType->currentText();

    if (controlName.length() >= 2)
    {
      controlName.remove(0, 1);
      controlName[0] = controlName[0].toLower();
    }

    ui->lineEditControlName->setText(controlName);
  }

  update();
}

void MainWindow::on_comboBoxSignal_currentIndexChanged(const QString &signal)
{
  update();
}

void MainWindow::on_lineEditControlName_textChanged(const QString &controlName)
{
  update();
}

void MainWindow::update()
{
  ui->lineEditResult->setText(QString("void on_%1_%2;").arg(ui->lineEditControlName->text()).arg(ui->comboBoxSignal->currentText()));
}

void MainWindow::readFile()
{
  QFile file ("Signals.txt");
  if (!file.open(QFile::ReadOnly))
  {
    return;
  }

  QString fileContent(file.readAll());

  QStringList blocks = fileContent.split("\n\n");

  for (auto block = blocks.begin(); block != blocks.end(); block++)
  {
    QStringList lines = block->split("\n");

    QString className;
    QStringList signalNames;
    for (auto line = lines.begin(); line != lines.end(); line++)
    {
      if (line == lines.begin())
      {
        className = *line;
      }
      else
      {
        signalNames.append(*line);
      }
    }
    signalNames.removeDuplicates();
    signalNames.sort();
    ui->comboBoxType->addItem(className, signalNames);
  }
}

void MainWindow::on_pushButtonCopyToClipboard_clicked()
{
  QApplication::clipboard()->setText(QString("%1\n").arg(ui->lineEditResult->text()));
}
