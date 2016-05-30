#include "SelectorDeclarationType.h"
#include "ui_SelectorDeclarationType.h"

SelectorDeclarationType::SelectorDeclarationType(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::SelectorDeclarationType)
{
  ui->setupUi(this);

  ui->comboBox->addItem(tr("no declaration"), Class::DeclarationType::NoDeclaration);
  ui->comboBox->addItem(tr("public declaration"), Class::DeclarationType::Public);
  ui->comboBox->addItem(tr("private declaration"), Class::DeclarationType::Private);
}

SelectorDeclarationType::~SelectorDeclarationType()
{
  delete ui;
}

Class::DeclarationType SelectorDeclarationType::declarationType() const
{
  return static_cast<Class::DeclarationType>(ui->comboBox->itemData(ui->comboBox->currentIndex()).toInt());
}

bool SelectorDeclarationType::setDeclarationType(Class::DeclarationType declarationType)
{
  for (int i = 0; i < ui->comboBox->count(); i++)
  {
    if (ui->comboBox->itemData(i).toInt() == declarationType)
    {
      ui->comboBox->setCurrentIndex(i);
      return true;
    }
  }

  return false;
}

void SelectorDeclarationType::setEnabled(bool enabled)
{
  ui->comboBox->setEnabled(enabled);
}

void SelectorDeclarationType::on_comboBox_currentIndexChanged(int index)
{
  emit declarationTypeChanged(ui->comboBox->itemData(index).toInt());
}
