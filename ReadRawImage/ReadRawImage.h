#ifndef READRAWIMAGE_H
#define READRAWIMAGE_H

#include <QWidget>

namespace Ui {
class ReadRawImage;
}

class ReadRawImage : public QWidget
{
    Q_OBJECT
    
public:
    explicit ReadRawImage(QWidget *parent = 0);
    ~ReadRawImage();
    
private:
    Ui::ReadRawImage *ui;
};

#endif // READRAWIMAGE_H
