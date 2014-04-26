#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QList>
#include <QPair>
#include <QLineEdit>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    
private slots:
    void on_lineEditDec_returnPressed();
    void on_lineEditHex_returnPressed();
    void on_lineEditOct_returnPressed();
    void on_lineEditBin_returnPressed();

private:
    Ui::Widget *ui;
    void updateWidgets(QLineEdit *source, int base);
};

#endif // WIDGET_H
