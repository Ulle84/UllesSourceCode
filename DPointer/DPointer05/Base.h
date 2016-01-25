#ifndef BASE_H
#define BASE_H

class BasePrivate;

class Base
{
public:
  Base();
  ~Base();

  Base(const Base& rhs);
  Base& operator=(const Base& rhs);

  int value() const;
  void setValue(int value);
  void printValue() const;

  void reset();

  void update();

protected:
  Base(BasePrivate& d);
  BasePrivate* d;
};

#endif // BASE_H
