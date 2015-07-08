#include <QClipboard>

#include "HtmlTableGenerator.h"
#include "ui_HtmlTableGenerator.h"

HtmlTableGenerator::HtmlTableGenerator(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::HtmlTableGenerator)
{
  ui->setupUi(this);
}

HtmlTableGenerator::~HtmlTableGenerator()
{
  delete ui;
}



void HtmlTableGenerator::update()
{
  updateHtmlTable();
  ui->tableWidget->resizeColumnsToContents();
  ui->tableWidget->resizeRowsToContents();
}

void HtmlTableGenerator::updateHtmlTable()
{
  QString leadingSpace = "";

  for (int i = 0; i < ui->spinBoxTabCount->value(); i++)
  {
    leadingSpace.append("  ");
  }

  QString tableTag = QString("%1<table").arg(leadingSpace);

  if (ui->lineEditTitle->text().size() > 0)
  {
    tableTag += QString(" title=\"%1\"").arg(ui->lineEditTitle->text());
  }

  if (ui->lineEditId->text().size() > 0)
  {
    tableTag += QString(" id=\"%1\"").arg(ui->lineEditId->text());
  }

  tableTag += ">";
  ui->plainTextEdit->setPlainText(tableTag);

  for (int row = 0; row < ui->tableWidget->rowCount(); row++)
  {
    ui->plainTextEdit->appendPlainText(QString("%1  <tr>").arg(leadingSpace));

    for (int column = 0; column < ui->tableWidget->columnCount(); column++)
    {
      QString cellContent = "";

      if (ui->tableWidget->item(row, column))
      {
        cellContent = ui->tableWidget->item(row, column)->text();
      }

      QString tagName;

      if (row == 0 && ui->checkBox->isChecked())
      {
        tagName = "th";
      }
      else
      {
        tagName = "td";
      }

      ui->plainTextEdit->appendPlainText(QString("%3    <%2>%1</%2>").arg(cellContent).arg(tagName).arg(leadingSpace));
    }

    ui->plainTextEdit->appendPlainText(QString("%1  </tr>").arg(leadingSpace));
  }

  ui->plainTextEdit->appendPlainText(QString("%1</table>").arg(leadingSpace));
}

void HtmlTableGenerator::on_pushButtonAddRow_clicked()
{
  ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
  update();
}

void HtmlTableGenerator::on_pushButtonAddColumn_clicked()
{
  ui->tableWidget->setColumnCount(ui->tableWidget->columnCount() + 1);
  update();
}

void HtmlTableGenerator::on_pushButtonClearTable_clicked()
{
  ui->tableWidget->clearContents();
  ui->tableWidget->setRowCount(0);
  ui->tableWidget->setColumnCount(0);
  update();
}

void HtmlTableGenerator::on_pushButtonRemoveRow_clicked()
{
  ui->tableWidget->setRowCount(ui->tableWidget->rowCount() - 1);
  update();
}

void HtmlTableGenerator::on_pushButtonRemoveColumn_clicked()
{
  ui->tableWidget->setColumnCount(ui->tableWidget->columnCount() - 1);
  update();
}

void HtmlTableGenerator::on_tableWidget_cellChanged(int row, int column)
{
  update();
}

void HtmlTableGenerator::on_pushButtonCopyToClipboard_clicked()
{
  QApplication::clipboard()->setText(ui->plainTextEdit->toPlainText());
}

void HtmlTableGenerator::on_checkBox_stateChanged(int newState)
{
  update();
}

void HtmlTableGenerator::on_lineEditTitle_textChanged(const QString& arg1)
{
  update();
}

void HtmlTableGenerator::on_lineEditId_textChanged(const QString& arg1)
{
  update();
}

void HtmlTableGenerator::on_spinBoxTabCount_valueChanged(int newValue)
{
  update();
}
