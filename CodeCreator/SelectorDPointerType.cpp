#include "SelectorDPointerType.h"
#include "ui_SelectorDPointerType.h"

SelectorDPointerType::SelectorDPointerType(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::SelectorDPointerType)
{
  ui->setupUi(this);

  ui->comboBox->addItem(tr("no declaration"), Class::DPointerType::NoDPointer);
  ui->comboBox->addItem(tr("normal declaration"), Class::DPointerType::DPointer);
  //ui->comboBox->addItem(tr("d-pointer with q-pointer"), Class::DPointerType::DPointerWithQPointer);
  //ui->comboBox->addItem(tr("inheritable d-pointer"), Class::DPointerType::InheritableDPointer);
}

SelectorDPointerType::~SelectorDPointerType()
{
  delete ui;
}

Class::DPointerType SelectorDPointerType::dPointerType()
{
  int dPointerType = ui->comboBox->itemData(ui->comboBox->currentIndex()).toInt();

  switch(dPointerType)
  {
  case Class::DPointerType::NoDPointer:
    return Class::DPointerType::NoDPointer;
  case Class::DPointerType::DPointer:
    return Class::DPointerType::DPointer;
    //case Class::DPointerType::DPointerWithQPointer:
    //    return Class::DPointerType::DPointerWithQPointer;
    //case Class::DPointerType::InheritableDPointer:
    //  return Class::DPointerType::InheritableDPointer;
  }
}

bool SelectorDPointerType::setDPointerType(Class::DPointerType dPointerType)
{
  for (int i = 0; i < ui->comboBox->count(); i++)
  {
    if (ui->comboBox->itemData(i).toInt() == dPointerType)
    {
      ui->comboBox->setCurrentIndex(i);
      return true;
    }
  }

  return false;
}

void SelectorDPointerType::setEnabled(bool enabled)
{
  ui->comboBox->setEnabled(enabled);
}

void SelectorDPointerType::on_comboBox_currentIndexChanged(int index)
{
  emit dPointerTypeChanged(ui->comboBox->itemData(index).toInt());
}