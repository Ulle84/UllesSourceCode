#include <QFileDialog>

#include "PathSelector.h"
#include "ui_PathSelector.h"

PathSelector::PathSelector(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::PathSelector)
{
  ui->setupUi(this);
}

PathSelector::~PathSelector()
{
  delete ui;
}

bool PathSelector::setPath(const QString &path)
{
  ui->comboBox->setCurrentText(path);
}

QString PathSelector::path()
{
  return ui->comboBox->currentText();
}

/*void PathSelector::on_lineEdit_textChanged(const QString& path)
{
  QFile file(path);
  //ui->lineEdit->setProperty("input", (path.isEmpty() || file.exists() ? "correct" : "wrong"));

  // unfortunately this is neccessary, after changing dynamic properties
  //qApp->setStyleSheet(qApp->styleSheet());
}*/

void PathSelector::on_pushButton_clicked()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("select file"), ui->comboBox->currentText());

  if (!fileName.isEmpty())
  {
    ui->comboBox->setCurrentText(fileName);
    ui->comboBox->insertItem(0, ui->comboBox->currentText());

    /*if (ui->comboBox->currentText() != fileName)
    {
      if (!ui->comboBox->currentText().isEmpty())
        ui->comboBox->insertItem(0, ui->comboBox->currentText());
      ui->comboBox->setCurrentText(fileName);
    }*/

  }
}

void PathSelector::on_comboBox_currentIndexChanged(int index)
{

  //ui->comboBox->mov
}

void PathSelector::on_comboBox_activated(int index)
{
  /*if (index < 1)
  {
    return;
  }

  QString currentText = ui->comboBox->itemText(index);
  ui->comboBox->removeItem(index);
  ui->comboBox->insertItem(0, currentText);*/
}

void PathSelector::on_comboBox_activated(const QString &selectedText)
{
    //ui->comboBox->insertItem(0, selectedText);

}
