#include <QClipboard>
#include <QCryptographicHash>

#include "CryptoHelper.h"
#include "ui_CryptoHelper.h"

CryptoHelper::CryptoHelper(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CryptoHelper)
{
  ui->setupUi(this);
}

CryptoHelper::~CryptoHelper()
{
  delete ui;
}

void CryptoHelper::on_lineEditInput_textChanged(const QString &arg1)
{
    QByteArray inputBytes(arg1.toUtf8());
    QByteArray myHash = QCryptographicHash::hash(inputBytes, QCryptographicHash::Sha1);
    QString result(myHash.toHex());

    ui->lineEditOutput->setText(result);
}

void CryptoHelper::on_pushButton_clicked()
{
    QApplication::clipboard()->setText(ui->lineEditOutput->text());
}
