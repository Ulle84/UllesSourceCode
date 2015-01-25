#include <QMessageBox>

#include "Observer.h"
#include "ui_Observer.h"
#include "XmlHelper.h"
#include "Options.h"
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

bool Observer::generate(const QString &folder)
{
  if (ui->lineEditObserver->text().isEmpty())
  {
    QMessageBox messageBox;
    messageBox.setText(tr("Please type in observer name!"));
    messageBox.exec();
    return false;
  }

  if (ui->lineEditSubject->text().isEmpty())
  {
    QMessageBox messageBox;
    messageBox.setText(tr("Please type in subject name!"));
    messageBox.exec();
    return false;
  }

  Options options;
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

  return mCodeGenerator->copyFromTemplate(options);
}

void Observer::readXml(QXmlStreamReader &xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Subject")
    {
      XmlHelper::readXml(xml, ui->lineEditSubject);
    }
    else if (xml.name() == "Observer")
    {
      XmlHelper::readXml(xml, ui->lineEditObserver);
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void Observer::writeXml(QXmlStreamWriter &xml)
{
  XmlHelper::writeXml(xml, "Subject", ui->lineEditSubject);
  XmlHelper::writeXml(xml, "Observer", ui->lineEditObserver);
}
