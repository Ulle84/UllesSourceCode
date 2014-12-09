#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

    int getPc();
    int getProductMin();
    int getProductMax();
    int getSellerMin();
    int getSellerMax();

private slots:
    void on_pushButtonOk_clicked();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
