#include "clipboardextended.h"
#include <iostream>
#include <QtGui>

// Bugs
// Textboxen und Listenansichten sind editierbar
// Programm erzeugt Rechenlast von 100 Prozent, wenn große Texte in der Zwischenablge sind (z. B. beim Umkopieren von großen Excel-Tabellen)

// ToDos
// Datum und Zeit Template

// Ideas

// Enhancements
// Beim Starten aktuelle Zwischenablage einlesen
// Basis-Klasse Window
// Qt Info Dialog
// Don't display active Clipboard in History
// Global Hotkeys
// History View: Add leading Date and Time
// Visual Feedback, when actual clipboard content changes (red lightning)
// Maximale (einstellbare) Anzahl von History-Einträgen
// Programmicon hinzufügen
// Fensterpostionen und Dimensionen speichern
// Button: Aktuelle Zwischenablage zu den Vorlagen hinzufügen
// Templates Speichern und Laden
// Anzahl der Template und History Einträge anzeigen


ClipboardExtended::ClipboardExtended(QWidget *parent) : QWidget(parent) {
    dateTimeEdit = new QLineEdit("yyyy-MM-dd hh:mm'h'");
    historyStringList = new QStringList();

    templatesStringList = new QStringList();
    templatesStringList->append("--------------------------------------------------------------------------------");
    templatesStringList->append("//------------------------------------------------------------------------------");
    templatesStringList->append("//------------------------------------------------------------------------------\n// \n//------------------------------------------------------------------------------");
    templatesStringList->append("//##############################################################################");
    //templatesStringList->append("/*\nBugs\n\nToDo\n\nIdea\n\nDone\n\n*/");
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
    textEditClipboard = new QTextEdit();
    QPushButton *deleteHistoryButton = new QPushButton(tr("Clear History"));
    QPushButton *dateTimeButton = new QPushButton(tr("Ermittle Ergebnis"));

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
    historyListView->setModel(historyModel);

    historyListView->setAlternatingRowColors(true);
    textEditClipboard->setReadOnly(true);

    // creating Layout
    QHBoxLayout *hBoxLayout = new QHBoxLayout();
    hBoxLayout->addWidget(dateTimeEdit);
    hBoxLayout->addWidget(dateTimeButton);

    QVBoxLayout *vBoxLayout = new QVBoxLayout();
    vBoxLayout->addWidget(new QLabel(tr("Content of Clipboard")));
    vBoxLayout->addWidget(textEditClipboard);
    vBoxLayout->addLayout(hBoxLayout);
    vBoxLayout->addWidget(new QLabel(tr("Templates")));
    vBoxLayout->addWidget(templatesListView);
    vBoxLayout->addWidget(new QLabel(tr("History")));
    vBoxLayout->addWidget(historyListView);
    vBoxLayout->addWidget(deleteHistoryButton);

    // connecting signals and slots
    connect(templatesListView, SIGNAL(clicked(QModelIndex)), this, SLOT(templateToClipboard()));
    connect(historyListView, SIGNAL(clicked(QModelIndex)), this, SLOT(historyToClipboard()));
    connect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(clipboardDataChanged()));
    connect(deleteHistoryButton, SIGNAL(clicked()), this, SLOT(clearHistory()));
    connect(dateTimeButton, SIGNAL(clicked()), this, SLOT(dateTimeToClipboard()));

    setLayout(vBoxLayout);
}

ClipboardExtended::~ClipboardExtended() {

}

void ClipboardExtended::templateToClipboard() {
    QApplication::clipboard()->setText(templatesStringList->at(templatesListView->currentIndex().row()));
}

void ClipboardExtended::historyToClipboard() {
    QApplication::clipboard()->setText(historyStringList->at(historyListView->currentIndex().row()));
}

void ClipboardExtended::clipboardDataChanged() {
    QString clipboardString = QApplication::clipboard()->text();
    textEditClipboard->setText(clipboardString);
    if (historyModel->rowCount() == 0) { // ist die History noch leer?
        historyStringList->append(clipboardString);
        historyModel->setStringList(*historyStringList);
        return;
    }
    if (clipboardString != historyStringList->at(0)) { // ist der String nicht schon ganz oben in der History?
        historyStringList->insert(0, clipboardString);
        historyModel->setStringList(*historyStringList);
    }
    return;
}

void ClipboardExtended::clearHistory() {
    historyStringList->clear();
    historyModel->setStringList(*historyStringList);
}

void ClipboardExtended::dateTimeToClipboard() {
    QDateTime dateTime = QDateTime::currentDateTime();
    QApplication::clipboard()->setText(dateTime.toString(dateTimeEdit->text()));
}
