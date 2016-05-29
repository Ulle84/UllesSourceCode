#include "SelectorSingletonType.h"
#include "ui_SelectorSingletonType.h"

SelectorSingletonType::SelectorSingletonType(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::SelectorSingletonType)
{
  ui->setupUi(this);

  ui->comboBox->addItem(tr("no singleton"), Class::SingletonType::NoSingleton);
  ui->comboBox->addItem(tr("eager initialization"), Class::SingletonType::Eager);
  ui->comboBox->addItem(tr("lazy initialization, protected with QMutex"), Class::SingletonType::LazyProtectedWithQMutex);
}

SelectorSingletonType::~SelectorSingletonType()
{
  delete ui;
}

Class::SingletonType SelectorSingletonType::singletonType()
{
  int singletonType = ui->comboBox->itemData(ui->comboBox->currentIndex()).toInt();

  switch(singletonType)
  {
  case Class::SingletonType::NoSingleton:
    return Class::SingletonType::NoSingleton;
  case Class::SingletonType::Eager:
    return Class::SingletonType::Eager;
  case Class::SingletonType::LazyProtectedWithQMutex:
    return Class::SingletonType::LazyProtectedWithQMutex;
  }
}

bool SelectorSingletonType::setSingletonType(Class::SingletonType singletonType)
{
  for (int i = 0; i < ui->comboBox->count(); i++)
  {
    if (ui->comboBox->itemData(i).toInt() == singletonType)
    {
      ui->comboBox->setCurrentIndex(i);
      return true;
    }
  }

  return false;
}

void SelectorSingletonType::setEnabled(bool enabled)
{
  ui->comboBox->setEnabled(enabled);
}

void SelectorSingletonType::on_comboBox_currentIndexChanged(int index)
{
  emit singletonTypeChanged(ui->comboBox->itemData(index).toInt());
}
