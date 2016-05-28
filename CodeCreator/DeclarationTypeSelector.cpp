#include "DeclarationTypeSelector.h"
#include "ui_DeclarationTypeSelector.h"

DeclarationTypeSelector::DeclarationTypeSelector(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::DeclarationTypeSelector)
{
  ui->setupUi(this);

  ui->comboBox->addItem(tr("no declaration"), Class::DeclarationType::NoDeclaration);
  ui->comboBox->addItem(tr("public declaration"), Class::DeclarationType::Public);
  ui->comboBox->addItem(tr("private declaration"), Class::DeclarationType::Private);
}

DeclarationTypeSelector::~DeclarationTypeSelector()
{
  delete ui;
}

Class::DeclarationType DeclarationTypeSelector::declarationType()
{
  int declarationType = ui->comboBox->itemData(ui->comboBox->currentIndex()).toInt();

  switch(declarationType)
  {
  case Class::DeclarationType::NoDeclaration:
    return Class::DeclarationType::NoDeclaration;
  case Class::DeclarationType::Public:
    return Class::DeclarationType::Public;
  case Class::DeclarationType::Private:
      return Class::DeclarationType::Private;
  }
}

bool DeclarationTypeSelector::setDeclarationType(Class::DeclarationType declarationType)
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

void DeclarationTypeSelector::setEnabled(bool enabled)
{
  ui->comboBox->setEnabled(enabled);
}
