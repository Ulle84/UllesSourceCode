#include <QApplication>
#include <QClipboard>
#include <QDebug>
#include <QProcess>
#include <QSettings>

#include "PackageHelper.h"
#include "ui_PackageHelper.h"

PackageHelper::PackageHelper(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::PackageHelper)
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "DevelopmentHelper.PackageHelper", this);

  if (m_settings->contains("packageName"))
  {
    ui->lineEdit->setText(m_settings->value("packageName").toString());
    on_lineEdit_returnPressed();
  }

  // TODO read directories via config file
  m_packageDirectories["ViWidgetsConfig"] = "\\\\dev1\\Vitronic\\Industrie\\ViWidgets\\ViWidgetsConfig";
  m_packageDirectories["ViAuthorisation"] = "\\\\dev1\\Vitronic\\ViBase\\ViAuthorisation";
}

PackageHelper::~PackageHelper()
{
  m_settings->setValue("packageName", ui->lineEdit->text());

  delete ui;
}

void PackageHelper::on_lineEdit_returnPressed()
{
  if (m_packageDirectories.contains(ui->lineEdit->text()))
  {
    ui->label->setText(m_packageDirectories[ui->lineEdit->text()]);
  }
  else
  {
    QString packageName = ui->lineEdit->text();
    QString packageDirectory;

    if (packageName.startsWith("ViQtWidget"))
    {
      packageDirectory = "\\\\dev1\\Vitronic\\Industrie\\ViQtWidgets\\" + packageName;
    }
    else if (packageName.startsWith("Vi") && packageName.endsWith("Widget"))
    {
      packageDirectory = "\\\\dev1\\Vitronic\\Industrie\\ViWidgets\\" + packageName;
    }
    else if (packageName.startsWith("ViAcqui"))
    {
      packageDirectory = "\\\\dev1\\Vitronic\\ViBase\\ViAcqui\\" + packageName;
    }
    else if (packageName.startsWith("ViIO"))
    {
      packageDirectory = "\\\\dev1\\Vitronic\\Industrie\\ViIO\\" + packageName;
    }
    else if (packageName.startsWith("Hwd"))
    {
      packageDirectory = "\\\\buildmachine1\\Download\\Packages\\Internal\\" + packageName;
    }
    else if (packageName.startsWith("ExtQt"))
    {
      packageDirectory = "\\\\DEV1\\Vitronic\\ViBase\\ExtQt";
    }

    ui->label->setText(QString("%1").arg(packageDirectory));
  }
}

void PackageHelper::on_pushButton_clicked()
{
  QApplication::clipboard()->setText(ui->label->text());
}

void PackageHelper::on_pushButtonOpenInExplorer_clicked()
{
  if (!ui->label->text().startsWith("\\\\"))
  {
    return;
  }

  QProcess::execute("C:\\Windows\\SysWOW64\\explorer.exe", QStringList() << ui->label->text());
}
