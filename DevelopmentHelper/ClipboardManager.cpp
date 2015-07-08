#include <QApplication>
#include <QClipboard>
#include <QDebug>
#include <QFont>
#include <QStringListModel>

#include "ClipboardManager.h"
#include "ui_ClipboardManager.h"

ClipboardManager::ClipboardManager(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ClipboardManager)
{
  ui->setupUi(this);

  m_stringListModel = new QStringListModel(this);

  QFont font("Courier", 10);

#ifdef Q_WS_MAC
  // change font on mac os x
  font.setFamily("Monaco");
  font.setPointSize(14);
#endif

  ui->plainTextEditCurrentClipboard->setFont(font);
  ui->listViewClipbaordHistory->setFont(font);
  ui->listViewClipbaordHistory->setModel(m_stringListModel);

  ui->listViewClipbaordHistory->setAlternatingRowColors(true);
  ui->listViewClipbaordHistory->setStyleSheet("alternate-background-color: darkgrey;");

  connect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(clipboardDataChanged()));
  connect(ui->listViewClipbaordHistory, SIGNAL(clicked(QModelIndex)), this, SLOT(historyToClipboard()));

  clipboardDataChanged();
}

ClipboardManager::~ClipboardManager()
{
  delete ui;
}

void ClipboardManager::clipboardDataChanged()
{
  QString clipbaordText = QApplication::clipboard()->text();

  if (clipbaordText.isEmpty())
  {
    return;
  }

  if (clipbaordText != m_currentClipbardData)
  {
    m_lastClipbardData = m_currentClipbardData;
    m_currentClipbardData = clipbaordText;
    update();
  }
}

void ClipboardManager::historyToClipboard()
{
  QApplication::clipboard()->setText(m_clipbardHistory.at(ui->listViewClipbaordHistory->currentIndex().row()));
}

void ClipboardManager::update()
{
  if (m_currentClipbardData.size() > 10000)
  {
    m_currentClipbardData = "sorry, clipboard content ist too long!";
  }

  ui->plainTextEditCurrentClipboard->setPlainText(m_currentClipbardData);

  if (!m_lastClipbardData.isEmpty())
  {
    m_clipbardHistory.prepend(m_lastClipbardData);
  }

  m_stringListModel->setStringList(m_clipbardHistory);
}

void ClipboardManager::on_pushButtonClearHistory_clicked()
{
  m_lastClipbardData.clear();
  m_clipbardHistory.clear();
  m_stringListModel->setStringList(m_clipbardHistory);
}

void ClipboardManager::on_pushButtonClearClipboard_clicked()
{
  QApplication::clipboard()->clear();
  ui->plainTextEditCurrentClipboard->clear();
}
