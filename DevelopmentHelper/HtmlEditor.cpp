#include <QString>

#include "HtmlEditor.h"
#include "ui_HtmlEditor.h"

HtmlEditor::HtmlEditor(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::HtmlEditor)
{
  ui->setupUi(this);
}

HtmlEditor::~HtmlEditor()
{
  delete ui;
}

void HtmlEditor::on_pushButton_clicked()
{
  QString htmlContent = "";
  htmlContent.append("<html><head><style rel=\"stylesheet\" type=\"text/css\">");
  htmlContent.append(ui->plainTextEditCSS->toPlainText());
  htmlContent.append("</style><script language=\"JavaScript\">");
  htmlContent.append(ui->plainTextEditJavaScript->toPlainText());
  htmlContent.append("</script></head><body>");
  htmlContent.append(ui->plainTextEditHTML->toPlainText());
  htmlContent.append("</body></html>");
  ui->textEdit->clear();
  ui->textEdit->setText(htmlContent);
}
