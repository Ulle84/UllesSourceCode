# Ulles C++ Style-Guide

## Sprache
Grundsätzlich werden Quellcode und Kommentare in englischer Sprache verfasst!

## Kommentare
* Nach Möglichkeit sollte auf Kommentare verzichtet werden. Der Code sollte ohne Kommentare verständlich sein.
* Wenn man sich dabei erwischt lange Kommentare zu verfassen, dann sollte man eher über ein Refactoring nachdenken.
* Verschachtelung von Templates kommentieren - z. B. `QMap<QString /*domainName*/, QMap<QString /*domainUserName*/, QStringList /*localRoleNames*/> > m_domainUserMapping;`
* richtiger Kommentar mit Space nach Slahes: `// richter Kommentar`
* auskommentierter Code ohne Space nach Slahes: `//int i = 0;` oder per `/*multiple lines of code*/`

## Exceptions
* Exceptions sind sehr sinnvoll und hilfreich! Das automatische Stack-Unwinding hilft enorm!
* Wenn in einem Projekt oder einer Umgebung bisher keine Exceptions geworfen wurde, sollte man nicht der erste sein, der damit anfängt, weil die Gefahr groß ist, dass keiner die Exception fängt und es zum Programmabbruch kommt.
* Wenn man jedoch auf der grünen Wiese steht, sollte man Exceptions verwenden - wichtig ist, dass man im Header nach der Funktion angibt welche Exceptions geworfen werden -> die verwendeten Exceptions sollten zum Bestandteil der Signatur werden!

## AStyle
Style-Guides werden nur dann akzeptiert, wenn sie durch die Bank weg einheitlich angwendet werden.
Um die Anwendung eines Style-Guides zu vereinfachen wird das Tool Artistic Style (AStyle) verwendet.
Die Einstellungsdatei hat folgenden Inhalt
```
# options for AStyle
--indent=spaces=2
--style=allman
--add-brackets
--align-pointer=type
--align-reference=type
--indent-col1-comments
--break-blocks
--pad-oper
--pad-header
--unpad-paren
--convert-tabs
```

## Trennung zwischen Header und SourceFile
* Header-Dateien haben die Endung 'h'.
* Source-Dateien haben die Endung 'cpp'.
* In der Header-Datei wird kein Code implementiert! Ausnahme sind inline-Funktions und Template-Klassen-Funktionen, diese können ausserhalb der Klassendeklaration im Header implementiert werden.

## Benennung
* Variablen und Funktionsnamen sollten immer sprechend sein. Ändert sich die Aufgabe einer Funktion, sollte die Funktion auch umbenannt werden!
* der Typ einer Varialbe muss nicht im Namen auftauchen
* Grundsätzlich werden Namen in Camel-Case Schreibweise geschrieben, z. B. `aCamelCaseVariable` und `aXmlReader`
* Variablen und Funktionsnamen beginnen mit einem Kleinbuchstaben, Klassen mit einem Großbuchstaben.
* `qty` als Präfix für "eine Anzahl von" z. B. `m_qtySoldArticles`
* Member werden mit einem vorausgehenden `m_` gekennzeichnet - Ausnahme: pImpl heißt nur `m`
* Globale Variablen werden mit einem vorausgehenden `g_` gekennzeichnet, z. B. `g_fileHandler`- globale Variablen sollten nur im Ausnahmefall verwendert werden.
* Konstante Variablen werden nicht mit Präfix gekennzeichnet da es sonst:
  * Uneinigkeiten mit const members (`cm_` oder `mc_`) gibt
  * Uneinigkeiten mit const globals (`cg_` oder `gc_`) gibt
* Funktionsnamen beginnen mit einem kleinen Buchstaben um besser zwischen Funktionsaufruf und Objekterstellung zu Unterscheiden.
* Pointer werden nicht speziell deklariert. Pointer kommen in C++ so oft vor, dass eine spezielle Auszeichnung keinen Sinn macht!
* Setter werden mit dem Präfix `set` versehen.
* Getter haben normalerweise kein Präfix - Ausnahme: Getter bekommen ein Präfix `get`, wenn eine Referenz übergeben wird, z. B. `void getBlub(ALargeClassWhichTakesLongToCopy& blub);`
* Beispiele für die Benennungen:
```
m_aCamelCaseMember foo;
aVariableWithXmlAbbreviation foo; // not: aVariableWithXMLAbbreviation
aCamelCaseVariable foo;
aCamelCaseFunction();
ACamelCaseClass foo;
```

