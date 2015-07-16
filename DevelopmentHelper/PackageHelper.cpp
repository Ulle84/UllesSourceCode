#include <QApplication>
#include <QClipboard>

#include "PackageHelper.h"
#include "ui_PackageHelper.h"

PackageHelper::PackageHelper(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::PackageHelper)
{
  ui->setupUi(this);

  // TODO read directories via config file
  m_packageDirectories["ViWidgetsConfig"] = "\\\\dev1\\Vitronic\\Industrie\\ViWidgets\\ViWidgetsConfig";
  m_packageDirectories["ViAcquiDeviceTest"] = "\\\\dev1\\Vitronic\\ViBase\\ViAcqui\\ViAcquiDeviceTest";
  m_packageDirectories["ViIOPLCNamedPipe"] = "\\\\dev1\\Vitronic\\Industrie\\ViIO\\ViIOPLCNamedPipe";
}

PackageHelper::~PackageHelper()
{
  delete ui;
}

void PackageHelper::on_lineEdit_returnPressed()
{
  ui->label->setText(m_packageDirectories[ui->lineEdit->text()]);
}

void PackageHelper::on_pushButton_clicked()
{
  QApplication::clipboard()->setText(ui->label->text());
}
