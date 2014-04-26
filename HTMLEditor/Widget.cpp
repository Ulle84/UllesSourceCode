#include "Widget.h"
#include "ui_Widget.h"

#include <QString>

Widget::Widget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Widget)
{
  ui->setupUi(this);
}

Widget::~Widget()
{
  delete ui;
}

void Widget::on_pushButton_clicked()
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
