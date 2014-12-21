#ifndef TUKIBASAR_H
#define TUKIBASAR_H

#include <QMainWindow>
#include <QStandardItemModel>

#include "ProductItemManager.h"

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
    //void on_pushButton_clicked();

    void on_actionSettings_triggered(bool checked);

    void on_actionEvaluation_triggered(bool checked);

private:
    Ui::TuKiBasar *ui;
    //ProductItemManager m_productItemManager;
    //QStandardItemModel* m_model;
};

#endif // TUKIBASAR_H