## Aufbau einer Klasse
* Reihenfolge
  * public
  * protected
  * private
* Unterreihenfolge
  * Konstruktoren
  * Destruktor
  * Operatoren
  * weitere Funktionen

## Verschiedenes
### Überflüssiges void
Manchmal findet man die Schreibweise

```
class AuthenticationType
{
public:
  AuthenticationType(void);
}
```

Den Ausdruck `void` in den Klammern kann man löschen!
    
### Überflüssige Klammern
Manchmal findet man die Schreibweise `return (0);`
Die Klammern um den return value kann man löschen! Man würde ja auch nicht `int a = (10);` schreiben

### Schwachsinnige Abfragen vermeiden
```
bool valid;
bool break;

if ((valid == false) || (break == false)) // bad

if (!valid || !break) // good
```

### Korrekte Schlüsselwörter verwenden
```
bool runLoop = true;

for(;runLoop;) {} // bad
while(runLoop) {} // good
```

## Beispiele
### StyleGuide.h
```
#ifndef STYLEGUIDE_H
#define STYLEGUIDE_H

class StyleGuidePrivate;

class StyleGuide
{
public:
  StyleGuide();
  StyleGuide(int value);
  ~StyleGuide(){}
  
  int value();
  void setValue(int value);
  
  void getHuge(Huge& huge);
  void setHuge(const Huge& huge);

private:
  int m_value;
  Huge m_huge;
  StyleGuidePrivate* m;
};

#endif // STYLEGUIDE_H
```

### StyleGuidePrivate.h
```
#ifndef STYLEGUIDEPRIVATE_H
#define STYLEGUIDEPRIVATE_H

class StyleGuidePrivate
{
public:
  StyleGuidePrivate();

  bool flag;
};

#endif // STYLEGUIDEPRIVATE_H
```

### StyleGuide.cpp
```
#include "StyleGuide.h"

StyleGuide::StyleGuide()
{
  
}

StyleGuide::StyleGuide(int value) :
  m_value(value),
  m(new StyleGuidePrivate())
{
  m->flag = true;
}

StyleGuide::~StyleGuide()
{
  delete m;
}
```

## Sonstiges
* portabler code - kein `#pragma once`
* keine Macros -> nur inline functions
* keine defines -> nur constanten, bzw. enums
* struct möglichst nicht verwenden
* kein typedef so lange es keinen zwingenden Grund gibt - `ViPICTURE` -> `ViPIXEL**`; `ViPIXEL` -> `ViUBYTE`; `ViUBYTE` -> `unsigned char` das führt nur zur Verwirrung - besser direkt `unsigned char**` -  Falls man Code wirklich portieren will, kann man diese stupiden Ersetzungen auch per Script machen (der Präcompiler macht nichst anderes!)
* auto nur bei begrenztem scope und wenn es wirklich Schreibarbeit erspart, z. B. bei Iteratoren
```
std::list<Foo> fooList;
for (auto it = fooList.begin(); it != fooList.end(); it++)
{
  // do something with it
}
```
* jede variablendefinition hat eine eigene Zeile. double meanValue; double median; double standardDeviation nicht double meanValue, median, standardDeviation - zusätzliche schreibarbeit kann durch Block-Editing verhindert werden
* kein Postfix Interface in Header-Dateinamen verwenden -> kann nämlich sein, dass irgendwann doch mal eine non-pure-virtual function hinzukommt und schon ist der Name des Headers falsch -> Headernamen kann man oft nicht im Nachhinein ändern. Weiterhin ist es für den Anwender egal, ob er gegen ein Interface oder eine konkrete Klasse programmiert
* Klassen, von denen abgeleitet wird, brauchen immer einen virtuellen Destruktor -> sonst drohen Speicherlecks!!!
* pImpl
  * Exportierte Klassen sollten immer einen pImpl haben. Die Membervarialbe heißt dann `m` Die ImplKlasse trägt das Suffix 'Private'
  * Member einer privaten p_impl Klasse bekommen kein Präfix
  * Instanz der pImpl Klasse hat einfach nur den Namen `m` wegen Symmetrie `m_directMember` und `m->indirectMember`

## Mögliche Vorlagen
* Qt Styleguide
* Google Styleguide