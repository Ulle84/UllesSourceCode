#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QStringList>
#include <QMessageBox>
#include <QTextStream>

#include "TuKiBasar.h"
#include "ui_TuKiBasar.h"

#include "Article.h"

TuKiBasar::TuKiBasar(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TuKiBasar)
{
    ui->setupUi(this);

    // font depends on operating system
    #ifdef Q_WS_MAC
      ui->plainTextEditArticleList->setFont(QFont::QFont("Monaco", 14, 0, false));
    #endif
    #ifdef Q_WS_WIN
      ui->plainTextEditArticleList->setFont(QFont::QFont("Courier", 10, 0, false));
    #endif



    /*ui->spinBoxArticleNumber->setMinimum(m_settings.getProductMin());
    ui->spinBoxArticleNumber->setMaximum(m_settings.getProductMax());
    ui->spinBoxSellerNumber->setMinimum(m_settings.getSellerMin());
    ui->spinBoxSellerNumber->setMaximum(m_settings.getSellerMax());*/
}

TuKiBasar::~TuKiBasar()
{
    delete ui;
}

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
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, tr("Vorhandene Artikel löschen?"),
                                    tr("Möchten Sie die bereits importierten Artikel löschen?"),
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
          m_articleManager.clear();
      }

    QString dirName = QFileDialog::getExistingDirectory(this, tr("Bitte Ordner mit den Artikellisten wählen...")); //TODO set folder of last selection?

    if (dirName.isEmpty())
    {
        return;
    }

    QDir dir(dirName);

    QStringList filters;
    filters << "articleList_*.txt";
    dir.setNameFilters(filters);

    QStringList fileNames = dir.entryList();

    unsigned int sellerCounter = 0;
    unsigned int articleCounter = 0;

    const int headerOffset = 3;
    const int linesPerArticle = 4;

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

        bool conversionSellerNumber;
        int sellerNumber = fileContent.at(2).toInt(&conversionSellerNumber);

        if (!conversionSellerNumber)
        {
            file.close();
            continue;
        }

        int numberOfArticles = (fileContent.length() - headerOffset) / linesPerArticle;

        for (int i = 0; i < numberOfArticles; i++)
        {
            bool conversionPrize;
            double prize = fileContent.value(headerOffset + linesPerArticle * i + 1).replace(",", ".").toDouble(&conversionPrize);
            if (!conversionPrize)
            {
                continue;
            }

            int articleNumber = fileContent.at(headerOffset + linesPerArticle * i).toInt();
            QString size = fileContent.at(headerOffset + linesPerArticle * i + 2);
            QString description = fileContent.at(headerOffset + linesPerArticle * i + 3);

            Article* article = new Article(articleNumber, sellerNumber, prize, size, description);
            m_articleManager.addArticle(article); //TODO check that no article is added twice

            articleCounter++;
        }

        file.close();
        sellerCounter++;
    }

    m_articleManager.toXml();

    QMessageBox mb;
    if (articleCounter > 0)
    {
        mb.setText(tr("Es wurden erfolgreich %1 Artikel von %2 Verkäufern importiert.").arg(articleCounter).arg(sellerCounter));
    }
    else
    {
        mb.setText(tr("Es wurden keine Artikel importiert."));
    }

    mb.exec();    
}

void TuKiBasar::on_lineEditScannerInput_returnPressed()
{
    QString input = ui->lineEditScannerInput->text();

    bool conversion1 = false;
    bool conversion2 = false;

    int sellerNumber = input.left(3).toInt(&conversion1);
    int articleNumber = input.right(3).toInt(&conversion2);

    ui->lineEditScannerInput->clear();
    if (!conversion1 || !conversion2)
    {
        return;
    }

    Article* article = m_articleManager.getArticle(sellerNumber, articleNumber);

    if (article != 0)
    {
        m_articleManager.addArticleToCurrentSale(article);
        ui->plainTextEditArticleList->setPlainText(m_articleManager.currentSaleToText());
        ui->textEdit->setHtml(m_articleManager.currentSaleToHtml());

        QTableWidgetItem *tableWidgetItemArticleNumber = new QTableWidgetItem(QString("%1").arg(articleNumber));
        ui->tableWidget->setItem(0, 0, tableWidgetItemArticleNumber);

        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);

    }


}
