#include "WebSitePreview.h"
#include "ui_WebSitePreview.h"

WebSitePreview::WebSitePreview(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::WebSitePreview)
{
  ui->setupUi(this);
}

WebSitePreview::~WebSitePreview()
{
  delete ui;
}
