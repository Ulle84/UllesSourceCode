#include "TuKiBasar.h"
#include "ui_TuKiBasar.h"

TuKiBasar::TuKiBasar(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TuKiBasar)
{
    ui->setupUi(this);

    /*m_model = new QStandardItemModel(0, 3, this);
    model->setHorizontalHeaderItem(0, new QStandardItem(tr("Verkäufer")));
    model->setHorizontalHeaderItem(1, new QStandardItem(tr("Artikel")));
    model->setHorizontalHeaderItem(2, new QStandardItem(tr("Preis")));

    QStandardItem *firstRow = new QStandardItem(QString("ColumnValue"));
    model->setItem(0, 0, firstRow);

    ui->tableViewProductItems->setModel(model);

    ProductItem* pi100 = new ProductItem(100, 101, 100.0, "einhundert");
    ProductItem* pi200 = new ProductItem(200, 202, 200.0, "zweihundert");
    ProductItem* pi300 = new ProductItem(300, 303, 300.0, "dreihundert");

    m_productItemManager.addProductItem(pi100);
    m_productItemManager.addProductItem(pi200);
    m_productItemManager.addProductItem(pi300);*/
}

TuKiBasar::~TuKiBasar()
{
    delete ui;
    //delete m_model;
}

/*void TuKiBasar::on_pushButton_clicked()
{
    Settings settings(this);
    settings.exec();
}*/

void TuKiBasar::on_actionSettings_triggered(bool checked)
{
    m_settings.exec();
}

void TuKiBasar::on_actionEvaluation_triggered(bool checked)
{
    m_evaluation.exec();
}
