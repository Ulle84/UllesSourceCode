#ifndef SMALLTEST_H
#define SMALLTEST_H

#include <QWidget>

namespace Ui {
class SmallTest;
}

class SmallTest : public QWidget
{
    Q_OBJECT
    
public:
    explicit SmallTest(QWidget *parent = 0);
    ~SmallTest();
    
private slots:
    void on_pushButtonCommit_clicked();

private:
    Ui::SmallTest *ui;
};

#endif // SMALLTEST_H
