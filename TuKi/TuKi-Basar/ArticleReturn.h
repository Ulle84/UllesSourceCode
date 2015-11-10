#ifndef ARTICLERETURN_H
#define ARTICLERETURN_H

#include <QDialog>

namespace Ui {
class ArticleReturn;
}

class ArticleReturn : public QDialog
{
    Q_OBJECT

public:
    explicit ArticleReturn(QWidget *parent = 0);
    ~ArticleReturn();

private:
    Ui::ArticleReturn *ui;
};

#endif // ARTICLERETURN_H
