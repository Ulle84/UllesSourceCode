#include <QtGui>
#include <QSettings>

#include <iostream>

#include "clipboardextended.h"
#include "SuperUser.h"

/*
Bugs

ToDos
- Umstellgung auf UI File

Enhancements
- HotKey mit Drop-Down an aktueller Mouseposition -> pasten in aktive Applikation (geht das mit Qt plattformunabhängig?)
- Basis-Klasse Window
- Qt Info Dialog
- Don't display active Clipboard in History
- Global Hotkeys
- History View: Add leading Date and Time
- Visual Feedback, when actual clipboard content changes (red lightning)
- Maximale (einstellbare) Anzahl von History-EintrÃ¤gen
- Programmicon hinzufÃ¼gen
- Fensterpostionen und Dimensionen speichern
- Button: Aktuelle Zwischenablage zu den Vorlagen hinzufÃ¼gen
- Templates Speichern und Laden
- Anzahl der Template und History EintrÃ¤ge anzeigen

Ideas

Done
- Textboxen und Listenansichten sind editierbar
- Datum und Zeit Template
- Alternative Hintergrundfarbe deutlicher gestalten
- Initial auch die Zwischenablage auslesen
- Programm erzeugt Rechenlast von 100 Prozent, wenn groÃŸe Texte in der Zwischenablge sind (z. B. beim Umkopieren von groÃŸen Excel-Tabellen) -> Bei Clipboard-Texten mit Zeichenlänge größer 10000 wird "sorry, clipboard is too long" anstatt des clipboard contents hineingeschrieben
*/

ClipboardExtended::ClipboardExtended(QWidget* parent) : QWidget(parent)
{
  dateTimeEdit = new QLineEdit("yyyy-MM-dd hh:mm'h'");
  historyStringList = new QStringList();

  templatesStringList = new QStringList();
  templatesStringList->append("--------------------------------------------------------------------------------");
  templatesStringList->append("//------------------------------------------------------------------------------");
  templatesStringList->append("//------------------------------------------------------------------------------\n// \n//------------------------------------------------------------------------------");
  templatesStringList->append("//##############################################################################");
  templatesStringList->append("/*\nBugs\n\nToDo\n\nEnhancements\n\nIdeas\n\nDone\n\n*/");
  templatesStringList->append("/*******************************************************************************");
  templatesStringList->append("*******************************************************************************/");

  // model/view
  templatesModel = new QStringListModel(this);
  templatesModel->setStringList(*templatesStringList);
  historyModel = new QStringListModel(this);
  historyModel->setStringList(*historyStringList);

  // init GUI-Staff
  templatesListView = new QListView();
  historyListView = new QListView();
  historyListView->setStyleSheet("alternate-background-color: darkgrey;");
  historyListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  textEditClipboard = new QTextEdit();
  QPushButton* deleteHistoryButton = new QPushButton(tr("Clear History"));
  QPushButton* dateTimeButton = new QPushButton(tr("date-string to clipboard"));
  QPushButton* superUserButton = new QPushButton(tr("SuperUser Password to clipboard"));

  // font depends on operating system
#ifdef Q_WS_MAC
  templatesListView->setFont(QFont::QFont("Monaco", 14, 0, false));
  historyListView->setFont(QFont::QFont("Monaco", 14, 0, false));
  textEditClipboard->setFont(QFont::QFont("Monaco", 14, 0, false));
#endif
#ifdef Q_WS_WIN
  templatesListView->setFont(QFont::QFont("Courier", 10, 0, false));
  historyListView->setFont(QFont::QFont("Courier", 10, 0, false));
  textEditClipboard->setFont(QFont::QFont("Courier", 10, 0, false));
#endif
  templatesListView->setModel(templatesModel);
  templatesListView->setAlternatingRowColors(true);
  templatesListView->setStyleSheet("alternate-background-color: darkgrey;");
  templatesListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  historyListView->setModel(historyModel);

  historyListView->setAlternatingRowColors(true);
  textEditClipboard->setReadOnly(true);

  // creating Layout
  QHBoxLayout* hBoxLayout = new QHBoxLayout();
  //hBoxLayout->addWidget(dateTimeEdit);
  //hBoxLayout->addWidget(dateTimeButton);
  hBoxLayout->addWidget(superUserButton);

  QVBoxLayout* vBoxLayout = new QVBoxLayout();
  vBoxLayout->addWidget(new QLabel(tr("Content of Clipboard")));
  vBoxLayout->addWidget(textEditClipboard);
  vBoxLayout->addLayout(hBoxLayout);
  //vBoxLayout->addWidget(new QLabel(tr("Templates")));
  //vBoxLayout->addWidget(templatesListView);
  vBoxLayout->addWidget(new QLabel(tr("History")));
  vBoxLayout->addWidget(historyListView);
  vBoxLayout->addWidget(deleteHistoryButton);

  // connecting signals and slots
  connect(templatesListView, SIGNAL(clicked(QModelIndex)), this, SLOT(templateToClipboard()));
  connect(historyListView, SIGNAL(clicked(QModelIndex)), this, SLOT(historyToClipboard()));
  connect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(clipboardDataChanged()));
  connect(deleteHistoryButton, SIGNAL(clicked()), this, SLOT(clearHistory()));
  connect(dateTimeButton, SIGNAL(clicked()), this, SLOT(dateTimeToClipboard()));
  connect(superUserButton, SIGNAL(clicked()), this, SLOT(superUserPasswordToClipboard()));

  setLayout(vBoxLayout);

  clipboardDataChanged();

  QSettings settings;
  restoreGeometry(settings.value("mainWindowGeometry").toByteArray());
}

ClipboardExtended::~ClipboardExtended()
{
  QSettings settings;
  settings.setValue("mainWindowGeometry", saveGeometry());
}

void ClipboardExtended::templateToClipboard()
{
  QApplication::clipboard()->setText(templatesStringList->at(templatesListView->currentIndex().row()));
}

void ClipboardExtended::historyToClipboard()
{
  QApplication::clipboard()->setText(historyStringList->at(historyListView->currentIndex().row()));
}

void ClipboardExtended::clipboardDataChanged()
{
  QString clipboardString = QApplication::clipboard()->text();

  if (clipboardString.length() == 0)
  {
    return;
  }

  if (clipboardString.length() > 10000)
  {
    clipboardString = "sorry, clipboard content ist too long!";
  }

  textEditClipboard->setText(clipboardString);

  if (historyModel->rowCount() == 0)   // ist die History noch leer?
  {
    historyStringList->append(clipboardString);
    historyModel->setStringList(*historyStringList);
    return;
  }

  if (clipboardString != historyStringList->at(0))   // ist der String nicht schon ganz oben in der History?
  {
    historyStringList->insert(0, clipboardString);
    historyModel->setStringList(*historyStringList);
  }

  return;
}

void ClipboardExtended::clearHistory()
{
  historyStringList->clear();
  historyModel->setStringList(*historyStringList);
}

void ClipboardExtended::dateTimeToClipboard()
{
  QDateTime dateTime = QDateTime::currentDateTime();
  QApplication::clipboard()->setText(dateTime.toString(dateTimeEdit->text()));
}

void ClipboardExtended::superUserPasswordToClipboard()
{
  QApplication::clipboard()->setText(SuperUser::password());
}
