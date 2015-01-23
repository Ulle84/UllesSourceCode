#include <QMessageBox>

#include "Observer.h"
#include "ui_Observer.h"

#include "OptionsTemplate.h"
#include "CodeGenerator.h"

Observer::Observer(CodeGenerator* codeGenerator, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Observer),
  mCodeGenerator(codeGenerator)
{
  ui->setupUi(this);
}

Observer::~Observer()
{
  delete ui;
}

void Observer::generate(const QString &folder)
{
  if (ui->lineEditObserver->text().isEmpty())
  {
    QMessageBox messageBox;
    messageBox.setText(tr("Please type in observer name!"));
    messageBox.exec();
    return;
  }

  if (ui->lineEditSubject->text().isEmpty())
  {
    QMessageBox messageBox;
    messageBox.setText(tr("Please type in subject name!"));
    messageBox.exec();
    return;
  }

  OptionsTemplate options;
  options.folderOutput = folder;
  options.folderInput = "templates/observer/";

  options.files << "ITemplateSubject.h";
  options.files << "ITemplateObserver.h";
  options.files << "TemplateSubject.h";
  options.files << "TemplateSubject.cpp";
  options.files << "TemplateObserver.h";
  options.files << "TemplateObserver.cpp";

  options.searchAndReplace["TemplateSubject"] = ui->lineEditSubject->text();
  options.searchAndReplace["TemplateObserver"] = ui->lineEditObserver->text();

  mCodeGenerator->copyFromTemplate(options);
}

void Observer::readXml(QXmlStreamReader &xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Subject")
    {
      ui->lineEditSubject->setText(xml.readElementText());
    }
    else if (xml.name() == "Observer")
    {
      ui->lineEditObserver->setText(xml.readElementText());
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void Observer::writeXml(QXmlStreamWriter &xml)
{
  xml.writeTextElement("Subject", ui->lineEditSubject->text());
  xml.writeTextElement("Observer", ui->lineEditObserver->text());
}
