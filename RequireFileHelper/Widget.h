#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDomDocument>
#include <QFile>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void setFile(QString fileName);
    
private slots:
    void on_pushButtonFixlevel_clicked();

    void on_pushButtonMajor_clicked();

    void on_pushButtonMinor_clicked();

private:
    Ui::Widget *ui;
    QString fileName;
    void readFile();
    void updateFile();
    void writeFile();
    int readInt(QString tagName);
    void writeInt(QString tagName, int value);
    int major;
    int minor;
    int fixlevel;
    QDomDocument domDocument;
    void updateVersionLabel();

};

#endif // WIDGET_H
