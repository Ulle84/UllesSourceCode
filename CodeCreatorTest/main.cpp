#include "MainWindow.h"
#include <QApplication>

#include <QDebug>

#include "Subject.h"
#include "Observer.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  SubjectI* s= new Subject();
  ObserverI* o1 = new Observer("A");
  ObserverI* o2 = new Observer("B");

  s->registerObserver(o1);
  s->registerObserver(o2);

  s->notifyObservers();
  s->unregisterObserver(o2);
  delete o2;

  s->notifyObservers();

  s->unregisterObserver(o1);
  delete o1;
  delete s;

  return a.exec();
}
