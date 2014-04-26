#ifndef WEBSITEPREVIEW_H
#define WEBSITEPREVIEW_H

#include <QDialog>

namespace Ui {
class WebSitePreview;
}

class WebSitePreview : public QDialog
{
  Q_OBJECT
  
public:
  explicit WebSitePreview(QWidget *parent = 0);
  ~WebSitePreview();
  
private:
  Ui::WebSitePreview *ui;
};

#endif // WEBSITEPREVIEW_H
