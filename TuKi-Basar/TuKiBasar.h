#ifndef TUKIBASAR_H
#define TUKIBASAR_H

#include <QMainWindow>

namespace Ui {
class TuKiBasar;
}

class TuKiBasar : public QMainWindow
{
    Q_OBJECT

public:
    explicit TuKiBasar(QWidget *parent = 0);
    ~TuKiBasar();

private slots:
    void on_pushButton_clicked();

private:
    Ui::TuKiBasar *ui;
};

#endif // TUKIBASAR_H