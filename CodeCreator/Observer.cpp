#include <QMessageBox>

#include "Observer.h"
#include "ui_Observer.h"

#include "OptionsTemplate.h"
#include "CodeGenerator.h"

Observer::Observer(CodeGenerator* codeGenerator, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Observer),
  m_codeGenerator(codeGenerator)
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
  options.m_folderOutput = folder;
  options.m_folderInput = "templates/observer/";

  options.m_files << "TemplateSubjectInterface.h";
  options.m_files << "TemplateSubject.h";
  options.m_files << "TemplateSubject.cpp";
  options.m_files << "TemplateObserverInterface.h";
  options.m_files << "TemplateObserver.h";
  options.m_files << "TemplateObserver.cpp";

  // subject
  options.m_searchString = "TemplateSubject";
  options.m_replaceString = ui->lineEditSubject->text();

  m_codeGenerator->copyFromTemplate(options);

  // observer
  options.m_searchString = "TemplateObserver";
  options.m_replaceString = ui->lineEditObserver->text();

  m_codeGenerator->copyFromTemplate(options);
}

void Observer::readXml(QXmlStreamReader &xml)
{
}

void Observer::writeXml(QXmlStreamWriter &xml)
{
}
