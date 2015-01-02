#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QStringList>
#include <QMessageBox>
#include <QTextStream>

#include "TuKiBasar.h"
#include "ui_TuKiBasar.h"

#include "ProductItem.h"

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

void TuKiBasar::on_actionImportArticleLists_triggered(bool checked)
{
    // clear current content first?


    // open folder selection dialog
    QString dirName = QFileDialog::getExistingDirectory(this, tr("Bitte Ordner mit den Artikellisten wählen...")); //TODO set folder of last selection?

    QDir dir(dirName);

    QStringList filters;
    filters << "articleList_*.txt";
    dir.setNameFilters(filters);

    QStringList fileNames = dir.entryList();

    unsigned int sellerCounter = 0;
    unsigned int articleCounter = 0;

    const int headerOffset = 3;
    const int linesPerArticle = 4;

    // read the seller number from the file
    for (int i = 0; i < fileNames.length(); i++)
    {
        QString filePath = dir.filePath(fileNames.at(i));

        QFile file(filePath);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            continue;
        }

        QStringList fileContent;
        QTextStream in(&file);
        while (!in.atEnd())
        {
            fileContent.append(in.readLine());
        }

        if (fileContent.length() < headerOffset)
        {
            file.close();
            continue;
        }

        if (fileContent.at(0) != "Article List")
        {
            file.close();
            continue;
        }

        if ((fileContent.length() - headerOffset) % linesPerArticle != 0)
        {
            file.close();
            continue;
        }

        //TODO use version information if nessessary

        bool conversionOkay;
        int sellerNumber = fileContent.at(2).toInt(&conversionOkay);

        if (!conversionOkay)
        {
            file.close();
            continue;
        }

        int numberOfArticles = (fileContent.length() - headerOffset) / linesPerArticle;

        for (int i = 0; i < numberOfArticles; i++)
        {
            int articleNumber = fileContent.at(headerOffset + linesPerArticle * i).toInt();
            double prize = fileContent.value(headerOffset + linesPerArticle * i + 1).replace(",", ".").toDouble();
            QString description = fileContent.at(headerOffset + linesPerArticle * i + 3);

            ProductItem* pi = new ProductItem(articleNumber, sellerNumber, prize, description);
            m_productItemManager.addProductItem(pi);

            articleCounter++;
        }

        file.close();
        sellerCounter++;
    }

    // open file and read content to ProductItems

    // append content to ProductItemManager

    // show sucess message

    QMessageBox mb;
    mb.setText(tr("Es wurden erfolgreich %1 Artikel von %2 Verkäufern importiert.").arg(articleCounter).arg(sellerCounter));
    mb.exec();
}
