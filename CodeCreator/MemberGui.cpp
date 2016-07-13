#include "MemberGui.h"
#include "ui_MemberGui.h"

MemberGui::MemberGui(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MemberGui)
{
  ui->setupUi(this);

  ui->comboBoxDeclarationType->addItem(tr("public"), Member::DeclarationType::Public);
  ui->comboBoxDeclarationType->addItem(tr("protected"), Member::DeclarationType::Protected);
  ui->comboBoxDeclarationType->addItem(tr("private"), Member::DeclarationType::Private);

  ui->comboBoxDeclarationType->setCurrentIndex(2);
}

MemberGui::~MemberGui()
{
  delete ui;
}

Member MemberGui::member() const
{
  Member member;
  member.setName(ui->lineEditName->text());
  member.setType(ui->lineEditType->text());
  member.setDefaultValue(ui->lineEditDefaultValue->text());
  member.setDeclarationType(static_cast<Member::DeclarationType>(ui->comboBoxDeclarationType->itemData(ui->comboBoxDeclarationType->currentIndex()).toInt()));
  member.setGetter(ui->checkBoxGetter->isChecked());
  member.setSetter(ui->checkBoxSetter->isChecked());

  return member;
}

void MemberGui::setMember(const Member &member)
{
  ui->lineEditName->setText(member.name());
  ui->lineEditType->setText(member.type());
  ui->lineEditDefaultValue->setText(member.defaultValue());
  ui->checkBoxGetter->setChecked(member.hasGetter());
  ui->checkBoxSetter->setChecked(member.hasSetter());

  for (int i = 0; i < ui->comboBoxDeclarationType->count(); i++)
  {
    if (ui->comboBoxDeclarationType->itemData(i).toInt() == member.declarationType())
    {
      ui->comboBoxDeclarationType->setCurrentIndex(i);
      break;
    }
  }
}
