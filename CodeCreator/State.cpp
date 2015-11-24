#include <QMessageBox>

#include "State.h"
#include "ui_State.h"
#include "Options.h"
#include "CodeGenerator.h"
#include "XmlHelper.h"
#include "InterfaceHelper.h"

State::State(CodeGenerator* codeGenerator, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::State),
  mCodeGenerator(codeGenerator)
{
  ui->setupUi(this);
}

State::~State()
{
  delete ui;
}

bool State::generate(const QString &folder)
{
  if (!ui->checkBoxContext->isChecked() && !ui->checkBoxState->isChecked() && !ui->checkBoxStateInterface->isChecked())
  {
    QMessageBox messageBox;
    messageBox.setText(tr("No option is selected!"));
    messageBox.exec();
    return false;
  }

  if (ui->checkBoxContext->isChecked() && ui->lineEditContext->text().isEmpty())
  {
    QMessageBox messageBox;
    messageBox.setText(tr("Please enter a context name!"));
    messageBox.exec();
    return false;
  }

  if (ui->checkBoxState->isChecked() && ui->lineEditState->text().isEmpty())
  {
    QMessageBox messageBox;
    messageBox.setText(tr("Please enter a state name!"));
    messageBox.exec();
    return false;
  }

  Options options;
  options.folderOutput = folder;
  options.folderInput = "State/";

  options.searchAndReplace["Context"] = ui->lineEditContext->text();
  options.searchAndReplace["State"] = ui->lineEditState->text();
  options.searchAndReplace["Interface"] = ui->lineEditState->text();

  options.searchAndReplace["//TODO Implementation Context"] = InterfaceHelper::createFunctionImplementations(ui->plainTextEditStateInterface, "Context");
  options.searchAndReplace["//TODO Implementation State"] = InterfaceHelper::createFunctionImplementations(ui->plainTextEditStateInterface, "State");
  options.searchAndReplace["  // TODO add functions here"] = InterfaceHelper::createVirtualFunctionDeclarations(ui->plainTextEditStateInterface);
  options.searchAndReplace["  // IState"] = "  // IState\n" + InterfaceHelper::createFunctionDeclarations(ui->plainTextEditStateInterface);

  if (ui->checkBoxContext->isChecked())
  {
    options.files << "Context.h";
    options.files << "Context.cpp";
  }

  if (ui->checkBoxStateInterface->isChecked())
  {
    options.files << "IInterface.h";
  }

  if (ui->checkBoxState->isChecked())
  {
    options.files << "State.h";
    options.files << "State.cpp";
  }

  return mCodeGenerator->copyFromTemplate(options);
}

void State::readXml(QXmlStreamReader &xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "GenerateState")
    {
      XmlHelper::readXml(xml, ui->checkBoxState);
    }
    else if (xml.name() == "GenerateContext")
    {
      XmlHelper::readXml(xml, ui->checkBoxContext);
    }
    else if (xml.name() == "GenerateStateInterface")
    {
      XmlHelper::readXml(xml, ui->checkBoxStateInterface);
    }
    else if (xml.name() == "State")
    {
      XmlHelper::readXml(xml, ui->lineEditState);
    }
    else if (xml.name() == "Context")
    {
      XmlHelper::readXml(xml, ui->lineEditContext);
    }
    else if (xml.name() == "StateInterface")
    {
      XmlHelper::readXml(xml, ui->plainTextEditStateInterface);
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void State::writeXml(QXmlStreamWriter &xml)
{
  XmlHelper::writeXml(xml, "GenerateState", ui->checkBoxState);
  XmlHelper::writeXml(xml, "GenerateContext", ui->checkBoxContext);
  XmlHelper::writeXml(xml, "GenerateStateInterface", ui->checkBoxStateInterface);
  XmlHelper::writeXml(xml, "State", ui->lineEditState);
  XmlHelper::writeXml(xml, "Context", ui->lineEditContext);
  XmlHelper::writeXml(xml, "StateInterface", ui->plainTextEditStateInterface);
}

void State::on_checkBoxContext_toggled(bool checked)
{
  ui->lineEditContext->setEnabled(checked);
}

void State::on_checkBoxState_toggled(bool checked)
{
  ui->lineEditState->setEnabled(checked);
}

void State::on_checkBoxStateInterface_toggled(bool checked)
{
  ui->plainTextEditStateInterface->setEnabled(checked);
}
